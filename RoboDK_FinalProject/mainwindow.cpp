#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "embedexample.h"

#include <QFileDialog>
#include <QWindow>
#include <QScreen>
#include <QtConcurrent/QtConcurrent>

#ifdef WIN32
// this is used to integrate RoboDK window as a child window
#include <windows.h>
#pragma comment(lib,"user32.lib")
#endif

//#include <thread>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    opencv_process = nullptr;

    // initialize dialog
    dialog_semi = nullptr;
    dialog_about = nullptr;

    robodk_window = NULL;
    ui->setupUi(this);
    ui->widgetRoboDK->hide();
    adjustSize();

    // start RoboDK program
//    system("start RoboDK.lnk");
//    Sleep(100);

    // Start RoboDK API here (RoboDK will start if it is not running)
    ROBOT = NULL;

    while (true){
        RDK = new RoboDK();
        if(RDK->Connected())
            break;
        delete RDK;
        qDebug() << "Failed to start RoboDK API!!";
        Sleep(100);
    }

    // retrieve and display TCP server IP address
    const QHostAddress &localhost = QHostAddress(QHostAddress::LocalHost);
    for (const QHostAddress &address: QNetworkInterface::allAddresses()) {
        if (address.protocol() == QAbstractSocket::IPv4Protocol && address != localhost)
             ui->label_tcp_server_ip->setText("Server IP: " + address.toString());
    }

    // initialize TCP Server
    server = new TcpServer(1234, this);
    connect(server, &TcpServer::ClientConnected, this, &MainWindow::client_connected);
    connect(server, &TcpServer::DataReceived, this, &MainWindow::receive_message);
    connect(server, &TcpServer::ClientDisconnected, this, &MainWindow::client_disconnected);
}

void MainWindow::Initialize_Window(QString robot_path, QString cam_buf_path, bool debug_mode)
{
    // make RoboDK inside main window
    on_radIntegrateRoboDK_clicked();
    // maximize the window
    this->setWindowState(Qt::WindowMaximized);

    // hide the controls in demo mode
    ui->verticalLayout_9->setEnabled(debug_mode);
    ui->verticalLayout_10->setEnabled(debug_mode);
    ui->btnLoadFile->setVisible(debug_mode);
    ui->btnSelectRobot->setVisible(debug_mode);
    ui->btnMoveRobotHome->setVisible(debug_mode);
    ui->btnEmbed->setVisible(debug_mode);
    ui->btnTestButton->setVisible(debug_mode);
    ui->btnTestCamera->setVisible(debug_mode);
    ui->groupBoxDisplayMode->setVisible(debug_mode);
    ui->groupBoxSimMode->setVisible(debug_mode);
    ui->btnGetPosition->setVisible(debug_mode);
    ui->label->setVisible(debug_mode);
    ui->label_2->setVisible(debug_mode);
    ui->btnMoveJoints->setVisible(debug_mode);
    ui->btnMovePose->setVisible(debug_mode);
    ui->txtJoints->setVisible(debug_mode);
    ui->txtXYZWPR->setVisible(debug_mode);
    ui->label_3->setVisible(debug_mode);
    ui->txtProgName->setVisible(debug_mode);
    ui->btnProgRun->setVisible(debug_mode);
    ui->btn_snap_cam->setVisible(debug_mode);
    ui->btn_show_semi_ui->setVisible(debug_mode);
    // disble undo button
    ui->btnOpPlaceCube->setDisabled(true);
    ui->btnOpUndo->setDisabled(true);

    // load robot and program from file
    RDK->AddFile(robot_path);

    // select robot
    Select_Robot();

    // initialize items in the program
    initialize_cubes();

    // reset cubes
    on_btnResetCubes_clicked();

    // initialize camera
    Item obj_cam = RDK->getItem("Camera", RDK->ITEM_TYPE_ANY);
    camera = RDK->Cam2D_Add(obj_cam, "FOCAL_LENGHT=1 FOV=46.55 FAR_LENGHT=1000 SIZE=470x352 SNAPSHOT=1920x1080 NO_TASKBAR BG_COLOR=black");
    cam_buffer_path = cam_buf_path;
}

MainWindow::~MainWindow() {
    robodk_window_clear();
    RDK->CloseRoboDK();
    if(opencv_process != nullptr)
        opencv_process->close();

    delete ui;
    delete RDK;
}

bool MainWindow::Check_RoboDK(){
    if (RDK == NULL){
        statusBar()->showMessage("RoboDK API is not connected");
        return false;
    }
    if (!RDK->Connected()){
        statusBar()->showMessage("RoboDK is not running");
        return false;
    }
    return true;
}

bool MainWindow::Check_Robot(){
    if (!Check_RoboDK()){ return false; }

    if (ROBOT == NULL){
        statusBar()->showMessage("Select a robot first");
        return false;
    }
    if (!ROBOT->Valid()){
        statusBar()->showMessage("Robot item is not valid");
        return false;
    }
    return true;
}

void MainWindow::Select_Robot(){
    if (ROBOT != NULL){
        delete ROBOT;
        ROBOT = NULL;
    }
    ROBOT = new Item(RDK->ItemUserPick("Select a robot", RoboDK::ITEM_TYPE_ROBOT));
    //ROBOT = new Item(RDK->getItem("UR10", RoboDK::ITEM_TYPE_ROBOT));
    if (Check_Robot()){
        statusBar()->showMessage("Robot selected: " + ROBOT->Name());
    }
}

