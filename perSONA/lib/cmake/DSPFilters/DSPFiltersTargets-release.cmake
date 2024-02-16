#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "DSPFilters::DSPFilters" for configuration "Release"
set_property(TARGET DSPFilters::DSPFilters APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(DSPFilters::DSPFilters PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/DSPFilters/DSPFilters.lib"
  )

list(APPEND _IMPORT_CHECK_TARGETS DSPFilters::DSPFilters )
list(APPEND _IMPORT_CHECK_FILES_FOR_DSPFilters::DSPFilters "${_IMPORT_PREFIX}/lib/DSPFilters/DSPFilters.lib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
