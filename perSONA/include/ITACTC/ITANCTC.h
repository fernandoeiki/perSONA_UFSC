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

#ifndef INCLUDE_WATCHER_ITA_N_CTC
#define INCLUDE_WATCHER_ITA_N_CTC

#include <ITACTCDefinitions.h>
#include <ITAFFT.h>
#include <ITAHDFTSpectra.h>
#include <ITASampleFrame.h>
#include <ITAStopWatch.h>
#include <VistaBase/VistaVector3D.h>
#include <VistaMath/VistaGeometries.h>
#include <atomic>
#include <string>
#include <vector>
//#include <VistaBase/VistaQuaternion.h>

class ITANCTCStreamFilter;
class DAFFContentIR;
class DAFFContentDFT;
class ITADatasource;

//! ITANCTC - Crosstalk-Cancellation framework
/**
 *
 * See dissertation of Bruno Masiero
 *
 * non-reentrant
 *
 * Crosstalk-Cancellation-Engine for arbitrary loudspeaker
 *					configurations using pseudo-inverse matrix solution with
 *					all channels active
 *
 */
class ITA_CTC_API ITANCTC
{
public:
	//! CTC filter algorithms
	enum CTCFilterAlgorithms
	{
		CTC_REGULARIZED = 0, //!< Regularized algorithm
		CTC_WIENER_REG,      //!< Regularized Wiener algorithm
		CTC_WIENER_REG_MIN,  //!< Regularized Wiener algorithm with minimum phase filter
	};

	//! Data class that encapsules the pose of an object
	/**
	 * The pose of an object such as a loudspeaker or head
	 * stores the position as well as orientation. While
	 * view and up vectors are used to determine the orientation
	 * of the object, they can also be set in yaw, pitch and
	 * roll convention.
	 */
	class ITA_CTC_API Pose
	{
	public:
		inline Pose( ) { };

		VistaVector3D vPos; //!< Position vector
		// VistaQuaternion qOrient;	//!< Orientation
		VistaVector3D vView; //!< View direction (OpenGL convention)
		VistaVector3D vUp;   //!< Up direction (OpenGL convention)

		Pose& operator=( const Pose& );

		//! Set the orientation using yaw-pitch-roll (YPR) convention [degrees]
		/**
		 * \note All angles in degrees [°]
		 */
		void SetOrientationYPRdeg( const float fYaw, const float fPitch, const float fRoll );

		//! Get YPR angles
		void GetOrientationYPRdeg( float& fYaw, float& fPitch, float& fRoll ) const;
	};


	//! NCTC configuration data class
	/**
	 * This static configuration data has to be passed
	 * for each instance if the CircularNCTC class. Changes
	 * cannot be made afterwards.
	 * For dynamic parameters like Beta oder Delay have a look at
	 * the corresponding setters/getters
	 *
	 */
	class ITA_CTC_API Config
	{
	public:
		enum
		{
			OPTIMIZATION_NONE = 0, //!< No optimization in filter design
		};

		Config( );

		int N;                                       //!< Number of loudspeakers
		int iCTCFilterLength;                        //!< CTC filter taps, i.e. 4096
		float fSampleRate;                           //!< Sampling rate
		float fSpeedOfSound;                         //!< Speed of sound, m/s
		int iOptimization;                           //!< Optimization algorithm (future work, see features/room_compensation)
		float fCrossTalkCancellationFactor;          //!< Factor for cross-talk cancellation (none = 0.0, full = 1.0)
		float fWaveIncidenceAngleCompensationFactor; //!< Factor for cross-talk cancellation (none = 0.0, full = 1.0)
		float fRegularizationFactor;                 //!< Regularization factor (beta)

