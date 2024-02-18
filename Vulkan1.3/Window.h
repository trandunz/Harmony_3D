#pragma once
#ifndef _WINDOW_H
#define _WINDOW_H

#include "Statics.h"

#define WINDOW_WIDTH_DEFAULT 800
#define WINDOW_HEIGHT_DEFAULT 600
#define MAX_FRAMES_IN_FLIGHT 2
#define ENABLE_ACTIVATION_LAYERS false

struct QueueFamilyIndices 
{
	std::optional<uint32_t> GraphicsFamily;
	std::optional<uint32_t> PresentFamily;

	bool IsComplete();
};

struct SwapChainSupportDetails 
{
	VkSurfaceCapabilitiesKHR Capabilities;
	std::vector<VkSurfaceFormatKHR> Formats;
	std::vector<VkPresentModeKHR> PresentModes;
};

class Window
{
public:
	inline static Window& Get() {
		static Window Instance;
		return Instance;
	}
	static std::vector<char> ReadFile(const std::string& Filename);
	static VKAPI_ATTR VkBool32 VKAPI_CALL VulkanDebugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData);
	static void FramebufferResizeCallback(GLFWwindow* window, int width, int height);

	int Cleanup();
	void CleanupSwapChain();

	void Init();
	void Draw();

	VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger);
	void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator);
	void PopulateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
	void InitDebugMessenger();

	void CreateVulkanInstance();
	void CreateSurface();
	void PickPhysicalDevice();
	void CreateLogicalDevice();
	void CreateSwapChain();
	void RecreateSwapChain();
	void CreateImageViews();
	void CreateRenderPass();
	void CreateDescriptorSetLayout();
	void CreateGraphicsPipeline();
	void CreateFramebuffers();
	void CreateCommandPool();

	//
	void CreateBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
	void CopyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
	//

	void CreateCommandBuffers();
	void CreateSyncObjects();
	void GrabExtensions();

	void RecordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);

	VkShaderModule CreateShaderModule(const std::vector<char>& code);

	VkSurfaceFormatKHR ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);

	VkPresentModeKHR ChooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);

	VkExtent2D ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);

	SwapChainSupportDetails QuerySwapChainSupport(VkPhysicalDevice device);

	bool IsDeviceSuitable(VkPhysicalDevice device);

	bool CheckDeviceExtensionSupport(VkPhysicalDevice device);

	QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device);

	std::vector<const char*> GetRequiredExtensions();

	bool CheckValidationLayerSupport();

	uint32_t FindMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);

	struct GLFWwindow* GlfwWindow{ nullptr };

	VkInstance VulkanInstance{};
	VkDebugUtilsMessengerEXT VulkanDebugMessenger;
	VkSurfaceKHR VulkanSurface;

	VkPhysicalDevice VulkanPhysicalDevice{ VK_NULL_HANDLE };
	VkDevice VulkanDevice;

	VkQueue VulkanGraphicsQueue;
	VkQueue VulkanPresentQueue;

	VkSwapchainKHR VulkanSwapChain;
	std::vector<VkImage> VulkanSwapChainImages;
	VkFormat VulkanSwapChainImageFormat;
	VkExtent2D VulkanSwapChainExtent;
	std::vector<VkImageView> VulkanSwapChainImageViews;
	std::vector<VkFramebuffer> VulkanSwapChainFramebuffers;

	VkRenderPass VulkanRenderPass;
	VkDescriptorSetLayout VulkanDescriptorSetLayout;
	VkPipelineLayout VulkanPipelineLayout;
	VkPipeline VulkanGraphicsPipeline;

	VkCommandPool VulkanCommandPool;
	std::vector<VkCommandBuffer> VulkanCommandBuffers;

	std::vector<VkSemaphore> VulkanImageAvailableSemaphores;
	std::vector<VkSemaphore> VulkanRenderFinishedSemaphores;
	std::vector<VkFence> VulkanInFlightFences;
	uint32_t CurrentFrame{};

	bool FramebufferResized{};

	const std::vector<const char*> ValidationLayers{
		"VK_LAYER_KHRONOS_validation"
	};

	const std::vector<const char*> DeviceExtensions{
		VK_KHR_SWAPCHAIN_EXTENSION_NAME
	};
};
#endif 

