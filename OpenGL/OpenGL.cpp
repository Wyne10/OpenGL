#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "window.h"
#include "input.h"
#include "shader.h"
#include "drawing.h"

using namespace Window;
using namespace Input;
using namespace Shaders;
using namespace Drawing;

void initGlfw();
void initGlad();

GLFWwindow* window;

int main()
{
#pragma region Init
    initGlfw();

    window = createWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "OpenGL");
    initGlad();
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
#pragma endregion

#pragma region Shaders
    Shader* vertexShader = new Shader("F:\\Coding\\C++\\OpenGL\\OpenGL\\vertex.vert", GL_VERTEX_SHADER, true);
    Shader* fragmentShader = new Shader("F:\\Coding\\C++\\OpenGL\\OpenGL\\fragment.frag", GL_FRAGMENT_SHADER, true);
    vertexShader->printError();
    fragmentShader->printError();

    Shader* shaders[] = { vertexShader, fragmentShader };

    ShaderProgram* shaderProgram = new ShaderProgram(shaders, 2);
    shaderProgram->printError();

    delete vertexShader;
    delete fragmentShader;
#pragma endregion

#pragma region Vertices
    float vertices[] = {
        // positions         // colors
         0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
        -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
         0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top 
    };
    float rectVertices[] = {
     0.5f,  0.5f, 0.0f,  // top right
     0.5f, -0.5f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f,  // bottom left
    -0.5f,  0.5f, 0.0f   // top left 
    };
    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    };
#pragma endregion

    Object* triangle = new Object(vertices, sizeof(vertices), GL_STATIC_DRAW);
    triangle->vertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    triangle->enableVertexAttribArray(0);
    triangle->vertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    triangle->enableVertexAttribArray(1);
    triangle->unbindBuffers();

    ElementObject* rectangle = new ElementObject(rectVertices, indices, sizeof(rectVertices), sizeof(indices), GL_STATIC_DRAW);
    rectangle->vertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    rectangle->enableVertexAttribArray(0);
    rectangle->unbindBuffers();

    std::vector<InputBind*> binds = createInputList(window);

    while (!glfwWindowShouldClose(window))
    {
        processInput(binds);
 
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shaderProgram->useProgram();

        //float timeValue = glfwGetTime();
        //float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
        //int vertexColorLocation = glGetUniformLocation(shaderProgram->getShaderProgram(), "ourColor");
        //glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

        //rectangle->draw(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        triangle->draw(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    delete triangle;
    delete rectangle;
    delete shaderProgram;

    glfwTerminate();
    return 0;
}

void initGlfw()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void initGlad()
{
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
    }
}