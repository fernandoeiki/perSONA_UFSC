#ifndef INCLUDE_WATCHER_ITA_SIMULATION_SCHEDULER_UTILS_STATISTICS_UTILS
#define INCLUDE_WATCHER_ITA_SIMULATION_SCHEDULER_UTILS_STATISTICS_UTILS

// std includes
#include <memory>
#include <valarray>

// API includes
#include <ITA/SimulationScheduler/definitions.h>

namespace ITA
{
	namespace SimulationScheduler
	{
		namespace Utils
		{
			struct ITA_SIMULATION_SCHEDULER_API Statistics
			{
				static float CalculateMean( const std::valarray<float>& input )
				{
					auto mean = input.sum( );

					mean = mean / input.size( );

					return mean;
				}

				template<class T>
				static T CalculateMean( const std::vector<T>& data )
				{
					return std::accumulate( data.begin( ), data.end( ), 0.0 ) / data.size( );
				}

				static float CalculateVariance( const std::valarray<float>& input )
				{
					const auto mean = CalculateMean( input );

					const auto varTmp = pow( input - mean, 2.0f );

					const auto var = varTmp.sum( ) / ( input.size( ) - 1 );

					return var;
				}

				template<class T>
				static T CalculateVariance( const std::vector<T>& data )
				{
					auto mean   = CalculateMean( data );
					auto sq_sum = std::inner_product( data.begin( ), data.end( ), data.begin( ), 0.0 );
					return sq_sum / data.size( ) - mean * mean;
				}

				static float CalculateStandardDeviation( const std::valarray<float>& input ) { return std::sqrt( CalculateVariance( input ) ); }

				template<class T>
				static T CalculateStandardDeviation( const std::vector<T>& data )
				{
					return std::sqrt( CalculateVariance( data ) );
				}
			};
		} // namespace Utils
	}     // namespace SimulationScheduler
} // namespace ITA

#endif // INCLUDE_WATCHER_ITA_SIMULATION_SCHEDULER_UTILS_STATISTICS_UTILS