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

#ifndef IW_ITA_NUP_CONVOLUTION
#define IW_ITA_NUP_CONVOLUTION

#include <ITAConvolutionDefinitions.h>
#include <ITANUPFilter.h>

// ITA includes
#include <ITATimeSeriesAnalyzer.h>
#include <ITAUncopyable.h>

// STL includes
#include <cstdint>
#include <string>
#include <vector>

class ITADatasource;

//! Non-uniform partitioned convolution (NUPC) engine namespace
/**
 * Uses block convolution with arbitrary segmentation for efficient impulse response convolution
 * of long FIR filters, like those in room acoustics.
 *
 */
namespace ITANUPC
{
	//! Datentyp welcher für Zyklen (Zeitpunkte) verwendet wird
	typedef uint64_t CYCLE;

	// Literals
	const unsigned int NUPC_AUTO = 0;

	//! Fading function
	typedef enum
	{
		LINEAR = 0,   // Linear
		COSINE_SQUARE // Squared cosine function
	} FadingFunction;

	//! Segmentation schemes
	typedef enum
	{
		AUTO = 0,
		UNIFORM,
		GARDNER,
		FROM_FILE,
	} SegmentationScene;

	//! Runtime infos on stages
	typedef struct
	{
		int iPartLength;
		int iNumDropouts;
		ITATimeseriesAnalyzerData<double> tadExecutionDeadtime;
		ITATimeseriesAnalyzerData<double> tadExecutionTime;
		ITATimeseriesAnalyzerData<int> tadTaskInterruptions;
	} StageRuntimeInfo;

	//! General runtime info
	typedef struct
	{
		ITANUPC::CYCLE tCycles; //!< Number of processed blocks
		bool bError;
		double dOverallRuntime;
		double dRuntimeCyclesMinimum;
		double dRuntimeCyclesAverage;
		double dRuntimeCyclesMaximum;
		double dRuntimeCyclesVariance;
		double dRuntimeDirectAnswerAverage;
		double dRuntimeDirectAnswerMaximum;
		double dRuntimeDirectAnswerStdDeviation;
		double dDirectAnswerLoadAverage; //!< load average in buffer switch callback
		double dLoadAverage;
		int iNumDropouts;
		std::vector<ITANUPC::StageRuntimeInfo> vStageInfos;
		int iBaseExp2; //!< Smallest base-two stage
	} RuntimeInfo;


	//! Parameter (purely inline)
	class CConvolutionParameter
	{
	public:
		double dSampleRate;
		int iBlockLength;
		int iImpulseResponseFilterLength; //!< (Maximum) filter length
		SegmentationScene eSegmentationScheme;
		std::string sSegmentationFile;
		std::string sParam;
		int nThreads;
		bool bSynchronous; // Forces to process all tasks in callback function

		inline CConvolutionParameter( )
		    : dSampleRate( 0 )
		    , iBlockLength( 0 )
		    , iImpulseResponseFilterLength( 0 )
		    , eSegmentationScheme( AUTO )
		    , nThreads( NUPC_AUTO )
		    , bSynchronous( false ) { };

		//! Convolution parameter constructor
		/**
		 * \param[in] dSampleRate			Abtastrate [Hz] (>0)
		 * \param[in] iBlockLength			Blocklänge (Potenz n=k^2 zur Basis 2 und kleinstmöglicher Wert 4)
		 * \param[in] iImpulseResponseFilterLength			Maximale Filterlänge [Anzahl Filterkoeffizienten]
		 */
		inline CConvolutionParameter( const double dSampleRate, const int iBlockLength, const int iImpulseResponseFilterLength )
		    : dSampleRate( dSampleRate )
		    , iBlockLength( iBlockLength )
		    , iImpulseResponseFilterLength( iImpulseResponseFilterLength )
		    , eSegmentationScheme( AUTO )
		    , nThreads( NUPC_AUTO )
		    , bSynchronous( false ) { };
	};

	//! Input description class
	class IInput
	{
	public:
		virtual int GetID( ) const = 0;

		// Returns the buffer of the input
		// Input data must be put in here (size = blocklength)
		virtual float* GetBuffer( ) const = 0;

