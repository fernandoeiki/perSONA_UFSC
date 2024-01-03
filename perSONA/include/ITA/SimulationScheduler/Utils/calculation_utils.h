#ifndef INCLUDE_WATCHER_ITA_SIMULATION_SCHEDULER_UTILS_CALCULATION_UTILS
#define INCLUDE_WATCHER_ITA_SIMULATION_SCHEDULER_UTILS_CALCULATION_UTILS

// std includes
#include <algorithm>
#include <memory>
#include <valarray>
#include <vector>

// API includes
#include <ITA/SimulationScheduler/definitions.h>
#include <ITA/SimulationScheduler/Utils/data_type_utils.h>
#include <ITA/SimulationScheduler/Utils/fft_utils.h>
#include <ITA/SimulationScheduler/Utils/statistics_utils.h>

// ITA includes
#include <ITAConstants.h>
#include <ITAFiniteImpulseResponse.h>
#include <ITAHDFTSpectra.h>
#include <ITAMultichannelFiniteImpulseResponse.h>

// VISTA includes
#include <VistaBase/VistaQuaternion.h>
#include <VistaBase/VistaVector3D.h>


namespace ITA
{
	namespace SimulationScheduler
	{
		namespace Utils
		{
			ITABase::CHDFTSpectra* operator/( const ITABase::CMultichannelFiniteImpulseResponse& lhs, const ITABase::CMultichannelFiniteImpulseResponse& rhs );

			struct ITA_SIMULATION_SCHEDULER_API CalculationUtils
			{
				inline static ITABase::CMultichannelFiniteImpulseResponse Mean( std::vector<ITABase::CMultichannelFiniteImpulseResponse> irsVector )
				{
					if( irsVector.size( ) == 1 ) // mean over channels
					{
						// add every channel together.
						auto mean = ITABase::CMultichannelFiniteImpulseResponse( 1, irsVector.at( 0 ).GetLength( ), irsVector.at( 0 ).GetSampleRate( ), true );

						for( auto i = 0; i < irsVector.at( 0 ).GetNumChannels( ); ++i )
						{
							mean[0].add_buf( irsVector.at( 0 )[i] );
						}

						mean[0].div_scalar( float( irsVector.at( 0 ).GetNumChannels( ) ) );

						return mean;
					}
					else if( irsVector.size( ) > 1 ) // mean over multiple multichannel irs
					{
						// check all the same channel count
						const auto channelCount = irsVector.at( 0 ).GetNumChannels( );
						auto sameChannelCount   = true;

						for( auto& irs: irsVector )
						{
							sameChannelCount &= irs.GetNumChannels( ) == channelCount;
						}

						if( !sameChannelCount )
						{
							ITA_EXCEPT_INVALID_PARAMETER( "Not all CMultichannelFiniteImpulseResponses have the same channel count." )
						}

						// add every object together.
						auto mean = ITABase::CMultichannelFiniteImpulseResponse( irsVector.at( 0 ).GetNumChannels( ), irsVector.at( 0 ).GetLength( ),
						                                                         irsVector.at( 0 ).GetSampleRate( ), true );

						for( auto& irs: irsVector )
						{
							mean.add_frame( irs );
						}

						// divide by number of objects.
						mean.div_scalar( float( irsVector.size( ) ) );

						return mean;
					}
					else
						ITA_EXCEPT_INVALID_PARAMETER( "Somehting went wrong with the channel count." )
				};

				inline static std::vector<double> CalculateStdDevOfAbsSpectralDifference( const ITABase::CMultichannelFiniteImpulseResponse& reference,
				                                                                          const std::vector<ITABase::CMultichannelFiniteImpulseResponse>& results )
				{
					auto referenceCopy = reference;

					ITABase::CMultichannelFiniteImpulseResponse secondMean;
					if( results.size( ) != 1 )
						secondMean = CalculationUtils::Mean( results );
					else
						secondMean = results[0];

					DataTypeUtils::MakeSameLength( referenceCopy, secondMean );

					const auto diffSpectra = *( referenceCopy / secondMean );

					const auto meanSpectraValue = DataTypeUtils::ConvertToValueArray( diffSpectra );

					std::vector<double> stdDev;

					for( const auto& vals: meanSpectraValue )
					{
						stdDev.push_back( Statistics::CalculateStandardDeviation( vals ) );
					}

					return stdDev;
				};

