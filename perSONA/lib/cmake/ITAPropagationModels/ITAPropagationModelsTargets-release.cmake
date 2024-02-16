#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "ITAPropagationModels::ITAPropagationModels" for configuration "Release"
set_property(TARGET ITAPropagationModels::ITAPropagationModels APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(ITAPropagationModels::ITAPropagationModels PROPERTIES
  IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/lib/ITAPropagationModels/ITAPropagationModels.lib"
  IMPORTED_LINK_DEPENDENT_LIBRARIES_RELEASE "ITAFFT::ITAFFT"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/ITAPropagationModels.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS ITAPropagationModels::ITAPropagationModels )
list(APPEND _IMPORT_CHECK_FILES_FOR_ITAPropagationModels::ITAPropagationModels "${_IMPORT_PREFIX}/lib/ITAPropagationModels/ITAPropagationModels.lib" "${_IMPORT_PREFIX}/bin/ITAPropagationModels.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
