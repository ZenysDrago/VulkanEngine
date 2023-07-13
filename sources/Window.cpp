#include "Window.hpp"
#include "VulkanManager.hpp"

using namespace Core;


static void FramebufferResizeCallback(GLFWwindow* window, int width, int height) 
{
	auto app = reinterpret_cast<VulkanManager*>(glfwGetWindowUserPointer(window));
	app->framebufferResized = true;
}

Window* Window::Create(const std::string windowName, const int windowWidth, const int windowHeight)
{
	Window* window = new Window();
	window->name   = windowName;
	window->width  = windowWidth;
	window->height = windowHeight;

	glfwInit();
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	window->glfWindow = glfwCreateWindow(windowWidth, windowHeight, windowName.c_str(), nullptr, nullptr);
	glfwSetWindowUserPointer(window->glfWindow, window);
	glfwSetFramebufferSizeCallback(window->glfWindow, FramebufferResizeCallback);
	return window;
}

void Window::Destroy()
{
	glfwDestroyWindow(glfWindow);
	glfwTerminate();
}