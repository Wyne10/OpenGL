#pragma once
#include <GLFW/glfw3.h>
#include <vector>

namespace Input {
	class InputBind
	{
	private:
		GLFWwindow* window;
		int key;
		int actionKey;
		void (*action) (GLFWwindow*);
	public:
		InputBind(GLFWwindow* window, int key, int actionKey, void (*action)(GLFWwindow* window));
		~InputBind();
		void processInput();
	};

	std::vector<InputBind*> createInputList(GLFWwindow* window);
	void processInput(std::vector<InputBind*> binds);
}