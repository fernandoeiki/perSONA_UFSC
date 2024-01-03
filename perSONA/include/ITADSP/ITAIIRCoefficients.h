/*
 * ----------------------------------------------------------------
 *
 *		ITA core libs
 *		(c) Copyright Institute of Technical Acoustics (ITA)
 *		RWTH Aachen University, Germany, 2015-2022
 *
 * ----------------------------------------------------------------
 *				    ____  __________  _______
 *				   //  / //__   ___/ //  _   |
 *				  //  /    //  /    //  /_|  |
 *				 //  /    //  /    //  ___   |
 *				//__/    //__/    //__/   |__|
 *
 * ----------------------------------------------------------------
 *
 */

#ifndef IW_ITA_IIR_COEFFICIENTS
#define IW_ITA_IIR_COEFFICIENTS

#include <ITADSPDefinitions.h>
#include <ITAIIRCoefficients.h>
#include <string>
#include <vector>

namespace ITADSP
{
	enum FilterDesignAlgorithm // used to select the algorithm used to design filter coefficients
	{
		UNSPECIFIED = 0,
		BURG        = 1, // Use the Burg algorithm for designing the filter coefficients
	};

	struct CFilterCoefficients
	{
		unsigned int uiOrder;
		bool bIsARMA;
		int iDesignAlgorithm;

		std::vector<float> vfNumerator;
		std::vector<float> vfDenominator;

		inline CFilterCoefficients( unsigned int uiOrder = 0, bool bARMAInit = false ) : iDesignAlgorithm( ITADSP::UNSPECIFIED ), bIsARMA( bARMAInit )
		{
			Initialise( uiOrder, bARMAInit );
		};

		//! Initialize (sets coeffs to zero)
		inline void Initialise( unsigned int uiOrder_, bool bARMAInit_ )
		{
			bIsARMA = bARMAInit_;
			uiOrder = uiOrder_;
			if( bIsARMA )
				vfNumerator.resize( uiOrder + 1 );
			else
				vfNumerator.resize( 1 );

			vfDenominator.resize( uiOrder + 1 );

			SetZero( );
		};

		//! Initialize with given order (sets coeffs to zero)
		inline void InitialiseOrder( unsigned int uiOrder_ )
		{
			uiOrder = uiOrder_;
			if( bIsARMA )
				vfNumerator.resize( uiOrder + 1 );
			else
				vfNumerator.resize( 1 );

			vfDenominator.resize( uiOrder + 1 );

			SetZero( );
		};

		inline void SetZero( )
		{
			for( size_t i = 0; i < vfNumerator.size( ); i++ )
				vfNumerator[i] = 0.0f;

			if( vfDenominator.size( ) > 0 )
				vfDenominator[0] = 1.0f;

			for( size_t i = 1; i < vfDenominator.size( ); i++ )
				vfDenominator[i] = 0.0f;
		};

		inline void SetIdentity( )
		{
			SetZero( );

			if( vfNumerator.size( ) > 0 )
				vfNumerator[0] = 1.0f;

			if( vfDenominator.size( ) > 0 )
				vfDenominator[0] = 1.0f;

			for( size_t i = 1; i < vfDenominator.size( ); i++ )
				vfDenominator[i] = 0.0f;
		};
	};

} // namespace ITADSP


#endif // IW_ITA_IIR_COEFFICIENTS
