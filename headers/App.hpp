#pragma once

#pragma region Include

#include "Engine.hpp"
#include "VulkanManager.hpp"

#pragma endregion


namespace Core
{
	class App
	{
	private :
		static App* instance;
		Engine* engine;
		Window* window;
		VulkanManager* vkManager;
		Camera* camera;

		bool shouldClose = false;
	
	public :

	private :
		
	public:
		/* Singleton operators  */
		static void Create();
		static void Destroy();
		static App* Get();


		/* App functions */
		void Run (const std::string windowName, const int windowWidth, const int windowHeight);
		bool Init(const std::string windowName, const int windowWidth, const int windowHeight);
		void Quit();
		void Release();
		void Render();

		/* UI Handler */
		void HandleInput();
	};
}