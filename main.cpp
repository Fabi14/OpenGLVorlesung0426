#include <cstdlib>
#include "Engine.h"

int main()
{
    Engine viewer3D;
    if (!viewer3D.init())
    {
        return EXIT_FAILURE;
    }
    viewer3D.run();
    return EXIT_SUCCESS;
}