#include "graphics/enumeration_to_string.hpp"

#include <ostream>

std::string_view ToString(const WGPUAdapterType value) {
  switch (value) {
  case WGPUAdapterType_DiscreteGPU:
    return "WGPUAdapterType_DiscreteGPU";
  case WGPUAdapterType_IntegratedGPU:
    return "WGPUAdapterType_IntegratedGPU";
  case WGPUAdapterType_CPU:
    return "WGPUAdapterType_CPU";
  case WGPUAdapterType_Unknown:
    return "WGPUAdapterType_Unknown";
  case WGPUAdapterType_Force32:
    return "WGPUAdapterType_Force32";
  default:
    throw std::invalid_argument("unknown enumeration value");
  }
}

std::ostream &operator<<(std::ostream &out, const WGPUAdapterType value) {
  return out << ToString(value);
}

std::string_view ToString(const WGPUAddressMode value) {
  switch (value) {
  case WGPUAddressMode_Undefined:
    return "WGPUAddressMode_Undefined";
  case WGPUAddressMode_ClampToEdge:
    return "WGPUAddressMode_ClampToEdge";
  case WGPUAddressMode_Repeat:
    return "WGPUAddressMode_Repeat";
  case WGPUAddressMode_MirrorRepeat:
    return "WGPUAddressMode_MirrorRepeat";
  case WGPUAddressMode_Force32:
    return "WGPUAddressMode_Force32";
  default:
    throw std::invalid_argument("unknown enumeration value");
  }
}

std::ostream &operator<<(std::ostream &out, const WGPUAddressMode value) {
  return out << ToString(value);
}

std::string_view ToString(const WGPUBackendType value) {
  switch (value) {
  case WGPUBackendType_Undefined:
    return "WGPUBackendType_Undefined";
  case WGPUBackendType_Null:
    return "WGPUBackendType_Null";
  case WGPUBackendType_WebGPU:
    return "WGPUBackendType_WebGPU";
  case WGPUBackendType_D3D11:
    return "WGPUBackendType_D3D11";
  case WGPUBackendType_D3D12:
    return "WGPUBackendType_D3D12";
  case WGPUBackendType_Metal:
    return "WGPUBackendType_Metal";
  case WGPUBackendType_Vulkan:
    return "WGPUBackendType_Vulkan";
  case WGPUBackendType_OpenGL:
    return "WGPUBackendType_OpenGL";
  case WGPUBackendType_OpenGLES:
    return "WGPUBackendType_OpenGLES";
  case WGPUBackendType_Force32:
    return "WGPUBackendType_Force32";
  default:
    throw std::invalid_argument("unknown enumeration value");
  }
}

std::ostream &operator<<(std::ostream &out, const WGPUBackendType value) {
  return out << ToString(value);
}

std::string_view ToString(const WGPUBlendFactor value) {
  switch (value) {
  case WGPUBlendFactor_Undefined:
    return "WGPUBlendFactor_Undefined";
  case WGPUBlendFactor_Zero:
    return "WGPUBlendFactor_Zero";
  case WGPUBlendFactor_One:
    return "WGPUBlendFactor_One";
  case WGPUBlendFactor_Src:
    return "WGPUBlendFactor_Src";
  case WGPUBlendFactor_OneMinusSrc:
    return "WGPUBlendFactor_OneMinusSrc";
  case WGPUBlendFactor_SrcAlpha:
    return "WGPUBlendFactor_SrcAlpha";
  case WGPUBlendFactor_OneMinusSrcAlpha:
    return "WGPUBlendFactor_OneMinusSrcAlpha";
  case WGPUBlendFactor_Dst:
    return "WGPUBlendFactor_Dst";
  case WGPUBlendFactor_OneMinusDst:
    return "WGPUBlendFactor_OneMinusDst";
  case WGPUBlendFactor_DstAlpha:
    return "WGPUBlendFactor_DstAlpha";
  case WGPUBlendFactor_OneMinusDstAlpha:
    return "WGPUBlendFactor_OneMinusDstAlpha";
  case WGPUBlendFactor_SrcAlphaSaturated:
    return "WGPUBlendFactor_SrcAlphaSaturated";
  case WGPUBlendFactor_Constant:
    return "WGPUBlendFactor_Constant";
  case WGPUBlendFactor_OneMinusConstant:
    return "WGPUBlendFactor_OneMinusConstant";
  case WGPUBlendFactor_Src1:
    return "WGPUBlendFactor_Src1";
  case WGPUBlendFactor_OneMinusSrc1:
    return "WGPUBlendFactor_OneMinusSrc1";
  case WGPUBlendFactor_Src1Alpha:
    return "WGPUBlendFactor_Src1Alpha";
  case WGPUBlendFactor_OneMinusSrc1Alpha:
    return "WGPUBlendFactor_OneMinusSrc1Alpha";
  case WGPUBlendFactor_Force32:
    return "WGPUBlendFactor_Force32";
  default:
    throw std::invalid_argument("unknown enumeration value");
  }
}

std::ostream &operator<<(std::ostream &out, const WGPUBlendFactor value) {
  return out << ToString(value);
}

std::string_view ToString(const WGPUBlendOperation value) {
  switch (value) {
  case WGPUBlendOperation_Undefined:
    return "WGPUBlendOperation_Undefined";
  case WGPUBlendOperation_Add:
    return "WGPUBlendOperation_Add";
  case WGPUBlendOperation_Subtract:
    return "WGPUBlendOperation_Subtract";
  case WGPUBlendOperation_ReverseSubtract:
    return "WGPUBlendOperation_ReverseSubtract";
  case WGPUBlendOperation_Min:
    return "WGPUBlendOperation_Min";
  case WGPUBlendOperation_Max:
    return "WGPUBlendOperation_Max";
  case WGPUBlendOperation_Force32:
    return "WGPUBlendOperation_Force32";
  default:
    throw std::invalid_argument("unknown enumeration value");
  }
}

std::ostream &operator<<(std::ostream &out, const WGPUBlendOperation value) {
  return out << ToString(value);
}

std::string_view ToString(const WGPUBufferBindingType value) {
  switch (value) {
  case WGPUBufferBindingType_BindingNotUsed:
    return "WGPUBufferBindingType_BindingNotUsed";
  case WGPUBufferBindingType_Undefined:
    return "WGPUBufferBindingType_Undefined";
  case WGPUBufferBindingType_Uniform:
    return "WGPUBufferBindingType_Uniform";
  case WGPUBufferBindingType_Storage:
    return "WGPUBufferBindingType_Storage";
  case WGPUBufferBindingType_ReadOnlyStorage:
    return "WGPUBufferBindingType_ReadOnlyStorage";
  case WGPUBufferBindingType_Force32:
    return "WGPUBufferBindingType_Force32";
  default:
    throw std::invalid_argument("unknown enumeration value");
  }
}

std::ostream &operator<<(std::ostream &out, const WGPUBufferBindingType value) {
  return out << ToString(value);
}

std::string_view ToString(const WGPUBufferMapState value) {
  switch (value) {
  case WGPUBufferMapState_Unmapped:
    return "WGPUBufferMapState_Unmapped";
  case WGPUBufferMapState_Pending:
    return "WGPUBufferMapState_Pending";
  case WGPUBufferMapState_Mapped:
    return "WGPUBufferMapState_Mapped";
  case WGPUBufferMapState_Force32:
    return "WGPUBufferMapState_Force32";
  default:
    throw std::invalid_argument("unknown enumeration value");
  }
}

std::ostream &operator<<(std::ostream &out, const WGPUBufferMapState value) {
  return out << ToString(value);
}

std::string_view ToString(const WGPUCallbackMode value) {
  switch (value) {
  case WGPUCallbackMode_WaitAnyOnly:
    return "WGPUCallbackMode_WaitAnyOnly";
  case WGPUCallbackMode_AllowProcessEvents:
    return "WGPUCallbackMode_AllowProcessEvents";
  case WGPUCallbackMode_AllowSpontaneous:
    return "WGPUCallbackMode_AllowSpontaneous";
  case WGPUCallbackMode_Force32:
    return "WGPUCallbackMode_Force32";
  default:
    throw std::invalid_argument("unknown enumeration value");
  }
}

std::ostream &operator<<(std::ostream &out, const WGPUCallbackMode value) {
  return out << ToString(value);
}

