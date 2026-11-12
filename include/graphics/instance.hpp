#pragma once

#include <vector>

#include <webgpu/wgpu.h>

#include "graphics/adapter.hpp"

namespace rigel::graphics {

class Window;
class Surface;
class Adapter;

class Instance {
public:
  explicit Instance(const WGPUInstanceDescriptor &descriptor = WGPU_INSTANCE_DESCRIPTOR_INIT);

  Instance(const Instance &);
  Instance &operator=(const Instance &);

  Instance(Instance &&) = default;
  Instance &operator=(Instance &&) = default;

  ~Instance();

  std::vector<Adapter> EnumerateAdapters(
      WGPUInstanceEnumerateAdapterOptions options = {
          .nextInChain = nullptr,
          .backends = WGPUInstanceBackend_All,
      }) const;

  Adapter ChooseAdapter();

  Surface CreateSurface(const Window &window);

private:
  WGPUInstance instance_;
};

} // namespace rigel::graphics
