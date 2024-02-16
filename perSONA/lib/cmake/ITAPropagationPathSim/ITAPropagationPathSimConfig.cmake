include(CMakeFindDependencyMacro)

string(REGEX MATCHALL "[^;]+" SEPARATE_DEPENDENCIES "ITABase;ITAGeo;$<$<BOOL:ON>:OpenMP>")

foreach(dependency ${SEPARATE_DEPENDENCIES})
  string(REPLACE " " ";" args "${dependency}")
  find_dependency(${args})
endforeach()

include("${CMAKE_CURRENT_LIST_DIR}/ITAPropagationPathSimTargets.cmake")