void MainWindow::client_connected(bool isConnected)
{
    if(isConnected)
    {
        ui->label_tcp_status->setText("Connected");
        // reset RoboDK objects
        on_btnResetCubes_clicked();
        // choose Auto operation mode
        ui->radAutoMode->setChecked(true);
        ui->radSemiMode->setChecked(false);
    }
    else
        ui->label_tcp_status->setText("Cannot Connect");
}

void MainWindow::receive_message(QString msg)
{
    //ui->label_msg->setText(msg);
    // process messages from client
    if(msg == "CUBE_RESET")
    {
        server->WriteSocket("OK");
        on_btnResetCubes_clicked();
    }
    else if(msg == "CUBE_RAND_PLACE")
    {
        server->WriteSocket("OK");
        on_btnPlaceCube_clicked();
    }
    else if(msg == "MODE_AUTO")
    {
        ui->radAutoMode->setChecked(true);
        ui->radSemiMode->setChecked(false);
    }
    else if(msg == "MODE_SEMI_AUTO")
    {
        ui->radAutoMode->setChecked(false);
        ui->radSemiMode->setChecked(true);
    }
    else if(msg == "OP_PLACE")
    {
        on_btnOpPlaceCube_clicked();
        // in auto mode
        if(ui->radAutoMode->isChecked())
            server->WriteSocket("OK");
        else
        {   // in semi mode should return the color result
            switch(disting_color_result)
            {
            case CUBE_RED:
                server->WriteSocket("Red");
            break;
            case CUBE_GREEN:
                server->WriteSocket("Green");
            break;
            case CUBE_BLUE:
                server->WriteSocket("Blue");
            break;
            }
        }
    }
    else if(msg == "OP_UNDO")
    {
        server->WriteSocket("OK");
        on_btnOpUndo_clicked();
    }
    else if(msg == "POS_HOME")
        on_btnGripperHome_clicked();
    else if(msg == "POS_WORK")
        on_btnGripperWork_clicked();
    else if(msg == "INC_TX_MINUS")
        on_btnTXn_clicked();
    else if(msg == "INC_TX_PLUS")
        on_btnTXp_clicked();
    else if(msg == "INC_TY_MINUS")
        on_btnTYn_clicked();
    else if(msg == "INC_TY_PLUS")
        on_btnTYp_clicked();
    else if(msg == "INC_TZ_MINUS")
        on_btnTZn_clicked();
    else if(msg == "INC_TZ_PLUS")
        on_btnTZp_clicked();

    // deal with semi-auto mode
    else if(msg == "SEMI_MODE_CONTINUE")
    {
        server->WriteSocket("OK");
        if(dialog_semi == nullptr)
            return;
        dialog_semi->close();
        semi_dialog_results(CubeToBox(disting_color_result), disting_color_result);
    }
    else if(msg == "SEMI_MODE_AVAILABLE_BOX")
    {
        QString emptyBox = "";
        if(box_state[BOX_RED] == BOX_STATE::EMPTY)
            emptyBox += "RED";
        if(box_state[BOX_GREEN] == BOX_STATE::EMPTY)
            emptyBox += " GREEN";
        if(box_state[BOX_BLUE] == BOX_STATE::EMPTY)
            emptyBox += " BLUE";
        server->WriteSocket(emptyBox);
    }
    else if(msg == "SEMI_MODE_CANCEL")
    {
        if(dialog_semi == nullptr)
            return;
        dialog_semi->close();
        dialog_semi = nullptr;
    }
    else if(msg == "SEMI_MODE_RED_BOX")
    {
        server->WriteSocket("OK");
        if(dialog_semi == nullptr)
            return;
        dialog_semi->close();
        semi_dialog_results(BOX_RED, disting_color_result);
    }
    else if(msg == "SEMI_MODE_GREEN_BOX")
    {
        server->WriteSocket("OK");
        if(dialog_semi == nullptr)
            return;
        dialog_semi->close();
        semi_dialog_results(BOX_GREEN, disting_color_result);
    }
    else if(msg == "SEMI_MODE_BLUE_BOX")
    {
        server->WriteSocket("OK");
        if(dialog_semi == nullptr)
            return;
        dialog_semi->close();
        semi_dialog_results(BOX_BLUE, disting_color_result);
    }
}

void MainWindow::client_disconnected()
{
    ui->label_tcp_status->setText("Disconnected");
}


void MainWindow::on_btnLoadFile_clicked() {
    if (!Check_RoboDK()){ return; }

    QStringList files = QFileDialog::getOpenFileNames(this, tr("Open one or more files with RoboDK"));
    foreach (QString file, files){
        qDebug() << "Loading: " << file;
        RDK->AddFile(file);
    }

    if (!Check_Robot()){
        Select_Robot();
    }
}

void MainWindow::on_btnSelectRobot_clicked(){
    Select_Robot();
}


void MainWindow::on_btnGetPosition_clicked(){
    if (!Check_Robot()){ return; }

    QString separator = " , ";
    int decimals = 1;

    // Get robot joints
    tJoints joints(ROBOT->Joints());
    QString joints_str = joints.ToString(separator, decimals);
    ui->txtJoints->setText(joints_str);

    // Get robot pose
    Mat robot_pose(ROBOT->Pose());
    QString pose_str = robot_pose.ToString(separator, decimals);
    ui->txtXYZWPR->setText(pose_str);
}

void MainWindow::on_btnMoveJoints_clicked(){
    if (!Check_Robot()){ return; }

    tJoints joints;

    joints.FromString(ui->txtJoints->text());

    bool blocking = true;

    ROBOT->MoveJ(joints, blocking);

}

void MainWindow::on_btnMovePose_clicked(){
    if (!Check_Robot()){ return; }

    Mat pose;

    pose.FromString(ui->txtXYZWPR->text());

    bool blocking = true;

    ROBOT->MoveJ(pose, blocking);

}

