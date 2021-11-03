//
// Created by Sumn on 2021/10/26.
//

#ifndef LEARNOPENGL_COORDINATESYSTEMS_H
#define LEARNOPENGL_COORDINATESYSTEMS_H

#include "glad.h"
#include "glfw3.h"

class CoordinateSystems {
    //窗口注册一个回调函数(Callback Function)，它会在每次窗口大小被调整的时候被调用
    static void framebuffer_size_callback(GLFWwindow* window,int width,int  height);
    static void processInput(GLFWwindow *window);
public:
    int init();
};


#endif //LEARNOPENGL_COORDINATESYSTEMS_H
