# Silica Quickstart
This guide assumes you are using Meson. If you aren't, you may need to use pre-compiled binaries or find some way to integrate Meson into your system.  
1. Add Silica as a subproject  
    1. Set up a `silica.wrap` file in your `subprojects` directory. It should look something like this:
	```INI
	[wrap-git]
	url = https://github.com/RobotLeopard86/Silica
	depth = 1
	revision = <tag, branch, or commit to clone>
	```
	2. Add these lines to your `meson.build`:
	```Meson
	silica = subproject('silica', required: true, default_options: ['generator=true'])
	silica_generator = silica.get_variable('silica_generator')
	silica_dep = silica.get_variable('silica_dep')
	```  
2. Configure reflection codegen
	1. Create the custom target. It should look something like this:
	```Meson
	reflection = custom_target('example.silica.[cpphpp]', output: ['example.silica.hpp', 'example.silica.cpp'], input: [<input header files>], 
	command: [silica_generator, '-c', meson.global_build_root(), '-o', meson.current_build_dir(), '-p', 'example', '<path to header file directory to scan>'])
	```
	2. Add the custom target to your executable sources
	3. Add `silica_dep` to your dependencies
	4. Not strictly necessary, but recommended: add `-Wno-unknown-attributes` (or equivalent flag) to your extra C++ arguments. This will silence warnings regarding the Silica custom attributes
3. Add reflection attributes
	1. Note: for a class to be reflectable, it must satisfy the `silica::reflection::Reflectable` concept. See [basics.md](basics.md) for what that requires.
	2. Add the `[[silica::reflect]]` attribute to your class (or enum), like this:
	```cpp
	class [[silica::reflect]] SomeClass {...};
	```
4. Reflect!
	1. Include `silica/reflection/reflection.hpp` and your generated reflection header
	2. Use `silica::reflection::reflect(<pointer>)`
