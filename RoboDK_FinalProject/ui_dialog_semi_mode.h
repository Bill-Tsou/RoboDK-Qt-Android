/********************************************************************************
** Form generated from reading UI file 'dialog_semi_mode.ui'
**
** Created by: Qt User Interface Compiler version 5.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_SEMI_MODE_H
#define UI_DIALOG_SEMI_MODE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_Dialog_Semi_Mode
{
public:
    QLabel *label;
    QLabel *label_color_result;
    QLabel *label_2;
    QPushButton *btn_yes;
    QPushButton *btn_cancel;
    QLabel *label_3;
    QPushButton *btn_red;
    QPushButton *btn_green;
    QPushButton *btn_blue;

    void setupUi(QDialog *Dialog_Semi_Mode)
    {
        if (Dialog_Semi_Mode->objectName().isEmpty())
            Dialog_Semi_Mode->setObjectName(QStringLiteral("Dialog_Semi_Mode"));
        Dialog_Semi_Mode->resize(279, 203);
        Dialog_Semi_Mode->setMinimumSize(QSize(279, 203));
        Dialog_Semi_Mode->setMaximumSize(QSize(279, 203));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\273\237\346\255\243\351\273\221\351\253\224"));
        font.setPointSize(10);
        Dialog_Semi_Mode->setFont(font);
        label = new QLabel(Dialog_Semi_Mode);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 20, 171, 16));
        label_color_result = new QLabel(Dialog_Semi_Mode);
        label_color_result->setObjectName(QStringLiteral("label_color_result"));
        label_color_result->setGeometry(QRect(200, 20, 51, 16));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\276\256\350\273\237\346\255\243\351\273\221\351\253\224"));
        font1.setPointSize(12);
        font1.setBold(true);
        label_color_result->setFont(font1);
        label_2 = new QLabel(Dialog_Semi_Mode);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(60, 50, 161, 16));
        btn_yes = new QPushButton(Dialog_Semi_Mode);
        btn_yes->setObjectName(QStringLiteral("btn_yes"));
        btn_yes->setGeometry(QRect(55, 80, 80, 24));
        btn_cancel = new QPushButton(Dialog_Semi_Mode);
        btn_cancel->setObjectName(QStringLiteral("btn_cancel"));
        btn_cancel->setGeometry(QRect(145, 80, 80, 24));
        label_3 = new QLabel(Dialog_Semi_Mode);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(84, 130, 111, 16));
        btn_red = new QPushButton(Dialog_Semi_Mode);
        btn_red->setObjectName(QStringLiteral("btn_red"));
        btn_red->setGeometry(QRect(10, 160, 80, 24));
        btn_green = new QPushButton(Dialog_Semi_Mode);
        btn_green->setObjectName(QStringLiteral("btn_green"));
        btn_green->setGeometry(QRect(100, 160, 80, 24));
        btn_blue = new QPushButton(Dialog_Semi_Mode);
        btn_blue->setObjectName(QStringLiteral("btn_blue"));
        btn_blue->setGeometry(QRect(190, 160, 80, 24));

        retranslateUi(Dialog_Semi_Mode);

        QMetaObject::connectSlotsByName(Dialog_Semi_Mode);
    } // setupUi

    void retranslateUi(QDialog *Dialog_Semi_Mode)
    {
        Dialog_Semi_Mode->setWindowTitle(QApplication::translate("Dialog_Semi_Mode", "Semi-Auto Mode Confirm", nullptr));
        label->setText(QApplication::translate("Dialog_Semi_Mode", "Distinguished Cube Color: ", nullptr));
        label_color_result->setText(QApplication::translate("Dialog_Semi_Mode", "Red", nullptr));
        label_2->setText(QApplication::translate("Dialog_Semi_Mode", "Do you want to continue?", nullptr));
        btn_yes->setText(QApplication::translate("Dialog_Semi_Mode", "Yes", nullptr));
        btn_cancel->setText(QApplication::translate("Dialog_Semi_Mode", "Cancel", nullptr));
        label_3->setText(QApplication::translate("Dialog_Semi_Mode", "Other operations:", nullptr));
        btn_red->setText(QApplication::translate("Dialog_Semi_Mode", "Place Red", nullptr));
        btn_green->setText(QApplication::translate("Dialog_Semi_Mode", "Place Green", nullptr));
        btn_blue->setText(QApplication::translate("Dialog_Semi_Mode", "Place Blue", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog_Semi_Mode: public Ui_Dialog_Semi_Mode {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_SEMI_MODE_H
