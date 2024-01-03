#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "ITACTC::ITACTC" for configuration "Release"
set_property(TARGET ITACTC::ITACTC APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(ITACTC::ITACTC PROPERTIES
  IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/lib/ITACTC/ITACTC.lib"
  IMPORTED_LINK_DEPENDENT_LIBRARIES_RELEASE "ITABase::ITABase;ITAFFT::ITAFFT;ITADataSources::ITADataSources;DAFF::DAFF;ITAConvolution::ITAConvolution"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/ITACTC.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS ITACTC::ITACTC )
list(APPEND _IMPORT_CHECK_FILES_FOR_ITACTC::ITACTC "${_IMPORT_PREFIX}/lib/ITACTC/ITACTC.lib" "${_IMPORT_PREFIX}/bin/ITACTC.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