void MainWindow::on_btnProgRun_clicked(){
    if (!Check_Robot()){ return; }

    QString program_name = ui->txtProgName->text();

    RDK->RunProgram(program_name);
}

// Example to run a second instance of the RoboDK api in parallel:
// make sure to include #include <thread>
//std::thread *t1 = new std::thread(blocking_task);
/*
void blocking_task(){
    RoboDK rdk; // important! It will not block the main thread (blocking or non blocking won'T make a difference)

    // show the blocking popup:
    rdk.Popup_ISO9283_CubeProgram();

}
*/

// then, start the thread and let it finish once the user finishes with the popup
void MainWindow::on_btnTestButton_clicked(){

    // example to listen to events
    QtConcurrent::run(this, &MainWindow::EventsLoop);
    //RDK->EventsLoop();


    if (!Check_Robot()){ return; }

    /*
    if (false) {
        //ROBOT->setPose
        Item robot_base = ROBOT->Parent();

        // Create or select a reference frame
        Item ref = RDK->getItem("Ref 1");
        if (!ref.Valid()){
            ref = RDK->AddFrame("Ref 1", &robot_base);
            ref.setPose(Mat::transl(100,200,300));
        }

        // create or load a tool
        Item tcp = RDK->getItem("Tool 1");
        if (!tcp.Valid()){
            tcp = ROBOT->AddTool(Mat::transl(0,0,150)*Mat::rotx(0.5*M_PI), "Tool 1");
        }

        // Set the robot base and tool
        ROBOT->setPoseFrame(ref);
        ROBOT->setPoseTool(tcp);

        Mat TargetPose = ROBOT->Pose();

        RDK->Render();

        Item prog = RDK->AddProgram("AutomaticProg", ROBOT);
        prog.setPoseFrame(ref);
        prog.setPoseTool(tcp);

        //Create a target (or select it)
        for (int i=0; i<=100; i++){
            QString target_name(QString("Target %1").arg(i+1));
            Item target = RDK->getItem(target_name, RoboDK::ITEM_TYPE_TARGET);
            if (!target.Valid()){
                target = RDK->AddTarget(target_name, &ref);
                target.setAsCartesianTarget();
                target.setPose(TargetPose * transl(0,0, 2*i) * rotz((i/100.0)*30.0*M_PI/180.0));
                if (i == 0){
                    prog.MoveJ(target);
                } else {
                    prog.MoveL(target);
                }
            }
        }
    }

    // manage a gripper
    if (false){
        //RDK->getItem("");
        Item gripper = ROBOT->Childs()[0];

        tJoints joints_original = gripper.Joints();

        double pjoints[] = {0};
        tJoints joints_new(pjoints, 1);
        gripper.setJoints(joints_new);

        gripper.MoveJ(joints_original);
    }

    //target.Delete();

    // example to display text in the 3D window
    if (true){
        Item station = RDK->getActiveStation();
        Item text_object = RDK->AddFile("", &station);
        text_object.setPose(transl(200,300,100));
        //text_object.setPoseAbs(transl(200,300,100));
        text_object.setName("Display 3D text");
    }

    // Other useful functions to draw primitives
    //RDK->AddShape()
    //RDK->AddCurve()
    //RDK->AddPoints()


    return;
*/



    //int runmode = RDK->RunMode(); // retrieve the run mode

    //RoboDK *RDK = new RoboDK();
    //Item *ROBOT = new Item(RDK->getItem("Motoman SV3"));

    // Draw a hexagon inside a circle of radius 100.0 mm
    int n_sides = 6;
    float size = 100.0;
    // retrieve the reference frame and the tool frame (TCP)
    Mat pose_frame = ROBOT->PoseFrame();
    Mat pose_tool = ROBOT->PoseTool();
    Mat pose_ref = ROBOT->Pose();

    // Program start
    ROBOT->MoveJ(pose_ref);
    ROBOT->setPoseFrame(pose_frame);  // set the reference frame
    ROBOT->setPoseTool(pose_tool);    // set the tool frame: important for Online Programming
    ROBOT->setSpeed(100);             // Set Speed to 100 mm/s
    ROBOT->setRounding(5);            // set the rounding instruction (C_DIS & APO_DIS / CNT / ZoneData / Blend Radius / ...)
    ROBOT->RunInstruction("CallOnStart"); // run a program
    for (int i = 0; i <= n_sides; i++) {
        // calculate angle in degrees:
        double angle = ((double) i / n_sides) * 360.0;

        // create a pose relative to the pose_ref
        Mat pose_i(pose_ref);
        pose_i.rotate(angle,0,0,1.0);
        pose_i.translate(size, 0, 0);
        pose_i.rotate(-angle,0,0,1.0);

        // add a comment (when generating code)
        ROBOT->RunInstruction("Moving to point " + QString::number(i), RoboDK::INSTRUCTION_COMMENT);

        // example to retrieve the pose as Euler angles (X,Y,Z,W,P,R)
        double xyzwpr[6];
        pose_i.ToXYZRPW(xyzwpr);

        ROBOT->MoveL(pose_i);  // move the robot
    }
    ROBOT->RunInstruction("CallOnFinish");
    ROBOT->MoveL(pose_ref);     // move back to the reference point

    return;


    // Example to iterate through all the existing targets in the station (blocking):
    QList<Item> targets = RDK->getItemList(RoboDK::ITEM_TYPE_TARGET);
    foreach (Item target, targets){
        if (target.Type() == RoboDK::ITEM_TYPE_TARGET){
            ui->statusBar->showMessage("Moving to: " + target.Name());
            qApp->processEvents();
            ROBOT->MoveJ(target);
        }
    }
    return;

    QList<Item> list = RDK->getItemList();


    Mat pose_robot_base_abs = ROBOT->PoseAbs();
    Mat pose_robot = ROBOT->Pose();
    Mat pose_tcp = ROBOT->PoseTool();

    qDebug() << "Absolute Position of the robot:";
    qDebug() << pose_robot_base_abs;

    qDebug() << "Current robot position (active tool with respect to the active reference):";
    qDebug() << pose_robot;

    qDebug() << "Position of the active TCP:";
    qDebug() << pose_tcp;

    QList<Item> tool_list = ROBOT->Childs();
    if (tool_list.length() <= 0){
        statusBar()->showMessage("No tools available for the robot " + ROBOT->Name());
        return;
    }

    Item tool = tool_list.at(0);
    qDebug() << "Using tool: " << tool.Name();

    Mat pose_robot_flange_abs = tool.PoseAbs();
    pose_tcp = tool.PoseTool();
    Mat pose_tcp_abs = pose_robot_flange_abs * pose_tcp;


    Item object = RDK->getItem("", RoboDK::ITEM_TYPE_FRAME);
    Mat pose_object_abs = object.PoseAbs();
    qDebug() << pose_tcp;

    Mat tcp_wrt_obj = pose_object_abs.inverted() * pose_tcp_abs;

    qDebug() << "Pose of the TCP with respect to the selected reference frame";
    qDebug() << tcp_wrt_obj;

    tXYZWPR xyzwpr;
    tcp_wrt_obj.ToXYZRPW(xyzwpr);

    this->statusBar()->showMessage(QString("Tool with respect to %1").arg(object.Name()) + QString(": [X,Y,Z,W,P,R]=[%1, %2, %3, %4, %5, %6] mm/deg").arg(xyzwpr[0],0,'f',3).arg(xyzwpr[1],0,'f',3).arg(xyzwpr[2],0,'f',3).arg(xyzwpr[3],0,'f',3).arg(xyzwpr[4],0,'f',3).arg(xyzwpr[5],0,'f',3) );


    // Example to define a reference frame given 3 points:
    tMatrix2D* framePts = Matrix2D_Create();
    Matrix2D_Set_Size(framePts, 3, 3);
    double *p1 = Matrix2D_Get_col(framePts, 0);
    double *p2 = Matrix2D_Get_col(framePts, 1);
    double *p3 = Matrix2D_Get_col(framePts, 2);

    // Define point 1:
    p1[0] = 100;
    p1[1] = 200;
    p1[2] = 300;

    // Define point 2:
    p2[0] = 500;
    p2[1] = 200;
    p2[2] = 300;

    // Define point 3:
    p3[0] = 100;
    p3[1] = 500;
    p3[2] = 300;
    Mat diagLocalFrame = RDK->CalibrateReference(framePts, RoboDK::CALIBRATE_FRAME_3P_P1_ON_X);
    Item localPlaneFrame = RDK->AddFrame("Plane Coord");
    localPlaneFrame.setPose(diagLocalFrame);
    Matrix2D_Delete(&framePts);
    return;

    // Inverse kinematics test:
    //Mat tool_pose = transl(10,20,30);
    //Mat ref_pose = transl(100, 100,500);

    qDebug() << "Testing pose:";
    qDebug() << "Using robot: " << ROBOT;
    Mat pose_test(0.733722985, 0.0145948902, -0.679291904, -814.060547, 0.000000000, -0.999769211, -0.0214804877, -8.96536446, -0.679448724, 0.0157607272, -0.733553648, 340.561951);
    ROBOT->setAccuracyActive(1);
    pose_test.MakeHomogeneous();
    qDebug() << pose_test;

    // Calculate a single solution (closest to the current robot position):
    tJoints joints = ROBOT->SolveIK(pose_test); //, &tool_pose, &ref_pose);
    qDebug() << "Solution : " << joints;

    // Iterate through all possible solutions
    // Calculate all nominal solutions:
    ROBOT->setAccuracyActive(0);
    auto all_solutions = ROBOT->SolveIK_All(pose_test); //, &tool_pose, &ref_pose);
    // Use accurate kinematics and calculate inverse kinematics using the closest point
    ROBOT->setAccuracyActive(1);
    for (int i=0; i<all_solutions.length(); i++){
        tJoints joints_nominal_i = all_solutions.at(i);
        qDebug() << "Nominal  solution " << i << ": " << joints_nominal_i;
        tJoints joints_accurate_i = ROBOT->SolveIK(pose_test, joints_nominal_i); //, &tool_pose, &ref_pose);
        qDebug() << "Accurate solution " << i << ": " << joints_accurate_i;
    }




    /*qDebug() << joints.ToString();
    tJoints joints = ROBOT->SolveIK(pose_problems);
    qDebug() << joints.ToString();
    */
    return;


    /*
    // Example to create the ISO cube program
        tXYZ xyz;
        xyz[0] = 100;
        xyz[1] = 200;
        xyz[2] = 300;
        RDK->Popup_ISO9283_CubeProgram(ROBOT, xyz, 100, false);
        return;
    */

}

