#ifndef INCLUDE_WATCHER_ITA_SIMULATION_SCHEDULER_UTILS_FFT_UTILS
#define INCLUDE_WATCHER_ITA_SIMULATION_SCHEDULER_UTILS_FFT_UTILS

// std includes
#include <array>
#include <memory>

// API includes
#include <ITA/SimulationScheduler/definitions.h>

// simulation scheduler includes
#include <ITA/SimulationScheduler/Utils/data_type_utils.h>

// ITA includes
#include <ITAConstants.h>
#include <ITAFFT.h>
#include <ITAFiniteImpulseResponse.h>
#include <ITAHDFTSpectra.h>
#include <ITAHDFTSpectrum.h>
#include <ITAMultichannelFiniteImpulseResponse.h>

namespace ITA
{
	namespace SimulationScheduler
	{
		namespace Utils
		{
			struct ITA_SIMULATION_SCHEDULER_API FFTUtils
			{
				static std::unique_ptr<ITABase::CHDFTSpectrum> Transform( const ITABase::CFiniteImpulseResponse& ir )
				{
					auto spectrum = std::make_unique<ITABase::CHDFTSpectrum>( ir.GetSampleRate( ), ir.GetLength( ), true );
					ITASampleBuffer tmpBuffer( ir.GetLength( ), true );
					ITAFFT fft( ITAFFT::FFT_R2C, ir.GetLength( ), tmpBuffer.GetData( ), spectrum->GetData( ) );

					// Make local copy of input (will be destroyed by in-place FFT)
					tmpBuffer.write( ir.GetData( ), ir.GetLength( ) );

					float* fIn  = tmpBuffer.GetData( );
					float* fOut = spectrum->GetData( );
					fft.execute( fIn, fOut );

					return spectrum;
				}

				static ITABase::CFiniteImpulseResponse Transform( const ITABase::CHDFTSpectrum& spectrum )
				{
					ITABase::CFiniteImpulseResponse ir( spectrum.GetDFTSize( ), spectrum.GetSampleRate( ), true );
					ITASampleBuffer tmpBuffer( ( spectrum.GetDFTSize( ) + 1 ) * 2, true );
					ITAFFT ifft( ITAFFT::IFFT_C2R, spectrum.GetDFTSize( ), tmpBuffer.GetData( ), ir.GetData( ) );

					// Make local copy of input (will be destroyed by in-place FFT)
					tmpBuffer.write( spectrum.GetData( ), tmpBuffer.GetLength( ) );

					float* fIn  = tmpBuffer.GetData( );
					float* fOut = ir.GetData( );
					ifft.execute( fIn, fOut );

					// Normalize after IFFT
					ir.div_scalar( float( spectrum.GetDFTSize( ) ) );

					return ir;
				}

				static std::unique_ptr<ITABase::CHDFTSpectra> Transform( const ITABase::CMultichannelFiniteImpulseResponse& irs );

				static ITABase::CMultichannelFiniteImpulseResponse Transform( const ITABase::CHDFTSpectra& spectra )
				{
					ITABase::CMultichannelFiniteImpulseResponse irs( spectra.GetNumChannels( ), spectra.GetDFTSize( ), spectra.GetSampleRate( ), true );

					for( auto i = 0; i < spectra.GetNumChannels( ); ++i )
					{
						irs[i].WriteSamples( Transform( *spectra[i] ).GetData( ), irs[i].GetLength( ) );
					}

					return irs;
				}

				static std::valarray<std::complex<double>> FFT( const std::valarray<double>& xIn, int nPoint = -1 )
				{
					std::valarray<double> x;
					if( nPoint > 0 )
					{
						x.resize( nPoint, 0.0 );
						for( auto i = 0; i < xIn.size( ); ++i )
						{
							x[i] = xIn[i];
						}
					}
					else
					{
						x = xIn;
					}

					std::valarray<std::complex<double>> complex( x.size( ) );

					for( auto i = 0; i < x.size( ); ++i )
					{
						complex[i] = x[i];
					}

					FFTImpl( complex );

					return complex;
				}

				static std::valarray<double> IFFT( const std::valarray<std::complex<double>>& xIn )
				{
					// conjugate the complex numbers
					auto x = xIn.apply( std::conj );

					// forward fft
					FFTImpl( x );

					// conjugate the complex numbers again
					x = x.apply( std::conj );

					// scale the numbers
					x /= (double)x.size( );

					std::valarray<double> result( x.size( ) );

					for( auto i = 0; i < x.size( ); ++i )
					{
						result[i] = abs( x[i] );
					}

					return result;
				}

			private:
				static void FFTImpl( std::valarray<std::complex<double>>& x )
				{
					const size_t N = x.size( );
					if( N <= 1 )
						return;

					// divide
					std::valarray<std::complex<double>> even = x[std::slice( 0, N / 2, 2 )];
					std::valarray<std::complex<double>> odd  = x[std::slice( 1, N / 2, 2 )];

					// conquer
					FFTImpl( even );
					FFTImpl( odd );

					// combine
					for( size_t k = 0; k < N / 2; ++k )
					{
						auto t       = std::polar( 1.0, -2 * ITAConstants::PI_D * k / N ) * odd[k];
						x[k]         = t + even[k];
						x[k + N / 2] = even[k] - t;
					}
				}
			};

			inline std::unique_ptr<ITABase::CHDFTSpectra> FFTUtils::Transform( const ITABase::CMultichannelFiniteImpulseResponse& irs )
			{
				auto pSpectra = std::make_unique<ITABase::CHDFTSpectra>( float( irs.GetSampleRate( ) ), irs.GetNumChannels( ), irs.GetLength( ), true );

				for( auto i = 0; i < irs.GetNumChannels( ); ++i )
					( *pSpectra )[i]->Copy( Transform( DataTypeUtils::Convert( irs[i] ) ).get( ) );

				return pSpectra;
			}
		} // namespace Utils
	}     // namespace SimulationScheduler
} // namespace ITA

#endif // INCLUDE_WATCHER_ITA_SIMULATION_SCHEDULER_UTILS_FFT_UTILS