std::string_view ToString(const WGPUCompareFunction value) {
  switch (value) {
  case WGPUCompareFunction_Undefined:
    return "WGPUCompareFunction_Undefined";
  case WGPUCompareFunction_Never:
    return "WGPUCompareFunction_Never";
  case WGPUCompareFunction_Less:
    return "WGPUCompareFunction_Less";
  case WGPUCompareFunction_Equal:
    return "WGPUCompareFunction_Equal";
  case WGPUCompareFunction_LessEqual:
    return "WGPUCompareFunction_LessEqual";
  case WGPUCompareFunction_Greater:
    return "WGPUCompareFunction_Greater";
  case WGPUCompareFunction_NotEqual:
    return "WGPUCompareFunction_NotEqual";
  case WGPUCompareFunction_GreaterEqual:
    return "WGPUCompareFunction_GreaterEqual";
  case WGPUCompareFunction_Always:
    return "WGPUCompareFunction_Always";
  case WGPUCompareFunction_Force32:
    return "WGPUCompareFunction_Force32";
  default:
    throw std::invalid_argument("unknown enumeration value");
  }
}

std::ostream &operator<<(std::ostream &out, const WGPUCompareFunction value) {
  return out << ToString(value);
}

std::string_view ToString(const WGPUCompilationInfoRequestStatus value) {
  switch (value) {
  case WGPUCompilationInfoRequestStatus_Success:
    return "WGPUCompilationInfoRequestStatus_Success";
  case WGPUCompilationInfoRequestStatus_CallbackCancelled:
    return "WGPUCompilationInfoRequestStatus_CallbackCancelled";
  case WGPUCompilationInfoRequestStatus_Force32:
    return "WGPUCompilationInfoRequestStatus_Force32";
  default:
    throw std::invalid_argument("unknown enumeration value");
  }
}

std::ostream &operator<<(std::ostream &out, const WGPUCompilationInfoRequestStatus value) {
  return out << ToString(value);
}

std::string_view ToString(const WGPUCompilationMessageType value) {
  switch (value) {
  case WGPUCompilationMessageType_Error:
    return "WGPUCompilationMessageType_Error";
  case WGPUCompilationMessageType_Warning:
    return "WGPUCompilationMessageType_Warning";
  case WGPUCompilationMessageType_Info:
    return "WGPUCompilationMessageType_Info";
  case WGPUCompilationMessageType_Force32:
    return "WGPUCompilationMessageType_Force32";
  default:
    throw std::invalid_argument("unknown enumeration value");
  }
}

std::ostream &operator<<(std::ostream &out, const WGPUCompilationMessageType value) {
  return out << ToString(value);
}

std::string_view ToString(const WGPUComponentSwizzle value) {
  switch (value) {
  case WGPUComponentSwizzle_Undefined:
    return "WGPUComponentSwizzle_Undefined";
  case WGPUComponentSwizzle_Zero:
    return "WGPUComponentSwizzle_Zero";
  case WGPUComponentSwizzle_One:
    return "WGPUComponentSwizzle_One";
  case WGPUComponentSwizzle_R:
    return "WGPUComponentSwizzle_R";
  case WGPUComponentSwizzle_G:
    return "WGPUComponentSwizzle_G";
  case WGPUComponentSwizzle_B:
    return "WGPUComponentSwizzle_B";
  case WGPUComponentSwizzle_A:
    return "WGPUComponentSwizzle_A";
  case WGPUComponentSwizzle_Force32:
    return "WGPUComponentSwizzle_Force32";
  default:
    throw std::invalid_argument("unknown enumeration value");
  }
}

std::ostream &operator<<(std::ostream &out, const WGPUComponentSwizzle value) {
  return out << ToString(value);
}

std::string_view ToString(const WGPUCompositeAlphaMode value) {
  switch (value) {
  case WGPUCompositeAlphaMode_Auto:
    return "WGPUCompositeAlphaMode_Auto";
  case WGPUCompositeAlphaMode_Opaque:
    return "WGPUCompositeAlphaMode_Opaque";
  case WGPUCompositeAlphaMode_Premultiplied:
    return "WGPUCompositeAlphaMode_Premultiplied";
  case WGPUCompositeAlphaMode_Unpremultiplied:
    return "WGPUCompositeAlphaMode_Unpremultiplied";
  case WGPUCompositeAlphaMode_Inherit:
    return "WGPUCompositeAlphaMode_Inherit";
  case WGPUCompositeAlphaMode_Force32:
    return "WGPUCompositeAlphaMode_Force32";
  default:
    throw std::invalid_argument("unknown enumeration value");
  }
}

std::ostream &operator<<(std::ostream &out, const WGPUCompositeAlphaMode value) {
  return out << ToString(value);
}

std::string_view ToString(const WGPUCreatePipelineAsyncStatus value) {
  switch (value) {
  case WGPUCreatePipelineAsyncStatus_Success:
    return "WGPUCreatePipelineAsyncStatus_Success";
  case WGPUCreatePipelineAsyncStatus_CallbackCancelled:
    return "WGPUCreatePipelineAsyncStatus_CallbackCancelled";
  case WGPUCreatePipelineAsyncStatus_ValidationError:
    return "WGPUCreatePipelineAsyncStatus_ValidationError";
  case WGPUCreatePipelineAsyncStatus_InternalError:
    return "WGPUCreatePipelineAsyncStatus_InternalError";
  case WGPUCreatePipelineAsyncStatus_Force32:
    return "WGPUCreatePipelineAsyncStatus_Force32";
  default:
    throw std::invalid_argument("unknown enumeration value");
  }
}

std::ostream &operator<<(std::ostream &out, const WGPUCreatePipelineAsyncStatus value) {
  return out << ToString(value);
}

std::string_view ToString(const WGPUCullMode value) {
  switch (value) {
  case WGPUCullMode_Undefined:
    return "WGPUCullMode_Undefined";
  case WGPUCullMode_None:
    return "WGPUCullMode_None";
  case WGPUCullMode_Front:
    return "WGPUCullMode_Front";
  case WGPUCullMode_Back:
    return "WGPUCullMode_Back";
  case WGPUCullMode_Force32:
    return "WGPUCullMode_Force32";
  default:
    throw std::invalid_argument("unknown enumeration value");
  }
}

std::ostream &operator<<(std::ostream &out, const WGPUCullMode value) {
  return out << ToString(value);
}

std::string_view ToString(const WGPUDeviceLostReason value) {
  switch (value) {
  case WGPUDeviceLostReason_Unknown:
    return "WGPUDeviceLostReason_Unknown";
  case WGPUDeviceLostReason_Destroyed:
    return "WGPUDeviceLostReason_Destroyed";
  case WGPUDeviceLostReason_CallbackCancelled:
    return "WGPUDeviceLostReason_CallbackCancelled";
  case WGPUDeviceLostReason_FailedCreation:
    return "WGPUDeviceLostReason_FailedCreation";
  case WGPUDeviceLostReason_Force32:
    return "WGPUDeviceLostReason_Force32";
  default:
    throw std::invalid_argument("unknown enumeration value");
  }
}

std::ostream &operator<<(std::ostream &out, const WGPUDeviceLostReason value) {
  return out << ToString(value);
}

std::string_view ToString(const WGPUErrorFilter value) {
  switch (value) {
  case WGPUErrorFilter_Validation:
    return "WGPUErrorFilter_Validation";
  case WGPUErrorFilter_OutOfMemory:
    return "WGPUErrorFilter_OutOfMemory";
  case WGPUErrorFilter_Internal:
    return "WGPUErrorFilter_Internal";
  case WGPUErrorFilter_Force32:
    return "WGPUErrorFilter_Force32";
  default:
    throw std::invalid_argument("unknown enumeration value");
  }
}

std::ostream &operator<<(std::ostream &out, const WGPUErrorFilter value) {
  return out << ToString(value);
}

std::string_view ToString(const WGPUErrorType value) {
  switch (value) {
  case WGPUErrorType_NoError:
    return "WGPUErrorType_NoError";
  case WGPUErrorType_Validation:
    return "WGPUErrorType_Validation";
  case WGPUErrorType_OutOfMemory:
    return "WGPUErrorType_OutOfMemory";
  case WGPUErrorType_Internal:
    return "WGPUErrorType_Internal";
  case WGPUErrorType_Unknown:
    return "WGPUErrorType_Unknown";
  case WGPUErrorType_Force32:
    return "WGPUErrorType_Force32";
  default:
    throw std::invalid_argument("unknown enumeration value");
  }
}

