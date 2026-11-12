This is a 3D engine that will be used in a game for windows, linux and android.

## Build Setup
The wgpu-native implementation of WebGPU is being used.
The prebuilt binaries are from the v29.0.1.1 release:
https://github.com/gfx-rs/wgpu-native/releases

# Windows

Both the debug and release builds should be downloaded and placed in a directory named "wgpu" that is two directories up from the solution's root directory.

# Formatting
clang-format is used for formatting. On Windows the column marker needs to be kept in sync between .editorconfig and .clang-format. Windows also needs the "Max Line Length" extension in order for the column marker to be visible.