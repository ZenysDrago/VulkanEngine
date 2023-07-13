#include "App.hpp"

using namespace Core;

App* App::instance = nullptr;

#pragma region SingletonFunction

/* Singleton operators  */
void App::Create()
{
	if (!instance)
		instance = new App;
}

void App::Destroy()
{
	if (!instance)
		delete instance;
} 

App* App::Get()
{
	return instance;
}
#pragma endregion

#pragma region Private

#pragma endregion

#pragma region Public
/* App functions */
void  App::Run(const std::string windowName, const int windowWidth, const int windowHeight)
{
	if (Init(windowName, windowWidth, windowHeight))
	{
		while (!glfwWindowShouldClose(window->GetGLFWindow()) && !shouldClose)
		{
			glfwPollEvents();

			HandleInput();
			engine->Update();
			Render();
		}
		vkDeviceWaitIdle(*vkManager->GetDevice());
	}
	else
	{
		Quit();
	}
}

void App::Quit()
{
	shouldClose = true;
}

bool App::Init(const std::string windowName, const int windowWidth, const int windowHeight)
{
	/*TODO init application */
	window = Window::Create(windowName, windowWidth, windowHeight);
	camera = new Camera(0,0);

	vkManager = new VulkanManager(window, camera); /* need to be called after window create */
	engine = new Engine(camera, vkManager);
	return true;
}

void App::Release()
{
	//ImGui_ImplVulkan_Shutdown();
	//ImGui_ImplGlfw_Shutdown();
	//ImGui::DestroyContext();

	engine->Destroy();
	delete engine;

	vkManager->CleanUpVulkan();
	delete vkManager;

	delete camera;

	/* Window cleanup */
	window->Destroy();
	delete window;
}

void App::Render()
{
	/* ImGUi not implemented but should be here */

	/*ImGui_ImplVulkan_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	ImGui::Render();
	ImDrawData* draw_data = ImGui::GetDrawData();*/
}

void App::HandleInput()
{
	if (glfwGetKey(window->GetGLFWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		Quit();
		return;
	}

	camera->HandleInput(window, engine->deltaTime);	
}

#pragma endregion