cmake_minimum_required(VERSION 3.20)
project(LearnOpenGL)
# c++标准版本
set(CMAKE_CXX_STANDARD 11)
#设置一些OpenGL头文件所在目录的宏
set(GLEW_H /usr/local/Cellar/glew/2.2.0_1/include/GL)
set(GLFW_H /usr/local/Cellar/glfw/3.3.4/include/GLFW)
set(GLAD_H /usr/local/include/)
set(GLAD_H /usr/local/include/glad)
set(KH_H /usr/local/include/KHR)


#包含上述头文件所在目录
include_directories(${GLEW_H}
        ${GLFW_H}
        ${GLAD_H}
        ${KH_H}
        include
        src
        src/triangle
        src/change
        src/coordinate
        src/test
        include/glm
        include/glm/detail
        include/glm/ext
        include/glm/gtc
        include/glm/gtx
        include/glm/simd
        )
#设置OpenGL库所在位置，并链接
set(GLEW_LINK /usr/local/Cellar/glew/2.2.0_1/lib/libGLEW.2.2.0.dylib)
set(GLFW_LINK /usr/local/Cellar/glfw/3.3.4/lib/libglfw.3.3.dylib)
link_libraries(
        ${OPENGL}
        ${GLEW_LINK}
        ${GLFW_LINK})

# 保存目录变量
aux_source_directory(. DIR_root)
aux_source_directory(./src DIR_src)
aux_source_directory(./src/triangle DIR_TRIANGLE)
aux_source_directory(./src/change DIR_CHANGE)
aux_source_directory(./src/coordinate DIR_COORDINATE)
aux_source_directory(./src/test DIR_TEST)
add_executable(LearnOpenGL
        ${DIR_root}
        ${DIR_src}
        ${DIR_TRIANGLE}
        ${DIR_CHANGE}
        ${DIR_COORDINATE}
        ${DIR_TEST}
        )
add_custom_target(Custom
        res
        )


# mac下这步很重要
if (APPLE)
    target_link_libraries(LearnOpenGL "-framework OpenGL")
    target_link_libraries(LearnOpenGL "-framework GLUT")
endif()