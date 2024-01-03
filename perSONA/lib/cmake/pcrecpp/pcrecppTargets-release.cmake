#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "pcre::pcrecpp" for configuration "Release"
set_property(TARGET pcre::pcrecpp APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(pcre::pcrecpp PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LINK_INTERFACE_LIBRARIES_RELEASE "pcre::pcre"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/pcrecpp/pcrecpp.lib"
  )

list(APPEND _IMPORT_CHECK_TARGETS pcre::pcrecpp )
list(APPEND _IMPORT_CHECK_FILES_FOR_pcre::pcrecpp "${_IMPORT_PREFIX}/lib/pcrecpp/pcrecpp.lib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
