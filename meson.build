project('silica', 'cpp', version: '0.2.2', meson_version: '>=1.2.0', license: 'Apache-2.0', default_options: ['cpp_std=c++20', 'default_library=static'])

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
