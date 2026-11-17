#pragma once

#include <cstdint>

#include <webgpu/wgpu.h>

#include "webgpu/buffer.hpp"
#include "webgpu/sampler.hpp"
#include "webgpu/texture_view.hpp"

namespace webgpu {

class Binding {
public:
  Binding() = default;

  explicit Binding(
      const Buffer &buffer,
      const Sampler &sampler,
      const TextureView &texture_view,
      const WGPUBindGroupEntry &binding_group_entry);

  const WGPUBindGroupEntry &Get();

private:
  Buffer buffer_;
  Sampler sampler_;
  TextureView texture_view_;
  WGPUBindGroupEntry binding_group_entry_ = WGPU_BIND_GROUP_ENTRY_INIT;
};

class BindingBuilder {
public:
  BindingBuilder &SetBinding(std::uint32_t value);

  BindingBuilder &SetBuffer(const Buffer &buffer, std::uint32_t size, std::uint64_t offset = 0);

  BindingBuilder &SetSampler(const Sampler &sampler);

  BindingBuilder &SetTextureView(const TextureView &texture_view);

  Binding Build() const;

private:
  Buffer buffer_;
  Sampler sampler_;
  TextureView texture_view_;
  WGPUBindGroupEntry binding_group_entry_ = WGPU_BIND_GROUP_ENTRY_INIT;
};

} // namespace webgpu