std::ostream &operator<<(std::ostream &out, const WGPUErrorType value) {
  return out << ToString(value);
}

std::string_view ToString(const WGPUFeatureLevel value) {
  switch (value) {
  case WGPUFeatureLevel_Undefined:
    return "WGPUFeatureLevel_Undefined";
  case WGPUFeatureLevel_Compatibility:
    return "WGPUFeatureLevel_Compatibility";
  case WGPUFeatureLevel_Core:
    return "WGPUFeatureLevel_Core";
  case WGPUFeatureLevel_Force32:
    return "WGPUFeatureLevel_Force32";
  default:
    throw std::invalid_argument("unknown enumeration value");
  }
}

std::ostream &operator<<(std::ostream &out, const WGPUFeatureLevel value) {
  return out << ToString(value);
}

std::string_view ToString(const WGPUFeatureName value) {
  switch (value) {
  case WGPUFeatureName_CoreFeaturesAndLimits:
    return "WGPUFeatureName_CoreFeaturesAndLimits";
  case WGPUFeatureName_DepthClipControl:
    return "WGPUFeatureName_DepthClipControl";
  case WGPUFeatureName_Depth32FloatStencil8:
    return "WGPUFeatureName_Depth32FloatStencil8";
  case WGPUFeatureName_TextureCompressionBC:
    return "WGPUFeatureName_TextureCompressionBC";
  case WGPUFeatureName_TextureCompressionBCSliced3D:
    return "WGPUFeatureName_TextureCompressionBCSliced3D";
  case WGPUFeatureName_TextureCompressionETC2:
    return "WGPUFeatureName_TextureCompressionETC2";
  case WGPUFeatureName_TextureCompressionASTC:
    return "WGPUFeatureName_TextureCompressionASTC";
  case WGPUFeatureName_TextureCompressionASTCSliced3D:
    return "WGPUFeatureName_TextureCompressionASTCSliced3D";
  case WGPUFeatureName_TimestampQuery:
    return "WGPUFeatureName_TimestampQuery";
  case WGPUFeatureName_IndirectFirstInstance:
    return "WGPUFeatureName_IndirectFirstInstance";
  case WGPUFeatureName_ShaderF16:
    return "WGPUFeatureName_ShaderF16";
  case WGPUFeatureName_RG11B10UfloatRenderable:
    return "WGPUFeatureName_RG11B10UfloatRenderable";
  case WGPUFeatureName_BGRA8UnormStorage:
    return "WGPUFeatureName_BGRA8UnormStorage";
  case WGPUFeatureName_Float32Filterable:
    return "WGPUFeatureName_Float32Filterable";
  case WGPUFeatureName_Float32Blendable:
    return "WGPUFeatureName_Float32Blendable";
  case WGPUFeatureName_ClipDistances:
    return "WGPUFeatureName_ClipDistances";
  case WGPUFeatureName_DualSourceBlending:
    return "WGPUFeatureName_DualSourceBlending";
  case WGPUFeatureName_Subgroups:
    return "WGPUFeatureName_Subgroups";
  case WGPUFeatureName_TextureFormatsTier1:
    return "WGPUFeatureName_TextureFormatsTier1";
  case WGPUFeatureName_TextureFormatsTier2:
    return "WGPUFeatureName_TextureFormatsTier2";
  case WGPUFeatureName_PrimitiveIndex:
    return "WGPUFeatureName_PrimitiveIndex";
  case WGPUFeatureName_TextureComponentSwizzle:
    return "WGPUFeatureName_TextureComponentSwizzle";
  case WGPUFeatureName_Force32:
    return "WGPUFeatureName_Force32";
  default:
    throw std::invalid_argument("unknown enumeration value");
  }
}

std::ostream &operator<<(std::ostream &out, const WGPUFeatureName value) {
  return out << ToString(value);
}

std::string_view ToString(const WGPUFilterMode value) {
  switch (value) {
  case WGPUFilterMode_Undefined:
    return "WGPUFilterMode_Undefined";
  case WGPUFilterMode_Nearest:
    return "WGPUFilterMode_Nearest";
  case WGPUFilterMode_Linear:
    return "WGPUFilterMode_Linear";
  case WGPUFilterMode_Force32:
    return "WGPUFilterMode_Force32";
  default:
    throw std::invalid_argument("unknown enumeration value");
  }
}

std::ostream &operator<<(std::ostream &out, const WGPUFilterMode value) {
  return out << ToString(value);
}

std::string_view ToString(const WGPUFrontFace value) {
  switch (value) {
  case WGPUFrontFace_Undefined:
    return "WGPUFrontFace_Undefined";
  case WGPUFrontFace_CCW:
    return "WGPUFrontFace_CCW";
  case WGPUFrontFace_CW:
    return "WGPUFrontFace_CW";
  case WGPUFrontFace_Force32:
    return "WGPUFrontFace_Force32";
  default:
    throw std::invalid_argument("unknown enumeration value");
  }
}

std::ostream &operator<<(std::ostream &out, const WGPUFrontFace value) {
  return out << ToString(value);
}

std::string_view ToString(const WGPUIndexFormat value) {
  switch (value) {
  case WGPUIndexFormat_Undefined:
    return "WGPUIndexFormat_Undefined";
  case WGPUIndexFormat_Uint16:
    return "WGPUIndexFormat_Uint16";
  case WGPUIndexFormat_Uint32:
    return "WGPUIndexFormat_Uint32";
  case WGPUIndexFormat_Force32:
    return "WGPUIndexFormat_Force32";
  default:
    throw std::invalid_argument("unknown enumeration value");
  }
}

std::ostream &operator<<(std::ostream &out, const WGPUIndexFormat value) {
  return out << ToString(value);
}

std::string_view ToString(const WGPUInstanceFeatureName value) {
  switch (value) {
  case WGPUInstanceFeatureName_TimedWaitAny:
    return "WGPUInstanceFeatureName_TimedWaitAny";
  case WGPUInstanceFeatureName_ShaderSourceSPIRV:
    return "WGPUInstanceFeatureName_ShaderSourceSPIRV";
  case WGPUInstanceFeatureName_MultipleDevicesPerAdapter:
    return "WGPUInstanceFeatureName_MultipleDevicesPerAdapter";
  case WGPUInstanceFeatureName_Force32:
    return "WGPUInstanceFeatureName_Force32";
  default:
    throw std::invalid_argument("unknown enumeration value");
  }
}

std::ostream &operator<<(std::ostream &out, const WGPUInstanceFeatureName value) {
  return out << ToString(value);
}

std::string_view ToString(const WGPULoadOp value) {
  switch (value) {
  case WGPULoadOp_Undefined:
    return "WGPULoadOp_Undefined";
  case WGPULoadOp_Load:
    return "WGPULoadOp_Load";
  case WGPULoadOp_Clear:
    return "WGPULoadOp_Clear";
  case WGPULoadOp_Force32:
    return "WGPULoadOp_Force32";
  default:
    throw std::invalid_argument("unknown enumeration value");
  }
}

std::ostream &operator<<(std::ostream &out, const WGPULoadOp value) {
  return out << ToString(value);
}

std::string_view ToString(const WGPUMapAsyncStatus value) {
  switch (value) {
  case WGPUMapAsyncStatus_Success:
    return "WGPUMapAsyncStatus_Success";
  case WGPUMapAsyncStatus_CallbackCancelled:
    return "WGPUMapAsyncStatus_CallbackCancelled";
  case WGPUMapAsyncStatus_Error:
    return "WGPUMapAsyncStatus_Error";
  case WGPUMapAsyncStatus_Aborted:
    return "WGPUMapAsyncStatus_Aborted";
  case WGPUMapAsyncStatus_Force32:
    return "WGPUMapAsyncStatus_Force32";
  default:
    throw std::invalid_argument("unknown enumeration value");
  }
}

std::ostream &operator<<(std::ostream &out, const WGPUMapAsyncStatus value) {
  return out << ToString(value);
}

