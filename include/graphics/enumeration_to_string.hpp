#pragma once

#include <iosfwd>
#include <stdexcept>
#include <string_view>

#include <webgpu/wgpu.h>

std::string_view ToString(const WGPUAdapterType value);
std::ostream &operator<<(std::ostream &out, const WGPUAdapterType value);

std::string_view ToString(const WGPUAddressMode value);
std::ostream &operator<<(std::ostream &out, const WGPUAddressMode value);

std::string_view ToString(const WGPUBackendType value);
std::ostream &operator<<(std::ostream &out, const WGPUBackendType value);

std::string_view ToString(const WGPUBlendFactor value);
std::ostream &operator<<(std::ostream &out, const WGPUBlendFactor value);

std::string_view ToString(const WGPUBlendOperation value);
std::ostream &operator<<(std::ostream &out, const WGPUBlendOperation value);

std::string_view ToString(const WGPUBufferBindingType value);
std::ostream &operator<<(std::ostream &out, const WGPUBufferBindingType value);

std::string_view ToString(const WGPUBufferMapState value);
std::ostream &operator<<(std::ostream &out, const WGPUBufferMapState value);

std::string_view ToString(const WGPUCallbackMode value);
std::ostream &operator<<(std::ostream &out, const WGPUCallbackMode value);

std::string_view ToString(const WGPUCompareFunction value);
std::ostream &operator<<(std::ostream &out, const WGPUCompareFunction value);

std::string_view ToString(const WGPUCompilationInfoRequestStatus value);
std::ostream &operator<<(std::ostream &out, const WGPUCompilationInfoRequestStatus value);

std::string_view ToString(const WGPUCompilationMessageType value);
std::ostream &operator<<(std::ostream &out, const WGPUCompilationMessageType value);

std::string_view ToString(const WGPUComponentSwizzle value);
std::ostream &operator<<(std::ostream &out, const WGPUComponentSwizzle value);

std::string_view ToString(const WGPUCompositeAlphaMode value);
std::ostream &operator<<(std::ostream &out, const WGPUCompositeAlphaMode value);

std::string_view ToString(const WGPUCreatePipelineAsyncStatus value);
std::ostream &operator<<(std::ostream &out, const WGPUCreatePipelineAsyncStatus value);

std::string_view ToString(const WGPUCullMode value);
std::ostream &operator<<(std::ostream &out, const WGPUCullMode value);

std::string_view ToString(const WGPUDeviceLostReason value);
std::ostream &operator<<(std::ostream &out, const WGPUDeviceLostReason value);

std::string_view ToString(const WGPUErrorFilter value);
std::ostream &operator<<(std::ostream &out, const WGPUErrorFilter value);

std::string_view ToString(const WGPUErrorType value);
std::ostream &operator<<(std::ostream &out, const WGPUErrorType value);

std::string_view ToString(const WGPUFeatureLevel value);
std::ostream &operator<<(std::ostream &out, const WGPUFeatureLevel value);

std::string_view ToString(const WGPUFeatureName value);
std::ostream &operator<<(std::ostream &out, const WGPUFeatureName value);

std::string_view ToString(const WGPUFilterMode value);
std::ostream &operator<<(std::ostream &out, const WGPUFilterMode value);

std::string_view ToString(const WGPUFrontFace value);
std::ostream &operator<<(std::ostream &out, const WGPUFrontFace value);

std::string_view ToString(const WGPUIndexFormat value);
std::ostream &operator<<(std::ostream &out, const WGPUIndexFormat value);

std::string_view ToString(const WGPUInstanceFeatureName value);
std::ostream &operator<<(std::ostream &out, const WGPUInstanceFeatureName value);

std::string_view ToString(const WGPULoadOp value);
std::ostream &operator<<(std::ostream &out, const WGPULoadOp value);

std::string_view ToString(const WGPUMapAsyncStatus value);
std::ostream &operator<<(std::ostream &out, const WGPUMapAsyncStatus value);

std::string_view ToString(const WGPUMipmapFilterMode value);
std::ostream &operator<<(std::ostream &out, const WGPUMipmapFilterMode value);

