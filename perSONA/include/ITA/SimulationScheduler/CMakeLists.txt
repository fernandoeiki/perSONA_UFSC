target_sources (
	${PROJECT_NAME}
	PRIVATE definitions.h
			3d_object.h
			dummy_worker.h
			update_message.h
			update_config.h
			update_scene.h
			types.h
			simulation_result.h
			ir_simulation_result.h
			profiler.h
			result_handler.h
			scheduler_interface.h
			scheduler.h
			worker_interface.h
			config_interface.h
			worker_remote.h
)

add_subdirectory (AudibilityFilter)
add_subdirectory (OutdoorAcoustics)
add_subdirectory (RoomAcoustics)
add_subdirectory (Utils)