std::string_view ToString(const WGPUMipmapFilterMode value) {
  switch (value) {
  case WGPUMipmapFilterMode_Undefined:
    return "WGPUMipmapFilterMode_Undefined";
  case WGPUMipmapFilterMode_Nearest:
    return "WGPUMipmapFilterMode_Nearest";
  case WGPUMipmapFilterMode_Linear:
    return "WGPUMipmapFilterMode_Linear";
  case WGPUMipmapFilterMode_Force32:
    return "WGPUMipmapFilterMode_Force32";
  default:
    throw std::invalid_argument("unknown enumeration value");
  }
}

std::ostream &operator<<(std::ostream &out, const WGPUMipmapFilterMode value) {
  return out << ToString(value);
}

std::string_view ToString(const WGPUOptionalBool value) {
  switch (value) {
  case WGPUOptionalBool_False:
    return "WGPUOptionalBool_False";
  case WGPUOptionalBool_True:
    return "WGPUOptionalBool_True";
  case WGPUOptionalBool_Undefined:
    return "WGPUOptionalBool_Undefined";
  case WGPUOptionalBool_Force32:
    return "WGPUOptionalBool_Force32";
  default:
    throw std::invalid_argument("unknown enumeration value");
  }
}

std::ostream &operator<<(std::ostream &out, const WGPUOptionalBool value) {
  return out << ToString(value);
}

std::string_view ToString(const WGPUPopErrorScopeStatus value) {
  switch (value) {
  case WGPUPopErrorScopeStatus_Success:
    return "WGPUPopErrorScopeStatus_Success";
  case WGPUPopErrorScopeStatus_CallbackCancelled:
    return "WGPUPopErrorScopeStatus_CallbackCancelled";
  case WGPUPopErrorScopeStatus_Error:
    return "WGPUPopErrorScopeStatus_Error";
  case WGPUPopErrorScopeStatus_Force32:
    return "WGPUPopErrorScopeStatus_Force32";
  default:
    throw std::invalid_argument("unknown enumeration value");
  }
}

std::ostream &operator<<(std::ostream &out, const WGPUPopErrorScopeStatus value) {
  return out << ToString(value);
}

std::string_view ToString(const WGPUPowerPreference value) {
  switch (value) {
  case WGPUPowerPreference_Undefined:
    return "WGPUPowerPreference_Undefined";
  case WGPUPowerPreference_LowPower:
    return "WGPUPowerPreference_LowPower";
  case WGPUPowerPreference_HighPerformance:
    return "WGPUPowerPreference_HighPerformance";
  case WGPUPowerPreference_Force32:
    return "WGPUPowerPreference_Force32";
  default:
    throw std::invalid_argument("unknown enumeration value");
  }
}

std::ostream &operator<<(std::ostream &out, const WGPUPowerPreference value) {
  return out << ToString(value);
}

std::string_view ToString(const WGPUPredefinedColorSpace value) {
  switch (value) {
  case WGPUPredefinedColorSpace_SRGB:
    return "WGPUPredefinedColorSpace_SRGB";
  case WGPUPredefinedColorSpace_DisplayP3:
    return "WGPUPredefinedColorSpace_DisplayP3";
  case WGPUPredefinedColorSpace_Force32:
    return "WGPUPredefinedColorSpace_Force32";
  default:
    throw std::invalid_argument("unknown enumeration value");
  }
}

std::ostream &operator<<(std::ostream &out, const WGPUPredefinedColorSpace value) {
  return out << ToString(value);
}

std::string_view ToString(const WGPUPresentMode value) {
  switch (value) {
  case WGPUPresentMode_Undefined:
    return "WGPUPresentMode_Undefined";
  case WGPUPresentMode_Fifo:
    return "WGPUPresentMode_Fifo";
  case WGPUPresentMode_FifoRelaxed:
    return "WGPUPresentMode_FifoRelaxed";
  case WGPUPresentMode_Immediate:
    return "WGPUPresentMode_Immediate";
  case WGPUPresentMode_Mailbox:
    return "WGPUPresentMode_Mailbox";
  case WGPUPresentMode_Force32:
    return "WGPUPresentMode_Force32";
  default:
    throw std::invalid_argument("unknown enumeration value");
  }
}

std::ostream &operator<<(std::ostream &out, const WGPUPresentMode value) {
  return out << ToString(value);
}

std::string_view ToString(const WGPUPrimitiveTopology value) {
  switch (value) {
  case WGPUPrimitiveTopology_Undefined:
    return "WGPUPrimitiveTopology_Undefined";
  case WGPUPrimitiveTopology_PointList:
    return "WGPUPrimitiveTopology_PointList";
  case WGPUPrimitiveTopology_LineList:
    return "WGPUPrimitiveTopology_LineList";
  case WGPUPrimitiveTopology_LineStrip:
    return "WGPUPrimitiveTopology_LineStrip";
  case WGPUPrimitiveTopology_TriangleList:
    return "WGPUPrimitiveTopology_TriangleList";
  case WGPUPrimitiveTopology_TriangleStrip:
    return "WGPUPrimitiveTopology_TriangleStrip";
  case WGPUPrimitiveTopology_Force32:
    return "WGPUPrimitiveTopology_Force32";
  default:
    throw std::invalid_argument("unknown enumeration value");
  }
}

std::ostream &operator<<(std::ostream &out, const WGPUPrimitiveTopology value) {
  return out << ToString(value);
}

std::string_view ToString(const WGPUQueryType value) {
  switch (value) {
  case WGPUQueryType_Occlusion:
    return "WGPUQueryType_Occlusion";
  case WGPUQueryType_Timestamp:
    return "WGPUQueryType_Timestamp";
  case WGPUQueryType_Force32:
    return "WGPUQueryType_Force32";
  default:
    throw std::invalid_argument("unknown enumeration value");
  }
}

std::ostream &operator<<(std::ostream &out, const WGPUQueryType value) {
  return out << ToString(value);
}

std::string_view ToString(const WGPUQueueWorkDoneStatus value) {
  switch (value) {
  case WGPUQueueWorkDoneStatus_Success:
    return "WGPUQueueWorkDoneStatus_Success";
  case WGPUQueueWorkDoneStatus_CallbackCancelled:
    return "WGPUQueueWorkDoneStatus_CallbackCancelled";
  case WGPUQueueWorkDoneStatus_Error:
    return "WGPUQueueWorkDoneStatus_Error";
  case WGPUQueueWorkDoneStatus_Force32:
    return "WGPUQueueWorkDoneStatus_Force32";
  default:
    throw std::invalid_argument("unknown enumeration value");
  }
}

std::ostream &operator<<(std::ostream &out, const WGPUQueueWorkDoneStatus value) {
  return out << ToString(value);
}

std::string_view ToString(const WGPURequestAdapterStatus value) {
  switch (value) {
  case WGPURequestAdapterStatus_Success:
    return "WGPURequestAdapterStatus_Success";
  case WGPURequestAdapterStatus_CallbackCancelled:
    return "WGPURequestAdapterStatus_CallbackCancelled";
  case WGPURequestAdapterStatus_Unavailable:
    return "WGPURequestAdapterStatus_Unavailable";
  case WGPURequestAdapterStatus_Error:
    return "WGPURequestAdapterStatus_Error";
  case WGPURequestAdapterStatus_Force32:
    return "WGPURequestAdapterStatus_Force32";
  default:
    throw std::invalid_argument("unknown enumeration value");
  }
}

std::ostream &operator<<(std::ostream &out, const WGPURequestAdapterStatus value) {
  return out << ToString(value);
}

std::string_view ToString(const WGPURequestDeviceStatus value) {
  switch (value) {
  case WGPURequestDeviceStatus_Success:
    return "WGPURequestDeviceStatus_Success";
  case WGPURequestDeviceStatus_CallbackCancelled:
    return "WGPURequestDeviceStatus_CallbackCancelled";
  case WGPURequestDeviceStatus_Error:
    return "WGPURequestDeviceStatus_Error";
  case WGPURequestDeviceStatus_Force32:
    return "WGPURequestDeviceStatus_Force32";
  default:
    throw std::invalid_argument("unknown enumeration value");
  }
}

std::ostream &operator<<(std::ostream &out, const WGPURequestDeviceStatus value) {
  return out << ToString(value);
}

