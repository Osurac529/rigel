# Rigel Game Engine
This is the Rigel game engine built on webgpu.

## Goals
1. Use as few dependencies as possible so we can have as much control and flexibility as possible.  This will also reduce conversion between various implementations of data structures.
1. Cross platform 64-bit on Windows, Linux and Android.
1. C++20

## 3D Conventions
1. A left handed coordinate system is used.
    1. +Y is up.
    2. +Z is forward into the screen.
    3. +X is to the right.
    4. When setting up camera matrices the +Z axis points towards targets and can be used to increment the position of the camera when using a navigator.
2. Distance units, where they matter, are in Meters.
3. Winding
    - Clockwise winding will be the default because it follows the left hand rule.
4. Matrices are column major and match WGSL
    - When concatenating matrices, the order is from right to left.
 Example: To scale, then rotate, then translate
    ```
    auto result = translate * rotate * scale;
    ```
5. Through import and export conversions any handedness, majorness, and upness can be read and written.
