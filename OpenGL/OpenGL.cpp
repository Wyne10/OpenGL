#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "window.h"
#include "input.h"
#include "shader.h"

using namespace Window;
using namespace Input;
using namespace Shaders;

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
    Shader* vertexShader = new Shader("#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "}\0", GL_VERTEX_SHADER);
    Shader* fragmentShader = new Shader("#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
        "}\n\0", GL_FRAGMENT_SHADER);
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
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
    };

    GLuint VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
#pragma endregion

    std::vector<InputBind*> binds = createInputList(window);

    while (!glfwWindowShouldClose(window))
    {
        processInput(binds);
 
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shaderProgram->useProgram();
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

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