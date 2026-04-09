#include "Viewer3D.h"

int main()
{
    Viewer3D viewer3D;
    if (viewer3D.init())
    {
        viewer3D.run();
    }
    return 0;
}