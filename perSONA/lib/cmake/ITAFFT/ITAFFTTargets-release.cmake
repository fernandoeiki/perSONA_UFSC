#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "ITAFFT::ITAFFT" for configuration "Release"
set_property(TARGET ITAFFT::ITAFFT APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(ITAFFT::ITAFFT PROPERTIES
  IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/lib/ITAFFT/ITAFFT.lib"
  IMPORTED_LINK_DEPENDENT_LIBRARIES_RELEASE "FFTW3::fftw3f"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/ITAFFT.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS ITAFFT::ITAFFT )
list(APPEND _IMPORT_CHECK_FILES_FOR_ITAFFT::ITAFFT "${_IMPORT_PREFIX}/lib/ITAFFT/ITAFFT.lib" "${_IMPORT_PREFIX}/bin/ITAFFT.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
