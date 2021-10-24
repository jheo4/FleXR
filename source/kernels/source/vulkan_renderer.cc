#include "kernels/source/vulkan_renderer.h"
#include "utils/msg_sending_functions.h"

namespace flexr::kernels
{

VulkanRenderer::VulkanRenderer(const std::string& id)
  : FleXRKernel {id}
{
  setName("VulkanRenderer");
  portManager.registerOutPortTag(
    "out", flexr::utils::sendLocalBasicCopy<VulkanRendererMsgType>, nullptr, nullptr);

  renderer.emplace(256, 256);
}

auto VulkanRenderer::run() -> raft::kstatus
{
  renderer->Tick();

  auto output = portManager.getOutputPlaceholder<VulkanRendererMsgType>("out");
  using namespace std::string_literals;
  output->data = "Rendered frame"s;
  std::strcpy(output->tag, "rendered_frame");
  debug_print("Rendered frame");
  portManager.sendOutput<VulkanRendererMsgType>("out", output);
  return raft::stop;
}

} // namespace flexr::kernels