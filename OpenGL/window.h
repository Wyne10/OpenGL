#pragma once
#include <GLFW/glfw3.h>

namespace Window {
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

	GLFWwindow* createWindow(int width, int height, const char* title);
}