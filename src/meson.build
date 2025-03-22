# nhlomann json
nlohmann_json_dep = subproject('nlohmannjson', required: true).get_variable('nlohmann_json_dep')

# RE-flex
reflex = subproject('reflex', required: true, default_options: {
	'default_library': 'static'
})
reflex_exe = reflex.get_variable('reflex')
reflex_dep = reflex.get_variable('reflex_dep')

# Copy position.hpp header to generated sources directory
import('fs').copyfile('serialization' / 'position.hpp', 'position.hpp')

# Generate lexer files
json_lex = custom_target('lexer_json.yy.[cpph]', 
	output: ['lexer_json.yy.h', 'lexer_json.yy.cpp'],
	input: 'serialization' / 'json' / 'json.l',
	command: [reflex_exe, '@INPUT@', '--outfile=src' / 'lexer_json.yy.cpp', '--header-file=' + meson.current_source_dir() / 'serialization' / 'json' / 'lexer_json.yy.h']
)
yaml_lex = custom_target('lexer_yaml.yy.[cpph]', 
	output: ['lexer_yaml.yy.h', 'lexer_yaml.yy.cpp'],
	input: 'serialization' / 'yaml' / 'yaml.l',
	command: [reflex_exe, '@INPUT@', '--outfile=src' / 'lexer_yaml.yy.cpp', '--header-file=' + meson.current_source_dir() / 'serialization' / 'yaml' / 'lexer_yaml.yy.h']
)

# Define sources
silica_sources = [
	'err_helper.cpp',
	'reflection' / 'reflection.cpp',
	'variable' / 'box.cpp',
	'variable' / 'var.cpp',
	'tools' / 'stringify.cpp',
	'serialization' / 'binary' / 'binary.cpp',
	'serialization' / 'json' / 'json.cpp',
	'serialization' / 'json' / 'parser_json.cpp',
	json_lex,
	'serialization' / 'yaml' / 'yaml.cpp',
	'serialization' / 'yaml' / 'parser_yaml.cpp',
	yaml_lex
]

# Define includes
includes = include_directories('..' / 'include')

# Library
libsilica = library('silica', silica_sources, include_directories: includes, dependencies: [nlohmann_json_dep, reflex_dep], pic: true)

# Dependency
silica_dep = declare_dependency(link_with: libsilica, include_directories: includes)