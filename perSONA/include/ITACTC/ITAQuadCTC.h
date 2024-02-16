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

// $Id: ITAQuadCTC.h,v 1.10 2008-12-02 22:31:36 fwefers Exp $

#ifndef __ITA_QUADCTC_H__
#define __ITA_QUADCTC_H__

// STL Includes
#include <string>
#include <vector>

// ITA Includes
#include <AngularRange.h>
#include <ITAFFT.h>
#include <ITAHDFTSpectrum.h>
#include <ITAStopwatch.h>
#include <RG_LocalCS.h>
#include <VistaInterProcComm/Concurrency/VistaMutex.h>
#include <VistaInterProcComm/Concurrency/VistaThreadEvent.h>
#include <VistaInterProcComm/Concurrency/VistaThreadLoop.h>


// Vorwärtsdeklarationen
class ITADatasource;
class ITAQuadCTCStreamfilter;
class DAFFContentIR;
class DAFFContentDFT;
class DAFFReader;

class ITAQuadCTC : public VistaThreadLoop
{
public:
	ITAQuadCTC( double dSamplerate, int iBlocklength, const std::string& sConfigurationFile, DAFFContentIR* pHRIR = NULL );

	~ITAQuadCTC( );

	// Eingangsaudiodatenquelle setzen
	// (Hinweis: Muss genau zwei Kanäle haben)
	void setInputDatasource( ITADatasource* pdsInput );

	// Ausgabeaudiodatenquelle zurückgeben
	ITADatasource* getOutputDatasource( ) const;

	// Liefert die Lautsprecher-Kanäle der Audio-Hardware zurück,
	// auf welchen die CTC ausgegeben werden soll.
	// Diese Information stammt aus der CTC-Konfigurationsdatei.
	void getPhysicalOutputChannels( std::vector<int>& viChannels ) const;

	// Positionen und Orientierungen der Lautsprecher abfragen
	void getLoudspeakerPositionOrientation( int iSpeaker, RG_Vector& vPos, RG_Vector& vView, RG_Vector& vUp ) const;

	// Zustand der Lautsprecher zurückgeben
	void getLoudspeakerStates( std::vector<int>& viStates );

	// -= Abstrakte Methoden der Klasse "ITAQuadCTC" =-

	void testLS2H( RG_Vector& vPos );
	void testHRIR( );

	double getLatency( );

	void updateHeadPosition( const RG_Vector& vPos, const RG_Vector& vView, const RG_Vector& vUp, bool bForceFilterUpdate = false );

	void updateHeadPosition( double px, double py, double pz, double vx, double vy, double vz, double ux, double uy, double uz, bool bForceFilterUpdate = false );

	// Alternative Methode zum Setzen der Kopfposition (mit Winkeln, zum Debuggen)
	void updateHeadPosition( const float fX, const float fY, const float fZ, const float fPhiDEG, const float fThetaDEG, const float fRhoDEG,
	                         bool bForceFilterUpdate = false );

	// Diese Methode entscheiden ob für eine neue Kopfposition die CTC-Filter neu berechnet werden
	bool mustRecalculateFilters( const RG_Vector& vPos, const RG_Vector& vView, const RG_Vector& vUp );

	// CTC-Filter (neu)berechnen
	void calculateFilters( );

	// -= Definition der virtuellen Methoden in VistaThread =-

	void PreLoop( );
	void PostLoop( );
	bool LoopBody( );

private:
	class PositionViewUp
	{
	public:
		RG_Vector m_vPos, m_vView, m_vUp;

		PositionViewUp( const RG_Vector& vPos, const RG_Vector& vView, const RG_Vector& vUp ) : m_vPos( vPos ), m_vView( vView ), m_vUp( vUp ) {}
	};

	VistaThreadEvent m_evHeadDataAvail;      // Thread-Event: Berechnung starten
	std::vector<PositionViewUp> m_vHeadData; // Eingabe-Queue für Kopfdaten
	bool m_bForceFilterUpdate;               // Filterneuberechnung erzwingen
	bool m_bStopThread;
	VistaMutex m_mxHeadData; // Mutex: Exklusiver Zugriff auf Eingabe-Queue

