#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "ITADataSources::ITADataSources" for configuration "Release"
set_property(TARGET ITADataSources::ITADataSources APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(ITADataSources::ITADataSources PROPERTIES
  IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/lib/ITADataSources/ITADataSources.lib"
  IMPORTED_LINK_DEPENDENT_LIBRARIES_RELEASE "vista::vista_inter_proc_comm;portaudio::portaudio"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/ITADataSources.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS ITADataSources::ITADataSources )
list(APPEND _IMPORT_CHECK_FILES_FOR_ITADataSources::ITADataSources "${_IMPORT_PREFIX}/lib/ITADataSources/ITADataSources.lib" "${_IMPORT_PREFIX}/bin/ITADataSources.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
