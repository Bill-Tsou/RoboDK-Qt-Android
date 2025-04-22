#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QObject>
#include <QDebug>
#include <QtNetwork>

class TcpServer : public QObject
{
    Q_OBJECT
public:
    explicit TcpServer(int portNumber, QObject *parent = nullptr);
    ~TcpServer();

    void WriteSocket(QString msg);

signals:
    void ClientConnected(bool isConnected);
    void DataReceived(QString msg);
    void ClientDisconnected();

public slots:
    void newConnection();
    void ReadytoRead();
    void Disconnected();

private:
    QTcpServer *server;
    QTcpSocket *socket;
    void RespondSocket(QString msg);

    QString buffer;
};

#endif // MYSERVER_H
