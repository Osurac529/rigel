#include "webgpu/binding_builder.hpp"

namespace webgpu {

Binding::Binding(
    const Buffer &buffer,
    const Sampler &sampler,
    const TextureView &texture_view,
    const WGPUBindGroupEntry &binding_group_entry)
    : buffer_(buffer), sampler_(sampler), texture_view_(texture_view),
      binding_group_entry_(binding_group_entry) {}

const WGPUBindGroupEntry &Binding::Get() {
  binding_group_entry_.buffer = buffer_.handle();
  binding_group_entry_.sampler = sampler_.handle();
  binding_group_entry_.textureView = texture_view_.handle();

  return binding_group_entry_;
}

BindingBuilder &BindingBuilder::SetBinding(const std::uint32_t value) {
  binding_group_entry_.binding = value;

  return *this;
}

BindingBuilder &BindingBuilder::SetBuffer(
    const Buffer &buffer,
    const std::uint64_t size,
    const std::uint64_t offset) {
  buffer_ = buffer;
  binding_group_entry_.offset = offset;
  binding_group_entry_.size = size;

  return *this;
}

BindingBuilder &BindingBuilder::SetSampler(const Sampler &sampler) {
  sampler_ = sampler;

  return *this;
}

BindingBuilder &BindingBuilder::SetTextureView(const TextureView &texture_view) {
  texture_view_ = texture_view;

  return *this;
}

Binding BindingBuilder::Build() const {
  return Binding(buffer_, sampler_, texture_view_, binding_group_entry_);
}

} // namespace webgpu
