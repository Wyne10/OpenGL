#include "input.h"

Input::InputBind::InputBind(GLFWwindow* window, int key, int actionKey, void (*action)(GLFWwindow* window))
{
	this->window = window;
	this->key = key;
	this->actionKey = actionKey;
	this->action = action;
}

Input::InputBind::~InputBind()
{
	delete window;
}

void Input::InputBind::processInput()
{
	if (glfwGetKey(window, key) == actionKey)
		action(window);
}

std::vector<Input::InputBind*> Input::createInputList(GLFWwindow* window)
{
	std::vector<InputBind*> binds;
	binds.push_back(new InputBind(window, GLFW_KEY_ESCAPE, GLFW_PRESS, [](GLFWwindow* window) { glfwSetWindowShouldClose(window, true); }));
	return binds;
}

void Input::processInput(std::vector<InputBind*> binds)
{
	for (auto start = binds.begin(); start != binds.end(); start++)
	{
		(*start)->processInput();
	}
}