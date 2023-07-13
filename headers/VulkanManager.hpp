#pragma once

#include <vector>
#include <optional>
#include <set>
#include <algorithm>
#include <stdexcept>
#include <fstream>

#include "ImGUI/imgui.h"
#include "ImGUI/imgui_impl_glfw.h"
#include "ImGUI/imgui_impl_vulkan.h"

#include "Camera.hpp"
#include "Model.h"




namespace Core
{

#pragma region Structures



	struct QueueFamilyIndices
	{
		std::optional<uint32_t> graphicsFamily;
		std::optional<uint32_t> presentFamily;

		bool isComplete() { return graphicsFamily.has_value() && presentFamily.has_value(); }
	};

	struct SwapChainSupportDetails
	{
		VkSurfaceCapabilitiesKHR capabilities;
		std::vector<VkSurfaceFormatKHR> formats;
		std::vector<VkPresentModeKHR> presentModes;
	};

#pragma endregion

	class VulkanManager
	{
	private :
		Window* window;

		/* Vulkan variable */
		VkInstance vkInstance;
		VkDebugUtilsMessengerEXT vkDebugMessenger;
		VkDevice vkDevice;
		VkPhysicalDeviceFeatures vkDeviceFeatures{};
		VkQueue vkGraphicsQueue;
		VkSurfaceKHR vkSurface;
		VkQueue vkPresentQueue;
		VkSwapchainKHR vkSwapChain;
		std::vector<VkImage> vkSwapChainImages;
		VkFormat vkSwapChainImageFormat;
		VkExtent2D vkSwapChainExtent;
		std::vector<VkImageView> vkSwapChainImageViews;
		VkRenderPass vkRenderPass;
		VkPipelineLayout vkPipelineLayout;
		VkPipeline vkGraphicsPipeline;
		std::vector<VkFramebuffer> vkSwapChainFramebuffers;
		VkCommandPool vkCommandPool;
		std::vector<VkCommandBuffer> vkCommandBuffers;
		
		std::vector <VkSemaphore> vkImageAvailableSemaphores;
		std::vector <VkSemaphore> vkRenderFinishedSemaphores;
		std::vector <VkFence> vkInFlightFences;

		VkBuffer stagingBuffer;
		VkDeviceMemory stagingBufferMemory;

		VkImage depthImage;
		VkDeviceMemory depthImageMemory;
		VkImageView depthImageView;

		uint32_t currentFrame = 0;


		const std::vector<const char*> validationLayers = {
		"VK_LAYER_KHRONOS_validation"
		};

		const std::vector<const char*> deviceExtensions = {
		VK_KHR_SWAPCHAIN_EXTENSION_NAME
		};
		
		Camera* camera;

		/*ImGui*/
		ImGui_ImplVulkanH_Window g_MainWindowData;
		VkDescriptorPool pool;
		bool swapChainRebuild = false; 
		float windowWidth;
		float windowHeight;
	public:
		bool framebufferResized = false;
		VkDescriptorSetLayout vkDescriptorSetLayout;
		VkPhysicalDevice vkPhysicalDevice = VK_NULL_HANDLE;
		std::vector<Model*> modelList = {};

	private : 
		/* Private Vulkan functions */
		void InitVulkan();
		void CreateInstance();
		void CreateSurface();
		void SelectPhysicalDevice();
		void CreateLogicalDevice();
		void CreateSwapChain();
		void RecreateSwapChain();
		void CreateRenderPass();
		void CreateGraphicsPipeline();
		void CreateFramebuffers();
		void CreateCommandPool();
		void CreateCommandBuffers();
		void RecordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);
		void CreateSyncObjects();
		void DrawFrame();
		void CleanUpSwapChain();
		void CreateImageViews();

		void CreateDescriptorSetLayout();
		
		void CreateDepthResources();
		void LoadModels();

		VkShaderModule CreateShaderModule(const std::vector<char>& code);
		bool IsDeviceSuitable(VkPhysicalDevice devices);
		bool CheckDeviceExtensionSupport(VkPhysicalDevice device);
		QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device);
		SwapChainSupportDetails QuerySwapChainSupport(VkPhysicalDevice device);
		VkSurfaceFormatKHR ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
		VkPresentModeKHR ChooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
		VkExtent2D ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);

		
		VkCommandBuffer BeginSingleTimeCommands();
		void EndSingleTimeCommands(VkCommandBuffer commandBuffer);
		VkFormat FindSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);
		VkFormat FindDepthFormat();
		bool HasStencilComponent(VkFormat format);

		/* DEBUG Vulkan function */
		void SetupDebugMessenger();
		bool CheckValidationLayerSupport();
		std::vector<const char*> GetRequiredExtensions();
		void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator);
		void PopulateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);

		void Init_imgui();
	public :
		VulkanManager(Window* _window, Camera* cam);

		/* Public Vulkan functions */
		VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger);

		void CleanUpVulkan();
		uint32_t Render();
		void LoopImGui();

		/* Needed for model use */
		void CreateBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
		void CopyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
		void TransitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout);
		void CopyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height);
		uint32_t FindMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
		VkImageView CreateImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags);
		void CreateImage(uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory);

		/* Getter */
		VkDevice* GetDevice() { return &vkDevice; }
	};

};

