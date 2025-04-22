#include "dialog_about.h"
#include "ui_dialog_about.h"

Dialog_About::Dialog_About(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dialog_about)
{
    ui->setupUi(this);

    QString picture_logo = "ntut.png";
    QImage image(picture_logo);
    ui->pic_logo->setPixmap(QPixmap::fromImage(image));
}

Dialog_About::~Dialog_About()
{ delete ui; }

void Dialog_About::on_dialog_about_rejected()
{ emit onClose(); }

void Dialog_About::on_pushButton_clicked()
{
    this->close();
    emit onClose();
}