std::string_view ToString(const WGPUSamplerBindingType value) {
  switch (value) {
  case WGPUSamplerBindingType_BindingNotUsed:
    return "WGPUSamplerBindingType_BindingNotUsed";
  case WGPUSamplerBindingType_Undefined:
    return "WGPUSamplerBindingType_Undefined";
  case WGPUSamplerBindingType_Filtering:
    return "WGPUSamplerBindingType_Filtering";
  case WGPUSamplerBindingType_NonFiltering:
    return "WGPUSamplerBindingType_NonFiltering";
  case WGPUSamplerBindingType_Comparison:
    return "WGPUSamplerBindingType_Comparison";
  case WGPUSamplerBindingType_Force32:
    return "WGPUSamplerBindingType_Force32";
  default:
    throw std::invalid_argument("unknown enumeration value");
  }
}

std::ostream &operator<<(std::ostream &out, const WGPUSamplerBindingType value) {
  return out << ToString(value);
}

std::string_view ToString(const WGPUStatus value) {
  switch (value) {
  case WGPUStatus_Success:
    return "WGPUStatus_Success";
  case WGPUStatus_Error:
    return "WGPUStatus_Error";
  case WGPUStatus_Force32:
    return "WGPUStatus_Force32";
  default:
    throw std::invalid_argument("unknown enumeration value");
  }
}

std::ostream &operator<<(std::ostream &out, const WGPUStatus value) {
  return out << ToString(value);
}

std::string_view ToString(const WGPUStencilOperation value) {
  switch (value) {
  case WGPUStencilOperation_Undefined:
    return "WGPUStencilOperation_Undefined";
  case WGPUStencilOperation_Keep:
    return "WGPUStencilOperation_Keep";
  case WGPUStencilOperation_Zero:
    return "WGPUStencilOperation_Zero";
  case WGPUStencilOperation_Replace:
    return "WGPUStencilOperation_Replace";
  case WGPUStencilOperation_Invert:
    return "WGPUStencilOperation_Invert";
  case WGPUStencilOperation_IncrementClamp:
    return "WGPUStencilOperation_IncrementClamp";
  case WGPUStencilOperation_DecrementClamp:
    return "WGPUStencilOperation_DecrementClamp";
  case WGPUStencilOperation_IncrementWrap:
    return "WGPUStencilOperation_IncrementWrap";
  case WGPUStencilOperation_DecrementWrap:
    return "WGPUStencilOperation_DecrementWrap";
  case WGPUStencilOperation_Force32:
    return "WGPUStencilOperation_Force32";
  default:
    throw std::invalid_argument("unknown enumeration value");
  }
}

std::ostream &operator<<(std::ostream &out, const WGPUStencilOperation value) {
  return out << ToString(value);
}

std::string_view ToString(const WGPUStorageTextureAccess value) {
  switch (value) {
  case WGPUStorageTextureAccess_BindingNotUsed:
    return "WGPUStorageTextureAccess_BindingNotUsed";
  case WGPUStorageTextureAccess_Undefined:
    return "WGPUStorageTextureAccess_Undefined";
  case WGPUStorageTextureAccess_WriteOnly:
    return "WGPUStorageTextureAccess_WriteOnly";
  case WGPUStorageTextureAccess_ReadOnly:
    return "WGPUStorageTextureAccess_ReadOnly";
  case WGPUStorageTextureAccess_ReadWrite:
    return "WGPUStorageTextureAccess_ReadWrite";
  case WGPUStorageTextureAccess_Force32:
    return "WGPUStorageTextureAccess_Force32";
  default:
    throw std::invalid_argument("unknown enumeration value");
  }
}

std::ostream &operator<<(std::ostream &out, const WGPUStorageTextureAccess value) {
  return out << ToString(value);
}

std::string_view ToString(const WGPUStoreOp value) {
  switch (value) {
  case WGPUStoreOp_Undefined:
    return "WGPUStoreOp_Undefined";
  case WGPUStoreOp_Store:
    return "WGPUStoreOp_Store";
  case WGPUStoreOp_Discard:
    return "WGPUStoreOp_Discard";
  case WGPUStoreOp_Force32:
    return "WGPUStoreOp_Force32";
  default:
    throw std::invalid_argument("unknown enumeration value");
  }
}

std::ostream &operator<<(std::ostream &out, const WGPUStoreOp value) {
  return out << ToString(value);
}

std::string_view ToString(const WGPUSType value) {
  switch (value) {
  case WGPUSType_ShaderSourceSPIRV:
    return "WGPUSType_ShaderSourceSPIRV";
  case WGPUSType_ShaderSourceWGSL:
    return "WGPUSType_ShaderSourceWGSL";
  case WGPUSType_RenderPassMaxDrawCount:
    return "WGPUSType_RenderPassMaxDrawCount";
  case WGPUSType_SurfaceSourceMetalLayer:
    return "WGPUSType_SurfaceSourceMetalLayer";
  case WGPUSType_SurfaceSourceWindowsHWND:
    return "WGPUSType_SurfaceSourceWindowsHWND";
  case WGPUSType_SurfaceSourceXlibWindow:
    return "WGPUSType_SurfaceSourceXlibWindow";
  case WGPUSType_SurfaceSourceWaylandSurface:
    return "WGPUSType_SurfaceSourceWaylandSurface";
  case WGPUSType_SurfaceSourceAndroidNativeWindow:
    return "WGPUSType_SurfaceSourceAndroidNativeWindow";
  case WGPUSType_SurfaceSourceXCBWindow:
    return "WGPUSType_SurfaceSourceXCBWindow";
  case WGPUSType_SurfaceColorManagement:
    return "WGPUSType_SurfaceColorManagement";
  case WGPUSType_RequestAdapterWebXROptions:
    return "WGPUSType_RequestAdapterWebXROptions";
  case WGPUSType_TextureComponentSwizzleDescriptor:
    return "WGPUSType_TextureComponentSwizzleDescriptor";
  case WGPUSType_ExternalTextureBindingLayout:
    return "WGPUSType_ExternalTextureBindingLayout";
  case WGPUSType_ExternalTextureBindingEntry:
    return "WGPUSType_ExternalTextureBindingEntry";
  case WGPUSType_CompatibilityModeLimits:
    return "WGPUSType_CompatibilityModeLimits";
  case WGPUSType_TextureBindingViewDimension:
    return "WGPUSType_TextureBindingViewDimension";
  case WGPUSType_Force32:
    return "WGPUSType_Force32";
  default:
    throw std::invalid_argument("unknown enumeration value");
  }
}

std::ostream &operator<<(std::ostream &out, const WGPUSType value) {
  return out << ToString(value);
}

std::string_view ToString(const WGPUSurfaceGetCurrentTextureStatus value) {
  switch (value) {
  case WGPUSurfaceGetCurrentTextureStatus_SuccessOptimal:
    return "WGPUSurfaceGetCurrentTextureStatus_SuccessOptimal";
  case WGPUSurfaceGetCurrentTextureStatus_SuccessSuboptimal:
    return "WGPUSurfaceGetCurrentTextureStatus_SuccessSuboptimal";
  case WGPUSurfaceGetCurrentTextureStatus_Timeout:
    return "WGPUSurfaceGetCurrentTextureStatus_Timeout";
  case WGPUSurfaceGetCurrentTextureStatus_Outdated:
    return "WGPUSurfaceGetCurrentTextureStatus_Outdated";
  case WGPUSurfaceGetCurrentTextureStatus_Lost:
    return "WGPUSurfaceGetCurrentTextureStatus_Lost";
  case WGPUSurfaceGetCurrentTextureStatus_Error:
    return "WGPUSurfaceGetCurrentTextureStatus_Error";
  case WGPUSurfaceGetCurrentTextureStatus_Force32:
    return "WGPUSurfaceGetCurrentTextureStatus_Force32";
  default:
    throw std::invalid_argument("unknown enumeration value");
  }
}

std::ostream &operator<<(std::ostream &out, const WGPUSurfaceGetCurrentTextureStatus value) {
  return out << ToString(value);
}

std::string_view ToString(const WGPUTextureAspect value) {
  switch (value) {
  case WGPUTextureAspect_Undefined:
    return "WGPUTextureAspect_Undefined";
  case WGPUTextureAspect_All:
    return "WGPUTextureAspect_All";
  case WGPUTextureAspect_StencilOnly:
    return "WGPUTextureAspect_StencilOnly";
  case WGPUTextureAspect_DepthOnly:
    return "WGPUTextureAspect_DepthOnly";
  case WGPUTextureAspect_Force32:
    return "WGPUTextureAspect_Force32";
  default:
    throw std::invalid_argument("unknown enumeration value");
  }
}

