#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "ITASimulationScheduler::ITASimulationScheduler" for configuration "Release"
set_property(TARGET ITASimulationScheduler::ITASimulationScheduler APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(ITASimulationScheduler::ITASimulationScheduler PROPERTIES
  IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/lib/ITASimulationScheduler/ITASimulationScheduler.lib"
  IMPORTED_LINK_DEPENDENT_LIBRARIES_RELEASE "ITAPropagationModels::ITAPropagationModels"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/ITASimulationScheduler.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS ITASimulationScheduler::ITASimulationScheduler )
list(APPEND _IMPORT_CHECK_FILES_FOR_ITASimulationScheduler::ITASimulationScheduler "${_IMPORT_PREFIX}/lib/ITASimulationScheduler/ITASimulationScheduler.lib" "${_IMPORT_PREFIX}/bin/ITASimulationScheduler.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
