//
// Created by Sumn on 2021/10/21.
//

#include "TextureTriangle.h"
#include <iostream>
#include "Constant.h"
#include "stb_image.h"
//顶点着色器
const char *textureVertexShaderSource="#version 330 core\n"
                                      "layout(location=0) in vec3 aPos;\n"
                                      "layout(location=1) in vec3 aColor;\n"
                                      "layout(location=2) in vec2 aTexCoord;\n"
                                      "out vec3 ourColor;\n"
                                      "out vec2 TexCoord;\n"
                                      "void main()\n"
                                      "{"
                                      "gl_Position = vec4(aPos,1.0);\n"
                                      "ourColor= aColor;\n"
                                      "TexCoord=vec2(aTexCoord.x,aTexCoord.y);\n"
                                      "}"
                                      ;
const  char *textureFragmentShaderSource ="#version 330 core\n"
                                          "out vec4 FragColor;\n"
                                          "in vec3 ourColor;\n"
                                          "in vec2 TexCoord;\n"
                                          "uniform sampler2D ourTexture;\n"
                                          "void main()\n"
                                          "{"
                                          "FragColor=texture(ourTexture,TexCoord)*vec4(ourColor,1.0);\n"
                                          "}";



int TextureTriangle::init() {

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
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
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
    glShaderSource(vertexShader,1,&textureVertexShaderSource,nullptr);
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
    glShaderSource(fragmentShader,1,&textureFragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);
    //检测片段着色器是否正常编译且能使用
    glGetShaderiv(fragmentShader,GL_COMPILE_STATUS,&success);
    if (!success){
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
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
    //链接成功后,删除着色器,因为着色器程序中已经有着色器了
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    /**
     * 设定顶点数据并加载到GPU缓冲中
     */
    //顶点坐标集合
    float vertices[] = {
            // positions          // colors           // texture coords
            0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
            0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
            -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
            -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left
    };
    unsigned int indices[] = {
            0, 1, 3, // first triangle
            1, 2, 3  // second triangle
    };
    /*
     * 顶点缓冲对象(Vertex Buffer Objects, VBO):
     * 它会在GPU内存（通常被称为显存）中储存大量顶点。使用这些缓冲对象的好处是我们可以一次性的发送一大批数据到显卡上，而不是每个顶点发送一次。从CPU把数据发送到显卡相对较慢，所以只要可能我们都要尝试尽量一次性发送尽可能多的数据。当数据发送至显卡的内存中后，顶点着色器几乎能立即访问顶点，这是个非常快的过程。
     */
    unsigned int VBO,VAO,EBO;
    glGenVertexArrays(1,&VAO);
    //通过glGenBuffers函数和一个缓冲ID生成一个VBO对象
    glGenBuffers(1, &VBO);
    glGenBuffers(1,&EBO);
    //绑定VAO
    glBindVertexArray(VAO);
    //OpenGl有很多缓冲对象类型,顶点缓冲对象的类型是GL_ARRAY_BUFFER
    //将新创建的缓冲绑定到GL_ARRAY_BUFFER目标上
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //将定义的顶点坐标复制到GL_ARRAY_BUFFER缓冲内存中,此时GL_ARRAY_BUFFER=VBO;
    /*
     * 第四个参数指定了我们希望显卡如何管理给定的数据。它有三种形式：
     * GL_STATIC_DRAW ：数据不会或几乎不会改变。
     * GL_DYNAMIC_DRAW：数据会被改变很多。
     * GL_STREAM_DRAW ：数据每次绘制时都会改变
     * 三角形是固定的,位置数据不会改变,所以第一种即可
     */
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices),indices,GL_STATIC_DRAW);


    //设置顶点属性指针
    //坐标属性
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    //颜色属性
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,8* sizeof(float ),(void *)(3* sizeof(float )));
    glEnableVertexAttribArray(1);
    //纹理属性
    glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,8* sizeof(float ),(void *)(6* sizeof(float )));
    glEnableVertexAttribArray(2);
    /**
     * Texture 创建
     */
    unsigned int texture;
    glGenTextures(1,&texture);
    glBindTexture(GL_TEXTURE_2D,texture);
    //纹理过滤设置
    //每个选项都可以使用glTexParameter*函数对单独的一个坐标轴设置（s、t（如果是使用3D纹理那么还有一个r）它们和x、y、z是等价的）：
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
    //进行放大(Magnify)和缩小(Minify)操作的时候可以设置纹理过滤的选项
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

    int width, height, nrChannels;
    // The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
    unsigned char *data = stbi_load("../res/container.jpg", &width, &height, &nrChannels, 0);
    if (data)
    {
        std::cout << "bindTexture\n" << std::endl;
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
    //渲染循环(Render Loop)
    /*
     * glfwWindowShouldClose  函数在我们每次循环的开始前检查一次GLFW是否被要求退出，如果是的话该函数返回true然后渲染循环便结束了，之后为我们就可以关闭应用程序了
     * glfwPollEvents 函数检查有没有触发什么事件（比如键盘输入、鼠标移动等）、更新窗口状态，并调用对应的回调函数（可以通过回调方法手动设置）。
     * glfwSwapBuffers 函数会交换颜色缓冲（它是一个储存着GLFW窗口每一个像素颜色值的大缓冲），它在这一迭代中被用来绘制，并且将会作为输出显示在屏幕上。
     */
    while (!glfwWindowShouldClose(window)) {
        processInput(window);
        //渲染指令
        //glClearColor函数是一个状态设置函数
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        //glClear 状态使用的函数
        glClear(GL_COLOR_BUFFER_BIT);

        glBindTexture(GL_TEXTURE_2D,texture);
        //使用着色器
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


        //检查并调用事件,交换缓冲
        glfwPollEvents();
        glfwSwapBuffers(window);

    }
    glDeleteVertexArrays(1,&VAO);
    glDeleteBuffers(1,&VBO);
    glDeleteBuffers(1,&EBO);
    glDeleteProgram(shaderProgram);


    //释放之前的分配的所有资源
    glfwTerminate();
    return 0;
}
void TextureTriangle::framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    //告诉OpenGL渲染窗口的尺寸大小，即视口(Viewport)
    glViewport(0, 0, width, height);
}

void TextureTriangle::processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

