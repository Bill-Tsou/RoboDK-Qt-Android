/********************************************************************************
** Form generated from reading UI file 'dialog_about.ui'
**
** Created by: Qt User Interface Compiler version 5.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_ABOUT_H
#define UI_DIALOG_ABOUT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_dialog_about
{
public:
    QPushButton *pushButton;
    QLabel *pic_logo;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;

    void setupUi(QDialog *dialog_about)
    {
        if (dialog_about->objectName().isEmpty())
            dialog_about->setObjectName(QStringLiteral("dialog_about"));
        dialog_about->resize(400, 412);
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\273\237\346\255\243\351\273\221\351\253\224"));
        font.setPointSize(15);
        dialog_about->setFont(font);
        pushButton = new QPushButton(dialog_about);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(290, 370, 101, 31));
        pic_logo = new QLabel(dialog_about);
        pic_logo->setObjectName(QStringLiteral("pic_logo"));
        pic_logo->setGeometry(QRect(70, 20, 250, 192));
        label = new QLabel(dialog_about);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(60, 290, 281, 31));
        label_2 = new QLabel(dialog_about);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(60, 250, 281, 31));
        label_3 = new QLabel(dialog_about);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(60, 330, 281, 31));
        label_4 = new QLabel(dialog_about);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(60, 210, 281, 31));
        label_4->setStyleSheet(QStringLiteral("color: rgb(0, 0, 0);"));
        label_4->setAlignment(Qt::AlignCenter);

        retranslateUi(dialog_about);

        QMetaObject::connectSlotsByName(dialog_about);
    } // setupUi

    void retranslateUi(QDialog *dialog_about)
    {
        dialog_about->setWindowTitle(QApplication::translate("dialog_about", "About us...", nullptr));
        pushButton->setText(QApplication::translate("dialog_about", "OK", nullptr));
        pic_logo->setText(QApplication::translate("dialog_about", "Logo", nullptr));
        label->setText(QApplication::translate("dialog_about", "Team Members: Raja, Bill, Zac", nullptr));
        label_2->setText(QApplication::translate("dialog_about", "Instructor: Prof. \345\274\265\346\226\207\344\270\255", nullptr));
        label_3->setText(QApplication::translate("dialog_about", "Updated Date: 2022/06/12", nullptr));
        label_4->setText(QApplication::translate("dialog_about", "NTUT ARAA Course", nullptr));
    } // retranslateUi

};

namespace Ui {
    class dialog_about: public Ui_dialog_about {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_ABOUT_H
