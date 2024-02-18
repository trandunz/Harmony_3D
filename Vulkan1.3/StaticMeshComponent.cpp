#include "StaticMeshComponent.h"
#include "StaticMesh.h"
#include "Window.h"
#include "CameraComponent.h"

StaticMeshComponent::StaticMeshComponent(StaticMesh* StaticMesh)
{
    AssignedStaticMesh = StaticMesh;
}

void StaticMeshComponent::UpdateUniformBuffer(uint32_t currentImage)
{
    if (IsValid(AssignedStaticMesh) == false)
        return;

    Window* MainWindow = Statics::MainWindow;

    UniformBufferObject ubo{};
    ubo.model = GetTransformMatrix();
    ubo.view = Statics::ActiveCamera->GetViewMatrix();
    ubo.proj = Statics::ActiveCamera->GetProjectionMatrix();
    ubo.proj[1][1] *= -1;

    memcpy(AssignedStaticMesh->UniformBuffersMapped[currentImage], &ubo, sizeof(ubo));
}

void StaticMeshComponent::Draw()
{
	if (IsValid(AssignedStaticMesh) == false)
		return;

    UpdateUniformBuffer(Statics::MainWindow->CurrentFrame);

    VkCommandBuffer& CommandBuffer = Statics::MainWindow->VulkanCommandBuffers[Statics::MainWindow->CurrentFrame];
   
    VkBuffer vertexBuffers[] = { AssignedStaticMesh->VertexBuffer };
    VkDeviceSize offsets[] = { 0 };
    vkCmdBindVertexBuffers(CommandBuffer, 0, 1, vertexBuffers, offsets);
    vkCmdBindIndexBuffer(CommandBuffer, AssignedStaticMesh->IndexBuffer, 0, VK_INDEX_TYPE_UINT16);

    vkCmdBindDescriptorSets(CommandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, Statics::MainWindow->VulkanPipelineLayout, 0, 1, &AssignedStaticMesh->DescriptorSets[Statics::MainWindow->CurrentFrame], 0, nullptr);

    vkCmdDrawIndexed(CommandBuffer, static_cast<uint32_t>(AssignedStaticMesh->Indices.size()), 1, 0, 0, 0);
}
