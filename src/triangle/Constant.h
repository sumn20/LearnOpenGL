//
// Created by Sumn on 2021/10/20.
//

#ifndef LEARNOPENGL_CONSTANT_H
#define LEARNOPENGL_CONSTANT_H
//设置常量
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
//使用着色器语言配置顶点着色器
static const char *vertexShaderSource = "#version 330 core\n"
                                  "layout (location = 0) in vec3 aPos;\n"
                                  "void main()\n"
                                  "{\n"
                                  "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                  "}\0";
//配置片段着色器,颜色格式为RGBA 取值0.0-1.0
static const  char *fragmentShaderSource = "#version 330 core\n"
                                    "out vec4 FragColor;\n"
                                    "void main()\n"
                                    "{\n"
                                    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                                    "}\n\0";
static const char *fragmentShader2Source = "#version 330 core\n"
                                           "out vec4 FragColor;\n"
                                           "void main()\n"
                                           "{\n"
                                           "   FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
                                           "}\n\0";



#endif //LEARNOPENGL_CONSTANT_H
