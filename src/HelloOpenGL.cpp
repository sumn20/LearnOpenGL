//
// Created by Sumn on 2021/10/19.
//

#include "HelloOpenGL.h"
#include <iostream>


//设置常量
const unsigned int SCR_WIDTH=800;
const unsigned int SCR_HEIGHT=600;
/**
 * 顶点数组对象：Vertex Array Object，VAO
 * 顶点缓冲对象：Vertex Buffer Object，VBO
 * 索引缓冲对象：Element Buffer Object，EBO或Index Buffer Object，IBO
 */
int HelloOpenGL::init() {
    //实例化GLFW窗口
    //初始化GLFW
    glfwInit();
    //配置GLFW 配置OpenGL版本,主版本号(Major)和次版本号(Minor)为3.0
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    //设置OpenGL配置文件
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    //创建一个窗口对象
    GLFWwindow* window= glfwCreateWindow(SCR_WIDTH,SCR_HEIGHT,"LearnOpenGL", nullptr, nullptr);
    if (window== nullptr){
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    //设置gl回调
    glfwSetFramebufferSizeCallback(window,framebuffer_size_callback);
    //使用GLAD来管理OpenGL的函数指针,初始化GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    //渲染循环(Render Loop)
    /**
     * glfwWindowShouldClose  函数在我们每次循环的开始前检查一次GLFW是否被要求退出，如果是的话该函数返回true然后渲染循环便结束了，之后为我们就可以关闭应用程序了
     * glfwPollEvents 函数检查有没有触发什么事件（比如键盘输入、鼠标移动等）、更新窗口状态，并调用对应的回调函数（可以通过回调方法手动设置）。
     * glfwSwapBuffers 函数会交换颜色缓冲（它是一个储存着GLFW窗口每一个像素颜色值的大缓冲），它在这一迭代中被用来绘制，并且将会作为输出显示在屏幕上。
     */
    while (!glfwWindowShouldClose(window)){
        processInput(window);
        //渲染指令
        //glClearColor函数是一个状态设置函数
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        //glClear 状态使用的函数
        glClear(GL_COLOR_BUFFER_BIT);

        //检查并调用事件,交换缓冲
        glfwPollEvents();
        glfwSwapBuffers(window);

    }
    //释放之前的分配的所有资源
    glfwTerminate();
    return 0;
}
void HelloOpenGL::processInput(GLFWwindow *window){
    if (glfwGetKey(window,GLFW_KEY_ESCAPE)==GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}
void HelloOpenGL::framebuffer_size_callback(GLFWwindow* window,int width,int  height){
    //告诉OpenGL渲染窗口的尺寸大小，即视口(Viewport)
    glViewport(0,0,width,height);
}
