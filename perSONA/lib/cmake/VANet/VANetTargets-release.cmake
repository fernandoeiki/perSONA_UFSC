#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "VANet::VANet" for configuration "Release"
set_property(TARGET VANet::VANet APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(VANet::VANet PROPERTIES
  IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/lib/VANet/VANet.lib"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/VANet.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS VANet::VANet )
list(APPEND _IMPORT_CHECK_FILES_FOR_VANet::VANet "${_IMPORT_PREFIX}/lib/VANet/VANet.lib" "${_IMPORT_PREFIX}/bin/VANet.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
