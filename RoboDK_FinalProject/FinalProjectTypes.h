#ifndef FINALPROJECTTYPES_H
#define FINALPROJECTTYPES_H

// three different cubes in the program
enum CUBES {
    CUBE_RED,
    CUBE_GREEN,
    CUBE_BLUE,

    MAX_CUBES
};

// three different boxes in the program
enum BOXES {
    BOX_RED,
    BOX_GREEN,
    BOX_BLUE,

    MAX_BOXES
};

// record the state of cubes
enum CUBE_STATE {
    IDLE,
    WORK_PLACE,
    IN_BOX
};

// record the state of boxes
enum BOX_STATE {
    EMPTY,
    HAS_CUBE
};

BOXES CubeToBox(CUBES cube);

#endif // FINALPROJECTTYPES_H
