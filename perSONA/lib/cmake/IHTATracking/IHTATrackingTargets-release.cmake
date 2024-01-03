#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "IHTA::IHTATracking" for configuration "Release"
set_property(TARGET IHTA::IHTATracking APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(IHTA::IHTATracking PROPERTIES
  IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/lib/IHTATracking/IHTATracking.lib"
  IMPORTED_LINK_DEPENDENT_LIBRARIES_RELEASE "NatNetSDK"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/IHTATracking.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS IHTA::IHTATracking )
list(APPEND _IMPORT_CHECK_FILES_FOR_IHTA::IHTATracking "${_IMPORT_PREFIX}/lib/IHTATracking/IHTATracking.lib" "${_IMPORT_PREFIX}/bin/IHTATracking.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