void MainWindow::on_btnTXn_clicked(){ IncrementalMove(0, -1); }
void MainWindow::on_btnTYn_clicked(){ IncrementalMove(1, -1); }
void MainWindow::on_btnTZn_clicked(){ IncrementalMove(2, -1); }
void MainWindow::on_btnRXn_clicked(){ IncrementalMove(3, -1); }
void MainWindow::on_btnRYn_clicked(){ IncrementalMove(4, -1); }
void MainWindow::on_btnRZn_clicked(){ IncrementalMove(5, -1); }

void MainWindow::on_btnTXp_clicked(){ IncrementalMove(0, +1); }
void MainWindow::on_btnTYp_clicked(){ IncrementalMove(1, +1); }
void MainWindow::on_btnTZp_clicked(){ IncrementalMove(2, +1); }
void MainWindow::on_btnRXp_clicked(){ IncrementalMove(3, +1); }
void MainWindow::on_btnRYp_clicked(){ IncrementalMove(4, +1); }
void MainWindow::on_btnRZp_clicked(){ IncrementalMove(5, +1); }

void MainWindow::IncrementalMove(int id, double sense){
    if (!Check_Robot()) { return; }

    // check the index
    if (id < 0 || id >= 6){
        qDebug()<< "Invalid id provided to for an incremental move";
        return;
    }

    // calculate the relative movement
    double step = sense * ui->spnStep->value();

    // apply to XYZWPR
    tXYZWPR xyzwpr;
    for (int i=0; i<6; i++){
        xyzwpr[i] = 0;
    }
    xyzwpr[id] = step;

    Mat pose_increment;
    pose_increment.FromXYZRPW(xyzwpr);

    Mat pose_robot = ROBOT->Pose();

    Mat pose_robot_new;

    // apply relative to the TCP:
    pose_robot_new = pose_robot * pose_increment;

    ROBOT->MoveJ(pose_robot_new);

}

