#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "ITADSP::ITADSP" for configuration "Release"
set_property(TARGET ITADSP::ITADSP APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(ITADSP::ITADSP PROPERTIES
  IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/lib/ITADSP/ITADSP.lib"
  IMPORTED_LINK_DEPENDENT_LIBRARIES_RELEASE "TBB::tbb"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/ITADSP.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS ITADSP::ITADSP )
list(APPEND _IMPORT_CHECK_FILES_FOR_ITADSP::ITADSP "${_IMPORT_PREFIX}/lib/ITADSP/ITADSP.lib" "${_IMPORT_PREFIX}/bin/ITADSP.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
