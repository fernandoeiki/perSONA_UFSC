#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "VA::VACore" for configuration "Release"
set_property(TARGET VA::VACore APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(VA::VACore PROPERTIES
  IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/lib/VACore/VACore.lib"
  IMPORTED_LINK_DEPENDENT_LIBRARIES_RELEASE "ITADSP::ITADSP;ITADataSources::ITADataSources;ITAConvolution::ITAConvolution;ITACTC::ITACTC;DAFF::DAFF;TBB::tbb;ITASampler::ITASampler;ITAGeo::ITAGeo;ITAPropagationPathSim::ITAPropagationPathSim;ITAPropagationModels::ITAPropagationModels;ITASimulationScheduler::ITASimulationScheduler"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/VACore.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS VA::VACore )
list(APPEND _IMPORT_CHECK_FILES_FOR_VA::VACore "${_IMPORT_PREFIX}/lib/VACore/VACore.lib" "${_IMPORT_PREFIX}/bin/VACore.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
