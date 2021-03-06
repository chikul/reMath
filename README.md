# reMath Library

reMath is a simple yet convenient C++ math library developed primarily for graphics-related operations.

It provides an easy way to operate such mathematical entities as 2D and 3D vectors, square matrices, and quaternions. The aim was to ease the development process for OpenGL-based projects.

The library is intended to be cross-platform, however, currently, only Windows binding is fully tested. Linux and Mac OS X support are planned for the nearest future.

![Example](images/example01.png)

## Classes Overview

There are currently five main classes in the library:

* Vec2d - represents a 2d vector.
* Vec3d - represents a 3d vector.
* Quaternion - a 4d vector.
* Matrix3 - a 3x3 rotation-only matrix.
* Matrix4 - a 4x4 rotation & translation matrix.
