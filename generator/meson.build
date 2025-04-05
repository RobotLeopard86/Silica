# Simple dependencies
cli11_dep = subproject('cli11', required: true).get_variable('CLI11_dep')
inja_dep = subproject('inja', required: true, default_options: {
	'build_tests': false
}).get_variable('inja_dep')

# CMake setup (for LLVM/Clang)
cmake = import('cmake')
cmake_build_type = ''
cmake_msvc_lib = 'MultiThreaded'
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
cmake_msvc_lib += 'DLL'

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
	'LLVM_TARGETS_TO_BUILD': 'host',
	'LLVM_ENABLE_PROJECTS': 'clang',
	'CMAKE_POSITION_INDEPENDENT_CODE': 'ON',
	'CMAKE_POLICY_DEFAULT_CMP0156': 'NEW',
	'CMAKE_POLICY_DEFAULT_CMP0126': 'NEW',
	'CMAKE_MSVC_RUNTIME_LIBRARY': cmake_msvc_lib,
	'CMAKE_BUILD_TYPE': cmake_build_type
})
llvm_opts.append_compile_args('cpp', ['-I' + meson.current_source_dir(), '-Wno-unused-command-line-argument', '-DCLANG_BUILD_STATIC'])
llvm = cmake.subproject('llvm', options: llvm_opts, required: true)

# LLVM/Clang dependencies
clang_analysis_dep = llvm.dependency('clangAnalysis')
clang_apinotes_dep = llvm.dependency('clangAPINotes')
clang_ast_dep = llvm.dependency('clangAST')
clang_astmatchers_dep = llvm.dependency('clangASTMatchers')
clang_basic_dep = llvm.dependency('clangBasic')
clang_driver_dep = llvm.dependency('clangDriver')
clang_edit_dep = llvm.dependency('clangEdit')
clang_frontend_dep = llvm.dependency('clangFrontend')
clang_lex_dep = llvm.dependency('clangLex')
clang_parse_dep = llvm.dependency('clangParse')
clang_sema_dep = llvm.dependency('clangSema')
clang_serialization_dep = llvm.dependency('clangSerialization')
clang_support_dep = llvm.dependency('clangSupport')
clang_tooling_dep = llvm.dependency('clangTooling')
libclang_dep = llvm.dependency('libclang')
llvm_analysis_dep = llvm.dependency('LLVMAnalysis')
llvm_asmparser_dep = llvm.dependency('LLVMAsmParser')
llvm_binaryformat_dep = llvm.dependency('LLVMBinaryFormat')
llvm_bitreader_dep = llvm.dependency('LLVMBitReader')
llvm_bitstreamreader_dep = llvm.dependency('LLVMBitstreamReader')
llvm_core_dep = llvm.dependency('LLVMCore')
llvm_debuginfocodeview_dep = llvm.dependency('LLVMDebugInfoCodeView')
llvm_debuginfodwarf_dep = llvm.dependency('LLVMDebugInfoDWARF')
llvm_debuginfopdb_dep = llvm.dependency('LLVMDebugInfoPDB')
llvm_demangle_dep = llvm.dependency('LLVMDemangle')
llvm_frontendatomic_dep = llvm.dependency('LLVMFrontendAtomic')
llvm_frontendoffloading_dep = llvm.dependency('LLVMFrontendOffloading')
llvm_frontendopenmp_dep = llvm.dependency('LLVMFrontendOpenMP')
llvm_irreader_dep = llvm.dependency('LLVMIRReader')
llvm_mc_dep = llvm.dependency('LLVMMC')
llvm_mca_dep = llvm.dependency('LLVMMCA')
llvm_mcparser_dep = llvm.dependency('LLVMMCParser')
llvm_object_dep = llvm.dependency('LLVMObject')
llvm_option_dep = llvm.dependency('LLVMOption')
llvm_profiledata_dep = llvm.dependency('LLVMProfileData')
llvm_remarks_dep = llvm.dependency('LLVMRemarks')
llvm_scalaropts_dep = llvm.dependency('LLVMScalarOpts')
llvm_support_dep = llvm.dependency('LLVMSupport')
llvm_supportblake3_dep = llvm.dependency('LLVMSupportBlake3')
llvm_targetparser_dep = llvm.dependency('LLVMTargetParser')
llvm_textapi_dep = llvm.dependency('LLVMTextAPI')
llvm_transformutils_dep = llvm.dependency('LLVMTransformUtils')
llvm_windowsdriver_dep = llvm.dependency('LLVMWindowsDriver')

deps = [
	cli11_dep, inja_dep, clang_analysis_dep, clang_apinotes_dep, clang_ast_dep, clang_astmatchers_dep, clang_basic_dep, clang_driver_dep, clang_edit_dep, clang_frontend_dep, clang_lex_dep, clang_parse_dep,
	clang_sema_dep, clang_serialization_dep, clang_support_dep, clang_tooling_dep, libclang_dep, llvm_analysis_dep, llvm_asmparser_dep, llvm_binaryformat_dep, llvm_bitreader_dep, llvm_bitstreamreader_dep,
	llvm_core_dep, llvm_debuginfodwarf_dep, llvm_demangle_dep, llvm_frontendatomic_dep, llvm_frontendoffloading_dep, llvm_frontendopenmp_dep, llvm_irreader_dep, llvm_mc_dep, llvm_mca_dep, llvm_mcparser_dep,
	llvm_object_dep, llvm_option_dep, llvm_profiledata_dep, llvm_remarks_dep, llvm_scalaropts_dep, llvm_support_dep, llvm_supportblake3_dep, llvm_targetparser_dep, llvm_textapi_dep, llvm_transformutils_dep,
	llvm_windowsdriver_dep]

# Windows libraries
if host_machine.system() == 'windows'
	cxx = meson.get_compiler('cpp')
	deps += cxx.find_library('Version', required: true)
	deps += cxx.find_library('ntdll', required: true)
endif

# Define sources
generator_sources = [
	'main.cpp',
	'tools' / 'files.cpp',
	'parser' / 'parser.cpp'
]

# Executable
silica_generator = executable('silica', generator_sources, dependencies: deps, cpp_args: ['-DPROJECT_VER="' + meson.project_version() + '"'])