#pragma once
#include "Window.hpp"

class Camera
{
private:
	glm::mat4 proj;
	glm::mat4 view;

	glm::vec3 pos{ 0.f };
	glm::vec3 dir{ 0.f }; // rotation

	glm::vec3 forward, up;
	glm::vec3 rotation;
	glm::vec2 oldMousePos = { -1 , -1 };

	float turnSpeed = 0.5f;
	float moveSpeed = 100.f;

public:
	Camera(float width, float height);

	void UpdateViewMatrix(glm::vec3 _pos, glm::vec3 _dir = {-1,-1,-1}, glm::vec3 _up = { 0.f,0.f, -1.f });
	void UpdateViewMatrix(glm::mat4 _mat);

	void UpdateProjMatrix(const float width, const float height);
	void HandleInput(Core::Window* window, float deltaTime);

	glm::mat4 GetProjectionMatrix() { return proj; }
	glm::mat4 GetViewMatrix() { return view; }
};