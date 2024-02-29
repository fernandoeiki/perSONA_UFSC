set (CPM_DOWNLOAD_VERSION 0.32.2)
set (CPM_DOWNLOAD_LOCATION "${CMAKE_BINARY_DIR}/cmake/CPM_${CPM_DOWNLOAD_VERSION}.cmake")

if (NOT (EXISTS ${CPM_DOWNLOAD_LOCATION}))
	message (STATUS "Downloading CPM.cmake")
	file (DOWNLOAD https://github.com/TheLartians/CPM.cmake/releases/download/v${CPM_DOWNLOAD_VERSION}/CPM.cmake
		  ${CPM_DOWNLOAD_LOCATION}
	)
else (NOT (EXISTS ${CPM_DOWNLOAD_LOCATION}))
	message ("CPM already exists, do not need to download")
endif (NOT (EXISTS ${CPM_DOWNLOAD_LOCATION}))

include (${CPM_DOWNLOAD_LOCATION})

CPMAddPackage (
	NAME GrpSrcByDir
	GITHUB_REPOSITORY TheLartians/GroupSourcesByFolder.cmake
	VERSION 1.0
	DOWNLOAD_ONLY YES # Delay the inclusion of this to after the patch
)

if (GrpSrcByDir_ADDED)
	find_package (Git 2.29 REQUIRED)
	execute_process (
		COMMAND ${GIT_EXECUTABLE} apply --check "${CMAKE_CURRENT_LIST_DIR}/patches/source_group_rel_path.patch"
		RESULT_VARIABLE patch_ok
		WORKING_DIRECTORY ${GrpSrcByDir_SOURCE_DIR}
		ERROR_QUIET
	)

	if (${patch_ok} STREQUAL "0")
		execute_process (
			COMMAND ${GIT_EXECUTABLE} apply --whitespace=fix
					"${CMAKE_CURRENT_LIST_DIR}/patches/source_group_rel_path.patch"
			RESULT_VARIABLE patch_ok
			WORKING_DIRECTORY ${GrpSrcByDir_SOURCE_DIR}
		)
	endif ()

	# The file is now pathced, add it
	add_subdirectory (${GrpSrcByDir_SOURCE_DIR} ${GrpSrcByDir_BINARY_DIR})
endif ()

CPMAddPackage (
	NAME PkgProj
	VERSION 1.8.0
	GITHUB_REPOSITORY TheLartians/PackageProject.cmake
	DOWNLOAD_ONLY YES # Delay the inclusion of this to after the patch
)

if (PkgProj_ADDED)
	find_package (Git 2.29 REQUIRED)
	execute_process (
		COMMAND ${GIT_EXECUTABLE} apply --check "${CMAKE_CURRENT_LIST_DIR}/patches/change_install_dir.patch"
		RESULT_VARIABLE patch_ok
		WORKING_DIRECTORY ${PkgProj_SOURCE_DIR}
		ERROR_QUIET
	)

	if (${patch_ok} STREQUAL "0")
		execute_process (
			COMMAND ${GIT_EXECUTABLE} apply --whitespace=fix
					"${CMAKE_CURRENT_LIST_DIR}/patches/change_install_dir.patch"
			RESULT_VARIABLE patch_ok
			WORKING_DIRECTORY ${PkgProj_SOURCE_DIR}
		)
	endif ()

	# The file is now pathced, add it
	add_subdirectory (${PkgProj_SOURCE_DIR} ${PkgProj_BINARY_DIR})
endif ()

CPMAddPackage (
	NAME Format.cmake
	VERSION 1.7.2
	GITHUB_REPOSITORY TheLartians/Format.cmake
	OPTIONS "FORMAT_SKIP_CMAKE NO"
)

if (Format.cmake_ADDED)
	set_target_properties (format check-format fix-format PROPERTIES FOLDER "format_tools")
	set_target_properties (
		clang-format cmake-format check-clang-format check-cmake-format fix-clang-format fix-cmake-format
		PROPERTIES FOLDER "format_tools/helpers"
	)
endif ()

CPMAddPackage (
	NAME sndfile
	GITHUB_REPOSITORY libsndfile/libsndfile
	GIT_TAG 1.0.31
	OPTIONS "BUILD_PROGRAMS OFF" "BUILD_EXAMPLES OFF" "BUILD_SHARED_LIBS OFF" "BUILD_TESTING OFF" "INSTALL_MANPAGES OFF"
			"ENABLE_PACKAGE_CONFIG OFF"
	EXCLUDE_FROM_ALL TRUE
)