		// Puts one block of samples into the input
		// Note: Nullptr may be passed and is treated as nullsamples
		virtual void Put( const float* pfData ) = 0;

		// virtual float GetGain() const = 0;
		// virtual void SetGain(float fGain) = 0;

	protected:
		inline virtual ~IInput( ) { };
	};

	//! Output description class
	class IOutput
	{
	public:
		virtual int GetID( ) const              = 0;
		virtual const float* GetBuffer( ) const = 0;

		// Copies the latest block of samples into the given destination buffer
		virtual void Get( float* pfData ) = 0;

	protected:
		virtual inline ~IOutput( ) { };
	};

	//! Interface for non-uniform partitioned realtime convolution
	class ITA_CONVOLUTION_API IConvolution : public ITAUncopyable
	{
	public:
		//! Convolution instance factory
		/**
		 * Create non-uniform partitioned convolution engine with thie factory method.
		 * sampling rate and block length can not be changed during runtime. Convolves
		 * two channels.
		 * Throws ITANUPC::Exception on failure.
		 */
		static ITANUPC::IConvolution* Create( const CConvolutionParameter& oParams );

		virtual ~IConvolution( );
		virtual ITANUPC::CConvolutionParameter GetParams( ) const = 0;
		virtual void Reset( )                                     = 0;

		//! Audio stream callback function, processes a block of samples
		virtual void Process( ) = 0;

		//! Property bit flag getter (debug, SSE, etc) [deprecated]
		static unsigned int GetFlags( );

		//! Get runtime info
		/**
		 * @param[out] pRuntimeInfo pointer to runtime info instance
		 */
		virtual void GetRuntimeInfo( ITANUPC::RuntimeInfo* pRuntimeInfo ) = 0;
		virtual void ResetRuntimeInfo( )                                  = 0;

		virtual void GetInputs( std::vector<ITANUPC::IInput*>& vpInputs ) const            = 0;
		virtual ITANUPC::IInput* AddInput( )                                               = 0;
		virtual void RemoveInput( ITANUPC::IInput* pInput, const bool bRemoveImmediately ) = 0;
		virtual void GetOutputs( std::vector<ITANUPC::IOutput*>& vpOutputs ) const         = 0;

		//! Request empty filter
		virtual ITANUPC::IFilter* RequestFilter( ) = 0;

		//! Exchange filter
		virtual void ExchangeFilter( ITANUPC::IInput* pInput, ITANUPC::IFilter* pFilter ) = 0;


		virtual double GetOutputGain( )                                                            = 0;
		virtual void SetOutputGain( const double dOutputGain )                                     = 0;
		virtual void SetIRCrossfadeLength( const int iCrossfadeLength )                            = 0;
		virtual void SetSegmentIRCrossfadeLength( const int iSegment, const int iCrossfadeLength ) = 0;
		virtual void SetIRCrossfadeFunction( const int iCrossfadeFunc )                            = 0;
		virtual void SetSegmentIRCrossfadeFunction( const int iSegment, const int iCrossfadeFunc ) = 0;

		// @todo jst: check if the following is helpful for running convolution implementation

		//! Filterkomponente erzeugen
		/**
		 * Erzeugt eine Filterkomponente mit dem Startsegment 0 aus den angegebenen
		 * Filterkoeffizienten. Die Länge der Filterkomponente wir als nächstgrößere
		 * mögliche Länge der angegebenen Datenlänge gewählt.
		 *
		 * \param pfData Array der Filterkoeffizienten
		 * \param pfDataLength Anzahl der Filterkoeffizienten im Array
		 *
		 * \return Zeiger auf die erzeugte Filterkomponente
		 *
		 * \note Ein Nullzeiger als Parameter pfData ist erlaubt. In diesem Falle
		 *       wird die Filterkomponente nur erzeugt, aber nicht initialisiert.
		 *       Dies sollte vor der Benutzung im Falter mittels Aufruf der
		 *       Methode load geschehen.
		 */
		// virtual ITANUPCFilterComponent* CreateFilterComponent(const float* pfLeftData, unsigned int uiLeftDataLength, const float* pfRightData, unsigned int
		// uiRightDataLength)=0;

