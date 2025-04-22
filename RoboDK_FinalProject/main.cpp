#include "mainwindow.h"
#include <QApplication>

#define ROBOT_PATH "UR3_Pick_Place.rdk"
#define DEBUG_MODE false

#define SNAPSHOT_BUFFER_PATH "cam_shot.png"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    // initialize RoboDK in MainWindow
    w.Initialize_Window(ROBOT_PATH, SNAPSHOT_BUFFER_PATH, DEBUG_MODE);

    return a.exec();
}