if (sndfile_ADDED)
	set_property (TARGET sndfile PROPERTY FOLDER "external_libs")

	set_target_properties (
		sndfile PROPERTIES PUBLIC_HEADER
						   "${sndfile_BINARY_DIR}/include/sndfile.h;${sndfile_SOURCE_DIR}/include/sndfile.hh"
	)

	packageProject (
		NAME sndfile
		VERSION 1.0.31
		BINARY_DIR ${PROJECT_BINARY_DIR}
		INCLUDE_DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
		NAMESPACE Sndfile
		DISABLE_VERSION_SUFFIX YES
	)
endif ()

CPMAddPackage (
	NAME samplerate
	GITHUB_REPOSITORY libsndfile/libsamplerate
	GIT_TAG 0.2.1
	OPTIONS "LIBSAMPLERATE_EXAMPLES OFF" "BUILD_TESTING OFF" "LIBSAMPLERATE_INSTALL OFF" "BUILD_SHARED_LIBS ON"
	EXCLUDE_FROM_ALL TRUE
)

if (samplerate_ADDED)
	set_property (TARGET samplerate PROPERTY FOLDER "external_libs")

	packageProject (
		NAME samplerate
		VERSION 0.2.1
		BINARY_DIR ${PROJECT_BINARY_DIR}
		INCLUDE_DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
		NAMESPACE SampleRate
		DISABLE_VERSION_SUFFIX YES
	)
endif ()

file (DOWNLOAD https://people.sc.fsu.edu/~jburkardt/c_src/spline/spline.h
	  ${CMAKE_CURRENT_BINARY_DIR}/_external/spline/include/spline.h
)
file (DOWNLOAD https://people.sc.fsu.edu/~jburkardt/c_src/spline/spline.c
	  ${CMAKE_CURRENT_BINARY_DIR}/_external/spline/src/spline.c
)

if (EXISTS ${CMAKE_CURRENT_BINARY_DIR}/_external/spline/include/spline.h
	AND EXISTS ${CMAKE_CURRENT_BINARY_DIR}/_external/spline/src/spline.c
)
	file (READ ${CMAKE_CURRENT_BINARY_DIR}/_external/spline/include/spline.h spline_code)
	string (REPLACE double float spline_code "${spline_code}")
	file (WRITE ${CMAKE_CURRENT_BINARY_DIR}/_external/spline/include/spline.h "${spline_code}")

	file (READ ${CMAKE_CURRENT_BINARY_DIR}/_external/spline/src/spline.c spline_code)
	string (REPLACE double float spline_code "${spline_code}")
	file (WRITE ${CMAKE_CURRENT_BINARY_DIR}/_external/spline/src/spline.c "${spline_code}")

	add_library (
		spline STATIC ${CMAKE_CURRENT_BINARY_DIR}/_external/spline/include/spline.h
					  ${CMAKE_CURRENT_BINARY_DIR}/_external/spline/src/spline.c
	)
	add_library (Spline::spline ALIAS spline)

	set_source_files_properties (${CMAKE_CURRENT_BINARY_DIR}/_external/spline/src/spline.c PROPERTIES LANGUAGE CXX)

	target_include_directories (
		spline SYSTEM PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/_external/spline/include>
							 $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/spline>
	)

	set_property (TARGET spline PROPERTY FOLDER "external_libs")

	packageProject (
		NAME spline
		VERSION 1.0
		BINARY_DIR ${PROJECT_BINARY_DIR}
		INCLUDE_DIR ${CMAKE_CURRENT_BINARY_DIR}/_external/spline/include
		INCLUDE_DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/spline
		NAMESPACE Spline
		DISABLE_VERSION_SUFFIX YES
	)
endif ()

CPMAddPackage (
	NAME vista
	GIT_REPOSITORY https://git.rwth-aachen.de/ita/ViSTA
	GIT_TAG feature/ita
	DOWNLOAD_ONLY YES
)

