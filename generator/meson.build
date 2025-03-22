# Simple dependencies
cli11_dep = subproject('cli11', required: true, default_options: {
	'use_precompiled': true,
	'tests': false
}).get_variable('CLI11_dep')
inja_dep = subproject('inja', required: true, default_options: {
	'build_tests': false
}).get_variable('inja_dep')

# CMake setup (for LLVM/Clang)
cmake = import('cmake')
cmake_build_type = ''
bt = get_option('buildtype')
if bt.contains('debug')
	if bt == 'debug'
		cmake_build_type = 'Debug'
		cmake_msvc_lib += 'Debug'
	else
		cmake_build_type = 'RelWithDebInfo'
	endif
elif bt == 'plain' or bt == 'minsize'
	cmake_build_type = 'MinSizeRel'
elif bt == 'release'
	cmake_build_type = 'Release'
else
	error('Unsupported build type!')
endif

# LLVM/Clang setup
llvm_opts = cmake.subproject_options()
llvm_opts.add_cmake_defines({
	'BUILD_SHARED_LIBS': 'OFF',
	'CLANG_BUILD_TOOLS': 'ON',
	'CLANG_BUILD_EXAMPLES': 'OFF',
	'CLANG_ENABLE_ARCMT': 'OFF',
	'CLANG_ENABLE_LIBXML2': 'OFF',
	'CLANG_ENABLE_STATIC_ANALYZER': 'FALSE',
	'CLANG_INCLUDE_DOCS': 'OFF',
	'CLANG_INCLUDE_TESTS': 'OFF',
	'LIBCLANG_BUILD_STATIC': 'ON',
	'LLVM_BUILD_UTILS': 'ON',
	'LLVM_BUILD_RUNTIME': 'OFF',
	'LLVM_BUILD_RUNTIMES': 'OFF',
	'LLVM_BUILD_DOCS': 'OFF',
	'LLVM_BUILD_EXAMPLES': 'OFF',
	'LLVM_BUILD_TOOLS': 'OFF',
	'LLVM_ENABLE_BINDINGS': 'OFF',
	'LLVM_ENABLE_CURL': 'OFF',
	'LLVM_ENABLE_IDE': 'ON',
	'LLVM_ENABLE_LIBEDIT': 'OFF',
	'LLVM_ENABLE_LIBPFM': 'OFF',
	'LLVM_ENABLE_LIBXML2': 'OFF',
	'LLVM_ENABLE_OCAMLDOC': 'OFF',
	'LLVM_ENABLE_PIC': 'ON',
	'LLVM_ENABLE_RTTI': 'ON',
	'LLVM_ENABLE_ZLIB': 'OFF',
	'LLVM_ENABLE_ZSTD': 'OFF',
	'LLVM_INCLUDE_BENCHMARKS': 'OFF',
	'LLVM_INCLUDE_DOCS': 'OFF',
	'LLVM_INCLUDE_EXAMPLES': 'OFF',
	'LLVM_INCLUDE_RUNTIMES': 'OFF',
	'LLVM_INCLUDE_TESTS': 'OFF',
	'LLVM_INCLUDE_TOOLS': 'OFF',
	'LLVM_INCLUDE_UTILS': 'ON',
	'LLVM_TARGETS_TO_BUILD': '',
	'LLVM_ENABLE_PROJECTS': 'clang',
	'CMAKE_POSITION_INDEPENDENT_CODE': 'ON',
	'CMAKE_POLICY_DEFAULT_CMP0156': 'NEW',
	'CMAKE_BUILD_TYPE': cmake_build_type,
	'CMAKE_MSVC_RUNTIME_LIBRARY': cmake_msvc_lib,
})
llvm = cmake.subproject('er-cpp', options: llvm_opts, required: true)

# LLVM/Clang dependencies
clang_ast_dep = llvm.dependency('clangAST')
clang_ast_matchers_dep = llvm.dependency('clangASTMatchers')
clang_frontend_dep = llvm.dependency('clangFrontend')
clang_lex_dep = llvm.dependency('clangLex')
clang_tooling_dep = llvm.dependency('clangTooling')

# Define includes
gen_includes = include_directories('include')

# Note: Parser is being updated, so for now the rest of the parser stuff will not be implemented