	DAFFContentIR* m_pHRIRDatabase; // Hear-related impulse response (HRIR) database
	int m_iHRIRLength;              // Länge der HRIRs (Anzahl Filterkoeffizienten)
	float m_fHRIRDelay;             // Anzahl Taps bis zur Mitte der HRIRs

	double m_dSamplerate;                 // Abtastrate [Hz]
	int m_iBlocklength;                   // Streaming-Blocklänge
	ITADatasource* m_pdsInput;            // Eingangs-seitige Datenquelle
	ITAQuadCTCStreamfilter* m_psfFilter;  // Streaming-Filter
	std::vector<int> m_viSpeakerChannels; // Ausgabekanäle der Lautsprecher auf der Audio-Hardware
	float m_fc;                           // Schallgeschwindigkeit [m/s]
	RG_LocalCS m_csHead;                  // Kopf-bezogenes Koordinatensystem
	RG_LocalCS m_csSpeaker[4];            // Lautsprecher-bezogene Koordinatensysteme
	int m_iCTCFilterLength;               // Anzahl Filterkoeffizienten der Cancellation-Filter (Zeitbereich)
	int m_iOrder;                         // Ordnung der CTC (Größte Potenz von K)
	double m_dUpperLimitFrequency;        // Obere Grenzfrequenz für Tiefpassfilterung [Hz]
	double m_dLatency;                    // Gesamtlatenz der CTC [s]
	RG_Vector m_pvEarOffset[2];           // Versatz Kopf-Bezugspunkt -> Ohreingang (Links / Rechts)
	float m_fL2SDistMin, m_fL2SDistMax;   // Minimal-/Maximalabstand zu den Lautsprechern
	int m_iLowpassDelay;                  // Verzögerung aufgrund des kausalen FIR-Tiefpasses [Samples]
	int m_iFlexDelay;                     // TODO: Dokumentieren
	int m_iOnset;                         // Onset der CTC-Filter (Zusätzlicher Platz am Anfang)
	std::vector<int> m_viSpeakerStates;   // Lautsprecher-Zustände (aktiv=1, inaktiv=0)
	float m_fBeta;                        // Beta-Wert für die Regularisierung
	int m_iFadingMode;                    // bestimmt das Überblenden der Lautsprecher
	std::string m_sHRIRDataset;           // HRIR Datensatz

	DAFFReader* m_pHRIRReader;

	float *m_pfHRIRBufCh0, *m_pfHRIRBufCh1; // Puffer für HRIRs
	float *m_pfHRIR_LS0_Ch0,                // HRIRs Kopf -> Lautsprecher
	    *m_pfHRIR_LS0_Ch1, *m_pfHRIR_LS1_Ch0, *m_pfHRIR_LS1_Ch1, *m_pfHRIR_LS2_Ch0, *m_pfHRIR_LS2_Ch1, *m_pfHRIR_LS3_Ch0, *m_pfHRIR_LS3_Ch1;
	float *m_pfCTC_VLL, // CTC-Filter
	    *m_pfCTC_VRR, *m_pfCTC_VLR, *m_pfCTC_VRL, *m_pfCTC_HLL, *m_pfCTC_HRR, *m_pfCTC_HLR, *m_pfCTC_HRL;
	float *CTC_Filter90LS0_0, // CTC-Filter vor dem Fading
	    *CTC_Filter90LS0_1, *CTC_Filter90LS1_0, *CTC_Filter90LS1_1, *CTC_Filter180LS0_0, *CTC_Filter180LS0_1, *CTC_Filter180LS1_0, *CTC_Filter180LS1_1,
	    *CTC_Filter180LSV_0, *CTC_Filter180LSV_1, *CTC_Filter180LSH_0, *CTC_Filter180LSH_1;

	float* m_pfTemp;
	ITAHDFTSpectrum m_spCTC_LL, // Benötigte Spektren für die Berechnung
	    m_spCTC_LR, m_spCTC_RL, m_spCTC_RR, m_spH_LL, m_spH_RR, m_spH_LR, m_spH_RL, m_spK, m_spLowpass, determinante, HLLcon, HLRcon, HRLcon, HRRcon, a, b, c, d, temp;


	ITAFFT m_fft, m_ifft;

