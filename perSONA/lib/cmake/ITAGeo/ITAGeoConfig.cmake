include(CMakeFindDependencyMacro)

string(REGEX MATCHALL "[^;]+" SEPARATE_DEPENDENCIES "ITABase;SketchUpAPI;OpenMeshCore;$<$<BOOL:OFF>:citygml>")

foreach(dependency ${SEPARATE_DEPENDENCIES})
  string(REPLACE " " ";" args "${dependency}")
  find_dependency(${args})
endforeach()

include("${CMAKE_CURRENT_LIST_DIR}/ITAGeoTargets.cmake")
