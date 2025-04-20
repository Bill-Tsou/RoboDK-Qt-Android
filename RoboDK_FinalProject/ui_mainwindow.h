/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_11;
    QVBoxLayout *mainLayout;
    QHBoxLayout *horizontalLayout_7;
    QSpacerItem *horizontalSpacer_2;
    QVBoxLayout *verticalLayout_10;
    QVBoxLayout *verticalLayout_4;
    QPushButton *btnLoadFile;
    QPushButton *btnSelectRobot;
    QPushButton *btnMoveRobotHome;
    QPushButton *btnEmbed;
    QPushButton *btnTestButton;
    QPushButton *btnTestCamera;
    QSpacerItem *verticalSpacer_2;
    QGroupBox *groupBoxDisplayMode;
    QVBoxLayout *verticalLayout_5;
    QRadioButton *radShowRoboDK;
    QRadioButton *radHideRoboDK;
    QRadioButton *radIntegrateRoboDK;
    QVBoxLayout *verticalLayout_9;
    QHBoxLayout *horizontalLayout_8;
    QGroupBox *groupBoxSimMode;
    QVBoxLayout *verticalLayout_8;
    QRadioButton *radSimulation;
    QHBoxLayout *horizontalLayout_6;
    QRadioButton *radOfflineProgramming;
    QPushButton *btnMakeProgram;
    QRadioButton *radRunOnRobot;
    QSpacerItem *horizontalSpacer;
    QVBoxLayout *verticalLayout_7;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *btnGetPosition;
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QPushButton *btnMoveJoints;
    QLineEdit *txtJoints;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QPushButton *btnMovePose;
    QLineEdit *txtXYZWPR;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QLineEdit *txtProgName;
    QPushButton *btnProgRun;
    QPushButton *btn_snap_cam;
    QPushButton *btn_show_semi_ui;
    QSpacerItem *verticalSpacer;
    QVBoxLayout *verticalLayout_14;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_16;
    QLabel *label_tcp_server_ip;
    QLabel *label_tcp_status;
    QGroupBox *groupBox_3;
    QVBoxLayout *verticalLayout_13;
    QPushButton *btnResetCubes;
    QPushButton *btnPlaceCube;
    QGroupBox *groupBox_4;
    QVBoxLayout *verticalLayout_15;
    QRadioButton *radAutoMode;
    QRadioButton *radSemiMode;
    QPushButton *btnOpPlaceCube;
    QPushButton *btnOpUndo;
    QPushButton *btn_about;
    QSpacerItem *verticalSpacer_5;
    QVBoxLayout *verticalLayout_12;
    QGroupBox *groupBox_6;
    QVBoxLayout *verticalLayout_17;
    QPushButton *btnGripperHome;
    QPushButton *btnGripperWork;
    QSpacerItem *verticalSpacer_6;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_6;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_4;
    QDoubleSpinBox *spnStep;
    QGridLayout *gridLayout;
    QPushButton *btnTXn;
    QPushButton *btnTXp;
    QPushButton *btnTYn;
    QPushButton *btnTYp;
    QPushButton *btnTZn;
    QPushButton *btnTZp;
    QPushButton *btnRXn;
    QPushButton *btnRXp;
    QPushButton *btnRYn;
    QPushButton *btnRYp;
    QPushButton *btnRZn;
    QPushButton *btnRZp;
    QWidget *widgetRoboDK;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1246, 649);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout_11 = new QVBoxLayout(centralWidget);
        verticalLayout_11->setSpacing(6);
        verticalLayout_11->setContentsMargins(11, 11, 11, 11);
        verticalLayout_11->setObjectName(QStringLiteral("verticalLayout_11"));
        mainLayout = new QVBoxLayout();
        mainLayout->setSpacing(6);
        mainLayout->setObjectName(QStringLiteral("mainLayout"));
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        horizontalSpacer_2 = new QSpacerItem(20, 10, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_2);

        verticalLayout_10 = new QVBoxLayout();
        verticalLayout_10->setSpacing(6);
        verticalLayout_10->setObjectName(QStringLiteral("verticalLayout_10"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(2);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        btnLoadFile = new QPushButton(centralWidget);
        btnLoadFile->setObjectName(QStringLiteral("btnLoadFile"));

        verticalLayout_4->addWidget(btnLoadFile);

        btnSelectRobot = new QPushButton(centralWidget);
        btnSelectRobot->setObjectName(QStringLiteral("btnSelectRobot"));

        verticalLayout_4->addWidget(btnSelectRobot);

        btnMoveRobotHome = new QPushButton(centralWidget);
        btnMoveRobotHome->setObjectName(QStringLiteral("btnMoveRobotHome"));

        verticalLayout_4->addWidget(btnMoveRobotHome);

        btnEmbed = new QPushButton(centralWidget);
        btnEmbed->setObjectName(QStringLiteral("btnEmbed"));

        verticalLayout_4->addWidget(btnEmbed);

        btnTestButton = new QPushButton(centralWidget);
        btnTestButton->setObjectName(QStringLiteral("btnTestButton"));

        verticalLayout_4->addWidget(btnTestButton);

        btnTestCamera = new QPushButton(centralWidget);
        btnTestCamera->setObjectName(QStringLiteral("btnTestCamera"));

        verticalLayout_4->addWidget(btnTestCamera);


        verticalLayout_10->addLayout(verticalLayout_4);

        verticalSpacer_2 = new QSpacerItem(20, 2, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_10->addItem(verticalSpacer_2);

        groupBoxDisplayMode = new QGroupBox(centralWidget);
        groupBoxDisplayMode->setObjectName(QStringLiteral("groupBoxDisplayMode"));
        groupBoxDisplayMode->setEnabled(true);
        verticalLayout_5 = new QVBoxLayout(groupBoxDisplayMode);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        radShowRoboDK = new QRadioButton(groupBoxDisplayMode);
        radShowRoboDK->setObjectName(QStringLiteral("radShowRoboDK"));
        radShowRoboDK->setChecked(true);

        verticalLayout_5->addWidget(radShowRoboDK);

        radHideRoboDK = new QRadioButton(groupBoxDisplayMode);
        radHideRoboDK->setObjectName(QStringLiteral("radHideRoboDK"));

        verticalLayout_5->addWidget(radHideRoboDK);

        radIntegrateRoboDK = new QRadioButton(groupBoxDisplayMode);
        radIntegrateRoboDK->setObjectName(QStringLiteral("radIntegrateRoboDK"));

        verticalLayout_5->addWidget(radIntegrateRoboDK);


        verticalLayout_10->addWidget(groupBoxDisplayMode);


        horizontalLayout_7->addLayout(verticalLayout_10);

        verticalLayout_9 = new QVBoxLayout();
        verticalLayout_9->setSpacing(6);
        verticalLayout_9->setObjectName(QStringLiteral("verticalLayout_9"));
        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        groupBoxSimMode = new QGroupBox(centralWidget);
        groupBoxSimMode->setObjectName(QStringLiteral("groupBoxSimMode"));
        verticalLayout_8 = new QVBoxLayout(groupBoxSimMode);
        verticalLayout_8->setSpacing(6);
        verticalLayout_8->setContentsMargins(11, 11, 11, 11);
        verticalLayout_8->setObjectName(QStringLiteral("verticalLayout_8"));
        radSimulation = new QRadioButton(groupBoxSimMode);
        radSimulation->setObjectName(QStringLiteral("radSimulation"));
        radSimulation->setChecked(true);

        verticalLayout_8->addWidget(radSimulation);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        radOfflineProgramming = new QRadioButton(groupBoxSimMode);
        radOfflineProgramming->setObjectName(QStringLiteral("radOfflineProgramming"));

        horizontalLayout_6->addWidget(radOfflineProgramming);

        btnMakeProgram = new QPushButton(groupBoxSimMode);
        btnMakeProgram->setObjectName(QStringLiteral("btnMakeProgram"));

        horizontalLayout_6->addWidget(btnMakeProgram);


        verticalLayout_8->addLayout(horizontalLayout_6);

        radRunOnRobot = new QRadioButton(groupBoxSimMode);
        radRunOnRobot->setObjectName(QStringLiteral("radRunOnRobot"));

        verticalLayout_8->addWidget(radRunOnRobot);


        horizontalLayout_8->addWidget(groupBoxSimMode);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer);


        verticalLayout_9->addLayout(horizontalLayout_8);

        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        btnGetPosition = new QPushButton(centralWidget);
        btnGetPosition->setObjectName(QStringLiteral("btnGetPosition"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::MinimumExpanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(btnGetPosition->sizePolicy().hasHeightForWidth());
        btnGetPosition->setSizePolicy(sizePolicy);

        horizontalLayout_5->addWidget(btnGetPosition);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        btnMoveJoints = new QPushButton(centralWidget);
        btnMoveJoints->setObjectName(QStringLiteral("btnMoveJoints"));

        horizontalLayout->addWidget(btnMoveJoints);


        verticalLayout->addLayout(horizontalLayout);

        txtJoints = new QLineEdit(centralWidget);
        txtJoints->setObjectName(QStringLiteral("txtJoints"));

        verticalLayout->addWidget(txtJoints);


        verticalLayout_3->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_2->addWidget(label_2);

        btnMovePose = new QPushButton(centralWidget);
        btnMovePose->setObjectName(QStringLiteral("btnMovePose"));

        horizontalLayout_2->addWidget(btnMovePose);


        verticalLayout_2->addLayout(horizontalLayout_2);

        txtXYZWPR = new QLineEdit(centralWidget);
        txtXYZWPR->setObjectName(QStringLiteral("txtXYZWPR"));

        verticalLayout_2->addWidget(txtXYZWPR);


        verticalLayout_3->addLayout(verticalLayout_2);


        horizontalLayout_5->addLayout(verticalLayout_3);


        verticalLayout_7->addLayout(horizontalLayout_5);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_3->addWidget(label_3);

        txtProgName = new QLineEdit(centralWidget);
        txtProgName->setObjectName(QStringLiteral("txtProgName"));

        horizontalLayout_3->addWidget(txtProgName);

        btnProgRun = new QPushButton(centralWidget);
        btnProgRun->setObjectName(QStringLiteral("btnProgRun"));

        horizontalLayout_3->addWidget(btnProgRun);


        verticalLayout_7->addLayout(horizontalLayout_3);


        verticalLayout_9->addLayout(verticalLayout_7);

        btn_snap_cam = new QPushButton(centralWidget);
        btn_snap_cam->setObjectName(QStringLiteral("btn_snap_cam"));

        verticalLayout_9->addWidget(btn_snap_cam);

        btn_show_semi_ui = new QPushButton(centralWidget);
        btn_show_semi_ui->setObjectName(QStringLiteral("btn_show_semi_ui"));

        verticalLayout_9->addWidget(btn_show_semi_ui);

        verticalSpacer = new QSpacerItem(20, 2, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_9->addItem(verticalSpacer);


        horizontalLayout_7->addLayout(verticalLayout_9);

        verticalLayout_14 = new QVBoxLayout();
        verticalLayout_14->setSpacing(6);
        verticalLayout_14->setObjectName(QStringLiteral("verticalLayout_14"));
        groupBox_2 = new QGroupBox(centralWidget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        verticalLayout_16 = new QVBoxLayout(groupBox_2);
        verticalLayout_16->setSpacing(6);
        verticalLayout_16->setContentsMargins(11, 11, 11, 11);
        verticalLayout_16->setObjectName(QStringLiteral("verticalLayout_16"));

        label_tcp_server_ip = new QLabel(groupBox_2);
        label_tcp_server_ip->setObjectName(QStringLiteral("label_tcp_server_ip"));
        label_tcp_server_ip->setAlignment(Qt::AlignCenter);
        verticalLayout_16->addWidget(label_tcp_server_ip);

        label_tcp_status = new QLabel(groupBox_2);
        label_tcp_status->setObjectName(QStringLiteral("label_tcp_status"));
        QFont font;
        font.setPointSize(12);
        font.setBold(true);
        label_tcp_status->setFont(font);
        label_tcp_status->setAlignment(Qt::AlignCenter);

        verticalLayout_16->addWidget(label_tcp_status);


        verticalLayout_14->addWidget(groupBox_2);

        groupBox_3 = new QGroupBox(centralWidget);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(groupBox_3->sizePolicy().hasHeightForWidth());
        groupBox_3->setSizePolicy(sizePolicy1);
        groupBox_3->setMinimumSize(QSize(0, 0));
        groupBox_3->setCheckable(false);
        verticalLayout_13 = new QVBoxLayout(groupBox_3);
        verticalLayout_13->setSpacing(6);
        verticalLayout_13->setContentsMargins(11, 11, 11, 11);
        verticalLayout_13->setObjectName(QStringLiteral("verticalLayout_13"));
        btnResetCubes = new QPushButton(groupBox_3);
        btnResetCubes->setObjectName(QStringLiteral("btnResetCubes"));

        verticalLayout_13->addWidget(btnResetCubes);

        btnPlaceCube = new QPushButton(groupBox_3);
        btnPlaceCube->setObjectName(QStringLiteral("btnPlaceCube"));

        verticalLayout_13->addWidget(btnPlaceCube);


        verticalLayout_14->addWidget(groupBox_3);

        groupBox_4 = new QGroupBox(centralWidget);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        verticalLayout_15 = new QVBoxLayout(groupBox_4);
        verticalLayout_15->setSpacing(6);
        verticalLayout_15->setContentsMargins(11, 11, 11, 11);
        verticalLayout_15->setObjectName(QStringLiteral("verticalLayout_15"));
        radAutoMode = new QRadioButton(groupBox_4);
        radAutoMode->setObjectName(QStringLiteral("radAutoMode"));
        radAutoMode->setChecked(true);

        verticalLayout_15->addWidget(radAutoMode);

        radSemiMode = new QRadioButton(groupBox_4);
        radSemiMode->setObjectName(QStringLiteral("radSemiMode"));

        verticalLayout_15->addWidget(radSemiMode);

        btnOpPlaceCube = new QPushButton(groupBox_4);
        btnOpPlaceCube->setObjectName(QStringLiteral("btnOpPlaceCube"));

        verticalLayout_15->addWidget(btnOpPlaceCube);

        btnOpUndo = new QPushButton(groupBox_4);
        btnOpUndo->setObjectName(QStringLiteral("btnOpUndo"));
        btnOpUndo->setCheckable(false);
        btnOpUndo->setChecked(false);

        verticalLayout_15->addWidget(btnOpUndo);


        verticalLayout_14->addWidget(groupBox_4);

        btn_about = new QPushButton(centralWidget);
        btn_about->setObjectName(QStringLiteral("btn_about"));

        verticalLayout_14->addWidget(btn_about);

        verticalSpacer_5 = new QSpacerItem(20, 2, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_14->addItem(verticalSpacer_5);


        horizontalLayout_7->addLayout(verticalLayout_14);

        verticalLayout_12 = new QVBoxLayout();
        verticalLayout_12->setSpacing(6);
        verticalLayout_12->setObjectName(QStringLiteral("verticalLayout_12"));
        groupBox_6 = new QGroupBox(centralWidget);
        groupBox_6->setObjectName(QStringLiteral("groupBox_6"));
        verticalLayout_17 = new QVBoxLayout(groupBox_6);
        verticalLayout_17->setSpacing(6);
        verticalLayout_17->setContentsMargins(11, 11, 11, 11);
        verticalLayout_17->setObjectName(QStringLiteral("verticalLayout_17"));
        btnGripperHome = new QPushButton(groupBox_6);
        btnGripperHome->setObjectName(QStringLiteral("btnGripperHome"));

        verticalLayout_17->addWidget(btnGripperHome);

        btnGripperWork = new QPushButton(groupBox_6);
        btnGripperWork->setObjectName(QStringLiteral("btnGripperWork"));

        verticalLayout_17->addWidget(btnGripperWork);


        verticalLayout_12->addWidget(groupBox_6);

        verticalSpacer_6 = new QSpacerItem(20, 2, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_12->addItem(verticalSpacer_6);

        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        verticalLayout_6 = new QVBoxLayout(groupBox);
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout_4->addWidget(label_4);

        spnStep = new QDoubleSpinBox(groupBox);
        spnStep->setObjectName(QStringLiteral("spnStep"));
        spnStep->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        spnStep->setDecimals(1);
        spnStep->setMaximum(1000);
        spnStep->setValue(50);

        horizontalLayout_4->addWidget(spnStep);


        verticalLayout_6->addLayout(horizontalLayout_4);

        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        btnTXn = new QPushButton(groupBox);
        btnTXn->setObjectName(QStringLiteral("btnTXn"));

        gridLayout->addWidget(btnTXn, 0, 0, 1, 1);

        btnTXp = new QPushButton(groupBox);
        btnTXp->setObjectName(QStringLiteral("btnTXp"));

        gridLayout->addWidget(btnTXp, 0, 1, 1, 1);

        btnTYn = new QPushButton(groupBox);
        btnTYn->setObjectName(QStringLiteral("btnTYn"));

        gridLayout->addWidget(btnTYn, 1, 0, 1, 1);

        btnTYp = new QPushButton(groupBox);
        btnTYp->setObjectName(QStringLiteral("btnTYp"));

        gridLayout->addWidget(btnTYp, 1, 1, 1, 1);

        btnTZn = new QPushButton(groupBox);
        btnTZn->setObjectName(QStringLiteral("btnTZn"));

        gridLayout->addWidget(btnTZn, 2, 0, 1, 1);

        btnTZp = new QPushButton(groupBox);
        btnTZp->setObjectName(QStringLiteral("btnTZp"));

        gridLayout->addWidget(btnTZp, 2, 1, 1, 1);

        btnRXn = new QPushButton(groupBox);
        btnRXn->setObjectName(QStringLiteral("btnRXn"));

        gridLayout->addWidget(btnRXn, 3, 0, 1, 1);

        btnRXp = new QPushButton(groupBox);
        btnRXp->setObjectName(QStringLiteral("btnRXp"));

        gridLayout->addWidget(btnRXp, 3, 1, 1, 1);

        btnRYn = new QPushButton(groupBox);
        btnRYn->setObjectName(QStringLiteral("btnRYn"));

        gridLayout->addWidget(btnRYn, 4, 0, 1, 1);

        btnRYp = new QPushButton(groupBox);
        btnRYp->setObjectName(QStringLiteral("btnRYp"));

        gridLayout->addWidget(btnRYp, 4, 1, 1, 1);

        btnRZn = new QPushButton(groupBox);
        btnRZn->setObjectName(QStringLiteral("btnRZn"));

        gridLayout->addWidget(btnRZn, 5, 0, 1, 1);

        btnRZp = new QPushButton(groupBox);
        btnRZp->setObjectName(QStringLiteral("btnRZp"));

        gridLayout->addWidget(btnRZp, 5, 1, 1, 1);


        verticalLayout_6->addLayout(gridLayout);


        verticalLayout_12->addWidget(groupBox);


        horizontalLayout_7->addLayout(verticalLayout_12);


        mainLayout->addLayout(horizontalLayout_7);

        widgetRoboDK = new QWidget(centralWidget);
        widgetRoboDK->setObjectName(QStringLiteral("widgetRoboDK"));
        QSizePolicy sizePolicy2(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(100);
        sizePolicy2.setHeightForWidth(widgetRoboDK->sizePolicy().hasHeightForWidth());
        widgetRoboDK->setSizePolicy(sizePolicy2);
        widgetRoboDK->setMinimumSize(QSize(0, 150));

        mainLayout->addWidget(widgetRoboDK);


        verticalLayout_11->addLayout(mainLayout);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1246, 21));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "RoboDK Color Distinguish", nullptr));
        btnLoadFile->setText(QApplication::translate("MainWindow", "Load File", nullptr));
        btnSelectRobot->setText(QApplication::translate("MainWindow", "Select Robot", nullptr));
        btnMoveRobotHome->setText(QApplication::translate("MainWindow", "Move Robot Home", nullptr));
        btnEmbed->setText(QApplication::translate("MainWindow", "Embed window", nullptr));
        btnTestButton->setText(QApplication::translate("MainWindow", "Test Event Loop", nullptr));
        btnTestCamera->setText(QApplication::translate("MainWindow", "Test Camera", nullptr));
        groupBoxDisplayMode->setTitle(QApplication::translate("MainWindow", "Display Mode", nullptr));
        radShowRoboDK->setText(QApplication::translate("MainWindow", "Show RoboDK", nullptr));
        radHideRoboDK->setText(QApplication::translate("MainWindow", "Hide RoboDK", nullptr));
        radIntegrateRoboDK->setText(QApplication::translate("MainWindow", "Integrate RoboDK Window", nullptr));
        groupBoxSimMode->setTitle(QApplication::translate("MainWindow", "Simulation Mode", nullptr));
        radSimulation->setText(QApplication::translate("MainWindow", "Simulation", nullptr));
        radOfflineProgramming->setText(QApplication::translate("MainWindow", "Offline Programming", nullptr));
        btnMakeProgram->setText(QApplication::translate("MainWindow", "Make Program", nullptr));
        radRunOnRobot->setText(QApplication::translate("MainWindow", "Run On Robot", nullptr));
        btnGetPosition->setText(QApplication::translate("MainWindow", "Retrieve\n"
"Current\n"
"Position", nullptr));
        label->setText(QApplication::translate("MainWindow", "Joint Values", nullptr));
        btnMoveJoints->setText(QApplication::translate("MainWindow", "Move to Joints", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "Cartesian Position", nullptr));
        btnMovePose->setText(QApplication::translate("MainWindow", "Move to Position", nullptr));
        label_3->setText(QApplication::translate("MainWindow", "Program Name:", nullptr));
        txtProgName->setText(QApplication::translate("MainWindow", "TestProgram", nullptr));
        btnProgRun->setText(QApplication::translate("MainWindow", "Run Program", nullptr));
        btn_snap_cam->setText(QApplication::translate("MainWindow", "Take Snapshot of Camera", nullptr));
        btn_show_semi_ui->setText(QApplication::translate("MainWindow", "Show Semi-Auto UI", nullptr));
        groupBox_2->setTitle(QApplication::translate("MainWindow", "TCP Connection", nullptr));
        label_tcp_server_ip->setText(QApplication::translate("MainWindow", "Server IP: (None)", nullptr));
        label_tcp_status->setText(QApplication::translate("MainWindow", "Unconnected", nullptr));
        groupBox_3->setTitle(QApplication::translate("MainWindow", "Cube Placement", nullptr));
        btnResetCubes->setText(QApplication::translate("MainWindow", "Reset Cubes", nullptr));
        btnPlaceCube->setText(QApplication::translate("MainWindow", "Random Place", nullptr));
        groupBox_4->setTitle(QApplication::translate("MainWindow", "Operations", nullptr));
        radAutoMode->setText(QApplication::translate("MainWindow", "Autonomous", nullptr));
        radSemiMode->setText(QApplication::translate("MainWindow", "Semi-Autonomous", nullptr));
        btnOpPlaceCube->setText(QApplication::translate("MainWindow", "Place", nullptr));
        btnOpUndo->setText(QApplication::translate("MainWindow", "Undo", nullptr));
        btn_about->setText(QApplication::translate("MainWindow", "About Us", nullptr));
        groupBox_6->setTitle(QApplication::translate("MainWindow", "Sucker Position", nullptr));
        btnGripperHome->setText(QApplication::translate("MainWindow", "Home", nullptr));
        btnGripperWork->setText(QApplication::translate("MainWindow", "Work Space", nullptr));
        groupBox->setTitle(QApplication::translate("MainWindow", "Incremental Move", nullptr));
        label_4->setText(QApplication::translate("MainWindow", "Step (mm or deg)", nullptr));
        btnTXn->setText(QApplication::translate("MainWindow", "Tx-", nullptr));
        btnTXp->setText(QApplication::translate("MainWindow", "Tx+", nullptr));
        btnTYn->setText(QApplication::translate("MainWindow", "Ty-", nullptr));
        btnTYp->setText(QApplication::translate("MainWindow", "Ty+", nullptr));
        btnTZn->setText(QApplication::translate("MainWindow", "Tz-", nullptr));
        btnTZp->setText(QApplication::translate("MainWindow", "Tz+", nullptr));
        btnRXn->setText(QApplication::translate("MainWindow", "Rx-", nullptr));
        btnRXp->setText(QApplication::translate("MainWindow", "Rx+", nullptr));
        btnRYn->setText(QApplication::translate("MainWindow", "Ry-", nullptr));
        btnRYp->setText(QApplication::translate("MainWindow", "Ry+", nullptr));
        btnRZn->setText(QApplication::translate("MainWindow", "Rz-", nullptr));
        btnRZp->setText(QApplication::translate("MainWindow", "Rz+", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