				inline static double CalculateAzimuthOnTargetInDegree( const VistaVector3D& positionOrigin, const VistaQuaternion& orientation,
				                                                       const VistaVector3D& positionTarget )
				{
					auto direction = positionTarget - positionOrigin;
					direction.Normalize( );

					const auto azimuthAngle = atan2( direction.Dot( orientation.GetRightDir( ) ), direction.Dot( orientation.GetViewDir( ) ) ) * 180 / ITAConstants::PI_D;

					return azimuthAngle < 0 ? azimuthAngle + 360 : azimuthAngle;
				};

				inline static double CalculateElevationOnTargetInDegree( const VistaVector3D& positionOrigin, const VistaQuaternion& orientation,
				                                                         const VistaVector3D& positionTarget )
				{
					auto direction = positionTarget - positionOrigin;
					direction.Normalize( );

					return asin( direction.Dot( orientation.GetUpDir( ) ) ) * 180 / ITAConstants::PI_D;
				};

				inline static void Normalize( ITABase::CMultichannelFiniteImpulseResponse& irs )
				{
					irs.Normalize( );
					irs.mul_scalar( 0.99f );
				};

				inline static std::valarray<float> NormalizedCrossCorrelation( const ITABase::CFiniteImpulseResponse& x, const ITABase::CFiniteImpulseResponse& y )
				{
					const auto nx  = x.GetLength( );
					const auto ny  = y.GetLength( );
					const auto m   = ( std::max )( nx, ny );
					const auto mxl = m - 1;

					// extend data
					ITABase::CFiniteImpulseResponse x_data( 2 * m, 44100 );
					ITABase::CFiniteImpulseResponse y_data( 2 * m, 44100 );

					x_data.WriteSamples( x.GetData( ), x.GetLength( ) );
					y_data.WriteSamples( y.GetData( ), y.GetLength( ) );

					auto X = FFTUtils::Transform( x_data );
					auto Y = FFTUtils::Transform( y_data );

					X->MulConj( Y.get( ) );

					auto c = DataTypeUtils::ConvertToValueArray( FFTUtils::Transform( *X ) );

					std::valarray<float> correlation( c.size( ) - 1 );

					correlation[std::slice( 0, mxl, 1 )]       = static_cast<std::valarray<float>>( c[std::slice( 2 * m - mxl, mxl, 1 )] );
					correlation[std::slice( mxl, mxl + 1, 1 )] = static_cast<std::valarray<float>>( c[std::slice( 0, mxl + 1, 1 )] );

					const auto cxx0            = pow( abs( DataTypeUtils::ConvertToValueArray( x ) ), 2.0f ).sum( );
					const auto cyy0            = pow( abs( DataTypeUtils::ConvertToValueArray( y ) ), 2.0f ).sum( );
					const auto scaleCoeffCross = sqrt( cxx0 * cyy0 );
					return correlation /= scaleCoeffCross;
				};

				inline static std::vector<std::valarray<float>> NormalizedCrossCorrelation( const ITASampleFrame& x, const ITASampleFrame& y )
				{
					if( x.GetNumChannels( ) != y.GetNumChannels( ) )
						ITA_EXCEPT_INVALID_PARAMETER( "Different number of channels not supported." );

					std::vector<std::valarray<float>> returnVec( x.GetNumChannels( ) );

					for( auto i = 0; i < x.GetNumChannels( ); ++i )
					{
						returnVec.at( i ) = NormalizedCrossCorrelation( x[i], y[i] );
					}

					return returnVec;
				};

				inline static std::vector<std::valarray<float>> NormalizedCrossCorrelation( const ITABase::CMultichannelFiniteImpulseResponse& x,
				                                                                            const ITABase::CMultichannelFiniteImpulseResponse& y )
				{
					if( x.GetNumChannels( ) != y.GetNumChannels( ) )
						ITA_EXCEPT_INVALID_PARAMETER( "Different number of channels not supported." );

					std::vector<std::valarray<float>> returnVec( x.GetNumChannels( ) );

					for( auto i = 0; i < x.GetNumChannels( ); ++i )
					{
						returnVec.at( i ) = NormalizedCrossCorrelation( x[i], y[i] );
					}

					return returnVec;
				};

