#include "Camera.hpp"

Camera::Camera(float width, float height)
{
	if (height == 0)
		height = 1;

	pos = { 2,2.5,1.7 };
	forward = { -0.6,-0.6,-0.4 };
	up = { 0,0,1 };
	rotation = { -24,-138,0 };
	
	UpdateViewMatrix(glm::lookAt(pos, pos + forward, up));
	UpdateProjMatrix(width, height);
}

void Camera::UpdateViewMatrix(glm::vec3 _pos, glm::vec3 _dir, glm::vec3 up)
{
	glm::vec3 direction;

	if (_dir == glm::vec3{ -1, -1, -1 })
	{
		_dir = dir;
		direction = _dir;
	}
	else
		direction = this->dir + _dir;

	glm::vec3 position = this->pos + _pos;

	const glm::vec3 w{ glm::normalize(direction)};
	const glm::vec3 u{ glm::normalize(glm::cross(w,up)) };
	const glm::vec3 v{ glm::cross(w,u) };

	view = glm::mat4{ 1.f };
	view[0][0] = u.x;
	view[1][0] = u.y;
	view[2][0] = u.z;

	view[0][1] = v.x;
	view[1][1] = v.y;
	view[2][1] = v.z;

	view[0][2] = w.x;
	view[1][2] = w.y;
	view[2][2] = w.z;

	view[3][0] = -glm::dot(u, position);
	view[3][1] = -glm::dot(v, position);
	view[3][2] = -glm::dot(w, position);

	this->pos = position;
	this->dir = direction;
}

void Camera::UpdateViewMatrix(glm::mat4 _mat)
{
	view = _mat;
}

void Camera::UpdateProjMatrix(const float width, const float height)
{
	proj = glm::perspective(glm::radians(45.f), width / (float)height, 0.1f, 10.0f);
}

void Camera::HandleInput(Core::Window* window, float deltaTime)
{
	if (glfwGetKey(window->GetGLFWindow(), GLFW_KEY_W) == GLFW_PRESS)
		pos += forward * deltaTime * moveSpeed;
	if (glfwGetKey(window->GetGLFWindow(), GLFW_KEY_S) == GLFW_PRESS)
		pos -= forward * deltaTime * moveSpeed;
	if (glfwGetKey(window->GetGLFWindow(), GLFW_KEY_A) == GLFW_PRESS)
		pos -= (glm::cross(forward, up)) * deltaTime * moveSpeed;
	if (glfwGetKey(window->GetGLFWindow(), GLFW_KEY_D) == GLFW_PRESS)
		pos += (glm::cross(forward, up)) * deltaTime * moveSpeed;


	// Mouse position.
	glm::vec2 mousePos;
	double mouseX, mouseY;
	glfwGetCursorPos(window->GetGLFWindow(), &mouseX, &mouseY);
	mousePos = -glm::vec2((float)mouseY, (float)mouseX);
	mousePos.x *= -1;

	glm::vec2 deltaMouse = glm::vec2{ 0,0 };
	if (oldMousePos != glm::vec2{ -1,-1 })
		deltaMouse = oldMousePos - mousePos;

	oldMousePos = mousePos;

	if (glfwGetMouseButton(window->GetGLFWindow(), GLFW_MOUSE_BUTTON_2))
	{
		rotation.x += deltaMouse.x * turnSpeed;
		rotation.y += deltaMouse.y * turnSpeed;

		if (rotation.x >= 89)
			rotation.x = 89;

		if (rotation.x <= -89)
			rotation.x = -89;

		glm::vec3 dir =
		{
			sin(glm::radians(rotation.y)) * cos(glm::radians(rotation.x)),
			cos(glm::radians(rotation.y)) * cos(glm::radians(rotation.x)),
			sin(glm::radians(rotation.x))
		};
		forward = glm::normalize(dir);

	}

	UpdateViewMatrix(glm::lookAt(pos, pos + forward, up));
}