		//! Filterkomponente erzeugen
		/**
		 * Erzeugt eine Filterkomponente mit dem angegebenen Offset und Länge
		 * aus den angegebenen Filterkoeffizienten.
		 *
		 * \param uiStartSegment Index (Nummer) des Segments der Zerlegung der Impulsantworten
		 *                       bei dem diese Filterkomponente beginnt.
		 *                       (Bsp: Sei die Zerlegung beispielsweise (0, 1000, 3000, ...)
		 *                             Startsegment = 0 -> Filterkomponente beginnt bei Sample 0
		 *                             Startsegment = 2 -> Filterkomponente beginnt bei Sample 4000)
		 * \param uiLength Anzahl der Filterkoeffizienten
		 * \param pfData Array der Filterkoeffizienten
		 * \param uiDataLength Anzahl der Filterkoeffizienten im Array
		 *
		 * \return Zeiger auf die erzeugte Filterkomponente
		 *
		 * \note Ist pfDataLength < uiLength, werden automatisch (uiLength - uiDataLength)
		 *       Nullen angehangen
		 * \note Ein Nullzeiger als Parameter pfData ist nicht erlaubt
		 */
		// virtual ITANUPCFilterComponent* CreateFilterComponent(unsigned int uiStartSegment,
		//	                                              unsigned int uiLength,
		//									              const float* pfLeftData,
		//												  unsigned int uiLeftDataLength,
		//	                                              const float* pfRightData,
		//												  unsigned int uiRightDataLength)=0;

		//! Filterkomponente freigeben
		// virtual void DestroyFilterComponent(ITANUPCFilterComponent* pfcFilterComponent)=0;

		//! Freies Filter anfordern
		// virtual ITANUPCFilterComponent* RequestFilterComponent()=0;

		//! Filter wieder zur anderweitigen Benutzung freischalten
		// virtual void ReleaseFilterComponent(ITANUPCFilterComponent* pFilterComponent)=0;

		//! Maximale Länge der Impulsantworten zurückgeben
		/**
		 * Gibt die maximale Länge der Impulsantworten zurück, welche
		 * bei Erzeugung des Falters der create-Methode übergeben wurde.
		 */
		// virtual unsigned int GetMaxIRLength() const=0;

		////! Segmentoffsets zurückgeben
		///**
		// * Diese Methode gibt die Offsets der Segmente zurück,
		// * in welche Impulsantworten unterteilt sind.
		// *
		// * \return Vektor mit den Offsets (Ganzzahlwerte, in Reihenfolge)
		// *
		// * \sa selectFilterComponent
		// *
		// * \todo Sollte in publizierten Versionen nicht mehr enthalten sein!
		//    */
		// virtual std::vector<unsigned int> GetSegmentOffsets()=0;

		///* Unziehen in Segmentierung */

		////! Segmentindex eines Offset/Taps zurückgeben
		///**
		// * Diese Methode gibt zu einem Offset (tap) in der Impulsantwort
		// * das Segment zurück, in das dieser hineinfällt.
		// *
		// * \param uiSample Offset (tap)
		// * \return Segmentindex
		// *
		// * \note Falls uiSample größer gleich als die eingestellte IR-Länge ist,
		//    *       wird eine ITAException INVALID_PARAMETER ausgelöst.
		// */
		// virtual unsigned int GetSegment(unsigned int uiSample)=0;

		////! Nächstkleineren Segmentoffset zurückgeben
		// virtual unsigned int GetLowerSegmentOffset(unsigned int uiSample)=0;

		////! Nächstgrößeren Segmentoffset zurückgeben
		///**
		// * \note Wird die Methode mit einem Wert >= getLastSegmentOffset() des letzten Segments
		// *       aufgerufen, d.h. es gibt kein größeres Segment mehr, so wird eine
		// *       Ausnahme vom Typ ITANUPCException::INVALID_PARAMETER ausgelöst
		// * \sa getLastSegmentOffset()
		// */
		// virtual unsigned int GetUpperSegmentOffset(unsigned int uiSample)=0;

		////! Offset des letzten Segments zurückgeben
		// virtual unsigned int GetLastSegmentOffset()=0;

	protected:
		//! Protected constructor (use factory method Create() instead)
		IConvolution( );
	};
} // namespace ITANUPC

#endif // IW_ITA_NUP_CONVOLUTION
