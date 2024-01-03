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

#ifndef INCLUDE_WATCHER_ITA_FFT
#define INCLUDE_WATCHER_ITA_FFT

#include <ITAFFTDefinitions.h>

/*! \mainpage ITAFFT
 *
 * \section section_overview überblick
 *
 * ITAFFT ist eine Wrapper-Bibliothek für schnelle Fouriertransformationen. Ihre Aufgabe besteht darin,
 * eine Abstraktion von konkreten FFT-Bibliotheken (FFTW, Intel MKL, usw.) zu schaffen. Dadurch
 * können verschiedene FFT-Bibliotheken im Anwendungscode mit der gleichen Schnittstelle benutzt
 * und deshalb leicht ausgetauscht werden. Die Schnittstelle wird durch die Klasse ITAFFT bereitgestellt.
 * Entwurfsziel ist die einfache Benutzbarkeit. Verschiedene Typen von Fouriertransformationen
 * werden unterstützt. Folgende Grundprinzipien gelten:
 *
 * - Der Datentyp ist immer 32-Bit floating points (float)
 * - Alle* Transformationen speichern komplexe Fourierkoeffizienten im Fortran-Stil
 *   (auch interleaved memory layout genannt) der Form
 *
 *   Re(0), Im(0), Re(1), Im(1), ... , Re(k), Im(k)
 *
 *   d.h. Realteil und Imaginärteil folgen stets direkt aufeinander
 *
 * - Grundsätzlich sind alle Rücktransformationen unnormalisiert (Ausnahmen ...)
 *
 * \section section_feedback Feedback
 *
 * Hast Du Fragen oder Anmerkungen? Hast Du einen Fehler entdeckt?
 * Kontaktier den Autor: Frank.Wefers@akustik.rwth-aachen.de
 */

#include <string>

// Vorwärtsdeklarationen
class ITAFFTRealization;

/**
 * \section section_intro Aufgabe und Funktion der Klasse
 *
 * Dies ist Hauptklasse der Bibliothek. Sie stellt die Schnittstelle für die Arbeit mit schnellen
 * Fouriertransformationen (FFTs) bereit. Die Klasse kennt zwei Modi: Ungeplant und geplant.
 * Damit eine FFT/IFFT durchgeführt werden kann, muss sie zunüchst geplant werden.
 * Dies kann auch direkt bei der Erzeugung von Instanzen durch den Aufruf eines Planungs-
 * Konstruktors geschehen. Damit die Klasse auch flexibel als konkretes Member anderer Klassen
 * eingesetzt werden kann, ist auch ein Standardkonstruktor vorhanden, welcher eine
 * ungeplante Instanz erzeugt. Für die Planung müssen der Transformations-Typ, die Datengröße
 * sowie die Ein-/Ausgabedaten angegebenen werden. Ist die Transformation geplant, so kann sie
 * mit einer der execute-Methoden durchgeführt werden.
 *
 * \section section_transforms Berechnete Transformation
 *
 * Berechnet werden diskrete Fouriertransformationen (DFTs) und deren Rücktransformationen (IDFTs).
 *
 * - Komplex-zu-komplex DFT [FFT_C2C]
 *
 * \todo Grafik
 *
 * - Komplex-zu-komplex IDFT [IFFT_C2C]
 *
 * \todo Grafik
 *
 * - Reell-zu-komplex DFT [FFT_R2C]
 *
 * \todo Grafik
 *
 * - Komplex-zu-reell IDFT [IFFT_C2R]
 *
 * \todo Grafik
 *
 * \section section_usage Anwendungsbeispiele
 *
 * Beispiel: Allgemeine Benutzung
 *
 * <pre>
 *  float *A, *B, *C;
 *  ITAFFT fft(FFT_R2C, 128, A, B);
 *  ITAFFT ifft(FFT_C2R, 128, B, C);
 *
 *  fft.execute();
 *  // Mach etwas mit den Spektren...
 *  ifft.execute();
 * </pre>
 *
 * Beispiel: Benutzung von Fouriertransformationen als Member anderer Klassen
 *
 * <pre>
 *  class Filter {
 *  public:
 *    Filter();
 *
 *    ...
 *
 *  private:
 *    ITAFFT fft;
 *  };
 *
 *  // Entweder (Falls Größe/Daten bereits bekannt) ...
 *  Filter::Filter() : fft(FFT_R2C, 128, A, B) {
 *    ...
 *  }
 *
 *  // ... oder (Spätere Planung)
 *  Filter::Filter() {
 *    ...
 *    fft.plan(FFT_R2C, 128, A, B);
 *  }
 * </pre>
 *
 * \todo Erläuterung zu den Transformationen (Standardformat = Interleaved Format)
 * Speicherschema: Fortan-Stil (Real gefolgt von Imaginär), CCS complex conjugate symetric
 *
 * \note Es werden stets <b>unnormalisierte</b> Rücktransformationen (IFFTs) berechnet.
 * \note Bei reell-zu-komplex und komplex-zu-reell Fouriertransformationen bezieht sich
 *       die Grüüe der Transformation immer auf die Anzahl reeller Koeffizienten.
 */

