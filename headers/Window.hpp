#pragma once

#include <iostream>
#include <string>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

/*If GLM */
#define GLM_FORCE_DEFAULT_ALIGNED_GENTYPES
#define GLM_ENABLE_EXPERIMENTAL
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/hash.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

namespace Core
{
	class Window
	{
	private :
		std::string name;
		int width;
		int height;
		GLFWwindow* glfWindow = nullptr;

	public :
		static Window* Create(const std::string windowName, const int windowWidth, const int windowHeight);
		void Destroy();
		GLFWwindow* GetGLFWindow() { return glfWindow; }
		std::string GetName() { return name; }
	};
}