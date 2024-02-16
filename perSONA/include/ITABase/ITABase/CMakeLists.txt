target_sources (${PROJECT_NAME} PRIVATE ITAProgress.h ITAStatistics.h)

if (ITA_BASE_WITH_JSON_SUPPORT)
	target_sources (${PROJECT_NAME} PRIVATE UtilsJSON.h)
endif ()

add_subdirectory (Math)