if (vista_ADDED)
	find_package (Git 2.29 REQUIRED)
	execute_process (
		COMMAND ${GIT_EXECUTABLE} apply --check "${CMAKE_CURRENT_LIST_DIR}/patches/remove_unary_function.patch"
		RESULT_VARIABLE patch_ok
		WORKING_DIRECTORY ${vista_SOURCE_DIR}
		ERROR_QUIET
	)

	if (${patch_ok} STREQUAL "0")
		execute_process (
			COMMAND ${GIT_EXECUTABLE} apply --whitespace=fix
					"${CMAKE_CURRENT_LIST_DIR}/patches/remove_unary_function.patch"
			RESULT_VARIABLE patch_ok
			WORKING_DIRECTORY ${vista_SOURCE_DIR}
		)
	endif ()

	# ##################################################################################################################
	# vista_base
	# ##################################################################################################################

	file (GLOB_RECURSE vista_base_sources ${vista_SOURCE_DIR}/VistaCoreLibs/VistaBase/**.cpp)

	file (GLOB_RECURSE vista_base_headers ${vista_SOURCE_DIR}/VistaCoreLibs/VistaBase/**.h)

	add_library (vista_base ${vista_base_sources} ${vista_base_headers})
	add_library (vista::vista_base ALIAS vista_base)

	set_target_properties (vista_base PROPERTIES PUBLIC_HEADER "${vista_base_headers}")
	target_compile_features (vista_base PUBLIC cxx_std_17)

	target_include_directories (
		vista_base PUBLIC $<BUILD_INTERFACE:${vista_SOURCE_DIR}/VistaCoreLibs>
						  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/VistaBase>
	)

	set_property (TARGET vista_base PROPERTY FOLDER "vista_libs")

	if (BUILD_SHARED_LIBS AND NOT ITA_VISTA_BUILD_STATIC)
		target_compile_definitions (vista_base PUBLIC VISTABASE_EXPORTS)
	else ()
		target_compile_definitions (vista_base PUBLIC VISTABASE_STATIC)
	endif ()

	packageProject (
		NAME vista_base
		VERSION 1.16.0
		BINARY_DIR ${PROJECT_BINARY_DIR}
		INCLUDE_DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/VistaBase
		NAMESPACE vista
		DISABLE_VERSION_SUFFIX YES
	)

	# ##################################################################################################################
	# vista_aspects
	# ##################################################################################################################

	file (GLOB_RECURSE vista_aspects_sources ${vista_SOURCE_DIR}/VistaCoreLibs/VistaAspects/**.cpp)

	file (GLOB_RECURSE vista_aspects_headers ${vista_SOURCE_DIR}/VistaCoreLibs/VistaAspects/**.h)

	add_library (vista_aspects ${vista_aspects_sources} ${vista_aspects_headers})
	add_library (vista::vista_aspects ALIAS vista_aspects)

	set_target_properties (vista_aspects PROPERTIES PUBLIC_HEADER "${vista_aspects_headers}")
	target_compile_features (vista_aspects PUBLIC cxx_std_17)

	target_include_directories (
		vista_aspects PUBLIC $<BUILD_INTERFACE:${vista_SOURCE_DIR}/VistaCoreLibs>
							 $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/VistaAspects>
	)

	target_link_libraries (vista_aspects PUBLIC vista::vista_base)

	if (UNIX AND NOT APPLE)
		target_link_libraries (vista_aspects PUBLIC rt)
	endif ()

	set_property (TARGET vista_aspects PROPERTY FOLDER "vista_libs")

	if (BUILD_SHARED_LIBS AND NOT ITA_VISTA_BUILD_STATIC)
		target_compile_definitions (vista_aspects PUBLIC VISTAASPECTS_EXPORTS)
	else ()
		target_compile_definitions (vista_aspects PUBLIC VISTAASPECTS_STATIC)
	endif ()

	packageProject (
		NAME vista_aspects
		VERSION 1.16.0
		BINARY_DIR ${PROJECT_BINARY_DIR}
		INCLUDE_DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/VistaAspects
		NAMESPACE vista
		DISABLE_VERSION_SUFFIX YES
	)

	# ##################################################################################################################
	# vista_inter_proc_comm
	# ##################################################################################################################

	file (GLOB_RECURSE vista_inter_proc_comm_sources ${vista_SOURCE_DIR}/VistaCoreLibs/VistaInterProcComm/**.cpp)

	file (GLOB_RECURSE vista_inter_proc_comm_headers ${vista_SOURCE_DIR}/VistaCoreLibs/VistaInterProcComm/**.h)

	add_library (vista_inter_proc_comm ${vista_inter_proc_comm_sources} ${vista_inter_proc_comm_headers})
	add_library (vista::vista_inter_proc_comm ALIAS vista_inter_proc_comm)

	set_target_properties (vista_inter_proc_comm PROPERTIES PUBLIC_HEADER "${vista_inter_proc_comm_headers}")
	target_compile_features (vista_inter_proc_comm PUBLIC cxx_std_17)
	target_compile_definitions (vista_inter_proc_comm PRIVATE _HAS_STD_BYTE=0)

	target_include_directories (
		vista_inter_proc_comm PUBLIC $<BUILD_INTERFACE:${vista_SOURCE_DIR}/VistaCoreLibs>
									 $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/VistaInterProcComm>
	)

	target_link_libraries (vista_inter_proc_comm PUBLIC vista::vista_base vista::vista_aspects)

	if (WIN32)
		target_compile_definitions (vista_inter_proc_comm PUBLIC _USE_WIN32_MUTEX)
		target_link_libraries (vista_inter_proc_comm PUBLIC winmm ws2_32)
	elseif (UNIX)
		target_link_libraries (vista_inter_proc_comm PUBLIC pthread)
	endif ()

	option (VISTACORELIBS_IPC_USE_EXCEPTIONS "Specifies wether or nor the IPC throws exceptions when errors occur" ON)

	if (VISTACORELIBS_IPC_USE_EXCEPTIONS)
		target_compile_definitions (vista_inter_proc_comm PUBLIC VISTA_IPC_USE_EXCEPTIONS)
	endif (VISTACORELIBS_IPC_USE_EXCEPTIONS)

	set_property (TARGET vista_inter_proc_comm PROPERTY FOLDER "vista_libs")

	if (BUILD_SHARED_LIBS AND NOT ITA_VISTA_BUILD_STATIC)
		target_compile_definitions (vista_inter_proc_comm PUBLIC VISTAINTERPROCCOMM_EXPORTS)
	else ()
		target_compile_definitions (vista_inter_proc_comm PUBLIC VISTAINTERPROCCOMM_STATIC)
	endif ()

	packageProject (
		NAME vista_inter_proc_comm
		VERSION 1.16.0
		BINARY_DIR ${PROJECT_BINARY_DIR}
		INCLUDE_DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/VistaInterProcComm
		NAMESPACE vista
		DISABLE_VERSION_SUFFIX YES
	)

	# ##################################################################################################################
	# vista_math
	# ##################################################################################################################

	file (GLOB_RECURSE vista_math_sources ${vista_SOURCE_DIR}/VistaCoreLibs/VistaMath/**.cpp)

	file (GLOB_RECURSE vista_math_headers ${vista_SOURCE_DIR}/VistaCoreLibs/VistaMath/**.h)

	add_library (vista_math ${vista_math_sources} ${vista_math_headers})
	add_library (vista::vista_math ALIAS vista_math)

	set_target_properties (vista_math PROPERTIES PUBLIC_HEADER "${vista_math_headers}")
	target_compile_features (vista_math PUBLIC cxx_std_17)

	target_include_directories (
		vista_math PUBLIC $<BUILD_INTERFACE:${vista_SOURCE_DIR}/VistaCoreLibs>
						  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/VistaMath>
	)

	target_link_libraries (vista_math PUBLIC vista::vista_base)

	set_property (TARGET vista_math PROPERTY FOLDER "vista_libs")

	if (BUILD_SHARED_LIBS AND NOT ITA_VISTA_BUILD_STATIC)
		target_compile_definitions (vista_math PUBLIC VISTAMATH_EXPORTS)
	else ()
		target_compile_definitions (vista_math PUBLIC VISTAMATH_STATIC)
	endif ()

	packageProject (
		NAME vista_math
		VERSION 1.16.0
		BINARY_DIR ${PROJECT_BINARY_DIR}
		INCLUDE_DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/VistaMath
		NAMESPACE vista
		DISABLE_VERSION_SUFFIX YES
	)

	# ##################################################################################################################
	# vista_tools
	# ##################################################################################################################

	file (GLOB vista_tools_sources ${vista_SOURCE_DIR}/VistaCoreLibs/VistaTools/**.cpp)

	file (GLOB vista_tools_headers ${vista_SOURCE_DIR}/VistaCoreLibs/VistaTools/**.h)

	add_library (vista_tools ${vista_tools_sources} ${vista_tools_headers})
	add_library (vista::vista_tools ALIAS vista_tools)

	set_target_properties (vista_tools PROPERTIES PUBLIC_HEADER "${vista_tools_headers}")
	target_compile_features (vista_tools PUBLIC cxx_std_17)

	target_include_directories (
		vista_tools PUBLIC $<BUILD_INTERFACE:${vista_SOURCE_DIR}/VistaCoreLibs>
						   $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/VistaTools>
	)

	target_link_libraries (
		vista_tools PUBLIC vista::vista_base vista::vista_aspects vista::vista_inter_proc_comm vista::vista_math
	)

	if (WIN32)
		target_link_libraries (vista_tools PUBLIC PowrProf dbghelp Psapi)
	else ()
		target_link_libraries (vista_tools PUBLIC dl)
	endif ()

	set_property (TARGET vista_tools PROPERTY FOLDER "vista_libs")

	if (BUILD_SHARED_LIBS AND NOT ITA_VISTA_BUILD_STATIC)
		target_compile_definitions (vista_tools PUBLIC VISTATOOLS_EXPORTS)
	else ()
		target_compile_definitions (vista_tools PUBLIC VISTATOOLS_STATIC)
	endif ()

	packageProject (
		NAME vista_tools
		VERSION 1.16.0
		BINARY_DIR ${PROJECT_BINARY_DIR}
		INCLUDE_DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/VistaTools
		NAMESPACE vista
		DISABLE_VERSION_SUFFIX YES
	)

endif ()

if (ITA_BASE_WITH_REGULAR_EXPRESSIONS)
	CPMAddPackage (
		NAME pcre
		URL https://sourceforge.net/projects/pcre/files/pcre/8.45/pcre-8.45.tar.bz2
		OPTIONS "PCRE_BUILD_PCREGREP OFF" "PCRE_BUILD_TESTS OFF" "PCRE_SHOW_REPORT OFF" "BUILD_SHARED_LIBS OFF"
				"CMAKE_SKIP_INSTALL_RULES TRUE"
		EXCLUDE_FROM_ALL TRUE
	)

	if (pcre_ADDED)
		set_property (TARGET pcre PROPERTY FOLDER "external_libs")
		set_property (TARGET pcrecpp PROPERTY FOLDER "external_libs")
		set_property (TARGET pcreposix PROPERTY FOLDER "external_libs")
		target_include_directories (
			pcre PUBLIC $<BUILD_INTERFACE:${pcre_SOURCE_DIR}> $<BUILD_INTERFACE:${pcre_BINARY_DIR}>
		)
		target_include_directories (
			pcrecpp PUBLIC $<BUILD_INTERFACE:${pcre_SOURCE_DIR}> $<BUILD_INTERFACE:${pcre_BINARY_DIR}>
		)
		# target_link_libraries(pcrecpp PRIVATE pcre) target_include_directories(pcrecpp PUBLIC ${pcre_SOURCE_DIR})
	endif ()

	set_target_properties (pcre PROPERTIES PUBLIC_HEADER ${pcre_BINARY_DIR}/pcre.h)

	set_target_properties (
		pcrecpp
		PROPERTIES
			PUBLIC_HEADER
			"${pcre_SOURCE_DIR}/pcrecpp.h;${pcre_SOURCE_DIR}/pcre_scanner.h;${pcre_BINARY_DIR}/pcrecpparg.h;${pcre_BINARY_DIR}/pcre_stringpiece.h;${pcre_BINARY_DIR}/pcre.h"
	)

	packageProject (
		NAME pcre
		VERSION 8.45
		BINARY_DIR ${PROJECT_BINARY_DIR}
		INCLUDE_DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
		NAMESPACE pcre
		DISABLE_VERSION_SUFFIX YES
	)

	packageProject (
		NAME pcrecpp
		VERSION 8.45
		BINARY_DIR ${PROJECT_BINARY_DIR}
		INCLUDE_DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
		NAMESPACE pcre
		DISABLE_VERSION_SUFFIX YES
	)

endif ()

CPMAddPackage (
	NAME nlohmann_json
	GITHUB_REPOSITORY nlohmann/json
	VERSION 3.10.1
	OPTIONS "JSON_BuildTests OFF" "JSON_Install ON"
)

CPMAddPackage (
	NAME eigen
	GIT_REPOSITORY https://gitlab.com/libeigen/eigen
	GIT_TAG 3.4.0
	OPTIONS "EIGEN_BUILD_DOC OFF" "BUILD_TESTING OFF"
)

if (eigen_ADDED)
	set_target_properties (
		blas
		demos
		eigen_blas
		eigen_blas_static
		lapack
		eigen_lapack
		eigen_lapack_static
		uninstall
		PROPERTIES FOLDER external_libs/eigen
	)
endif ()
