#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "vista::vista_base" for configuration "Release"
set_property(TARGET vista::vista_base APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(vista::vista_base PROPERTIES
  IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/lib/vista_base/vista_base.lib"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/vista_base.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS vista::vista_base )
list(APPEND _IMPORT_CHECK_FILES_FOR_vista::vista_base "${_IMPORT_PREFIX}/lib/vista_base/vista_base.lib" "${_IMPORT_PREFIX}/bin/vista_base.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
