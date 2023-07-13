#include "Engine.hpp"

using namespace Core;
float Engine::deltaTime = 0;

void Engine::Awake()
{
	 
}

void Engine::Start()
{

}

void Engine::Update()
{
	static auto startTime = std::chrono::high_resolution_clock::now();

	auto currentTime = std::chrono::high_resolution_clock::now();
	deltaTime = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - startTime).count();

	for (Model* model : vkManager->modelList)
	{
		UpdateUniformBuffer(model, curImage);	
	}
	curImage = vkManager->Render();

	startTime = std::chrono::high_resolution_clock::now();
}

void Engine::UpdateUniformBuffer(Model* model , uint32_t currentImage)
{
	model->RotateModel(deltaTime * glm::radians(90.0f), glm::vec3{ 0,0,1 });

	UniformBufferObject ubo{};
	ubo.model = model->GetModelMatrix();
	ubo.view = camera->GetViewMatrix();
	ubo.proj = camera->GetProjectionMatrix();
	ubo.proj[1][1] *= -1;

	memcpy(model->uniformBuffersMapped[currentImage], &ubo, sizeof(ubo));
}

void Engine::Destroy()
{

}