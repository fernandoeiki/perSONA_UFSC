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

#ifndef IW_ITA_NUP_FILTER
#define IW_ITA_NUP_FILTER

#include <ITAUncopyable.h>

namespace ITANUPC
{
	// Within-namespace forwards
	class IConvolution;

	//! Filter for non-uniform partitioned convolution
	/**
	 * Time-domain representation of impules responses. Can have state 'in use' or 'unused'.
	 * You can use one filter in many convolution engines, but modification is only possible
	 * in 'unused' state.
	 * Use 'Load' method to import time domain data, values are internally transformed into
	 * required representation for partitioned convolution.
	 *
	 * You can only create an instance of a filter by requesting one from the convolution engine.
	 */
	class IFilter : public ITAUncopyable
	{
	public:
		//! Parent convolution engine or NULL pointer
		virtual IConvolution* GetParent( ) const = 0;

		//! If in use, returns true.
		virtual bool Used( ) const = 0;

		//! Release filter
		/**
		 * New sate will be 'unused', if release possible and if not otherwise used.
		 */
		virtual void Release( ) = 0;

		//! Empty filter with all coefficients set to zero ( h( 1:end ) = 0 )
		virtual void Zeros( ) = 0;

		//! Identity or unit impulse (Dirac, Delate function) ( h( 1 ) = 1, h( 2:end ) = 0)
		virtual void Identity( ) = 0;

		//! Load filter coefficients
		/**
		 * @note Throws ITAException if filter is in use or length is exceeding requested IR coefficients to be loaded.
		 */
		virtual void Load( const float* pfLeftFilterCoeffs, const int iNumLeftFilterCoeffs, const float* pfRightFilterCoeffs, const int iNumRightFilterCoeffs ) = 0;

		// virtual ITANUPC::Filter* Clone() const = 0;

	protected:
		inline IFilter( ) { };
		inline virtual ~IFilter( ) { };
	};
} // namespace ITANUPC

#endif // IW_ITA_NUP_FILTER
