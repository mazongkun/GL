
#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
//#include <GLFW/glfw3native.h>

#include <stdio.h>

#include "glUtils.hpp"
#include "utils.hpp"

using namespace glm;

const int FILE_READ_LENGTH = 256;
const GLfloat vertex[] = {
    -0.5f, 0.5f, 0,
    -0.5f, -0.5f, 0,
    0.5f, 0, 0
};

void close_callback(GLFWwindow * window, int key, int scanCode, int action, int mode) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

int main(void)  
{  
    char * vertexCode = NULL;
    char * fragmentCode = NULL;
    int program;

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE); 

    // 创建窗口
    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        perror("Failed to create GLFW window\n");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // glew
    glewExperimental = true;
    if (glewInit() != GLEW_OK) {
        perror("Failed to initialize GLEW\n");
        return -1;
    }

    // glfw
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
    printf("width=%d, height=%d\n", width, height);

    // create program
    vertexCode   = (char*)malloc(FILE_READ_LENGTH);
    fragmentCode = (char*)malloc(FILE_READ_LENGTH);
    readFileData("glsl/vertex.glsl", vertexCode, FILE_READ_LENGTH);
    readFileData("glsl/fragment.glsl", fragmentCode, FILE_READ_LENGTH);
    program = createProgram(vertexCode, fragmentCode);
    free(vertexCode);
    free(fragmentCode);

    

    // 游戏循环
    glfwSetKeyCallback(window, close_callback);
    while (! glfwWindowShouldClose(window)) {
        // check events
        glfwPollEvents();

        // render
        glClearColor(1.0, 1.0, 0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);

        // use program
        glUseProgram(program);
    GLuint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_STATIC_DRAW);

    GLuint posPos = glGetAttribLocation(program, "position");
    glEnableVertexAttribArray(posPos);
    glVertexAttribPointer(posPos, 3, GL_FLOAT, false, 3*sizeof(GL_FLOAT), vertex);
    GLuint colPos = glGetUniformLocation(program, "color");
    glUniform4f(colPos, 1.0, 0.5, 0, 1.0);
        glDrawArrays(GL_TRIANGLES, 0, 3);        



        // swap buffer
        glfwSwapBuffers(window);
    }
    // delete program
    glDeleteProgram(program);

    // end
    glfwTerminate();
    return 0;  
}
