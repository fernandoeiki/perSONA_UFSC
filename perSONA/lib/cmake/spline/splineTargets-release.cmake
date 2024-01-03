#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "Spline::spline" for configuration "Release"
set_property(TARGET Spline::spline APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(Spline::spline PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/spline/spline.lib"
  )

list(APPEND _IMPORT_CHECK_TARGETS Spline::spline )
list(APPEND _IMPORT_CHECK_FILES_FOR_Spline::spline "${_IMPORT_PREFIX}/lib/spline/spline.lib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
