#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "ITASampler::ITASampler" for configuration "Release"
set_property(TARGET ITASampler::ITASampler APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(ITASampler::ITASampler PROPERTIES
  IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/lib/ITASampler/ITASampler.lib"
  IMPORTED_LINK_DEPENDENT_LIBRARIES_RELEASE "ITABase::ITABase;ITADataSources::ITADataSources"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/ITASampler.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS ITASampler::ITASampler )
list(APPEND _IMPORT_CHECK_FILES_FOR_ITASampler::ITASampler "${_IMPORT_PREFIX}/lib/ITASampler/ITASampler.lib" "${_IMPORT_PREFIX}/bin/ITASampler.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
