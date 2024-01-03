#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "ITAPropagationPathSim::ITAPropagationPathSim" for configuration "Release"
set_property(TARGET ITAPropagationPathSim::ITAPropagationPathSim APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(ITAPropagationPathSim::ITAPropagationPathSim PROPERTIES
  IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/lib/ITAPropagationPathSim/ITAPropagationPathSim.lib"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/ITAPropagationPathSim.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS ITAPropagationPathSim::ITAPropagationPathSim )
list(APPEND _IMPORT_CHECK_FILES_FOR_ITAPropagationPathSim::ITAPropagationPathSim "${_IMPORT_PREFIX}/lib/ITAPropagationPathSim/ITAPropagationPathSim.lib" "${_IMPORT_PREFIX}/bin/ITAPropagationPathSim.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
