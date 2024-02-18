#pragma once
#ifndef _STATICMESH_H
#define _STATICMESH_H

#include "Statics.h"

struct Vertex
{
	glm::vec3 Position{};
	glm::vec3 Normal{};

	static VkVertexInputBindingDescription GetBindingDescription() {
		VkVertexInputBindingDescription bindingDescription{};
		bindingDescription.binding = 0;
		bindingDescription.stride = sizeof(Vertex);
		bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
		return bindingDescription;
	}
	static std::array<VkVertexInputAttributeDescription, 2> GetAttributeDescriptions() {
		std::array<VkVertexInputAttributeDescription, 2> attributeDescriptions{};

		attributeDescriptions[0].binding = 0;
		attributeDescriptions[0].location = 0;
		attributeDescriptions[0].format = VK_FORMAT_R32G32B32_SFLOAT;
		attributeDescriptions[0].offset = offsetof(Vertex, Position);

		attributeDescriptions[1].binding = 0;
		attributeDescriptions[1].location = 1;
		attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
		attributeDescriptions[1].offset = offsetof(Vertex, Normal);

		return attributeDescriptions;
	}
};

struct UniformBufferObject {
	glm::mat4 model;
	glm::mat4 view;
	glm::mat4 proj;
};

class StaticMesh
{
	friend class StaticMeshComponent;

public:
	StaticMesh();
	~StaticMesh();

protected:

	void CreateVertexBuffer();
	void CreateIndexBuffer();
	void CreateUniformBuffers();
	void CreateDescriptorPool();
	void CreateDescriptorSets();

	std::vector<Vertex> Vertices{
		{{-0.5f, -0.5f, 0.0f}, {}},
		{{0.5f, -0.5f, 0.0f}, {}},
		{{0.5f, 0.5f, 0.0f}, {}},
		{{-0.5f, 0.5f, 0.0f}, {}},
	};

	const std::vector<uint16_t> Indices{
	0, 1, 2, 2, 3, 0
	};

	VkBuffer VertexBuffer{};
	VkDeviceMemory VertexBufferMemory{};
	VkBuffer IndexBuffer{};
	VkDeviceMemory IndexBufferMemory{};

	std::vector<VkBuffer> UniformBuffers{};
	std::vector<VkDeviceMemory> UniformBuffersMemory{};
	std::vector<void*> UniformBuffersMapped{};

	VkDescriptorPool DescriptorPool{};
	std::vector<VkDescriptorSet> DescriptorSets{};
};
#endif