		class ITA_CTC_API Loudspeaker
		{
		public:
			enum
			{
				SIDE_NOT_SPECIFIED = 0, //!@ Side of the loudspeaker not specified
				LEFT_SIDE          = 1, //!@ Loudspeaker is left from listener viewpoint
				RIGHT_SIDE         = 2, //!@ Loudspeaker is right from listener viewpoint
			};
			Loudspeaker( );
			Loudspeaker( const Pose& oStaticPose );
			Pose oPose;                         //!< Pose of loudspeaker
			const DAFFContentDFT* pDirectivity; //!< Directivity data
			int iSide;
		};
		std::vector<Loudspeaker> voLoudspeaker; //!< Loudspeaker of this setup
	};

	//! Constructor
	/**
	 * Creates the NCTC module for N selected loudspeakers using the poses (position & orientation)
	 * given by the specified configuration file. The number of loudspeakers is defined
	 * through the configuration's SelectedSpeakers list. The configuration may have more
	 * loudspeakers defined than are selected in the end.
	 *
	 * @note Throws ITAException errors
	 *
	 * @param[in] oNCTCConfig The configuration, see @Config
	 *
	 */
	ITANCTC( const Config& oNCTCConfig );

	//! Destructor
	~ITANCTC( );

	//! Get the number of loudspeakers/channels for this CTC engine
	/**
	 * @return Number of channels (N)
	 *
	 */
	int GetNumChannels( ) const;

	//! Configuration getter
	/**
	 * \return Static configuration parameters
	 */

	const Config& GetConfig( ) const;

	//! Get regularization factor (beta)
	/**
	 * @return Regularization factor
	 */
	float GetRegularizationFactor( ) const;

	//! Set regularization factor
	/**
	 * @param fRegularizationFator Set the regularization factor (beta)
	 */
	void SetRegularizationFactor( const float fRegularizationFator );

	//! Get cross-talk cancellation factor
	/**
	 * \return Factor [0..1]
	 */
	float GetCrossTalkCancellationFactor( ) const;

	//! Set cross-talk cancellation factor
	/**
	 * \param fFactor number between [0..1] (none: 0, max range = 1.0)
	 */
	void SetCrossTalkCancellationFactor( const float fFactor );

	//! Get cross-talk cancellation factor
	/**
	 * \return Factor [0..1]
	 */
	float GetWaveIncidenceAngleCompensation( ) const;

	//! Set cross-talk cancellation factor
	/**
	 * \param fFactor number between [0..1] (none: 0, max range = 1.0)
	 */
	void SetWaveIncidenceAngleCompensationFactor( const float fFactor );

	//! Get additional delay parameter
	/**
	 * \return Delay in seconds
	 */
	std::vector<float> GetDelayTime( ) const;

	//! Set additional delay parameter in seconds (affects all channels)
	/**
	 * The default value is half of the filter length.
	 *
	 * @note Will overwrite existing individual values.
	 *
	 * @param fDelayTime Set the time delay (all channels)
	 */
	void SetDelayTime( const float fDelayTime );

	//! Set delay parameter in seconds for each loudspeaker channel individually
	/**
	 * The CTC filter set for each channel (loudspeaker) will be delayd by given time. This is
	 * helpful to overcome latency issues with different types of loudspeakers.
	 *
	 * The default value is half of the filter length.
	 *
	 * \param vfDelayTime Set the time delay (each channel/loudspeaker individually)
	 */
	void SetDelayTime( const std::vector<float>& vfDelayTime );

	//! Sets the optimization
	/**
	 * Optimization setter, i.e. early reflection compensation for aixCAVE (see enum of Config)
	 */
	void SetOptimization( const int iOptimization );

	//! Optimization getter
	/**
	 * Optimization getter, i.e. early reflection compensation for aixCAVE (see enum of Config)
	 */
	int GetOptimization( ) const;

	//! Get loudspeaker pose
	/**
	 * \param	iLoudspeakerID Identifier of loudspeaker (begins with 0, max N-1)
	 * \return	Returns the pose of a loudspeaker
	 */

	const Pose& GetLoudspeakerPose( const int iLoudspeakerID ) const;

