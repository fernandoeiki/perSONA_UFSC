#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "vista::vista_aspects" for configuration "Release"
set_property(TARGET vista::vista_aspects APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(vista::vista_aspects PROPERTIES
  IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/lib/vista_aspects/vista_aspects.lib"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/vista_aspects.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS vista::vista_aspects )
list(APPEND _IMPORT_CHECK_FILES_FOR_vista::vista_aspects "${_IMPORT_PREFIX}/lib/vista_aspects/vista_aspects.lib" "${_IMPORT_PREFIX}/bin/vista_aspects.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
