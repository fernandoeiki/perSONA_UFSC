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

#ifndef INCLUDE_WATCHER_ITA_N_CTC_STREAMING_FILTER
#define INCLUDE_WATCHER_ITA_N_CTC_STREAMING_FILTER

#include <ITACTCDefinitions.h>
#include <ITADataSourceRealization.h>
#include <ITAHDFTSpectra.h>
#include <vector>

// Forward declarations
class ITAUPConvolution;
class ITAUPFilter;
class ITAUPFilterPool;
class ITAUPTrigger;
class ITADatasource;

//! ITACircularNCTCStreamFilter realizes the CTC filtering
/**
 * Filtering for N physical output channels / loudspeaker
 */
class ITA_CTC_API ITANCTCStreamFilter : public ITADatasourceRealizationEventHandler
{
public:
	struct Config
	{
		int N;                      //!< Number of channels
		double dSampleRate;         //!< Audio processing sample rate
		int iBlockLength;           //!< Audio processing block length
		int iFilterLength;          //!< Length of filter
		int iFilterExchangeMode;    //!< Exchange mode \see ITAUPConvolution
		int iFilterCrossfadeLength; //!< Filter exchange crossfade length
	};
	const ITANCTCStreamFilter::Config oConfig; //!< Static configuration

	//! Constructor
	ITANCTCStreamFilter( const ITANCTCStreamFilter::Config& );

	//! Destructor
	~ITANCTCStreamFilter( );

	//! Set input data source
	void SetInputDatasource( ITADatasource* pdsInput );

	//! Get output data source
	ITADatasource* GetOutputDatasource( ) const;

	//! Exchange filters
	void ExchangeFilters( const std::vector<ITABase::CHDFTSpectra*>& vpCTCFilter );

	//! Set gains of loudspeaker two-channel connvolvers (N-sized vector of floats)
	void SetGains( const std::vector<float>& vfGains, bool bSetImmediately = false );

	//! Implementation for processing new input data
	void HandleProcessStream( ITADatasourceRealization* pSender, const ITAStreamInfo* pStreamInfo );

	//! Implementation for incrementing pointer on input data
	void HandlePostIncrementBlockPointer( ITADatasourceRealization* pSender );

private:
	ITADatasource* m_pdsInput;             //!< Input data source
	ITADatasourceRealization* m_pdsOutput; //!< Output data source

	ITAUPFilterPool* m_pFilterPool;         //!< Filter Pool containing dropped, current and queued filters
	ITAUPTrigger* m_pFilterExchangeTrigger; //!< Trigger for filter exchange

	std::vector<ITAUPConvolution*> m_vpConvolvers; //!< 2*N individual block convolver for each CTC filter, even number = left binaural signal
};

#endif // INCLUDE_WATCHER_ITA_N_CTC_STREAMING_FILTER
