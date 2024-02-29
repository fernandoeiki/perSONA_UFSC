target_sources (
	${PROJECT_NAME} PRIVATE master_simulation_controller.h rir_simulation_result.h room_acoustics_worker_interface.h
)

if (ITA_SIMULATION_SCHEDULER_RAVEN_MODULE)
	target_sources (
		${PROJECT_NAME}
		PRIVATE Raven/raven_scene.h
				Raven/raven_simulation_result.h
				Raven/simulation_task.h
				Raven/simulator.h
				Raven/raven_worker_interface.h
				Raven/worker_thread.h
				Raven/simulator_interface.h
	)
endif ()
