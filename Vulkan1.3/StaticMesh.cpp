#include "StaticMesh.h"
#include "Window.h"

StaticMesh::StaticMesh()
{
    CreateVertexBuffer();
    CreateIndexBuffer();
    CreateUniformBuffers();
    CreateDescriptorPool();
    CreateDescriptorSets();
}

StaticMesh::~StaticMesh()
{
    VkDevice& VulkanDevice = Statics::MainWindow->VulkanDevice;

    vkDestroyBuffer(VulkanDevice, VertexBuffer, nullptr);
    vkFreeMemory(VulkanDevice, VertexBufferMemory, nullptr);
    vkDestroyBuffer(VulkanDevice, IndexBuffer, nullptr);
    vkFreeMemory(VulkanDevice, IndexBufferMemory, nullptr);

    for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
        vkDestroyBuffer(VulkanDevice, UniformBuffers[i], nullptr);
        vkFreeMemory(VulkanDevice, UniformBuffersMemory[i], nullptr);
    }

    vkDestroyDescriptorPool(VulkanDevice, DescriptorPool, nullptr);
}

void StaticMesh::CreateVertexBuffer()
{
    VkDevice& VulkanDevice = Statics::MainWindow->VulkanDevice;
    Window* MainWindow = Statics::MainWindow;

    VkDeviceSize bufferSize = sizeof(Vertices[0]) * Vertices.size();

    VkBuffer stagingBuffer;
    VkDeviceMemory stagingBufferMemory;
    MainWindow->CreateBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);

    void* data;
    vkMapMemory(VulkanDevice, stagingBufferMemory, 0, bufferSize, 0, &data);
    memcpy(data, Vertices.data(), (size_t)bufferSize);
    vkUnmapMemory(VulkanDevice, stagingBufferMemory);

    MainWindow->CreateBuffer(bufferSize,
        VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
        VertexBuffer,
        VertexBufferMemory);

    MainWindow->CopyBuffer(stagingBuffer, VertexBuffer, bufferSize);

    vkDestroyBuffer(VulkanDevice, stagingBuffer, nullptr);
    vkFreeMemory(VulkanDevice, stagingBufferMemory, nullptr);
}

void StaticMesh::CreateIndexBuffer()
{
    VkDevice& VulkanDevice = Statics::MainWindow->VulkanDevice;
    Window* MainWindow = Statics::MainWindow;

    VkDeviceSize bufferSize = sizeof(Indices[0]) * Indices.size();

    VkBuffer stagingBuffer;
    VkDeviceMemory stagingBufferMemory;
    MainWindow->CreateBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);

    void* data;
    vkMapMemory(VulkanDevice, stagingBufferMemory, 0, bufferSize, 0, &data);
    memcpy(data, Indices.data(), (size_t)bufferSize);
    vkUnmapMemory(VulkanDevice, stagingBufferMemory);

    MainWindow->CreateBuffer(bufferSize,
        VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
        IndexBuffer,
        IndexBufferMemory);

    MainWindow->CopyBuffer(stagingBuffer, IndexBuffer, bufferSize);

    vkDestroyBuffer(VulkanDevice, stagingBuffer, nullptr);
    vkFreeMemory(VulkanDevice, stagingBufferMemory, nullptr);
}

void StaticMesh::CreateUniformBuffers()
{
    Window* MainWindow = Statics::MainWindow;
    VkDevice& VulkanDevice = Statics::MainWindow->VulkanDevice;

    VkDeviceSize bufferSize = sizeof(UniformBufferObject);

    UniformBuffers.resize(MAX_FRAMES_IN_FLIGHT);
    UniformBuffersMemory.resize(MAX_FRAMES_IN_FLIGHT);
    UniformBuffersMapped.resize(MAX_FRAMES_IN_FLIGHT);

    for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
        MainWindow->CreateBuffer(bufferSize, 
            VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, 
            UniformBuffers[i], 
            UniformBuffersMemory[i]);

        vkMapMemory(VulkanDevice, UniformBuffersMemory[i], 0, bufferSize, 0, &UniformBuffersMapped[i]);
    }
}

void StaticMesh::CreateDescriptorPool()
{
    VkDevice& VulkanDevice = Statics::MainWindow->VulkanDevice;

    VkDescriptorPoolSize poolSize{};
    poolSize.type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    poolSize.descriptorCount = static_cast<uint32_t>(MAX_FRAMES_IN_FLIGHT);

    VkDescriptorPoolCreateInfo poolInfo{};
    poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
    poolInfo.poolSizeCount = 1;
    poolInfo.pPoolSizes = &poolSize;
    poolInfo.maxSets = static_cast<uint32_t>(MAX_FRAMES_IN_FLIGHT);

    if (vkCreateDescriptorPool(VulkanDevice, &poolInfo, nullptr, &DescriptorPool) != VK_SUCCESS) {
        throw std::runtime_error("failed to create descriptor pool!");
    }
}

void StaticMesh::CreateDescriptorSets()
{
    Window* MainWindow = Statics::MainWindow;
    VkDevice& VulkanDevice = Statics::MainWindow->VulkanDevice;

    std::vector<VkDescriptorSetLayout> layouts(MAX_FRAMES_IN_FLIGHT, MainWindow->VulkanDescriptorSetLayout);
    VkDescriptorSetAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
    allocInfo.descriptorPool = DescriptorPool;
    allocInfo.descriptorSetCount = static_cast<uint32_t>(MAX_FRAMES_IN_FLIGHT);
    allocInfo.pSetLayouts = layouts.data();

    DescriptorSets.resize(MAX_FRAMES_IN_FLIGHT);
    if (vkAllocateDescriptorSets(VulkanDevice, &allocInfo, DescriptorSets.data()) != VK_SUCCESS) {
        throw std::runtime_error("failed to allocate descriptor sets!");
    }

    for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
        VkDescriptorBufferInfo bufferInfo{};
        bufferInfo.buffer = UniformBuffers[i];
        bufferInfo.offset = 0;
        bufferInfo.range = sizeof(UniformBufferObject);

        VkWriteDescriptorSet descriptorWrite{};
        descriptorWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
        descriptorWrite.dstSet = DescriptorSets[i];
        descriptorWrite.dstBinding = 0;
        descriptorWrite.dstArrayElement = 0;
        descriptorWrite.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
        descriptorWrite.descriptorCount = 1;
        descriptorWrite.pBufferInfo = &bufferInfo;

        vkUpdateDescriptorSets(VulkanDevice, 1, &descriptorWrite, 0, nullptr);
    }
}
