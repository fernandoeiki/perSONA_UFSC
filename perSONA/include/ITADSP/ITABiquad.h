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

#ifndef IW_ITA_BIQUAD
#define IW_ITA_BIQUAD

#include <ITADSPDefinitions.h>

//! Implements digital biquad component for IIR filtering
/**
 * @todo jst: translate comments to English.
 *
 * Diese Klasse realisiert ein Biquad IIR Filter. Es hat einen globalen Verstärkungsfaktor (Gain),
 * damit eine Kaskadierung vieler Biquads zur Bandfilterung benutzt werden kann.
 * Die Umsetzung erfolgt in Kanonischer Form, um möglichst wenig Multiplizierer/Addierer und
 * Verzögerer zu benutzen.
 */
class ITA_DSP_API CITABiquad
{
public:
	//! Parameter class for biquads / second-order sections
	class ITA_DSP_API CParams
	{
	public:
		float g;  //!< Gain (ScaleVector)
		float b0; //!< Denominator 1
		float b1; //!< Denominator 2
		float b2; //!< Denominator 3
		float a0; //!< Numerator 1
		float a1; //!< Numerator 2
		float a2; //!< Numerator 3

		CParams( );

		//! Set parameter old school
		/**
		 * @param[in] Filter parameters coefficients in order: g, b0, b1, b2, a1, a2
		 *
		 * @note Double check order.
		 */
		void SetParameters( const float params[] );
	} oParams;

	CITABiquad( );

	virtual inline ~CITABiquad( ) { };

	//! Clears all accumulators
	void ClearAccumulators( );

	//! Filter samples, simple variant without any gain (factor)
	/**
	 * Direct second canonical form.
	 *
	 * @param[in] pfInputData Input samples
	 * @param[out] pfOutputData Output samples
	 * @param[in] iNumSamples Number of samples to be processed
	 *
	 * @note Input and output samples must have same length
	 */
	void Process( const float* pfInputData, float* pfOutputData, const int iNumSamples );

	//! Filter samples, simple variant with given gain (factor)
	/**
	 * Direct second canonical form.
	 *
	 * @param[in] pfInputData Input samples
	 * @param[out] pfOutputData Output samples
	 * @param[in] iNumSamples Number of samples to be processed
	 * @param[in] fOutputGain Gain (factor) for output
	 * @param[in] iOutputMode Add to or overwrite output buffer
	 *
	 * @note Input and output samples must have same length
	 */
	void Process( const float* pfInputData, float* pfOutputData, const int iNumSamples, const float fOutputGain, const int iOutputMode );


	//! Filter samples, simple variant with given gain (factor)
	/**
	 * Direct second canonical form.
	 *
	 * @param[in] pfInputData Input samples
	 * @param[out] pfOutputData Output samples
	 * @param[in] iNumSamples Number of samples to be processed
	 * @param[in] fOutputGain1 Initial gain (factor) for output
	 * @param[in] fOutputGain2 Target gain (factor) for output
	 * @param[in] iOutputMode Add to or overwrite output buffer
	 *
	 * @note Input and output samples must have same length
	 */
	void Process( const float* pfInputData, float* pfOutputData, const int iNumSamples, const float fOutputGain1, const float fOutputGain2, const int iOutputMode );

private:
	float z[2]; //!< Accumulators
};

#endif // IW_ITA_BIQUAD