std::ostream &operator<<(std::ostream &out, const WGPUTextureAspect value) {
  return out << ToString(value);
}

std::string_view ToString(const WGPUTextureDimension value) {
  switch (value) {
  case WGPUTextureDimension_Undefined:
    return "WGPUTextureDimension_Undefined";
  case WGPUTextureDimension_1D:
    return "WGPUTextureDimension_1D";
  case WGPUTextureDimension_2D:
    return "WGPUTextureDimension_2D";
  case WGPUTextureDimension_3D:
    return "WGPUTextureDimension_3D";
  case WGPUTextureDimension_Force32:
    return "WGPUTextureDimension_Force32";
  default:
    throw std::invalid_argument("unknown enumeration value");
  }
}

std::ostream &operator<<(std::ostream &out, const WGPUTextureDimension value) {
  return out << ToString(value);
}

std::string_view ToString(const WGPUTextureFormat value) {
  switch (value) {
  case WGPUTextureFormat_Undefined:
    return "WGPUTextureFormat_Undefined";
  case WGPUTextureFormat_R8Unorm:
    return "WGPUTextureFormat_R8Unorm";
  case WGPUTextureFormat_R8Snorm:
    return "WGPUTextureFormat_R8Snorm";
  case WGPUTextureFormat_R8Uint:
    return "WGPUTextureFormat_R8Uint";
  case WGPUTextureFormat_R8Sint:
    return "WGPUTextureFormat_R8Sint";
  case WGPUTextureFormat_R16Unorm:
    return "WGPUTextureFormat_R16Unorm";
  case WGPUTextureFormat_R16Snorm:
    return "WGPUTextureFormat_R16Snorm";
  case WGPUTextureFormat_R16Uint:
    return "WGPUTextureFormat_R16Uint";
  case WGPUTextureFormat_R16Sint:
    return "WGPUTextureFormat_R16Sint";
  case WGPUTextureFormat_R16Float:
    return "WGPUTextureFormat_R16Float";
  case WGPUTextureFormat_RG8Unorm:
    return "WGPUTextureFormat_RG8Unorm";
  case WGPUTextureFormat_RG8Snorm:
    return "WGPUTextureFormat_RG8Snorm";
  case WGPUTextureFormat_RG8Uint:
    return "WGPUTextureFormat_RG8Uint";
  case WGPUTextureFormat_RG8Sint:
    return "WGPUTextureFormat_RG8Sint";
  case WGPUTextureFormat_R32Float:
    return "WGPUTextureFormat_R32Float";
  case WGPUTextureFormat_R32Uint:
    return "WGPUTextureFormat_R32Uint";
  case WGPUTextureFormat_R32Sint:
    return "WGPUTextureFormat_R32Sint";
  case WGPUTextureFormat_RG16Unorm:
    return "WGPUTextureFormat_RG16Unorm";
  case WGPUTextureFormat_RG16Snorm:
    return "WGPUTextureFormat_RG16Snorm";
  case WGPUTextureFormat_RG16Uint:
    return "WGPUTextureFormat_RG16Uint";
  case WGPUTextureFormat_RG16Sint:
    return "WGPUTextureFormat_RG16Sint";
  case WGPUTextureFormat_RG16Float:
    return "WGPUTextureFormat_RG16Float";
  case WGPUTextureFormat_RGBA8Unorm:
    return "WGPUTextureFormat_RGBA8Unorm";
  case WGPUTextureFormat_RGBA8UnormSrgb:
    return "WGPUTextureFormat_RGBA8UnormSrgb";
  case WGPUTextureFormat_RGBA8Snorm:
    return "WGPUTextureFormat_RGBA8Snorm";
  case WGPUTextureFormat_RGBA8Uint:
    return "WGPUTextureFormat_RGBA8Uint";
  case WGPUTextureFormat_RGBA8Sint:
    return "WGPUTextureFormat_RGBA8Sint";
  case WGPUTextureFormat_BGRA8Unorm:
    return "WGPUTextureFormat_BGRA8Unorm";
  case WGPUTextureFormat_BGRA8UnormSrgb:
    return "WGPUTextureFormat_BGRA8UnormSrgb";
  case WGPUTextureFormat_RGB10A2Uint:
    return "WGPUTextureFormat_RGB10A2Uint";
  case WGPUTextureFormat_RGB10A2Unorm:
    return "WGPUTextureFormat_RGB10A2Unorm";
  case WGPUTextureFormat_RG11B10Ufloat:
    return "WGPUTextureFormat_RG11B10Ufloat";
  case WGPUTextureFormat_RGB9E5Ufloat:
    return "WGPUTextureFormat_RGB9E5Ufloat";
  case WGPUTextureFormat_RG32Float:
    return "WGPUTextureFormat_RG32Float";
  case WGPUTextureFormat_RG32Uint:
    return "WGPUTextureFormat_RG32Uint";
  case WGPUTextureFormat_RG32Sint:
    return "WGPUTextureFormat_RG32Sint";
  case WGPUTextureFormat_RGBA16Unorm:
    return "WGPUTextureFormat_RGBA16Unorm";
  case WGPUTextureFormat_RGBA16Snorm:
    return "WGPUTextureFormat_RGBA16Snorm";
  case WGPUTextureFormat_RGBA16Uint:
    return "WGPUTextureFormat_RGBA16Uint";
  case WGPUTextureFormat_RGBA16Sint:
    return "WGPUTextureFormat_RGBA16Sint";
  case WGPUTextureFormat_RGBA16Float:
    return "WGPUTextureFormat_RGBA16Float";
  case WGPUTextureFormat_RGBA32Float:
    return "WGPUTextureFormat_RGBA32Float";
  case WGPUTextureFormat_RGBA32Uint:
    return "WGPUTextureFormat_RGBA32Uint";
  case WGPUTextureFormat_RGBA32Sint:
    return "WGPUTextureFormat_RGBA32Sint";
  case WGPUTextureFormat_Stencil8:
    return "WGPUTextureFormat_Stencil8";
  case WGPUTextureFormat_Depth16Unorm:
    return "WGPUTextureFormat_Depth16Unorm";
  case WGPUTextureFormat_Depth24Plus:
    return "WGPUTextureFormat_Depth24Plus";
  case WGPUTextureFormat_Depth24PlusStencil8:
    return "WGPUTextureFormat_Depth24PlusStencil8";
  case WGPUTextureFormat_Depth32Float:
    return "WGPUTextureFormat_Depth32Float";
  case WGPUTextureFormat_Depth32FloatStencil8:
    return "WGPUTextureFormat_Depth32FloatStencil8";
  case WGPUTextureFormat_BC1RGBAUnorm:
    return "WGPUTextureFormat_BC1RGBAUnorm";
  case WGPUTextureFormat_BC1RGBAUnormSrgb:
    return "WGPUTextureFormat_BC1RGBAUnormSrgb";
  case WGPUTextureFormat_BC2RGBAUnorm:
    return "WGPUTextureFormat_BC2RGBAUnorm";
  case WGPUTextureFormat_BC2RGBAUnormSrgb:
    return "WGPUTextureFormat_BC2RGBAUnormSrgb";
  case WGPUTextureFormat_BC3RGBAUnorm:
    return "WGPUTextureFormat_BC3RGBAUnorm";
  case WGPUTextureFormat_BC3RGBAUnormSrgb:
    return "WGPUTextureFormat_BC3RGBAUnormSrgb";
  case WGPUTextureFormat_BC4RUnorm:
    return "WGPUTextureFormat_BC4RUnorm";
  case WGPUTextureFormat_BC4RSnorm:
    return "WGPUTextureFormat_BC4RSnorm";
  case WGPUTextureFormat_BC5RGUnorm:
    return "WGPUTextureFormat_BC5RGUnorm";
  case WGPUTextureFormat_BC5RGSnorm:
    return "WGPUTextureFormat_BC5RGSnorm";
  case WGPUTextureFormat_BC6HRGBUfloat:
    return "WGPUTextureFormat_BC6HRGBUfloat";
  case WGPUTextureFormat_BC6HRGBFloat:
    return "WGPUTextureFormat_BC6HRGBFloat";
  case WGPUTextureFormat_BC7RGBAUnorm:
    return "WGPUTextureFormat_BC7RGBAUnorm";
  case WGPUTextureFormat_BC7RGBAUnormSrgb:
    return "WGPUTextureFormat_BC7RGBAUnormSrgb";
  case WGPUTextureFormat_ETC2RGB8Unorm:
    return "WGPUTextureFormat_ETC2RGB8Unorm";
  case WGPUTextureFormat_ETC2RGB8UnormSrgb:
    return "WGPUTextureFormat_ETC2RGB8UnormSrgb";
  case WGPUTextureFormat_ETC2RGB8A1Unorm:
    return "WGPUTextureFormat_ETC2RGB8A1Unorm";
  case WGPUTextureFormat_ETC2RGB8A1UnormSrgb:
    return "WGPUTextureFormat_ETC2RGB8A1UnormSrgb";
  case WGPUTextureFormat_ETC2RGBA8Unorm:
    return "WGPUTextureFormat_ETC2RGBA8Unorm";
  case WGPUTextureFormat_ETC2RGBA8UnormSrgb:
    return "WGPUTextureFormat_ETC2RGBA8UnormSrgb";
  case WGPUTextureFormat_EACR11Unorm:
    return "WGPUTextureFormat_EACR11Unorm";
  case WGPUTextureFormat_EACR11Snorm:
    return "WGPUTextureFormat_EACR11Snorm";
  case WGPUTextureFormat_EACRG11Unorm:
    return "WGPUTextureFormat_EACRG11Unorm";
  case WGPUTextureFormat_EACRG11Snorm:
    return "WGPUTextureFormat_EACRG11Snorm";
  case WGPUTextureFormat_ASTC4x4Unorm:
    return "WGPUTextureFormat_ASTC4x4Unorm";
  case WGPUTextureFormat_ASTC4x4UnormSrgb:
    return "WGPUTextureFormat_ASTC4x4UnormSrgb";
  case WGPUTextureFormat_ASTC5x4Unorm:
    return "WGPUTextureFormat_ASTC5x4Unorm";
  case WGPUTextureFormat_ASTC5x4UnormSrgb:
    return "WGPUTextureFormat_ASTC5x4UnormSrgb";
  case WGPUTextureFormat_ASTC5x5Unorm:
    return "WGPUTextureFormat_ASTC5x5Unorm";
  case WGPUTextureFormat_ASTC5x5UnormSrgb:
    return "WGPUTextureFormat_ASTC5x5UnormSrgb";
  case WGPUTextureFormat_ASTC6x5Unorm:
    return "WGPUTextureFormat_ASTC6x5Unorm";
  case WGPUTextureFormat_ASTC6x5UnormSrgb:
    return "WGPUTextureFormat_ASTC6x5UnormSrgb";
  case WGPUTextureFormat_ASTC6x6Unorm:
    return "WGPUTextureFormat_ASTC6x6Unorm";
  case WGPUTextureFormat_ASTC6x6UnormSrgb:
    return "WGPUTextureFormat_ASTC6x6UnormSrgb";
  case WGPUTextureFormat_ASTC8x5Unorm:
    return "WGPUTextureFormat_ASTC8x5Unorm";
  case WGPUTextureFormat_ASTC8x5UnormSrgb:
    return "WGPUTextureFormat_ASTC8x5UnormSrgb";
  case WGPUTextureFormat_ASTC8x6Unorm:
    return "WGPUTextureFormat_ASTC8x6Unorm";
  case WGPUTextureFormat_ASTC8x6UnormSrgb:
    return "WGPUTextureFormat_ASTC8x6UnormSrgb";
  case WGPUTextureFormat_ASTC8x8Unorm:
    return "WGPUTextureFormat_ASTC8x8Unorm";
  case WGPUTextureFormat_ASTC8x8UnormSrgb:
    return "WGPUTextureFormat_ASTC8x8UnormSrgb";
  case WGPUTextureFormat_ASTC10x5Unorm:
    return "WGPUTextureFormat_ASTC10x5Unorm";
  case WGPUTextureFormat_ASTC10x5UnormSrgb:
    return "WGPUTextureFormat_ASTC10x5UnormSrgb";
  case WGPUTextureFormat_ASTC10x6Unorm:
    return "WGPUTextureFormat_ASTC10x6Unorm";
  case WGPUTextureFormat_ASTC10x6UnormSrgb:
    return "WGPUTextureFormat_ASTC10x6UnormSrgb";
  case WGPUTextureFormat_ASTC10x8Unorm:
    return "WGPUTextureFormat_ASTC10x8Unorm";
  case WGPUTextureFormat_ASTC10x8UnormSrgb:
    return "WGPUTextureFormat_ASTC10x8UnormSrgb";
  case WGPUTextureFormat_ASTC10x10Unorm:
    return "WGPUTextureFormat_ASTC10x10Unorm";
  case WGPUTextureFormat_ASTC10x10UnormSrgb:
    return "WGPUTextureFormat_ASTC10x10UnormSrgb";
  case WGPUTextureFormat_ASTC12x10Unorm:
    return "WGPUTextureFormat_ASTC12x10Unorm";
  case WGPUTextureFormat_ASTC12x10UnormSrgb:
    return "WGPUTextureFormat_ASTC12x10UnormSrgb";
  case WGPUTextureFormat_ASTC12x12Unorm:
    return "WGPUTextureFormat_ASTC12x12Unorm";
  case WGPUTextureFormat_ASTC12x12UnormSrgb:
    return "WGPUTextureFormat_ASTC12x12UnormSrgb";
  case WGPUTextureFormat_Force32:
    return "WGPUTextureFormat_Force32";
  default:
    throw std::invalid_argument("unknown enumeration value");
  }
}

