#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "OpenMesh::OpenMeshCore" for configuration "Release"
set_property(TARGET OpenMesh::OpenMeshCore APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(OpenMesh::OpenMeshCore PROPERTIES
  IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/lib/OpenMeshCore/OpenMeshCore.lib"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/OpenMeshCore.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS OpenMesh::OpenMeshCore )
list(APPEND _IMPORT_CHECK_FILES_FOR_OpenMesh::OpenMeshCore "${_IMPORT_PREFIX}/lib/OpenMeshCore/OpenMeshCore.lib" "${_IMPORT_PREFIX}/bin/OpenMeshCore.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
