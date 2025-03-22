project('silica', 'cpp', version: '0.2.0', meson_version: '>=1.2.0', license: 'Apache-2.0', default_options: ['cpp_std=c++20'])

# Core dependencies
nlohmann_json_dep = subproject('nlohmannjson', required: true).get_variable('nlohmann_json_dep')
reflex_dep = subproject('reflex', required: true, default_options: {
	'default_library': 'static'
}).get_variable('reflex_dep')

# Build generator if requested
if get_option('generator')
	subdir('generator')
endif