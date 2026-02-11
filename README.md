# Silica
#### Modern C++ reflection library 

> [!IMPORTANT]  
> Silica is undergoing a rebranding and rebuilding transition. All development will continue in the [new Astra repo](https://github.com/RobotLeopard86/Astra) and Silica will receive no further updates.
> The Silica repo, however, will remain available (though archived) and all existing links will continue to work.
>   
> The reason for this is that, since the original purpose of the fork was to use Meson and a newer LLVM version, I never put much time into understanding the codebase or making significant improvement.
> Because of this, the repo contains a large amount of code that is difficult for me to maintain or understand.
>
> The new Astra project will retain many conventions from Silica, but the internals will be heavily reworked and some interfaces and patterns will change.
> As such, do not expect code based on Silica to be instantly portable to Astra, although the changes required should be minor.

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


