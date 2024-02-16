#ifndef INCLUDE_WATCHER_ITA_SIMULATION_SCHEDULER_PROFILER
#define INCLUDE_WATCHER_ITA_SIMULATION_SCHEDULER_PROFILER

#include <IHTA/Profiler/profiler.h>
#include <fstream>
#include <sstream>

#ifdef WITH_PROFILER

#	define PROFILER_EVENT_COUNT( NAME )  IHTA_PROFILER_EVENT_COUNT( NAME )
#	define PROFILER_VALUE( NAME, VALUE ) IHTA_PROFILER_VALUE( NAME, VALUE )
#	define PROFILER_SECTION( NAME )      IHTA_PROFILER_SECTION( NAME )
#	define PROFILER_FUNCTION( )          IHTA_PROFILER_FUNCTION( )
#	define PROFILER_END_SECTION( )       IHTA_PROFILER_END_SECTION( )
#	define PROFILER_NAME_THREAD( NAME )  IHTA_PROFILER_NAME_THREAD( NAME )
#	define PROFILER_NAME_THREAD_MAIN( )  IHTA_PROFILER_NAME_THREAD_MAIN( )

#	ifdef NO_SECTIONS
#		undef PROFILER_SECTION( NAME )
#		define PROFILER_SECTION( ... )

#		undef PROFILER_FUNCTION( NAME )
#		define PROFILER_FUNCTION( ... )

#		undef PROFILER_END_SECTION( NAME )
#		define PROFILER_END_SECTION( ... )
#	endif

#else

#	define PROFILER_EVENT_COUNT( ... )
#	define PROFILER_VALUE( ... )
#	define PROFILER_SECTION( ... )
#	define PROFILER_FUNCTION( )
#	define PROFILER_END_SECTION( )
#	define PROFILER_NAME_THREAD( ... )
#	define PROFILER_NAME_THREAD_MAIN( )

#endif

namespace ITA
{
	namespace SimulationScheduler
	{
		///
		/// \brief Store the profiler data as a json file.
		/// \param sProfilerFileName name for the json file.
		/// \note The file extension has to be defined by the user.
		///
		inline void StoreProfilerData( const std::string& sProfilerFileName )
		{
#ifdef WITH_PROFILER
			PROFILER_EVENT_COUNT( "STOP" );

			std::ofstream myProfile;
			myProfile.open( sProfilerFileName );
			myProfile << IHTA::Profiler::ProfilerToJson( ).str( );
			myProfile.close( );
#endif
		}
	} // namespace SimulationScheduler
} // namespace ITA

#endif // INCLUDE_WATCHER_ITA_SIMULATION_SCHEDULER_PROFILER