	//! Set HRIR dataset
	/**
	 * \param pHRIRDatabase The DAFF impulse response file with the head-related information
	 *
	 */
	void SetHRIR( const DAFFContentIR* pHRIR );

	//! Update the head position and orientation (combination = pose)
	/**
	 * Use this method to update the head pose (position and/or orientation). This is
	 * usually data that your tracking device provides. The CircularNCTC will then update
	 * for the new sweet spot.
	 *
	 * \param oHead	Pose of head (from tracking device)
	 */
	void UpdateHeadPose( const Pose& oHead );

	//! Returns the pointer to the currently used HRIR dataset
	/**
	 * \important	Not thread safe
	 */
	bool GetHRTF( std::vector<ITABase::CHDFTSpectra*>& vpHRTF ) const;

	//! Returns the currently used head pose
	/**
	 * \important	Not thread safe
	 */
	Pose GetHeadPose( ) const;

	//! Returns the minimum distance of head to all loudspeakers
	/**
	 *
	 */
	float GetMinimumDistanceHead2LS( ) const;

	//! Calculate the CTC filters
	/**
	 * Designs CTC filters
	 *
	 * @param[out] vpSpectra Target vector of two-channel CTC filter spectra for each loudspeaker (call-by-ref)
	 *
	 * @note Will raise ITAException on error
	 */
	void CalculateFilter( std::vector<ITABase::CHDFTSpectra*>& vpSpectra ) const;

	//! Calculate the Wiener-Hopf factorization
	void WienerHopfFactorization( const ITABase::CHDFTSpectrum* voSpecIn, ITABase::CHDFTSpectrum* voSpecOutPlus, ITABase::CHDFTSpectrum* voSpecOutMinus );

protected:
private:
	const Config m_oConfig; //!< CTC Configuration

	mutable std::atomic<float> m_fRegularizationFactor;                 //!< Beta parameter (regularization)
	mutable std::vector<float> m_vfDelayTime;                           //!< Add a delay [seconds] to the resulting CTC filter (individual channels)
	std::atomic<int> m_iOptimization;                                   //!< Optimization (see Config enum)
	mutable std::atomic<float> m_fCrossTalkCancellationFactor;          //!< Factor for cross-talk cancellation (none = 0.0, full = 1.0)
	mutable std::atomic<float> m_fWaveIncidenceAngleCompensationFactor; //!< Factor for cross-talk cancellation (none = 0.0, full = 1.0)
	const DAFFContentIR* m_pHRIR;                                       //!< HRIR dataset pointer

	Pose m_oHeadPose; //!< Current head Pose data

	mutable ITAFFT m_fft, m_ifft;        //!< Internal FFT and IFFT transformations
	mutable ITASampleFrame m_sfCTC_temp; //!< Internal CTC helper

	std::vector<float> m_vfWeights;                    //!< Diagonal values for the weighting matrix (W or Z), only non-zero entries allowed
	std::vector<ITABase::CHDFTSpectra*> m_vpHRTFs;     //!< N-dim vector with two-channel HRTF sets for each LS direction
	std::vector<ITABase::CHDFTSpectra*> m_vpHelper2x2; //!< Two-by-two helper matrix
	ITABase::CHDFTSpectrum* t;                         //!< Helper
	ITABase::CHDFTSpectrum* det;                       //!< Helper

	int GetLoudspeakerSide( const int ) const;

	//! Adds a HRIR into the target filter
	/**
	 * @param oLoudspeakerPose	Pose of loudspeaker (or virtual source)
	 * @param bOutOfRange	Indicator if the HRIR data for the required position is out of range
	 * @param sfTargetIR	Target impulse response, where the HRIR will be placed by mul-adding with given gain
	 *
	 */
	void AddHRIR( const Pose& oLoudspeakerPose, ITASampleFrame& sfTargetIR, bool& bOutOfRange, const double dGain = 1.0f,
	              const int iDistanceCompensationSamples = 0 ) const;

	friend class ITACTCStreamFilter;
};

#endif // INCLUDE_WATCHER_ITA_N_CTC
