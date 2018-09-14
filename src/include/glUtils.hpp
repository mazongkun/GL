/*
 * @Author: mazongkun 
 * @Date: 2018-09-13 14:37:31 
 * @Last Modified by: mazongkun
 * @Last Modified time: 2018-09-13 14:37:58
 */

#ifndef GLUTILS_HPP
#define GLUTILS_HPP

#include <stdio.h>
#include <GL/glew.h>

int checkCompileResult(int shader) {
    int success = 0;
    int logLength = 0;
    char * info = NULL;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (! success) {
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);
        info = (char*) malloc(logLength);
        glGetShaderInfoLog(shader, 512, NULL, info);
        printf("compile shader error: %s\n", info);
        free(info);
    }
    return success;
}

int checkLinkResult(int program) {
    int success = 0;
    int logLength = 0;
    char * info = NULL;
    glGetProgramiv(program, GL_LINK_STATUS, &success);

    if (! success) {
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);
        info = (char*) malloc(logLength);
        glGetProgramInfoLog(program, logLength, NULL, info);
        printf("link program error: %s\n", info);
        free(info);
    }
    return success;
}

int createProgram(const char * vertexCode, const char * fragmentCode) {
    int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexCode, NULL);
    glCompileShader(vertexShader);
    checkCompileResult(vertexShader);

    int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentCode, NULL);
    glCompileShader(fragmentShader);
    checkCompileResult(fragmentShader);

    unsigned int program = glCreateProgram();
    printf("program=%d\n", program);
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);

    glLinkProgram(program);
    checkLinkResult(program);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    return program;
}

#endif