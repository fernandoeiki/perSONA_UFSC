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

#ifndef IW_ITA_IIR_FILTER_ENGINE
#define IW_ITA_IIR_FILTER_ENGINE

#include <ITADSPDefinitions.h>
#include <ITAIIRCoefficients.h>
#include <atomic>
#include <vector>

//! Implements digital biquad component for IIR filtering
/**
 * @todo jst: translate comments to English.
 *
 * Diese Klasse realisiert ein Biquad IIR Filter. Es hat einen globalen Verstärkungsfaktor (Gain),
 * damit eine Kaskadierung vieler Biquads zur Bandfilterung benutzt werden kann.
 * Die Umsetzung erfolgt in Kanonischer Form, um möglichst wenig Multiplizierer/Addierer und
 * Verzögerer zu benutzen.
 */
class ITA_DSP_API CITAIIRFilterEngine
{
public:
	CITAIIRFilterEngine( unsigned int iOrder = 0, bool bIsARMA = false );

	virtual inline ~CITAIIRFilterEngine( ) { };

	void Initialise( unsigned int uiOrder, bool bIsArma );


	void Reset( );

	//! Clears all accumulators
	void ClearAccumulators( );

	unsigned int GetOrder( ) const;

	void SetCoefficientsToZero( );
	void SetCoefficientsToIdentity( );
	void SetCoefficients( const ITADSP::CFilterCoefficients& oCoefficients );

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

	void Process( const float* pfInputData, float* pfOutputData, const int iNumSamples, const float fOutputGain1, const float fOutputGain2, const int iOutputWriteMode );


private:
	ITADSP::CFilterCoefficients m_oCoeffs;
	ITADSP::CFilterCoefficients m_oCoeffsNew;
	std::atomic<bool> m_bNewFilterCoefficients;
	std::vector<float> m_vfAccumulator; //!< Accumulators
	unsigned int m_uiCursor;
};

#endif // IW_ITA_IIR_FILTER_ENGINE
