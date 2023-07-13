#pragma once
#include <chrono>
#include <VulkanManager.hpp>

namespace Core
{
	class Engine
	{
	private:
		Camera* camera;
		VulkanManager* vkManager;
		int curImage;

	public:
		static float deltaTime;
		Engine(Camera* cam, VulkanManager* vulkanManager) { camera = cam; vkManager = vulkanManager; }

		void Awake();
		void Start();
		void Update();
		void Destroy();
		void UpdateUniformBuffer(Model* model, uint32_t currentImage);

	};
}