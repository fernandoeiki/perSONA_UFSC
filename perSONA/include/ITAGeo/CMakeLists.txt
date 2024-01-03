target_sources (
	${PROJECT_NAME}
	PRIVATE Base.h
			Coordinates.h
			Definitions.h
			ModelBase.h
			ResourceManager.h
			Scene.h
			Utils.h
)

add_subdirectory (Atmosphere)
add_subdirectory (Directivity)
add_subdirectory (Halfedge)
add_subdirectory (Material)
add_subdirectory (SketchUp)
add_subdirectory (Urban)
add_subdirectory (Utils)

if (ITA_GEO_WITH_CITYGML_SUPPORT)
	add_subdirectory (CityGML)
endif ()
