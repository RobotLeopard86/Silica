# Generate reflection info
reflection = custom_target('example.silica.[cpphpp]', output: ['example.silica.hpp', 'example.silica.cpp'], input: ['data' / 'car.hpp', 'data' / 'colors.hpp', 'data' / 'suv.hpp'], 
	command: [silica_generator, '-c', meson.global_build_root(), '-o', meson.current_build_dir(), '-p', 'example', meson.current_source_dir() / 'data'])

# Create program
executable('silica_example', 'main.cpp', reflection, include_directories: include_directories('data'), dependencies: silica_dep, cpp_args: '-Wno-unknown-attributes')