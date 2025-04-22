#include "FinalProjectTypes.h"

BOXES CubeToBox(CUBES cube)
{
    switch(cube)
    {
    case CUBE_RED:
        return BOX_RED;
    case CUBE_GREEN:
        return BOX_GREEN;
    case CUBE_BLUE:
        return BOX_BLUE;
    default:
        break;
    }
    return BOX_RED;
}
