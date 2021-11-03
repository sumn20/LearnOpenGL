//
// Created by Sumn on 2021/10/19.
//

#include "TwoTriangle.h"
#include <iostream>
#include "Constant.h"


/*
 * 顶点数组对象：Vertex Array Object，VAO
 * 顶点缓冲对象：Vertex Buffer Object，VBO
 * 索引缓冲对象：Element Buffer Object，EBO或Index Buffer Object，IBO
 */
int TwoTriangle::init() {
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
    GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", nullptr, nullptr);
    if (window == nullptr) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    //设置gl回调
    glfwSetFramebufferSizeCallback(window,TwoTriangle:: framebuffer_size_callback);
    //使用GLAD来管理OpenGL的函数指针,初始化GLAD
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    //构建三角形
    // ------------------------------------------------------------------
    /**
     * 配置顶点着色器
     */
    unsigned int vertexShader;
    //创建顶点着色器
    vertexShader=glCreateShader(GL_VERTEX_SHADER);
    //将着色器代码附加到着色器对象上,然后编译它
    glShaderSource(vertexShader,1,&vertexShaderSource,nullptr);
    glCompileShader(vertexShader);
    //检测着色器代码是否正常编译且能使用
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader,GL_COMPILE_STATUS,&success);
    if (!success){
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    /**
     * 配置片段着色器
    */
    unsigned int fragmentShader;
    fragmentShader=glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader,1,&fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);
    //检测片段着色器是否正常编译且能使用
    glGetShaderiv(fragmentShader,GL_COMPILE_STATUS,&success);
    if (!success){
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    //配置第二个片段着色器
    unsigned int  fragmentShader2;
    fragmentShader2=glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader2,1,&fragmentShader2Source, nullptr);
    glCompileShader(fragmentShader2);
    //检测片段着色器是否正常编译且能使用
    glGetShaderiv(fragmentShader2,GL_COMPILE_STATUS,&success);
    if (!success){
        glGetShaderInfoLog(fragmentShader2, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    /**
     * 链接着色器程序
     */
    unsigned int shaderProgram;
    //创建着色器程序
    shaderProgram=glCreateProgram();
    //将顶点着色器和片段着色器链接上着色器程序上
    glAttachShader(shaderProgram,vertexShader);
    glAttachShader(shaderProgram,fragmentShader);
    glLinkProgram(shaderProgram);
    //检测着色器程序链接是否正常
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    //创建第二个着色器程序
    unsigned int  shaderProgram2;
    shaderProgram2=glCreateProgram();
    glAttachShader(shaderProgram2,vertexShader);
    glAttachShader(shaderProgram2,fragmentShader2);
    glLinkProgram(shaderProgram2);
    glGetProgramiv(shaderProgram2, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram2, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }



    //链接成功后,删除着色器,因为着色器程序中已经有着色器了
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    glDeleteShader(fragmentShader2);


    /**
     * 设定顶点数据并加载到GPU缓冲中
     */
    //顶点坐标集合
    float firstTriangle[] = {
            -0.9f, -0.5f, 0.0f,  // left
            -0.0f, -0.5f, 0.0f,  // right
            -0.45f, 0.5f, 0.0f,  // top
    };
    float secondTriangle[] = {
            0.0f, -0.5f, 0.0f,  // left
            0.9f, -0.5f, 0.0f,  // right
            0.45f, 0.5f, 0.0f   // top
    };
    /*
     * 顶点缓冲对象(Vertex Buffer Objects, VBO):
     * 它会在GPU内存（通常被称为显存）中储存大量顶点。使用这些缓冲对象的好处是我们可以一次性的发送一大批数据到显卡上，而不是每个顶点发送一次。从CPU把数据发送到显卡相对较慢，所以只要可能我们都要尝试尽量一次性发送尽可能多的数据。当数据发送至显卡的内存中后，顶点着色器几乎能立即访问顶点，这是个非常快的过程。
     */
    unsigned int VBOs[2],VAOs[2];
    glGenVertexArrays(2,VAOs);
    //通过glGenBuffers函数和一个缓冲ID生成一个VBO对象
    glGenBuffers(2, VBOs);
    //绑定VAO
    glBindVertexArray(VAOs[0]);
    //OpenGl有很多缓冲对象类型,顶点缓冲对象的类型是GL_ARRAY_BUFFER
    //将新创建的缓冲绑定到GL_ARRAY_BUFFER目标上
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
    //将定义的顶点坐标复制到GL_ARRAY_BUFFER缓冲内存中,此时GL_ARRAY_BUFFER=VBO;
    /*
     * 第四个参数指定了我们希望显卡如何管理给定的数据。它有三种形式：
     * GL_STATIC_DRAW ：数据不会或几乎不会改变。
     * GL_DYNAMIC_DRAW：数据会被改变很多。
     * GL_STREAM_DRAW ：数据每次绘制时都会改变
     * 三角形是固定的,位置数据不会改变,所以第一种即可
     */
    glBufferData(GL_ARRAY_BUFFER, sizeof(firstTriangle), firstTriangle, GL_STATIC_DRAW);
    //设置顶点属性指针
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //第二个数据源配置
    glBindVertexArray(VAOs[1]);
    glBindBuffer(GL_ARRAY_BUFFER,VBOs[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(secondTriangle),secondTriangle,GL_STATIC_DRAW);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3* sizeof(float ),(void *)0);
    glEnableVertexAttribArray(0);


    //渲染循环(Render Loop)
    /*
     * glfwWindowShouldClose  函数在我们每次循环的开始前检查一次GLFW是否被要求退出，如果是的话该函数返回true然后渲染循环便结束了，之后为我们就可以关闭应用程序了
     * glfwPollEvents 函数检查有没有触发什么事件（比如键盘输入、鼠标移动等）、更新窗口状态，并调用对应的回调函数（可以通过回调方法手动设置）。
     * glfwSwapBuffers 函数会交换颜色缓冲（它是一个储存着GLFW窗口每一个像素颜色值的大缓冲），它在这一迭代中被用来绘制，并且将会作为输出显示在屏幕上。
     */
    while (!glfwWindowShouldClose(window)) {
        TwoTriangle::processInput(window);
        //渲染指令
        //glClearColor函数是一个状态设置函数
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        //glClear 状态使用的函数
        glClear(GL_COLOR_BUFFER_BIT);
        //使用着色器
        glUseProgram(shaderProgram);
        glBindVertexArray(VAOs[0]);
        glDrawArrays(GL_TRIANGLES,0,3);

        glUseProgram(shaderProgram2);
        glBindVertexArray(VAOs[1]);
        glDrawArrays(GL_TRIANGLES,0,3);


        //检查并调用事件,交换缓冲
        glfwPollEvents();
        glfwSwapBuffers(window);

    }
    glDeleteVertexArrays(2,VAOs);
    glDeleteBuffers(2,VBOs);
    glDeleteProgram(shaderProgram);
    glDeleteProgram(shaderProgram2);


    //释放之前的分配的所有资源
    glfwTerminate();
    return 0;
}

void TwoTriangle::processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void TwoTriangle::framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    //告诉OpenGL渲染窗口的尺寸大小，即视口(Viewport)
    glViewport(0, 0, width, height);
}