class ITA_FFT_API ITAFFT
{
public:
	//! Transformationen
	/** Erläuterungen zu den Transformationen finden sich in ... */
	static const int FFT_C2C  = 1; //!< Allgemeine DFT (komplex-zu-komplex)
	static const int IFFT_C2C = 2; //!< Allgemeine unnormalisierte IDFT (komplex-zu-komplex)
	static const int FFT_R2C  = 3; //!< Reell-zu-komplex DFT (rein reellwertige Eingabedaten)
	static const int IFFT_C2R = 4; //!< Komplex-zu-reell IDFT (rein reellwertige Ausgabedaten)

	// Nur zur Kompatibilität mit alten Projekten (Sollte man nicht mehr verwenden!)
	// Gleiche Semantik, wie die alte MKL-Funktion SCFFT1DC!
	static const int SPLIT_FFT_R2C  = 5; //!< Reell-zu-komplex DFT mit altem C memory layout (Real- und Imaginürteile hintereinander getrennt)
	static const int SPLIT_IFFT_C2R = 6; //!< Reell-zu-komplex DFT mit altem C memory layout (Real- und Imaginürteile hintereinander getrennt)

	// Gleiche Semantik, wie die alte MKL-Funktion CSFFT1DC! (Diese spezielle Variante ist normalisiert!)
	static const int NORMALIZED_SPLIT_IFFT_C2R = 7; //!< Reell-zu-komplex DFT mit altem C memory layout (Real- und Imaginürteile hintereinander getrennt)

	// Aliase für alte MKL-Funktionen
	static const int MKL_SCFFT1DC = SPLIT_FFT_R2C;
	static const int MKL_CSFFT1DC = NORMALIZED_SPLIT_IFFT_C2R;

	/*
	//! Fehlerbehandlungsrichtlinien
	enum {
	    DO_NOTHING = 0,	//!< Nichts unternehmen im Fehlerfall. Programmablauf wird nicht unterbrochen
	    //ASSERTION,
	    THROW_EXCEPTION //!< Ausnahme auslösen im Fehlerfall. Programmablauf wird unterbrochen.
	};
	*/

	//! Flags zur Planung der FFTs
	enum
	{
		PLAN_USING_MEASUREMENT = 0, //!< Nutzt die genaue Planungsmethode für FFTs (für viele Koeffizienten sehr langsam)
		PLAN_USING_ESTIMATION  = 1  //!< Nutzt die schätzende Planungsmethode für FFTs (für viele Koeffizienten sehr schnell)
	} PlanningMethods;

	//! Standardkonstruktor
	/**
	 * Erzeugt eine ungeplante Fouriertransformation
	 */
	ITAFFT( );

	//! Planungskonstruktor
	/**
	 * Erzeugt und plant eine Fouriertransformation mit den angegebenen Eigenschaften
	 *
	 * \param type  Transformationstyp (\see TransformType)
	 * \param size  Größe der Transformation (Anzahl der Koeffizienten)
	 * \param in    Eingabedaten
	 * \param out   Ausgabedaten
	 * \param iPlanningMethod Methode der Planung, eines von \PlanningMethods
	 *
	 * \note Bei reell-zu-komplex und komplex-zu-reell Fouriertransformationen bezieht sich
	 *       die Grüüe der Transformation immer auf die Anzahl reeller Koeffizienten.
	 */
	ITAFFT( int type, int size, float* in, float* out, int iPlanningMethod = PLAN_USING_MEASUREMENT );

	//! Destruktor
	virtual ~ITAFFT( );

	//! Gibt zurück ob die Transformation bereits geplant wurde
	bool isPlanned( );

	//! Plant die Transformation
	/**
	 * Plant eine Fouriertransformation mit den angegebenen Eigenschaften
	 *
	 * \param type  Transformationstyp (\see TransformType)
	 * \param size  Größe der Transformation (Anzahl der Koeffizienten)
	 * \param in    Eingabedaten
	 * \param out   Ausgabedaten
	 * \param iPlanningMethod Methode der Planung, eines von \PlanningMethods
	 *
	 * \note Bei reell-zu-komplex und komplex-zu-reell Fouriertransformationen bezieht sich
	 *       die Grüüe der Transformation immer auf die Anzahl reeller Koeffizienten.
	 */
	void plan( int type, int size, float* in, float* out, int iPlannungMethod = PLAN_USING_MEASUREMENT );

	//! Transformation durchführen (auf geplanten Daten)
	/**
	 * Führt die Transformation auf den geplanten Daten aus
	 */
	void execute( );

	//! Transformation durchführen (auf anderen als geplante Daten)
	/**
	 * Führt die Transformation auf anderen Ein-/Ausgaben durch, als
	 * die bei der Planung angegebenen. Allerdings müssen die hier verwendeten
	 * Datenpuffer die gleichen Eigenschaften aufweisen, wie die bei der
	 * Planung verwendeten (in-place/out-of-place, SIMD alignment/no SIMD alignment)
	 */
	void execute( float* in, float* out );

	//! Gibt Informationen über die Transformation als Zeichenkette zurück
	std::string toString( );

private:
	// Kopieren der Instanzen verbieten
	ITAFFT( const ITAFFT& ) { };
	ITAFFT& operator=( const ITAFFT& ) { return *this; };

	ITAFFTRealization* m_pRealization; //!< Pointer zur Schnittstelle
};

#endif // INCLUDE_WATCHER_ITA_FFT
