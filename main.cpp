
#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>
//#include <GLFW/glfw3native.h>

#include <stdio.h>

void close_callback(GLFWwindow * window, int key, int scanCode, int action, int mode) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

int main(void)  
{  
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

    // 游戏循环
    glfwSetKeyCallback(window, close_callback);
    while (! glfwWindowShouldClose(window)) {
        // check events
        glfwPollEvents();

        // render
        glClearColor(0xFF, 0xFF, 0x00, 0xFF);
        glClear(GL_COLOR_BUFFER_BIT);

        // swap buffer
        glfwSwapBuffers(window);
    }

    glfwTerminate();

    return 0;  
}
