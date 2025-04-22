#ifndef DIALOG_SEMI_MODE_H
#define DIALOG_SEMI_MODE_H

#include <QDialog>
#include "FinalProjectTypes.h"

namespace Ui {
class Dialog_Semi_Mode;
}

class Dialog_Semi_Mode : public QDialog
{
    Q_OBJECT

public:

    explicit Dialog_Semi_Mode(CUBES org_result, BOX_STATE *box_state, QWidget *parent = nullptr);
    ~Dialog_Semi_Mode();

signals:
    void signal_result(BOXES res_color, CUBES org_color);

private slots:
    void on_btn_yes_clicked();
    void on_btn_cancel_clicked();

    void on_btn_red_clicked();
    void on_btn_green_clicked();
    void on_btn_blue_clicked();

    void on_Dialog_Semi_Mode_rejected();

private:
    Ui::Dialog_Semi_Mode *ui;

    CUBES org_color;
};

#endif // DIALOG_SEMI_MODE_H
