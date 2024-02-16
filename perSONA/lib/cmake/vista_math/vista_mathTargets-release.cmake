#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "vista::vista_math" for configuration "Release"
set_property(TARGET vista::vista_math APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(vista::vista_math PROPERTIES
  IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/lib/vista_math/vista_math.lib"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/vista_math.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS vista::vista_math )
list(APPEND _IMPORT_CHECK_FILES_FOR_vista::vista_math "${_IMPORT_PREFIX}/lib/vista_math/vista_math.lib" "${_IMPORT_PREFIX}/bin/vista_math.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
