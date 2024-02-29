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

#ifndef IW_ITA_INTERPOLATION
#define IW_ITA_INTERPOLATION

#include <ITABaseDefinitions.h>
#include <string>

class ITASampleBuffer;

//! Abstract interface for interpolation algorithms
/**
 * For equidistant sampling.
 *
 */
class IITASampleInterpolationRoutine
{
public:
	//! Human-readable name
	virtual std::string GetName( ) const = 0;

	//! Anzahl an Stützwerten, die linksseitig (Anfang) bzw. rechtseitig (Ende) benötigt werden
	/**
	 * Auf dem Überlappungsbereich wird die Interpolation angewendet, auch wenn sie
	 * auf diesen keine gültigen Daten liefern kann. Erst ab dem Offset iLeft und bis
	 * zum Ende abzüglich iRight werden in der Interpolationsroutine korrekte Daten
	 * abgelegt.
	 *
	 * @param[out] iLeft Anzahl Samples zur linken Seite (call-by-reference)
	 * @param[out] iRight Anzahl Samples zur rechten Seite (call-by-reference)
	 */
	virtual void GetOverlapSamples( int& iLeft, int& iRight ) const = 0;

	//! Interpolation/Resampling
	/**
	 * An input buffer with a given length will be interpolated starting at a given input offset.
	 * As many samples will be generated, as defined for the output buffer sample length. In- and
	 * output bufers are samples equidistant. An overlapping area is required in the source buffer
	 * to ensure a sufficient covererage of base samples (depending on algorithm). Those left-side
	 * and right-side samples can be retrieved via the function GetOverlapSamples().
	 *
	 * \param pInput			 In buffer pointer
	 * \param iInputLength		 Length of input samples to run interpolation on (not including overlapping samples required for algorithm, this is given by
	 *                           iInputStartOffset)
	 * \param iInputStartOffset  Offset on input buffer (usually = left-side overlap samples)
	 * \param pOutput			 Out buffer pointer
	 * \param iOutputLength	 Length of requested output sample
	 * \param iOutputOffset	 Offset where to write into output buffer
	 *
	 * \return True, if interpolation algorithm could be executed
	 *
	 * @note Raises an exception on bad input
	 *
	 */
	virtual bool Interpolate( const ITASampleBuffer* pInput, const int iInputLength, const int iInputStartOffset, ITASampleBuffer* pOutput, const int iOutputLength,
	                          const int iOutputOffset = 0 ) const = 0;
};

//! Linear interpolation (fast)
class ITA_BASE_API CITASampleLinearInterpolation : public IITASampleInterpolationRoutine
{
public:
	inline CITASampleLinearInterpolation( ) { };
	inline ~CITASampleLinearInterpolation( ) { };
	inline std::string GetName( ) const { return "Linear Interpolation"; };
	inline void GetOverlapSamples( int& iLeft, int& iRight ) const
	{
		iLeft  = 1;
		iRight = 0;
	};
	bool Interpolate( const ITASampleBuffer* pInput, const int iInputLength, const int iInputStartOffset, ITASampleBuffer* pOutput, const int iOutputLength,
	                  const int iOutputOffset = 0 ) const;
};

//! Cubic-Spline interpolation (efficient)
class ITA_BASE_API CITASampleCubicSplineInterpolation : public IITASampleInterpolationRoutine
{
public:
	inline CITASampleCubicSplineInterpolation( ) { };
	inline ~CITASampleCubicSplineInterpolation( ) { };
	inline std::string GetName( ) const { return "Cubic Spline Interpolation"; };
	inline void GetOverlapSamples( int& iLeft, int& iRight ) const
	{
		iLeft  = 2;
		iRight = 2;
	};
	bool Interpolate( const ITASampleBuffer* pInput, const int iInputLength, const int iInputStartOffset, ITASampleBuffer* pOutput, const int iOutputLength,
	                  const int iOutputOffset = 0 ) const;
};

//! Windowed Sinc-Interpolation (costly)
class ITA_BASE_API CITASampleWindowedSincInterpolation : public IITASampleInterpolationRoutine
{
public:
	inline CITASampleWindowedSincInterpolation( const int iWindowSize = 13 ) : m_iWindowSize( iWindowSize ) { m_iWindowSize = m_iWindowSize + m_iWindowSize % 1; };

	inline ~CITASampleWindowedSincInterpolation( ) { };
	inline std::string GetName( ) const { return "Windowed Sinc-Interpolation"; };
	inline void GetOverlapSamples( int& iLeft, int& iRight ) const
	{
		iLeft  = m_iWindowSize / 2;
		iRight = m_iWindowSize / 2;
	};
	bool Interpolate( const ITASampleBuffer* pInput, const int iInputLength, const int iInputStartOffset, ITASampleBuffer* pOutput, const int iOutputLength,
	                  const int iOutputOffset = 0 ) const;

private:
	int m_iWindowSize;
};

#endif // IW_ITA_INTERPOLATION
