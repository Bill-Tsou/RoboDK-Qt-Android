#include "dialog_semi_mode.h"
#include "ui_dialog_semi_mode.h"

Dialog_Semi_Mode::Dialog_Semi_Mode(CUBES org_result, BOX_STATE *box_state, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_Semi_Mode)
{
    ui->setupUi(this);
    // save and display the color result on label
    this->org_color = org_result;

    switch(org_result)
    {
    case CUBE_RED:
        ui->label_color_result->setText("Red");
        ui->label_color_result->setStyleSheet("QLabel { color : rgb(237, 28, 36); }");
        break;
    case CUBE_GREEN:
        ui->label_color_result->setText("Green");
        ui->label_color_result->setStyleSheet("QLabel { color : rgb(34, 177, 76); }");
        break;
    case CUBE_BLUE:
        ui->label_color_result->setText("Blue");
        ui->label_color_result->setStyleSheet("QLabel { color : rgb(0, 6, 238); }");
        break;
    default:
        break;
    }

    // disable the button which the box has the cube
    if(box_state[BOX_RED] == BOX_STATE::HAS_CUBE)
        ui->btn_red->setDisabled(true);
    if(box_state[BOX_GREEN] == BOX_STATE::HAS_CUBE)
        ui->btn_green->setDisabled(true);
    if(box_state[BOX_BLUE] == BOX_STATE::HAS_CUBE)
        ui->btn_blue->setDisabled(true);
}

Dialog_Semi_Mode::~Dialog_Semi_Mode()
{
    delete ui;
}

void Dialog_Semi_Mode::on_btn_yes_clicked()
{
    emit signal_result(CubeToBox(org_color), org_color);
    this->close();
}

void Dialog_Semi_Mode::on_btn_red_clicked()
{
    emit signal_result(BOX_RED, org_color);
    this->close();
}

void Dialog_Semi_Mode::on_btn_green_clicked()
{
    emit signal_result(BOX_GREEN, org_color);
    this->close();
}

void Dialog_Semi_Mode::on_btn_blue_clicked()
{
    emit signal_result(BOX_BLUE, org_color);
    this->close();
}

void Dialog_Semi_Mode::on_Dialog_Semi_Mode_rejected()
{
    emit signal_result(MAX_BOXES, org_color);
    this->close();
}

void Dialog_Semi_Mode::on_btn_cancel_clicked()
{
    emit signal_result(MAX_BOXES, org_color);
    this->close();
}
