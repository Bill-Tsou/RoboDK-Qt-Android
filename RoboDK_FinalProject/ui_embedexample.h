/********************************************************************************
** Form generated from reading UI file 'embedexample.ui'
**
** Created by: Qt User Interface Compiler version 5.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EMBEDEXAMPLE_H
#define UI_EMBEDEXAMPLE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_EmbedExample
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton;
    QPushButton *pushButton_2;

    void setupUi(QWidget *EmbedExample)
    {
        if (EmbedExample->objectName().isEmpty())
            EmbedExample->setObjectName(QStringLiteral("EmbedExample"));
        EmbedExample->resize(460, 340);
        verticalLayout = new QVBoxLayout(EmbedExample);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label = new QLabel(EmbedExample);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout->addWidget(label);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        pushButton = new QPushButton(EmbedExample);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        horizontalLayout->addWidget(pushButton);

        pushButton_2 = new QPushButton(EmbedExample);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        horizontalLayout->addWidget(pushButton_2);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(EmbedExample);

        QMetaObject::connectSlotsByName(EmbedExample);
    } // setupUi

    void retranslateUi(QWidget *EmbedExample)
    {
        EmbedExample->setWindowTitle(QApplication::translate("EmbedExample", "Form", nullptr));
        label->setText(QApplication::translate("EmbedExample", "Example Embeded Window c++", nullptr));
        pushButton->setText(QApplication::translate("EmbedExample", "Cancel", nullptr));
        pushButton_2->setText(QApplication::translate("EmbedExample", "Ok", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EmbedExample: public Ui_EmbedExample {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EMBEDEXAMPLE_H