void MainWindow::on_radSimulation_clicked()
{
    if (!Check_Robot()) { return; }

    // Important: stop any previous program generation (if we selected offline programming mode)
    ROBOT->Finish();

    // Set simulation mode
    RDK->setRunMode(RoboDK::RUNMODE_SIMULATE);
}

void MainWindow::on_radOfflineProgramming_clicked()
{
    if (!Check_Robot()) { return; }

    // Important: stop any previous program generation (if we selected offline programming mode)
    ROBOT->Finish();

    // Set simulation mode
    RDK->setRunMode(RoboDK::RUNMODE_MAKE_ROBOTPROG);

    // specify a program name, a folder to save the program and a post processor if desired
    RDK->ProgramStart("NewProgram");
}

void MainWindow::on_radRunOnRobot_clicked()
{
    if (!Check_Robot()) { return; }

    // Important: stop any previous program generation (if we selected offline programming mode)
    ROBOT->Finish();

    // Connect to real robot
    if (ROBOT->Connect())
    {
        // Set simulation mode
        RDK->setRunMode(RoboDK::RUNMODE_RUN_ROBOT);
    }
    else
    {
        ui->statusBar->showMessage("Can't connect to the robot. Check connection and parameters.");
    }
}

void MainWindow::on_btnMakeProgram_clicked()
{
    if (!Check_Robot()) { return; }

    // Trigger program generation
    ROBOT->Finish();

}



void MainWindow::robodk_window_clear(){
    if (robodk_window != NULL){
        robodk_window->setParent(NULL);
        robodk_window->setFlags(Qt::Window);
        //robodk_window->deleteLater();
        robodk_window = NULL;
        ui->widgetRoboDK->layout()->deleteLater();
    }
    // Make sure RoboDK widget is hidden
    ui->widgetRoboDK->hide();

    // Adjust the main window size
    adjustSize();
}

void MainWindow::take_cam_snapshot()
{
    QScreen *screen = QGuiApplication::primaryScreen();
    if (const QWindow *window = windowHandle())
        screen = window->screen();
    if (!screen)
        return;
    QPixmap originalPixmap = screen->grabWindow(0, 8, 32, 470, 352);
    originalPixmap.save(cam_buffer_path);
}

void MainWindow::place_cube(BOXES place_box, CUBES cube_color)
{
    // return to the work position
    on_btnGripperWork_clicked();

    switch(place_box)
    {
    case BOX_RED:
        RDK->RunProgram("Prog_Place_Red");
        break;
    case BOX_GREEN:
        RDK->RunProgram("Prog_Place_Green");
        break;
    case BOX_BLUE:
        RDK->RunProgram("Prog_Place_Blue");
        break;
    default:
        break;
    }

    // store the moved cube of this process
    last_place_cube = cube_color;
    last_place_box = place_box;
    // update UI
    ui->btnOpPlaceCube->setDisabled(true);
    ui->btnOpUndo->setDisabled(false);
}

void MainWindow::show_semi_auto_dialog(CUBES org_color)
{   // do not create duplicate dialog
    if(dialog_semi != nullptr)
        return;

    dialog_semi = new Dialog_Semi_Mode(org_color, box_state, this);
    connect(dialog_semi, &Dialog_Semi_Mode::signal_result, this, &MainWindow::semi_dialog_results);
    dialog_semi->show();

    // lock UI
    ui->btnResetCubes->setDisabled(true);
}

CUBES MainWindow::distinguish_color()
{
    if(opencv_process != nullptr)
        opencv_process->close();
    opencv_process = new QProcess(this);

    CUBES color_result;
    // capture the picture first
    take_cam_snapshot();

    // start process to distinguish color
    opencv_process->setProgram("python");
    opencv_process->setArguments(QStringList() << "color.py" << "result");
    opencv_process->start();
    // wait for python processing
    opencv_process->waitForFinished();
    QString result = opencv_process->readAllStandardOutput();
    // check the result string
    if(result == "Red")
        color_result = CUBE_RED;
    else if(result == "Green")
        color_result = CUBE_GREEN;
    else if(result == "Blue")
        color_result = CUBE_BLUE;

    // restart the process to show the OpenCV filtered result
    opencv_process->setArguments(QStringList() << "color.py" << "show_window");
    opencv_process->start();

    return color_result;
}