std::string_view ToString(const WGPUOptionalBool value);
std::ostream &operator<<(std::ostream &out, const WGPUOptionalBool value);

std::string_view ToString(const WGPUPopErrorScopeStatus value);
std::ostream &operator<<(std::ostream &out, const WGPUPopErrorScopeStatus value);

std::string_view ToString(const WGPUPowerPreference value);
std::ostream &operator<<(std::ostream &out, const WGPUPowerPreference value);

std::string_view ToString(const WGPUPredefinedColorSpace value);
std::ostream &operator<<(std::ostream &out, const WGPUPredefinedColorSpace value);

std::string_view ToString(const WGPUPresentMode value);
std::ostream &operator<<(std::ostream &out, const WGPUPresentMode value);

std::string_view ToString(const WGPUPrimitiveTopology value);
std::ostream &operator<<(std::ostream &out, const WGPUPrimitiveTopology value);

std::string_view ToString(const WGPUQueryType value);
std::ostream &operator<<(std::ostream &out, const WGPUQueryType value);

std::string_view ToString(const WGPUQueueWorkDoneStatus value);
std::ostream &operator<<(std::ostream &out, const WGPUQueueWorkDoneStatus value);

std::string_view ToString(const WGPURequestAdapterStatus value);
std::ostream &operator<<(std::ostream &out, const WGPURequestAdapterStatus value);

std::string_view ToString(const WGPURequestDeviceStatus value);
std::ostream &operator<<(std::ostream &out, const WGPURequestDeviceStatus value);

std::string_view ToString(const WGPUSamplerBindingType value);
std::ostream &operator<<(std::ostream &out, const WGPUSamplerBindingType value);

std::string_view ToString(const WGPUStatus value);
std::ostream &operator<<(std::ostream &out, const WGPUStatus value);

std::string_view ToString(const WGPUStencilOperation value);
std::ostream &operator<<(std::ostream &out, const WGPUStencilOperation value);

std::string_view ToString(const WGPUStorageTextureAccess value);
std::ostream &operator<<(std::ostream &out, const WGPUStorageTextureAccess value);

std::string_view ToString(const WGPUStoreOp value);
std::ostream &operator<<(std::ostream &out, const WGPUStoreOp value);

std::string_view ToString(const WGPUSType value);
std::ostream &operator<<(std::ostream &out, const WGPUSType value);

std::string_view ToString(const WGPUSurfaceGetCurrentTextureStatus value);
std::ostream &operator<<(std::ostream &out, const WGPUSurfaceGetCurrentTextureStatus value);

std::string_view ToString(const WGPUTextureAspect value);
std::ostream &operator<<(std::ostream &out, const WGPUTextureAspect value);

std::string_view ToString(const WGPUTextureDimension value);
std::ostream &operator<<(std::ostream &out, const WGPUTextureDimension value);

std::string_view ToString(const WGPUTextureFormat value);
std::ostream &operator<<(std::ostream &out, const WGPUTextureFormat value);

std::string_view ToString(const WGPUTextureSampleType value);
std::ostream &operator<<(std::ostream &out, const WGPUTextureSampleType value);

std::string_view ToString(const WGPUTextureViewDimension value);
std::ostream &operator<<(std::ostream &out, const WGPUTextureViewDimension value);

std::string_view ToString(const WGPUToneMappingMode value);
std::ostream &operator<<(std::ostream &out, const WGPUToneMappingMode value);

std::string_view ToString(const WGPUVertexFormat value);
std::ostream &operator<<(std::ostream &out, const WGPUVertexFormat value);

std::string_view ToString(const WGPUVertexStepMode value);
std::ostream &operator<<(std::ostream &out, const WGPUVertexStepMode value);

std::string_view ToString(const WGPUWaitStatus value);
std::ostream &operator<<(std::ostream &out, const WGPUWaitStatus value);

std::string_view ToString(const WGPUWGSLLanguageFeatureName value);
std::ostream &operator<<(std::ostream &out, const WGPUWGSLLanguageFeatureName value);
