project('silica', 'cpp', version: '0.2.0', meson_version: '>=1.2.0', license: 'Apache-2.0', default_options: ['cpp_std=c++20', 'default_library=static'])

# Build library
subdir('src')

# Build generator if requested
if get_option('generator')
	subdir('generator')
endif