
#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
//#include <GLFW/glfw3native.h>

#include <stdio.h>

#include "glUtils.hpp"
#include "utils.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

using namespace glm;

const int FILE_READ_LENGTH = 512;

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
    readFileData("../glsl/vertex.glsl", vertexCode, FILE_READ_LENGTH);
    readFileData("../glsl/fragment.glsl", fragmentCode, FILE_READ_LENGTH);
    printf("vertex Code: \n%s\n", vertexCode);
    printf("fragment Code: \n%s\n", fragmentCode);
    program = createProgram(vertexCode, fragmentCode);
    free(vertexCode);
    free(fragmentCode);

    const int VERTEX_STRIDE = 8;
    const GLfloat vertex[] = {
        // 顶点坐标         颜色                纹理坐标
        // -0.5f, 0.5f, 0,   1.0f, 0.5f, 0.0f,   0.0f,  2.0f,
        // -0.5f, -0.5f, 0,  0.5f, 0.5f, 0.0f,   0.0f,  0.0f,
        // 0.5f, -0.5f, 0,   0.0f, 0.5f, 0.0f,   3.0f,  0.0f,
        // 0.5f, 0.5f, 0,    0.0f, 0.5f, 1.0f,   3.0f,  2.0f,

        -0.5f, -0.5f, -0.5f, 1.0f, 0.5f, 0.0f,  0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  0.5f, 0.5f, 0.0f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  0.0f, 0.5f, 0.0f,  1.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  0.0f, 0.5f, 1.0f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f, 0.0f, 0.5f, 1.0f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 0.5f, 1.0f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 0.0f,  0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  0.0f, 0.5f, 1.0f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.0f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.0f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 0.0f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 0.0f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 0.0f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 0.0f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 0.0f,  1.0f, 0.0f,

        0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.0f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 0.0f,  1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f,  0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f,  0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.0f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f,  1.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f,  1.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 0.0f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 0.0f,  0.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 0.0f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.0f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.0f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 0.0f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 0.0f,  0.0f, 1.0f
    };


    const int indices[] = {
        0, 1, 2,
        0, 2, 3
    };

    // create VAO & VBO
    GLuint VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glBindVertexArray(0);

    // 获取支持的最大顶点数
    // int n;
    // glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &n);
    // printf("n=%d\n", n);

    // 游戏循环
    // static int count = 0;
    glfwSetKeyCallback(window, close_callback);
    while (! glfwWindowShouldClose(window)) {
        float now = glfwGetTime();

        // render
        glClearColor(1.0, 1.0, 0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // mode
        // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        // use program
        glUseProgram(program);
        glBindVertexArray(VAO);
        GLuint loc_a_Pos = glGetAttribLocation(program, "a_position");
        glEnableVertexAttribArray(loc_a_Pos);
        glVertexAttribPointer(loc_a_Pos, 3, GL_FLOAT, false, VERTEX_STRIDE*sizeof(GL_FLOAT), 0);
        GLuint loc_a_Col = glGetAttribLocation(program, "a_color");
        glEnableVertexAttribArray(loc_a_Col);
        glVertexAttribPointer(loc_a_Col, 3, GL_FLOAT, false, VERTEX_STRIDE*sizeof(GL_FLOAT), (void*)(3*sizeof(GL_FLOAT)));
        GLuint loc_a_TexCoord = glGetAttribLocation(program, "a_texCoord");
        glEnableVertexAttribArray(loc_a_TexCoord);
        glVertexAttribPointer(loc_a_TexCoord, 2, GL_FLOAT, false, VERTEX_STRIDE*sizeof(GL_FLOAT), (void*)(6*sizeof(GL_FLOAT)));

        // trans
// vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
mat4 trans = mat4(1.0f);
trans = translate(trans, vec3(0.5f, 0.5f, 0.0f));
trans = rotate(trans, radians(now*10), vec3(0.0f, 0.0f, 1.0f));
trans = scale(trans, vec3(1.5f, 0.5f, 2.0f));
// vec = trans * vec;
// printf("vec: %f, %f, %f\n", vec.x, vec.y, vec.z);        
        GLuint loc_u_Transform = glGetUniformLocation(program, "u_transform");
        glUniformMatrix4fv(loc_u_Transform, 1, false, value_ptr(trans));

// model view projection
mat4 matModel = mat4(1.0f);
mat4 matView = mat4(1.0f);
mat4 matProjection = mat4(1.0f);
matModel = rotate(matModel, radians(now*10), vec3(1.0f, 0.0f, 0.0f));
matView = translate(matView, vec3(0.0f, 0.0f, -3.0f));
matProjection = perspective(45.0f, (float)width/height, 0.1f, 100.0f);

        GLuint loc_u_Model = glGetUniformLocation(program, "u_model");
        GLuint loc_u_View = glGetUniformLocation(program, "u_view");
        GLuint loc_u_Proj = glGetUniformLocation(program, "u_projection");
        glUniformMatrix4fv(loc_u_Model, 1, false, value_ptr(matModel));
        glUniformMatrix4fv(loc_u_View, 1, false, value_ptr(matView));
        glUniformMatrix4fv(loc_u_Proj, 1, false, value_ptr(matProjection));

        // color
        float red = sin(now);
        // printf("now=%f, red=%f\n", now, red);
        GLuint loc_u_Col = glGetUniformLocation(program, "u_color");
        glUniform4f(loc_u_Col, red, 1.0f, 0.0f, 1.0f);
        GLuint loc_u_Tex = glGetUniformLocation(program, "u_texture");
        glUniform1i(loc_u_Tex, 0);
        GLuint loc_u_BackTex = glGetUniformLocation(program, "u_back_texture");
        glUniform1i(loc_u_BackTex, 1);

        // texture
        // printf("texW=%d, texH=%d, texChannel=%d\n", texW, texH, texChannel);
        GLuint tex2D;
        glGenTextures(1, &tex2D);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, tex2D);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // glTextureParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
        // glTextureParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
        // glTextureParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        // glTextureParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        int texW, texH, texChannel;
        stbi_set_flip_vertically_on_load(true);
        unsigned char* texBuffer = stbi_load("../texture/do.png", &texW, &texH, &texChannel, 0);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texW, texH, 0, GL_RGBA, GL_UNSIGNED_BYTE, texBuffer);
        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(texBuffer);
        //background
        GLuint backTex2D;
        glGenTextures(1, &backTex2D);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, backTex2D);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // glTextureParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
        // glTextureParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
        // glTextureParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        // glTextureParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        int backTexW, backTexH, backTexChannel;
        stbi_set_flip_vertically_on_load(true);
        unsigned char* backTexBuffer = stbi_load("../texture/mo.jpg", &backTexW, &backTexH, &backTexChannel, 0);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, backTexW, backTexH, 0, GL_RGB, GL_UNSIGNED_BYTE, backTexBuffer);
        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(backTexBuffer);
        
        // draw
        // glDrawArrays(GL_TRIANGLES, 1, 3); 
        glEnable(GL_DEPTH_TEST);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // after
        glDisableVertexAttribArray(loc_a_Pos);
        glDisableVertexAttribArray(loc_a_Col);
        glDisableVertexAttribArray(loc_a_TexCoord);
        glBindVertexArray(0);

        // swap buffer
        glfwSwapBuffers(window);
        // check events
        glfwPollEvents();
    }
    // delete program
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(program);

    // end
    glfwTerminate();
    return 0;  
}