std::ostream &operator<<(std::ostream &out, const WGPUTextureFormat value) {
  return out << ToString(value);
}

std::string_view ToString(const WGPUTextureSampleType value) {
  switch (value) {
  case WGPUTextureSampleType_BindingNotUsed:
    return "WGPUTextureSampleType_BindingNotUsed";
  case WGPUTextureSampleType_Undefined:
    return "WGPUTextureSampleType_Undefined";
  case WGPUTextureSampleType_Float:
    return "WGPUTextureSampleType_Float";
  case WGPUTextureSampleType_UnfilterableFloat:
    return "WGPUTextureSampleType_UnfilterableFloat";
  case WGPUTextureSampleType_Depth:
    return "WGPUTextureSampleType_Depth";
  case WGPUTextureSampleType_Sint:
    return "WGPUTextureSampleType_Sint";
  case WGPUTextureSampleType_Uint:
    return "WGPUTextureSampleType_Uint";
  case WGPUTextureSampleType_Force32:
    return "WGPUTextureSampleType_Force32";
  default:
    throw std::invalid_argument("unknown enumeration value");
  }
}

std::ostream &operator<<(std::ostream &out, const WGPUTextureSampleType value) {
  return out << ToString(value);
}

std::string_view ToString(const WGPUTextureViewDimension value) {
  switch (value) {
  case WGPUTextureViewDimension_Undefined:
    return "WGPUTextureViewDimension_Undefined";
  case WGPUTextureViewDimension_1D:
    return "WGPUTextureViewDimension_1D";
  case WGPUTextureViewDimension_2D:
    return "WGPUTextureViewDimension_2D";
  case WGPUTextureViewDimension_2DArray:
    return "WGPUTextureViewDimension_2DArray";
  case WGPUTextureViewDimension_Cube:
    return "WGPUTextureViewDimension_Cube";
  case WGPUTextureViewDimension_CubeArray:
    return "WGPUTextureViewDimension_CubeArray";
  case WGPUTextureViewDimension_3D:
    return "WGPUTextureViewDimension_3D";
  case WGPUTextureViewDimension_Force32:
    return "WGPUTextureViewDimension_Force32";
  default:
    throw std::invalid_argument("unknown enumeration value");
  }
}

std::ostream &operator<<(std::ostream &out, const WGPUTextureViewDimension value) {
  return out << ToString(value);
}

std::string_view ToString(const WGPUToneMappingMode value) {
  switch (value) {
  case WGPUToneMappingMode_Standard:
    return "WGPUToneMappingMode_Standard";
  case WGPUToneMappingMode_Extended:
    return "WGPUToneMappingMode_Extended";
  case WGPUToneMappingMode_Force32:
    return "WGPUToneMappingMode_Force32";
  default:
    throw std::invalid_argument("unknown enumeration value");
  }
}

