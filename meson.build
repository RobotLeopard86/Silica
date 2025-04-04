project('silica', 'cpp', version: '0.2.3', meson_version: '>=1.2.0', license: 'Apache-2.0', default_options: ['cpp_std=c++20', 'default_library=static', 'b_vscrt=from_buildtype'])

bt = get_option('buildtype')

# Define debug macro
if bt.contains('debug')
	add_project_arguments(['-D_DEBUG'], language: 'cpp')
endif

# Set some Windows-specific options
if host_machine.system() == 'windows'
	add_project_arguments(['-D_DLL', '-D_MT'], language: 'cpp')
	if bt == 'debug'
		add_project_arguments('-D_ITERATOR_DEBUG_LEVEL=2', language: 'cpp')
	endif
endif

# Get options
example = get_option('example')
generator = get_option('generator')

if example and not generator
	error('Cannot build example without generator!')
endif

# Build library
subdir('src')

# Build generator if requested
if generator
	subdir('generator')
endif

# Build example if requested
if example
	subdir('example')
endif
