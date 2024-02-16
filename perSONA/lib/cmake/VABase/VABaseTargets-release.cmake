#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "VA::VABase" for configuration "Release"
set_property(TARGET VA::VABase APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(VA::VABase PROPERTIES
  IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/lib/VABase/VABase.lib"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/VABase.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS VA::VABase )
list(APPEND _IMPORT_CHECK_FILES_FOR_VA::VABase "${_IMPORT_PREFIX}/lib/VABase/VABase.lib" "${_IMPORT_PREFIX}/bin/VABase.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