void MainWindow::on_radShowRoboDK_clicked()
{
    if (!Check_RoboDK()){ return; }

    // Hide embedded window
    robodk_window_clear();

    RDK->setWindowState(RoboDK::WINDOWSTATE_NORMAL);
    RDK->setWindowState(RoboDK::WINDOWSTATE_SHOW);
}

void MainWindow::on_radHideRoboDK_clicked()
{
    if (!Check_RoboDK()){ return; }

    // Hide embedded window
    robodk_window_clear();

    RDK->setWindowState(RoboDK::WINDOWSTATE_HIDDEN);
}

#ifdef _MSC_VER
HWND FindTopWindow(DWORD pid)
{
    std::pair<HWND, DWORD> params = { 0, pid };

    // Enumerate the windows using a lambda to process each window
    BOOL bResult = EnumWindows([](HWND hwnd, LPARAM lParam) -> BOOL
    {
        auto pParams = (std::pair<HWND, DWORD>*)(lParam);

        DWORD processId;
        if (GetWindowThreadProcessId(hwnd, &processId) && processId == pParams->second)
        {
            // Stop enumerating
            SetLastError(-1);
            pParams->first = hwnd;
            return FALSE;
        }

        // Continue enumerating
        return TRUE;
    }, (LPARAM)&params);

    if (!bResult && GetLastError() == -1 && params.first)
    {
        return params.first;
    }

    return 0;
}
#endif

void MainWindow::on_radIntegrateRoboDK_clicked()
{
    if (!Check_RoboDK()){ return; }

    qint64 procWID = RDK->ProcessID();
    if (procWID == 0) {
        ui->statusBar->showMessage("Invalid handle. Close RoboDK and open RoboDK with this application");
        return;
    }


#ifdef _MSC_VER
    if (procWID != 0){
        qDebug() << "Using parent process=" << procWID;
        //SetParent((HWND) procWID, (HWND)widget_container->window()->winId());

        // Retrieve the top level window
        HWND wid_rdk = FindTopWindow(procWID);
        qDebug() << "HWND RoboDK window: " << wid_rdk;
        //SetParent((HWND) wid_rdk, (HWND)widget_container->winId());//->window()->winId());
        if (wid_rdk == NULL){
            ui->statusBar->showMessage("RoboDK top level window was not found...");
            return;
        }
        //HWND wid_rdk = (HWND) RDK->WindowID();
        // set parent widget
        robodk_window = QWindow::fromWinId((WId)wid_rdk);
        QWidget *new_widget = createWindowContainer(robodk_window);
        QVBoxLayout *vl = new QVBoxLayout();
        ui->widgetRoboDK->setLayout(vl);
        vl->addWidget(new_widget);
        new_widget->show();
        this->adjustSize();

        RDK->setWindowState(RoboDK::WINDOWSTATE_SHOW);
        RDK->setWindowState(RoboDK::WINDOWSTATE_FULLSCREEN_CINEMA);

        // Show the RoboDK widget (embedded screen)
        ui->widgetRoboDK->show();
    }
#endif

}



/// <summary>
/// This is a sample function that is executed when a new RoboDK Event occurs.
/// </summary>
/// <param name="evt"></param>
/// <param name="itm"></param>
/// <returns></returns>
bool MainWindow::SampleRoboDkEvent(int evt, Item itm)
{
    qDebug() << "**** New event ****";

    //If this runs in a seperate thread from the api instance thaw sapwned it you won't be able to do
    //Regular api calls like item.Valid()
    //if (itm.Valid())
    //{
        //qDebug() << "  Item: " + itm.Name() + " -> Type: " + itm.Type();
    //}
    //else
    //{
        //Console.WriteLine("  Item not applicable");
    //}

    switch (evt)
    {
        case RoboDK::EVENT_SELECTION_TREE_CHANGED:
            qDebug() << "Event: Selection changed (the tree was selected)";
            break;
        case RoboDK::EVENT_ITEM_MOVED:
            qDebug() << "Event: Item Moved";
            break;
        case RoboDK::EVENT_REFERENCE_PICKED:
            qDebug() << "Event: Reference Picked";
            break;
        case RoboDK::EVENT_REFERENCE_RELEASED:
            qDebug() << "Event: Reference Released";
            break;
        case RoboDK::EVENT_TOOL_MODIFIED:
            qDebug() << "Event: Tool Modified";
            break;
        case RoboDK::EVENT_3DVIEW_MOVED:
            qDebug() << "Event: 3D view moved"; // use ViewPose to retrieve the pose of the camera
            break;
        case RoboDK::EVENT_ROBOT_MOVED:
            qDebug() << "Event: Robot moved";
            break;

        // Important: The following events require consuming additional data from the _COM_EVT buffer
        case RoboDK::EVENT_SELECTION_3D_CHANGED:
        {
            qDebug() << "Event: Selection changed";
            // data contains the following information (24 values):
            // pose (16), xyz selection (3), ijk normal (3), picked feature id (1), picked id (1)
            //double[] data = RDK._recv_Array(RDK->_COM_EVT);
            double data[24];
            int valueCount;
            RDK->Event_Receive_3D_POS(data,&valueCount);
            //
            Mat pose_abs = Mat(data);
            double xyz[3] = { data[16], data[17], data[18] };
            double ijk[3] = { data[19], data[20], data[21] };
            int feature_type = data[22];
            int feature_id = data[23];
            qDebug() << "Additional event data - Absolute position (PoseAbs):";
            qDebug() << pose_abs.ToString();
            qDebug() << "Additional event data - Point and Normal (point selected in relative coordinates)";
            qDebug() << QString::number(xyz[0]) + "," + QString::number(xyz[1]) + "," + QString::number(xyz[2]);
            qDebug() << QString::number(ijk[0]) + "," + QString::number(ijk[1]) + "," + QString::number(ijk[2]);
            qDebug() << "Feature Type and ID";
            qDebug() << QString::number(feature_type) + "-" + QString::number(feature_id);
            break;
        }
        case RoboDK::EVENT_KEY:
        {
            int mouseData[3];
            RDK->Event_Receive_Mouse_data(mouseData);
            int key_press = mouseData[0]; // 1 = key pressed, 0 = key released
            int key_id = mouseData[1]; // Key id as per Qt mappings: https://doc.qt.io/qt-5/qt.html#Key-enum
            int modifiers = mouseData[2]; // Modifier bits as per Qt mappings: https://doc.qt.io/qt-5/qt.html#KeyboardModifier-enum
            qDebug() << "Event: Key pressed: " + QString::number(key_id) + " " + ((key_press > 0) ? "Pressed" : "Released") + ". Modifiers: " + QString::number(modifiers);
            break;
        }
        case RoboDK::EVENT_ITEM_MOVED_POSE:
        {
            Mat pose_rel;
            bool flag = RDK->Event_Receive_Event_Moved(&pose_rel);
            //int nvalues = _recv_Int(_COM_EVT);
            //Mat pose_rel = _recv_Pose(_COM_EVT);
            if (flag == false)
            {
                // future compatibility
            }
            qDebug() << "Event: item moved. Relative pose: " + pose_rel.ToString();
            break;
        }
        default:
            qDebug() << "Unknown event " + QString::number(evt);
            break;
    }
    return true;
}

