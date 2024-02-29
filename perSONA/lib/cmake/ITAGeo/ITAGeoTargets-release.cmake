#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "ITAGeo::ITAGeo" for configuration "Release"
set_property(TARGET ITAGeo::ITAGeo APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(ITAGeo::ITAGeo PROPERTIES
  IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/lib/ITAGeo/ITAGeo.lib"
  IMPORTED_LINK_DEPENDENT_LIBRARIES_RELEASE "vista::vista_base;vista::vista_tools;vista::vista_math;DAFF::DAFF"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/ITAGeo.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS ITAGeo::ITAGeo )
list(APPEND _IMPORT_CHECK_FILES_FOR_ITAGeo::ITAGeo "${_IMPORT_PREFIX}/lib/ITAGeo/ITAGeo.lib" "${_IMPORT_PREFIX}/bin/ITAGeo.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
