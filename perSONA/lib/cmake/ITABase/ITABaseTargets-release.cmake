#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "ITABase::ITABase" for configuration "Release"
set_property(TARGET ITABase::ITABase APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(ITABase::ITABase PROPERTIES
  IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/lib/ITABase/ITABase.lib"
  IMPORTED_LINK_DEPENDENT_LIBRARIES_RELEASE "SampleRate::samplerate"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/ITABase.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS ITABase::ITABase )
list(APPEND _IMPORT_CHECK_FILES_FOR_ITABase::ITABase "${_IMPORT_PREFIX}/lib/ITABase/ITABase.lib" "${_IMPORT_PREFIX}/bin/ITABase.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
