# Generate reflection info
reflection = custom_target('example.silica.[cpph]', output: ['example.silica.hpp', 'example.silica.cpp'], input: silica_exe, 
	command: [silica_exe, '-c', meson.global_build_root(), '-o', meson.current_build_dir(), '-p', 'example', meson.current_source_dir() / 'data'])

# Create program
executable('silica_example', 'main.cpp', reflection, include_directories: include_directories('data'), dependencies: silica_dep, pie: true)