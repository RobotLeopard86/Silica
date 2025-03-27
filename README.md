# Silica
#### Modern C++ reflection library 

## About
Silica is a codegen-based reflection library for C++. It is forked from [the `easy_reflection_cpp` project by Maxim Voloshin](https://github.com/chocolacula/easy_reflection_cpp). More information is available in the `docs` directory.

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
* Invocation of superclass methods

## Building
You will need:  
* Git
* Meson
* Ninja
* CMake  

All other dependencies will be downloaded at configure-time.  
Configure the build directory with `meson setup build`, then run `meson compile -C build` to build the library. This can take a while.

## Branching Scheme
Silica uses two branches, `main` and `dev`. `main` should be considered stable and should **NEVER** be pushed to on its own. `dev` is where main work can happen and is allowed to be unstable and break. Only once `dev` is in a stable state can it be merged into `main` via a pull request.

## Licensing
The Silica library and generator are licensed under the Apache License 2.0, which can be found in the root directory. All third-party licenses are present in the `licenses` folder, including that of the original `easy_reflection_cpp` library.
Any third-party code used by these libraries should have their licenses located within the appropriate project directory (these may not be downloaded until configure-time by Meson).