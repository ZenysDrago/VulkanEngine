#pragma once
#include "Window.hpp"
#include <array>

const int MAX_FRAMES_IN_FLIGHT = 2;

namespace Core
{
	class VulkanManager;
}

struct Vertex {
	glm::vec3 pos;
	glm::vec3 color;
	glm::vec2 texCoord;

	static VkVertexInputBindingDescription getBindingDescription() {
		VkVertexInputBindingDescription bindingDescription{};
		bindingDescription.binding = 0;
		bindingDescription.stride = sizeof(Vertex);
		bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

		return bindingDescription;
	}

	static std::array<VkVertexInputAttributeDescription, 3> getAttributeDescriptions() {
		std::array<VkVertexInputAttributeDescription, 3> attributeDescriptions{};

		attributeDescriptions[0].binding = 0;
		attributeDescriptions[0].location = 0;
		attributeDescriptions[0].format = VK_FORMAT_R32G32B32_SFLOAT;
		attributeDescriptions[0].offset = offsetof(Vertex, pos);

		attributeDescriptions[1].binding = 0;
		attributeDescriptions[1].location = 1;
		attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
		attributeDescriptions[1].offset = offsetof(Vertex, color);

		attributeDescriptions[2].binding = 0;
		attributeDescriptions[2].location = 2;
		attributeDescriptions[2].format = VK_FORMAT_R32G32_SFLOAT;
		attributeDescriptions[2].offset = offsetof(Vertex, texCoord);

		return attributeDescriptions;
	}

	bool operator==(const Vertex& other) const {
		return pos == other.pos && color == other.color && texCoord == other.texCoord;
	}
};

struct UniformBufferObject {
	alignas(16) glm::mat4 model;
	alignas(16) glm::mat4 view;
	alignas(16) glm::mat4 proj;
};


namespace std {
	template<> struct hash<Vertex> {
		size_t operator()(Vertex const& vertex) const {
			return ((hash<glm::vec3>()(vertex.pos) ^ (hash<glm::vec3>()(vertex.color) << 1)) >> 1) ^ (hash<glm::vec2>()(vertex.texCoord) << 1);
		}
	};
}

class Model
{
private:
	VkDevice& vkDeviceRef;

	VkBuffer vertexBuffer;
	VkDeviceMemory vertexBufferMemory;
	VkBuffer indexBuffer;
	VkDeviceMemory indexBufferMemory;

	std::vector<VkBuffer> uniformBuffers;
	std::vector<VkDeviceMemory> uniformBuffersMemory;

	VkDescriptorPool vkDescriptorPool;
	VkDeviceMemory textureImageMemory;


	VkImageView textureImageView;
	VkSampler textureSampler;
	VkImage textureImage;

	std::vector<Vertex> vertices;
	std::vector<uint32_t> indices;


	std::string modelPath;
	std::string texturePath;

	Core::VulkanManager* vkManager;

	glm::mat4 modelMatrix;
public : 
	std::vector<VkDescriptorSet> vkDescriptorSets;
	std::vector<void*> uniformBuffersMapped;

private :
	void ParseModel();
	void CreateVertexBuffer();
	void CreateIndexBuffer();
	void CreateUniformBuffers();
	void CreateDescriptorSets();
	void CreateDescriptorPool();
	void CreateTextureImage();
	void CreateTextureSampler();
	void CreateTextureImageView();

public :

	Model(VkDevice& vkDevice, Core::VulkanManager* vulkanManager , std::string _modelPath, std::string _texturePath) : vkDeviceRef(vkDevice) 
	{
		vkManager = vulkanManager; 
		modelPath = _modelPath;
		texturePath = _texturePath;
		modelMatrix = glm::mat4(1.0f);

	}

	void LoadModel();
	void CleanModel();

	VkBuffer GetVertexBuffer() { return vertexBuffer; }
	VkBuffer GetIndexBuffer () { return indexBuffer ; }

	int GetIndicesSize() { return indices.size(); }
	int GetVerticesSize() { return vertices.size(); }

	glm::mat4 GetModelMatrix() { return modelMatrix; }

	void MoveModel(glm::vec3 _pos)					{ modelMatrix = glm::translate(modelMatrix, _pos); }
	void RotateModel(float angle, glm::vec3 axis)	{ modelMatrix = glm::rotate(modelMatrix, angle, axis); }
	void ScaleModel	(glm::vec3 _scale)				{ modelMatrix = glm::scale(modelMatrix, _scale); }

};

