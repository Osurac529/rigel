# Rigel Game Engine
This is the Rigel game engine built on webgpu.

# Goals
- Use as few dependencies as possible so we can have as much control and flexibility as possible.  This will also reduce conversion between various implementations of data structures.
- Cross platform on Windows, Linux and Android.
- C++20

# 3D Conventions
- A left handed coordinate system is used.
    - +Y is up.
    - +Z is forward into the screen.
    - +X is to the right.
    - When setting up camera matrices the +Z axis points towards targets and can be used to increment the position of the camera when using a navigator.
- Distance units, where they matter, are in Meters.
- Winding
    - Clockwise winding will be the default because it follows the left hand rule.
- Matrices are column major and match WGSL
    - When concatenating matrices, the order is from right to left.
 Example: To scale, then rotate, then translate
    ```
    auto result = translate * rotate * scale;
    ```
- Through import and export conversions any handedness, majorness, and upness can be read and written.
