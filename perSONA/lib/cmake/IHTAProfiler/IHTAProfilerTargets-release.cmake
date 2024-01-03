#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "IHTA::IHTAProfiler" for configuration "Release"
set_property(TARGET IHTA::IHTAProfiler APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(IHTA::IHTAProfiler PROPERTIES
  IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/lib/IHTAProfiler/IHTAProfiler.lib"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/IHTAProfiler.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS IHTA::IHTAProfiler )
list(APPEND _IMPORT_CHECK_FILES_FOR_IHTA::IHTAProfiler "${_IMPORT_PREFIX}/lib/IHTAProfiler/IHTAProfiler.lib" "${_IMPORT_PREFIX}/bin/IHTAProfiler.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
