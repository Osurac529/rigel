# WebGPU
This is a wrapper around the wgpu-native library.

## Design
The main goals of this wrapper are:
1. Manage life time of objects automatically
1. Use the builder pattern to avoid initializing, filling out and leaving WGPU related structures around.
1. Facilitate an easy way to manage fields that are variable in length.
1. Provide stream output operator for webgpu-native enumerations.
1. This wrapper is meant to be a 1:1 with webgpu-native, it does not provide anything higher level than what the existing functionality provides.

### Life time of object
The life time of objects are handled through the webgpu::Object class that fully implements the C++ life cycle of an object using the wgpu-native AddRef/Release functions.

### Builders
Where possible the builder pattern is used to fill out WGPU related structures and create objects, provide some better defaults for some fields and handle fields that can be dynamic through Add methods.