bool MainWindow::EventsLoop()
{
    RDK->EventsListen();

    qDebug() << "Events loop started";
    while (RDK->Event_Connected())
    {
        int evt;
        Item itm;
        RDK->WaitForEvent(evt,itm);
        SampleRoboDkEvent(evt, itm);
    }
    qDebug() << "Event loop finished";
    return true;
}

void MainWindow::on_btnEmbed_clicked()
{
    if (!Check_RoboDK()){ return; }
    on_radShowRoboDK_clicked();
    EmbedExample *newWindow = new EmbedExample();
    newWindow->show();
    QString windowName = newWindow->windowTitle();
    qDebug() << windowName;
    RDK->EmbedWindow(windowName);

}

void MainWindow::on_btnTestCamera_clicked(){
    //Item reference = RDK->ItemUserPick("Pick a coordinate system to attach the camera", RoboDK::ITEM_TYPE_FRAME);
    Item reference = RDK->getItem("Camera", RoboDK::ITEM_TYPE_ANY);
    if (!reference.Valid()){
        qDebug() << "No item selected or available";
        return;
    }

    // Get or set the camera location (reference it is linked to):
    //Mat pose_rel = reference.Pose(); // get current pose (relative, with respect to parent)
    //Mat pose_abs = reference.PoseAbs(); // get current pose (absolute, with respect to station reference)
    //reference.setPose(transl(100,200,300) * rotz(M_PI));

    // Set camera parameters so that it takes Full HD snapshot images and black background
    QString cam_params = "NEAR_LENGTH=5 FAR_LENGTH=100000 FOV=30 SNAPSHOT=1920x1080 NO_TASKBAR BG_COLOR=black";
    Item cam_item = RDK->Cam2D_Add(reference, cam_params);
    QString image_file = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation) + "/Camera-Snapshot.png";
    int success = RDK->Cam2D_Snapshot(image_file, cam_item);
    if (success == 0){
        qDebug() << "Failed to save image to: " << image_file;
    } else {
        qDebug() << "Snapshot saved successfully: " << image_file;
    }
}

void MainWindow::initialize_cubes()
{
    if (!Check_RoboDK()){ return; }

    // get the items from RoboDK Program
    cubes[CUBE_RED] = RDK->getItem("Red-Cube", RDK->ITEM_TYPE_OBJECT);
    cubes[CUBE_GREEN] = RDK->getItem("Green-Cube", RDK->ITEM_TYPE_OBJECT);
    cubes[CUBE_BLUE] = RDK->getItem("Blue-Cube", RDK->ITEM_TYPE_OBJECT);
}

void MainWindow::on_btnResetCubes_clicked()
{
    if (!Check_RoboDK()){ return; }

    Mat resetPos;
    float reset_x = 30.0f;
    resetPos.setPos(reset_x, 237.0f, 0.0f);

    for(int i = 0; i < MAX_CUBES; i++)
    {
        // reset the cubes position
        reset_x -= 100.0f;
        resetPos.setPos(reset_x, 237.0f, 0.0f);
        cubes[i].setPose(resetPos);
        // reset the cube states in memory
        cube_state[i] = CUBE_STATE::IDLE;
    }
    // reset the box states in memory
    for(int i = 0; i < MAX_BOXES; i++)
        box_state[i] = BOX_STATE::EMPTY;

    // lock UI
    ui->btnOpPlaceCube->setDisabled(true);
    ui->btnOpUndo->setDisabled(true);

    // display message in status bar
    statusBar()->showMessage("Cubes have been reset!");
}