std::ostream &operator<<(std::ostream &out, const WGPUToneMappingMode value) {
  return out << ToString(value);
}

std::string_view ToString(const WGPUVertexFormat value) {
  switch (value) {
  case WGPUVertexFormat_Uint8:
    return "WGPUVertexFormat_Uint8";
  case WGPUVertexFormat_Uint8x2:
    return "WGPUVertexFormat_Uint8x2";
  case WGPUVertexFormat_Uint8x4:
    return "WGPUVertexFormat_Uint8x4";
  case WGPUVertexFormat_Sint8:
    return "WGPUVertexFormat_Sint8";
  case WGPUVertexFormat_Sint8x2:
    return "WGPUVertexFormat_Sint8x2";
  case WGPUVertexFormat_Sint8x4:
    return "WGPUVertexFormat_Sint8x4";
  case WGPUVertexFormat_Unorm8:
    return "WGPUVertexFormat_Unorm8";
  case WGPUVertexFormat_Unorm8x2:
    return "WGPUVertexFormat_Unorm8x2";
  case WGPUVertexFormat_Unorm8x4:
    return "WGPUVertexFormat_Unorm8x4";
  case WGPUVertexFormat_Snorm8:
    return "WGPUVertexFormat_Snorm8";
  case WGPUVertexFormat_Snorm8x2:
    return "WGPUVertexFormat_Snorm8x2";
  case WGPUVertexFormat_Snorm8x4:
    return "WGPUVertexFormat_Snorm8x4";
  case WGPUVertexFormat_Uint16:
    return "WGPUVertexFormat_Uint16";
  case WGPUVertexFormat_Uint16x2:
    return "WGPUVertexFormat_Uint16x2";
  case WGPUVertexFormat_Uint16x4:
    return "WGPUVertexFormat_Uint16x4";
  case WGPUVertexFormat_Sint16:
    return "WGPUVertexFormat_Sint16";
  case WGPUVertexFormat_Sint16x2:
    return "WGPUVertexFormat_Sint16x2";
  case WGPUVertexFormat_Sint16x4:
    return "WGPUVertexFormat_Sint16x4";
  case WGPUVertexFormat_Unorm16:
    return "WGPUVertexFormat_Unorm16";
  case WGPUVertexFormat_Unorm16x2:
    return "WGPUVertexFormat_Unorm16x2";
  case WGPUVertexFormat_Unorm16x4:
    return "WGPUVertexFormat_Unorm16x4";
  case WGPUVertexFormat_Snorm16:
    return "WGPUVertexFormat_Snorm16";
  case WGPUVertexFormat_Snorm16x2:
    return "WGPUVertexFormat_Snorm16x2";
  case WGPUVertexFormat_Snorm16x4:
    return "WGPUVertexFormat_Snorm16x4";
  case WGPUVertexFormat_Float16:
    return "WGPUVertexFormat_Float16";
  case WGPUVertexFormat_Float16x2:
    return "WGPUVertexFormat_Float16x2";
  case WGPUVertexFormat_Float16x4:
    return "WGPUVertexFormat_Float16x4";
  case WGPUVertexFormat_Float32:
    return "WGPUVertexFormat_Float32";
  case WGPUVertexFormat_Float32x2:
    return "WGPUVertexFormat_Float32x2";
  case WGPUVertexFormat_Float32x3:
    return "WGPUVertexFormat_Float32x3";
  case WGPUVertexFormat_Float32x4:
    return "WGPUVertexFormat_Float32x4";
  case WGPUVertexFormat_Uint32:
    return "WGPUVertexFormat_Uint32";
  case WGPUVertexFormat_Uint32x2:
    return "WGPUVertexFormat_Uint32x2";
  case WGPUVertexFormat_Uint32x3:
    return "WGPUVertexFormat_Uint32x3";
  case WGPUVertexFormat_Uint32x4:
    return "WGPUVertexFormat_Uint32x4";
  case WGPUVertexFormat_Sint32:
    return "WGPUVertexFormat_Sint32";
  case WGPUVertexFormat_Sint32x2:
    return "WGPUVertexFormat_Sint32x2";
  case WGPUVertexFormat_Sint32x3:
    return "WGPUVertexFormat_Sint32x3";
  case WGPUVertexFormat_Sint32x4:
    return "WGPUVertexFormat_Sint32x4";
  case WGPUVertexFormat_Unorm10_10_10_2:
    return "WGPUVertexFormat_Unorm10_10_10_2";
  case WGPUVertexFormat_Unorm8x4BGRA:
    return "WGPUVertexFormat_Unorm8x4BGRA";
  case WGPUVertexFormat_Force32:
    return "WGPUVertexFormat_Force32";
  default:
    throw std::invalid_argument("unknown enumeration value");
  }
}

std::ostream &operator<<(std::ostream &out, const WGPUVertexFormat value) {
  return out << ToString(value);
}

std::string_view ToString(const WGPUVertexStepMode value) {
  switch (value) {
  case WGPUVertexStepMode_Undefined:
    return "WGPUVertexStepMode_Undefined";
  case WGPUVertexStepMode_Vertex:
    return "WGPUVertexStepMode_Vertex";
  case WGPUVertexStepMode_Instance:
    return "WGPUVertexStepMode_Instance";
  case WGPUVertexStepMode_Force32:
    return "WGPUVertexStepMode_Force32";
  default:
    throw std::invalid_argument("unknown enumeration value");
  }
}

std::ostream &operator<<(std::ostream &out, const WGPUVertexStepMode value) {
  return out << ToString(value);
}

std::string_view ToString(const WGPUWaitStatus value) {
  switch (value) {
  case WGPUWaitStatus_Success:
    return "WGPUWaitStatus_Success";
  case WGPUWaitStatus_TimedOut:
    return "WGPUWaitStatus_TimedOut";
  case WGPUWaitStatus_Error:
    return "WGPUWaitStatus_Error";
  case WGPUWaitStatus_Force32:
    return "WGPUWaitStatus_Force32";
  default:
    throw std::invalid_argument("unknown enumeration value");
  }
}

std::ostream &operator<<(std::ostream &out, const WGPUWaitStatus value) {
  return out << ToString(value);
}

std::string_view ToString(const WGPUWGSLLanguageFeatureName value) {
  switch (value) {
  case WGPUWGSLLanguageFeatureName_ReadonlyAndReadwriteStorageTextures:
    return "WGPUWGSLLanguageFeatureName_ReadonlyAndReadwriteStorageTextures";
  case WGPUWGSLLanguageFeatureName_Packed4x8IntegerDotProduct:
    return "WGPUWGSLLanguageFeatureName_Packed4x8IntegerDotProduct";
  case WGPUWGSLLanguageFeatureName_UnrestrictedPointerParameters:
    return "WGPUWGSLLanguageFeatureName_UnrestrictedPointerParameters";
  case WGPUWGSLLanguageFeatureName_PointerCompositeAccess:
    return "WGPUWGSLLanguageFeatureName_PointerCompositeAccess";
  case WGPUWGSLLanguageFeatureName_UniformBufferStandardLayout:
    return "WGPUWGSLLanguageFeatureName_UniformBufferStandardLayout";
  case WGPUWGSLLanguageFeatureName_SubgroupId:
    return "WGPUWGSLLanguageFeatureName_SubgroupId";
  case WGPUWGSLLanguageFeatureName_TextureAndSamplerLet:
    return "WGPUWGSLLanguageFeatureName_TextureAndSamplerLet";
  case WGPUWGSLLanguageFeatureName_SubgroupUniformity:
    return "WGPUWGSLLanguageFeatureName_SubgroupUniformity";
  case WGPUWGSLLanguageFeatureName_TextureFormatsTier1:
    return "WGPUWGSLLanguageFeatureName_TextureFormatsTier1";
  case WGPUWGSLLanguageFeatureName_LinearIndexing:
    return "WGPUWGSLLanguageFeatureName_LinearIndexing";
  case WGPUWGSLLanguageFeatureName_Force32:
    return "WGPUWGSLLanguageFeatureName_Force32";
  default:
    throw std::invalid_argument("unknown enumeration value");
  }
}

std::ostream &operator<<(std::ostream &out, const WGPUWGSLLanguageFeatureName value) {
  return out << ToString(value);
}
