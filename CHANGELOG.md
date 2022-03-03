# Changelog

All notable changes to this project will be documented in this file.
This project adheres to [Semantic Versioning](http://semver.org/).

## [Unreleased]

### Added

* An example of library usage.

### Updated

* Docstrings conversion in progress.
* Unit test coverage increased.

## [1.2.0] - 15.02.2022

### Added

* Added `distanceTo()` method to `Vec2d` and `Vec3d`, which calculates absolute distance to another vector.
* Added `triangleArea()` function to utilities.
* `Vec2d` unit test coverage finished completely.
* Added utils test suite.
* Started on the docstrings in Doxygen-style.

### Changed

* `math.h` and `string.h` includes replaced by `cmath` and `cstring` as former are deprecated by the standard.
* Upgraded Win platform version.

### Fixed

* `toDegrees` was returning incorrect result.
* `maxPowerOfTwo` was returning incorrect result.

## [1.1.0] - 05.02.2018

### Added

* `Matrix3` class to represent rotation-only matrix.
* Created an MSVS solution.
* Unit test project and `Vec2d` coverage.
* `lookAt()` function to `reMathUtil` which calculates the view matrix.
* Added subscript (array access) operators to all classes.
* Added quaternion by matrix multiplication.

### Changed

* Renamed `Matrix` to `Matrix4` as we now have `Matrix3` in addition.
* Updated all classes to the latest C++ standards.

### Fixed

* Matrix by matrix multiplication for some reason was nullifying translation.

## [1.0.1] - 22.07.2017

### Fixed

* Incorrect definition of friend operators.

## [1.0.0] - 22.07.2017

### Added

* Extracted math classes from core project.

### Changed

* Introduced `re` namespace.
