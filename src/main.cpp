#include <iostream>
#include "HelloOpenGL.h"
#include "triangle/Triangle.h"
#include "triangle/TwoTriangle.h"
#include "triangle/MovingTriangle.h"
#include "triangle/TextureTriangle.h"
#include "change/BoxRotation.h"
#include "CoordinateSystems.h"
#include "DesktopTest.h"

int main() {
    //Hello Word
    /*auto *helloOpenGl = new HelloOpenGL();
    return helloOpenGl->init();*/
    /* auto *triangle=new Triangle();
     return triangle->init();*/
    /* auto *twoTriangle=new TwoTriangle();
     return twoTriangle->init();*/
    /* auto *movingTriangle=new MovingTriangle();
      return movingTriangle->init();*/
    /*auto *textureTriangle=new TextureTriangle();
    return textureTriangle->init();*/
    /* auto *rotation=new BoxRotation();
     return rotation->init();*/
    /* auto *coordinateSystems=new CoordinateSystems();
      return coordinateSystems->init();*/
    auto *desktopTest = new DesktopTest();
    return desktopTest->init();
}

