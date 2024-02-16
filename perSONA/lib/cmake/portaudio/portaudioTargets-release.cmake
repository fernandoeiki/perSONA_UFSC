#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "portaudio::portaudio" for configuration "Release"
set_property(TARGET portaudio::portaudio APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(portaudio::portaudio PROPERTIES
  IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/lib/portaudio/portaudio_x64.lib"
  IMPORTED_LINK_INTERFACE_LIBRARIES_RELEASE "winmm;ole32;uuid;dsound;ole32;uuid;ole32;uuid;setupapi;ole32;uuid"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/portaudio_x64.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS portaudio::portaudio )
list(APPEND _IMPORT_CHECK_FILES_FOR_portaudio::portaudio "${_IMPORT_PREFIX}/lib/portaudio/portaudio_x64.lib" "${_IMPORT_PREFIX}/bin/portaudio_x64.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
