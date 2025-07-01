# Silica
#### Modern C++ reflection library 

## About
Silica is a codegen-based reflection library for C++. It is forked from [the `easy_reflection_cpp` project by Maxim Voloshin](https://github.com/chocolacula/easy_reflection_cpp). Silica uses C++20. More information about Silica is available in the `doc` directory.

## Features
* Automatic reflection info generation via code generator
* Serialization/Deserialization to:
	* JSON
	* YAML
	* Binary
* Cross-platform
* Enum <-> string conversion
* STL container support
* Smart pointer support

## Building
You will need:  
* Git
* Meson
* Ninja
* CMake  

All other dependencies will be downloaded at configure-time.  
Configure the build directory with `meson setup build --native-file native.ini`, then run `meson compile -C build` to build the library. This can take a while, especially if building the generator, as it relies on a patched from-source build of LLVM. You do not have to use the native file (which sets the compiler to Clang and the linker to LLD), but it is recommended.

## Licensing
The Silica library and generator are licensed under the Apache License 2.0, which can be found in the root directory. All third-party licenses are present in the `licenses` folder, including that of the original `easy_reflection_cpp` library.
Any third-party code used by these libraries should have their licenses located within the appropriate project directory (these may not be downloaded until configure-time by Meson).