void MainWindow::on_btnPlaceCube_clicked()
{
    if (!Check_RoboDK()){ return; }

    // check whether there is any cube in work place
    for(int i = 0; i < MAX_CUBES; i++)
        if(cube_state[i] == CUBE_STATE::WORK_PLACE)
        {
            statusBar()->showMessage("There is already a cube in work place!");
            return;
        }

    // randomly make one of the available cubes appear
    unsigned short int rand_cube = qrand() % MAX_CUBES;

    // detect whether cube is valid
    int i;
    for(i = 0; i < MAX_CUBES; i++)
    {
        if(cube_state[rand_cube] == CUBE_STATE::IDLE)
            break;
        else
            rand_cube = (rand_cube + 1) % MAX_CUBES;
    }
    // all of the cubes are not available
    if(i == MAX_CUBES)
    {
        statusBar()->showMessage("No more cubes available!");
        return;
    }
    // record the cube state in memory
    cube_state[rand_cube] = CUBE_STATE::WORK_PLACE;

    Mat placePos;
    placePos.setPos(170.0, -40.0, 0.0);
    cubes[rand_cube].setPose(placePos);

    // display the cube color in status bar
    QString msg;
    switch(rand_cube)
    {
    case CUBE_RED:
        msg = "Red Cube Placed";
        break;
    case CUBE_GREEN:
        msg = "Green Cube Placed";
        break;
    case CUBE_BLUE:
        msg = "Blue Cube Placed";
        break;
    }
    statusBar()->showMessage(msg);

    // update UI
    ui->btnOpPlaceCube->setDisabled(false);
    ui->btnOpUndo->setDisabled(true);
}

void MainWindow::on_btn_snap_cam_clicked()
{   // take snap shot of the camera screen (with screen shot method)
    take_cam_snapshot();
}

void MainWindow::on_btnGripperHome_clicked()
{
    if(!Check_RoboDK()) return;
    // run the program to make the gripper be at home position
    RDK->RunProgram("Prog_Home_Pos");
}


void MainWindow::on_btnGripperWork_clicked()
{
    if(!Check_RoboDK()) return;
    // run the program to make the gripper be at camera position
    RDK->RunProgram("Prog_Cam_Pos");
}


void MainWindow::on_btnOpPlaceCube_clicked()
{
    // find the cube in work place
    bool isCubeInWorkplace = false;
    CUBES current_cube;
    for(int i = 0; i < CUBES::MAX_CUBES; i++)
        if(cube_state[i] == CUBE_STATE::WORK_PLACE)
        {
            isCubeInWorkplace = true;
            current_cube = (CUBES)i;
            break;
        }
    if(!isCubeInWorkplace)
        return;

    // distinguish the color with OpenCV
    disting_color_result = distinguish_color();

    // check the operation mode
    if(ui->radAutoMode->isChecked())
    {
        // lock place button
        ui->btnOpPlaceCube->setDisabled(true);
        // call the program to place the cube
        place_cube(CubeToBox(disting_color_result), disting_color_result);
        // change the state of cube
        cube_state[(int)current_cube] = CUBE_STATE::IN_BOX;
        // change the state of box
        box_state[(int)current_cube] = BOX_STATE::HAS_CUBE;
    }
    else if(ui->radSemiMode->isChecked())
    {
        // confirm the decision with user before placing the cube
        show_semi_auto_dialog(disting_color_result);
    }
}

void MainWindow::on_btnOpUndo_clicked()
{
    // call the program in RoboDK to undo the cube movement
    switch(last_place_box)
    {
    case BOX_RED:
        RDK->RunProgram("Prog_Return_Red");
        break;
    case BOX_GREEN:
        RDK->RunProgram("Prog_Return_Green");
        break;
    case BOX_BLUE:
        RDK->RunProgram("Prog_Return_Blue");
        break;
    default:
        break;
    }

    // change the cube state
    cube_state[(int)last_place_cube] = CUBE_STATE::WORK_PLACE;
    // change the box state
    box_state[(int)last_place_box] = BOX_STATE::EMPTY;

    // update UI
    ui->btnOpPlaceCube->setDisabled(false);
    ui->btnOpUndo->setDisabled(true);
}


void MainWindow::on_btn_show_semi_ui_clicked()
{
    show_semi_auto_dialog(CUBE_RED);
}

// slots return from semi confirm dialog
void MainWindow::semi_dialog_results(BOXES result_color, CUBES org_color)
{
    // find the cube in work place
    bool isCubeInWorkplace = false;
    CUBES work_place_cube;
    for(int i = 0; i < MAX_CUBES; i++)
        if(cube_state[i] == CUBE_STATE::WORK_PLACE)
        {
            isCubeInWorkplace = true;
            work_place_cube = (CUBES)i;
            break;
        }
    if(!isCubeInWorkplace)
        return;

    // valid box value
    if((int)result_color < MAX_BOXES)
    {
        // call program to move box and change the cube state
        place_cube(result_color, work_place_cube);
        // change the state of cube
        cube_state[(int)work_place_cube] = CUBE_STATE::IN_BOX;
        // change the state of box
        box_state[(int)result_color] = BOX_STATE::HAS_CUBE;
        // lock place button
        ui->btnOpPlaceCube->setDisabled(true);
    }
    // otherwise, dialog was cancelled by user

    // unlock UI
    ui->btnResetCubes->setDisabled(false);

    // dialog has been closed and destroyed after clicking any buttons
    dialog_semi = nullptr;
}

void MainWindow::on_btn_about_clicked()
{   // do not create duplicate dialog
     if(dialog_semi != nullptr)
         return;
     dialog_about = new Dialog_About(this);
     connect(dialog_about, &Dialog_About::onClose, this, &MainWindow::about_dialog_closed);
     dialog_about->show();
}

void MainWindow::about_dialog_closed()
{
    dialog_about = nullptr;
}
