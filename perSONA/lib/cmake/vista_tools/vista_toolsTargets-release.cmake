#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "vista::vista_tools" for configuration "Release"
set_property(TARGET vista::vista_tools APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(vista::vista_tools PROPERTIES
  IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/lib/vista_tools/vista_tools.lib"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/vista_tools.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS vista::vista_tools )
list(APPEND _IMPORT_CHECK_FILES_FOR_vista::vista_tools "${_IMPORT_PREFIX}/lib/vista_tools/vista_tools.lib" "${_IMPORT_PREFIX}/bin/vista_tools.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