				inline static std::valarray<float> NormalizedCrossCorrelation( const ITASampleBuffer& x, const ITASampleBuffer& y )
				{
					return NormalizedCrossCorrelation( DataTypeUtils::Convert( x ), DataTypeUtils::Convert( y ) );
				};

				inline static std::valarray<double> NormalizedCrossCorrelation( const std::valarray<double>& x, const std::valarray<double>& y )
				{
					const auto nx  = x.size( );
					const auto ny  = y.size( );
					const auto m   = ( std::max )( nx, ny );
					const auto mxl = m - 1;

					auto X = FFTUtils::FFT( x, int( 2 * m ) );
					auto Y = FFTUtils::FFT( y, int( 2 * m ) );

					auto c = FFTUtils::IFFT( X * Y.apply( std::conj ) );

					std::valarray<double> correlation( c.size( ) - 1 );

					correlation[std::slice( 0, mxl, 1 )]       = static_cast<std::valarray<double>>( c[std::slice( 2 * m - mxl, mxl, 1 )] );
					correlation[std::slice( mxl, mxl + 1, 1 )] = static_cast<std::valarray<double>>( c[std::slice( 0, mxl + 1, 1 )] );

					const auto cxx0            = pow( abs( x ), 2.0 ).sum( );
					const auto cyy0            = pow( abs( y ), 2.0 ).sum( );
					const auto scaleCoeffCross = sqrt( cxx0 * cyy0 );
					return correlation /= scaleCoeffCross;
				};
			};

			inline ITABase::CHDFTSpectra* operator/( const ITABase::CMultichannelFiniteImpulseResponse& lhs, const ITABase::CMultichannelFiniteImpulseResponse& rhs )
			{
				if( lhs.GetNumChannels( ) != rhs.GetNumChannels( ) || lhs.GetLength( ) != rhs.GetLength( ) )
					ITA_EXCEPT_INVALID_PARAMETER( "Length and/or channel count do not match" );

				const auto lhsSpectra = ( *FFTUtils::Transform( lhs ).release( ) );
				const auto rhsSpectra = ( *FFTUtils::Transform( rhs ).release( ) );

				auto result = new ITABase::CHDFTSpectra( float( lhsSpectra.GetSampleRate( ) ), lhsSpectra.GetNumChannels( ), lhsSpectra.GetDFTSize( ), true );

				for( auto i = 0; i < lhsSpectra.GetNumChannels( ); ++i )
				{
					for( auto j = 0; j < lhsSpectra[0]->GetSize( ); ++j )
					{
						std::complex<float> coeff;
						if( rhsSpectra[i]->GetCoeff( j ).real( ) != 0.f )
						{
							coeff = lhsSpectra[i]->GetCoeff( j ) / rhsSpectra[i]->GetCoeff( j );
						}
						else
						{
							coeff = { 0, 0 };
						}

						result->operator[]( i )->SetCoeff( j, coeff );
					}
				}

				return result;
			};

			template<class T>
			inline std::vector<T> operator+( const std::vector<T>& lhs, const std::vector<T>& rhs )
			{
				if( lhs.size( ) != rhs.size( ) )
					std::exception( "Size miss match." );

				std::vector<T> result( lhs.size( ) );

				for( auto i = 0; i < lhs.size( ); ++i )
				{
					result[i] = lhs[i] + rhs[i];
				}

				return result;
			};

		} // namespace Utils

		inline std::valarray<float> operator-( const VistaEulerAngles& rhs, const VistaEulerAngles& lhs )
		{
			std::valarray<float> retArray( 3 );
			retArray[0] = rhs.a - lhs.a;
			retArray[1] = rhs.b - lhs.b;
			retArray[2] = rhs.c - lhs.c;
			return retArray;
		};

	} // namespace SimulationScheduler
} // namespace ITA

#endif // INCLUDE_WATCHER_ITA_SIMULATION_SCHEDULER_UTILS_CALCULATION_UTILS