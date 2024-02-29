#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "Sndfile::sndfile" for configuration "Release"
set_property(TARGET Sndfile::sndfile APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(Sndfile::sndfile PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "C"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/sndfile/sndfile.lib"
  )

list(APPEND _IMPORT_CHECK_TARGETS Sndfile::sndfile )
list(APPEND _IMPORT_CHECK_FILES_FOR_Sndfile::sndfile "${_IMPORT_PREFIX}/lib/sndfile/sndfile.lib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
