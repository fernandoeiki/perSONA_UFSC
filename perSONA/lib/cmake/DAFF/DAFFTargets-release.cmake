#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "DAFF::DAFF" for configuration "Release"
set_property(TARGET DAFF::DAFF APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(DAFF::DAFF PROPERTIES
  IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/lib/DAFF/DAFF.lib"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/DAFF.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS DAFF::DAFF )
list(APPEND _IMPORT_CHECK_FILES_FOR_DAFF::DAFF "${_IMPORT_PREFIX}/lib/DAFF/DAFF.lib" "${_IMPORT_PREFIX}/bin/DAFF.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