	int m_iFDSize;               // Filtergröße des fractional delay FIR-Filters
	float* m_pfFDResponse;       // Impulsantwort des fractional delay FIR-Filters
	bool m_bUseFractionalDelays; // Fractional delays mit einbeziehen

	ITAStopwatch m_swCTCFilterCalc;

	// Sektoren
	AngularRange m_arSector12Span, m_arSector12Core;
	AngularRange m_arSector23Span, m_arSector23Core;
	AngularRange m_arSector34Span, m_arSector34Core;
	AngularRange m_arSector41Span, m_arSector41Core;

	AngularRange m_arSector13Span, m_arSector13Core;
	AngularRange m_arSector24Span, m_arSector24Core;
	AngularRange m_arSector31Span, m_arSector31Core;
	AngularRange m_arSector42Span, m_arSector42Core;

	// Arbeitsbereich (Achsenbeschränkungen)
	struct
	{
		float fXMin, fXMax;
		float fYMin, fYMax;
		float fZMin, fZMax;
	} m_bounds;

	// Aktuelle Kopfposition (für die die CTC berechnet ist)
	struct
	{
		RG_Vector vPos;
		RG_Vector vView;
		RG_Vector vUp;
	} m_headpos;

	// aktive LS zurückgeben

	int* getActiveLS( );

	// Winkel (Azimuth, Elevation) von einem Lautsprecher zum Kopf berechnen (für Richtcharakteristik)
	// void getS2HAngles(int iSpeaker, const RG_Vector& vPos, float& fAzimuth, float& fElevation);

	void getHRIR( double dAzimuthRad, double dElevationRad, double dDistanceMeters, float* pfDataCh0, float* pfDataCh1, bool& bOutOfRange );

	// CTC-Konfiguration bestimmen
	std::vector<std::pair<int, float> > determineConfig( );

	// Berechnet neues CTCFilterSet für 2 LS
	void calculateFilterSet( float* HRIR_LS0_Ch0, float* HRIR_LS0_Ch1, float* HRIR_LS1_Ch0, float* HRIR_LS1_Ch1, float* CTC_FilterLS0_0, float* CTC_FilterLS0_1,
	                         float* CTC_FilterLS1_0, float* CTC_FilterLS1_1 );

	//Überblenden 2er CTC-LSConfigurationen (Fading 0=kein Fading, 1=linear, 2=TODO(Sinus))
	void SektorFading( float* Filter180_LL, float* Filter180_LR, float* Filter180_RL, float* Filter180_RR, float* Filter90_LL, float* Filter90_LR, float* Filter90_RL,
	                   float* Filter90_RR, float* Filter180_VL, float* Filter180_VR, float* Filter180_HL, float* Filter180_HR,
	                   std::vector<std::pair<int, float> > LSConfiguration, int Fading = 0 );

	// Lautstärkeabnahme über Entfernung bestimmen
	// double getDistanceGain(double dDistance);

	// Liest die komplette Konfigurationsdatei ein
	void parseConfigurationFile( const std::string& sConfigurationFile );

	// Liest aus Konfigurationsdatei die Angaben für einen Lautsprecher und überprüft sie auf Korrektheit
	void parseSpeakerSection( int iSpeaker, const std::string& sName, const std::string& sParentConfigurationFile );

	// Liest aus Konfigurationsdatei einen Winkelbereich für einen Sektor
	void parseSector( const std::string& sName, const std::string& sParentConfigurationFile, AngularRange& arange );

	// Debug-Funktion: Filter auf die Platte schreiben
	void dumpFilters( const std::string& sFilename, float* pf1, float* pf2, float* pf3, float* pf4, int iLength );

	// Debug-Funktion: Spektrum zurücktransformieren in den ZB, danach auf Platte schreiben
	void dumpSpectrum( const std::string& sFilename, ITAHDFTSpectrum& spSpectrum, bool bNorm = false );

	// Debug-Funktion: Spektrum zurücktransformieren in den ZB, Werte auf die Platte schreiben
	void dumpSpectrumText( const std::string& sFilename, ITAHDFTSpectrum& spSpectrum, bool bNorm = false );
};

#endif // __ITA_QUADCTC_H__