#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "ITAConvolution::ITAConvolution" for configuration "Release"
set_property(TARGET ITAConvolution::ITAConvolution APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(ITAConvolution::ITAConvolution PROPERTIES
  IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/lib/ITAConvolution/ITAConvolution.lib"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/ITAConvolution.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS ITAConvolution::ITAConvolution )
list(APPEND _IMPORT_CHECK_FILES_FOR_ITAConvolution::ITAConvolution "${_IMPORT_PREFIX}/lib/ITAConvolution/ITAConvolution.lib" "${_IMPORT_PREFIX}/bin/ITAConvolution.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
