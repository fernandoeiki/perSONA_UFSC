target_sources (
	${PROJECT_NAME}
	PRIVATE Definitions.h
			BaseEngine/BaseDiffraction.h
			BaseEngine/BaseImageSource.h
			CombinedModel/DiffractionLocator.h
			CombinedModel/ImageConstructor.h
			CombinedModel/PropagationEngine.h
			CombinedModel/PropagationShapes.h
			CombinedModel/RTree.h
			CombinedModel/ReflectionLocator.h
			ConvexDiffraction/Engine.h
			ConvexDiffraction/EngineImpl.h
			MirrorImage/Engine.h
			UrbanEngine/UrbanDiffraction.h
			UrbanEngine/UrbanImageSource.h
)

add_subdirectory (AtmosphericRayTracing)
