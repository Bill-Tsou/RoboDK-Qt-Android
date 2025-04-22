#include "TcpServer.h"

TcpServer::TcpServer(int portNumber, QObject *parent) : QObject(parent)
{
    socket = nullptr;
    server = new QTcpServer(this);
    connect(server, SIGNAL(newConnection()), this, SLOT(newConnection()));

    if(!server->listen(QHostAddress::Any, portNumber))
    {
        qDebug() << "Server could not start!";
        return;
    }
    else
    {
        qDebug() << "Server started";
    }
}

TcpServer::~TcpServer()
{
    if(socket != nullptr)
        socket->close();
}

void TcpServer::WriteSocket(QString msg)
{
    if(server == nullptr)
        return;

    msg += "\r\n";
    socket->write(msg.toLocal8Bit());
    socket->waitForBytesWritten(1);
}

void TcpServer::newConnection()
{
    if(socket != nullptr)
    {
        qDebug() << "Already connected!";
        return;
    }

    socket = server->nextPendingConnection();
    connect(socket, SIGNAL(readyRead()), SLOT(ReadytoRead()));
    connect(socket, SIGNAL(disconnected()), SLOT(Disconnected()));

    if(socket->isOpen() == false)
    {
        emit ClientConnected(false);
        return;
    }

    qDebug() << "Socket is open!";
    socket->waitForConnected();

    emit ClientConnected(true);
}

void TcpServer::ReadytoRead()
{
    if(socket == nullptr)
    {
        qDebug() << "socket closed while reading!";
        return;
    }

    buffer = "";
    while(true)
    {
        // read the messages from socket
        //socket->waitForReadyRead(1);

        qint64 len = socket->bytesAvailable();
        qDebug() << "socket data length: " << len;
        QByteArray alldata = socket->read(len);

        /*QTextCodec *utf8codec = QTextCodec::codecForName("UTF-8");
        QString utf8str = utf8codec->toUnicode(alldata.mid(2));
        qDebug() << "hex: [" << alldata.toHex().toUpper() << "]";
        qDebug() << "utf-8: [" << utf8str << "]";

        if(utf8str.contains("\r\n"))
        {
            buffer += utf8str.remove(utf8str.indexOf("\r\n"), 2);
            break;
        }
        buffer += utf8str;*/

        QString msg = QString(alldata);
        if(msg.contains("\r\n"))
        {
            buffer += msg.remove(msg.indexOf("\r\n"), 2);
            break;
        }
        buffer += msg;
    }

    emit DataReceived(buffer);
}

void TcpServer::Disconnected()
{
    socket->close();
    qDebug() << "Socket closed!";
    socket = nullptr;

    emit ClientDisconnected();
}

void TcpServer::RespondSocket(QString msg)
{
    msg += "\r\n";
    socket->write(msg.toLocal8Bit());
    socket->waitForBytesWritten(1);
}
