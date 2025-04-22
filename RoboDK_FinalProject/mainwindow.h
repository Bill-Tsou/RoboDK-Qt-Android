#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProcess>
#include "FinalProjectTypes.h"

#include "dialog_about.h"
// import the semi-auto mode confirm dialog
#include "dialog_semi_mode.h"

// TIP: use #define RDK_SKIP_NAMESPACE to avoid using namespaces
#include "robodk_api.h"

#include "TcpServer.h"

using namespace RoboDK_API;


namespace Ui {
class MainWindow;
}


/// Example's main window (robot panel)
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void Initialize_Window(QString robot_path, QString cam_buf_path, bool debug_mode = true);

    /// Select a robot
    void Select_Robot();

    /// Validate if RoboDK is running (RDK is valid)
    bool Check_RoboDK();

    /// Validate if a Robot has been selected (ROBOT variable is valid)
    bool Check_Robot();

    /// Apply an incremental movement
    void IncrementalMove(int id, double sense);


    bool EventsLoop();
    bool SampleRoboDkEvent(int evt, Item itm);
private slots:
    // slots from TcpServer
    void client_connected(bool isConnected);
    void receive_message(QString msg);
    void client_disconnected();

    // controls on UI
    void on_btnLoadFile_clicked();
    void on_btnSelectRobot_clicked();
    void on_btnTestButton_clicked();
    void on_btnGetPosition_clicked();
    void on_btnMoveJoints_clicked();
    void on_btnMovePose_clicked();
    void on_btnProgRun_clicked();
    void on_btnTXn_clicked();
    void on_btnTYn_clicked();
    void on_btnTZn_clicked();
    void on_btnRXn_clicked();
    void on_btnRYn_clicked();
    void on_btnRZn_clicked();
    void on_btnTXp_clicked();
    void on_btnTYp_clicked();
    void on_btnTZp_clicked();
    void on_btnRXp_clicked();
    void on_btnRYp_clicked();
    void on_btnRZp_clicked();

    void on_radSimulation_clicked();
    void on_radOfflineProgramming_clicked();
    void on_radRunOnRobot_clicked();
    void on_btnMakeProgram_clicked();

    void on_radShowRoboDK_clicked();
    void on_radHideRoboDK_clicked();
    void on_radIntegrateRoboDK_clicked();

    void on_btnEmbed_clicked();
    void on_btnTestCamera_clicked();

    void on_btn_snap_cam_clicked();

    void on_btnResetCubes_clicked();
    void on_btnPlaceCube_clicked();

    void on_btnGripperHome_clicked();
    void on_btnGripperWork_clicked();

    void on_btnOpPlaceCube_clicked();
    void on_btnOpUndo_clicked();

    void on_btn_show_semi_ui_clicked();

    void about_dialog_closed();
    void semi_dialog_results(BOXES result_color, CUBES org_color);

    void on_btn_about_clicked();

private:
    void initialize_cubes();
    void robodk_window_clear();

    void take_cam_snapshot();

    // call the program in RoboDK to move the cube to certain box
    void place_cube(BOXES place_box, CUBES cube_color = MAX_CUBES);
    // show semi-auto confirm dialog
    void show_semi_auto_dialog(CUBES res_color);
    // capture image of camera and distinguish color
    CUBES distinguish_color();

private:
    Ui::MainWindow *ui;
    Dialog_About *dialog_about;
    Dialog_Semi_Mode *dialog_semi;
    // OpenCV image process
    QProcess *opencv_process;

    // Tcp Server
    TcpServer *server;

    /// Pointer to RoboDK
    RoboDK *RDK;

    /// Pointer to the robot item
    Item *ROBOT;
    Item camera;
    QString cam_buffer_path;

    /// Pointer to the RoboDK window
    QWindow *robodk_window;
    // cube objects in RoboDK
    Item cubes[MAX_CUBES];

    CUBE_STATE cube_state[MAX_CUBES];
    BOX_STATE box_state[MAX_BOXES];
    // store the cube and the box last placed into
    CUBES last_place_cube;
    BOXES last_place_box;
    // semi mode distinguished color
    CUBES disting_color_result;
};

#endif // MAINWINDOW_H
