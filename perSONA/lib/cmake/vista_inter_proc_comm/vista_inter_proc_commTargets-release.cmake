#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "vista::vista_inter_proc_comm" for configuration "Release"
set_property(TARGET vista::vista_inter_proc_comm APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(vista::vista_inter_proc_comm PROPERTIES
  IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/lib/vista_inter_proc_comm/vista_inter_proc_comm.lib"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/vista_inter_proc_comm.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS vista::vista_inter_proc_comm )
list(APPEND _IMPORT_CHECK_FILES_FOR_vista::vista_inter_proc_comm "${_IMPORT_PREFIX}/lib/vista_inter_proc_comm/vista_inter_proc_comm.lib" "${_IMPORT_PREFIX}/bin/vista_inter_proc_comm.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
