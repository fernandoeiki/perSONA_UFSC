target_sources (
	${PROJECT_NAME} PRIVATE outdoor_simulation_result.h outdoor_worker_thread.h outdoor_simulator_interface.h
							FreeField/ff_simulator.h
)

if (ITA_SIMULATION_SCHEDULER_URBAN_MODULE)
	target_sources (${PROJECT_NAME} PRIVATE Urban/urban_simulator.h)
endif ()

if (ITA_SIMULATION_SCHEDULER_ART_MODULE)
	target_sources (${PROJECT_NAME} PRIVATE ART/art_simulator.h)
endif ()
