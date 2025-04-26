# RoboDK in Qt and Controlled by Android
Assuming that the workspace is radiactive (or has other poison substances), which does not allow people to operate in the environment.

A better way to perform task in a such hazardous environment is to put a robot and control it remotely.

Therefore, this repository built up the following simulation and tools:
1. radiative (or hazardous) workspace with RoboDK
1. GUI for interacting with the robot and objects inside RoboDK with Qt RoboDK API
1. remote control App for communicating with GUI to send commands via TCP with Android Studio
1. color distinguish for helping the operators to make correct decisions (which the box should the cube in workspace be put into) with Python OpenCV module

There are 2 operation modes in this repository:
* Autonomous Mode: put the cube in the workspace to the box with the same color automatically without approval from the operators
* Semi-Autonomous: after performing color distinguish on the cube in the workspace, the decision MUST be confirmed with the operators before the robot operates

## Demo Video
Here is the demo video of this repository:

[![Video](http://img.youtube.com/vi/0ad2fMN4XYM/0.jpg)](http://www.youtube.com/watch?v=0ad2fMN4XYM)

## Documents to the Related Work

* Report of our project: [ARAA_Group4 Final Report.pdf](https://drive.google.com/file/d/1AvyOT39n5eNLyFVbR2Ot2hYx1eFpI-Hd/view?usp=drive_link)
* Presentation of our project: [ARAA Presentation Slide](https://drive.google.com/file/d/1S9k1vKDmRrDj7z2GTeYznHCqmFZb7gYs/view?usp=drive_link)
* References for this repository:
    * [Human Robot Interaction for Further Remote Manipulation in Industry 4.0](https://ifatwww.et.uni-magdeburg.de/ifac2020/media/pdfs/4304.pdf)
    * [Bimanual Teleoperation of a Compliant, Whole-body-controlled Humanoid Robot](https://www.youtube.com/watch?v=M6mQWcLAiko)

## Binary Execution
To run our project with binary execuables on Windows, please follow the steps:

1. Download [RoboDK-Qt-Android-Executables.zip](https://drive.google.com/file/d/1SzRXJHRXHviDkX_vg10qfiJk8jfYFNE-/view?usp=drive_link)
1. Extract the contents to root directory of this repository
1. Install [RoboDK v5.4.1 (64-bit)](https://robodk.com/download)
1. Add RoboDK built-in Python v3.7.3 executable path to Windows environment variable `PATH`
1. Run command line and install Python dependent packages:
    ```
    python -m pip install --upgrade pip
    pip install -r requirements.txt
    ```
1. Copy Python color distinguish script and RoboDK project from path `RoboDK_FinalProject` to `Executables/RoboDK-API-Cpp`:
    ```
    copy RoboDK_FinalProject\color.py Executables\RoboDK-API-Cpp
    copy RoboDK_FinalProject\UR3_Pick_Place.rdk Executables\RoboDK-API-Cpp
    ```
1. Execute GUI executable in `Executables/RoboDK-API-Cpp/RoboDK-API-Cpp-Sample.exe`

    1. GUI should pop up and RoboDK workspace with camera view should also be shown.

    1. Now you can try to click the buttons in the field `Sucker Position` or `Cube Placement` on GUI and check whether the robot or objects are moving properly.

    1. Make sure the camera view window is in the initial position and there is no other window overlap the view.

    1. There are two operation modes for simulation:

        * In `Autonomous` operation mode, click the buttons `Random Place` and `Place` to perform color distinguish with camera view and place the cube to the box with the same color.

        * In `Semi-Autonomous` operation mode, click the buttons `Random Place` and `Place` to perform color distinguish on the current placed cube. The confirmation message pops up to let user check whether the color-distinguish result is correct. User can proceed with the detected result or place the current cube to the box with specific color manually.

    1. If GUI works fine, the Android install package in `Executables/Android-TCP-Client/app-debug.apk` can be transferred to Android device and install it.

        1. Make sure PC and Android device are connected to the same router.

        1. Execute the app `RoboDK Color Distinguish Demo`.

        1. Enter the TCP server IP address, which is displayed on GUI `Server IP` in the field `TCP Connection`.

        1. The buttons on the interfaces would be enabled when TCP connection established successfully. User can try to operate the RoboDK objects remotely and do the decision with Android app.

## Development IDE / Environment Setup
1. The following dependent IDE and environment must be installed:
    * [RoboDK v5.4.1 (64-bit)](https://robodk.com/download)
    * Python v3.7.3 (RoboDK built-in) with required packages installed (refer to step 5. in the previous section)
    * [Android Studio v3.6.1](https://redirector.gvt1.com/edgedl/android/studio/install/3.6.1.0/android-studio-ide-192.6241897-windows.exe?utm_source=androiddevtools&utm_medium=website)
    * [Qt Community v5.11.2](https://download.qt.io/new_archive/qt/5.11/5.11.2/) select `MinGW` tools in custom installation

1. Developers can open IDE and edit the corresponding projects:
    * RoboDK: `RoboDK_FinalProject/UR3_Pick_Place.rdk`

    * Qt GUI: run `Qt Creator` and go to menu `File` -> `Open File or Project...` -> select `RoboDK_FinalProject/RoboDK-API-Cpp-Sample.pro` -> click button `Run` (or Ctrl+R) to start compiling the project and debugging the application

    * Python color distinguish: edit Python script `RoboDK_FinalProject/color.py`

    * Android Remote App: run `Android Studio` and go to menu `File` -> `Open` -> select folder `AndroidClient` -> connect your real Android device and click button `Run` (or Shift+F10) to start compiling the project and debugging the application
