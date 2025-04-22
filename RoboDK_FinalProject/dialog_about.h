#ifndef DIALOG_ABOUT_H
#define DIALOG_ABOUT_H

#include <QDialog>

namespace Ui {
class dialog_about;
}

class Dialog_About : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_About(QWidget *parent = nullptr);
    ~Dialog_About();

signals:
    void onClose();

private slots:
    void on_dialog_about_rejected();

    void on_pushButton_clicked();

private:
    Ui::dialog_about *ui;
};

#endif // DIALOG_ABOUT_H
