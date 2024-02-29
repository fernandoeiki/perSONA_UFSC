#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "ART::DTrackSDK" for configuration "Release"
set_property(TARGET ART::DTrackSDK APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(ART::DTrackSDK PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/DTrackSDK/DTrackSDK.lib"
  )

list(APPEND _IMPORT_CHECK_TARGETS ART::DTrackSDK )
list(APPEND _IMPORT_CHECK_FILES_FOR_ART::DTrackSDK "${_IMPORT_PREFIX}/lib/DTrackSDK/DTrackSDK.lib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
