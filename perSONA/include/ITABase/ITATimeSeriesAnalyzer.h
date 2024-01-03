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

#ifndef INCLUDE_WATCHER_ITA_TIME_SERIES_ANALYZER
#define INCLUDE_WATCHER_ITA_TIME_SERIES_ANALYZER

#include <ITABaseDefinitions.h>
#include <algorithm>
#include <cmath>
#include <limits>
#include <sstream>
#include <string>
#include <vector>

//! Datenstruktur die Analysewerte für ein Zeitsignal speichert
template<typename T>
struct ITATimeseriesAnalyzerData
{
	T minimum;            // Minimalwert
	T maximum;            // Maximalwert
	double dMean;         // Arithmetischer Mittelwert (Erwartungswert)
	double dVariance;     // Varianz
	double dStdDeviation; // Standabweichung
};

/**
 * Ein Klassentemplate, welches Funktionalität definiert um ein Zeitsignal
 * zu analysieren. Einer Instanz des Klassentemplates werden Werte (samples)
 * des Templateparameter-Datentyps übergeben. Die Instanz analysiert das
 * so entstehende Zeitsignal und bestimmt dessen Grenzen (Minimum, Maximum),
 * sowie statistische Merkmale (Erwartungswert, Varianz, Standardabweichung).
 */
template<typename T>
class ITATimeseriesAnalyzer
{
public:
	inline ITATimeseriesAnalyzer( ) { reset( ); };

	//! Zurücksetzen
	/**
	 * Setzt alle Analysewerte zurück.
	 */
	inline void reset( )
	{
		m_minimum    = ( std::numeric_limits<T>::max )( );
		m_maximum    = ( std::numeric_limits<T>::min )( );
		m_uiSamples  = 0;
		m_dSum       = 0;
		m_dSquareSum = 0;
	};

	//! Einen Wert (sample) übergeben
	inline void handle( const T& value )
	{
		m_minimum = ( std::min )( m_minimum, value );
		m_maximum = ( std::max )( m_maximum, value );
		double x  = (double)value;
		m_dSum += x;
		m_dSquareSum += ( x * x );
		m_uiSamples++;
	};

	//! Mehrere Werte (sample) übergeben
	inline void handle( const T* value, unsigned int count )
	{
		for( unsigned int i = 0; i < count; i++ )
			handle( value[i] );
	};

	//! Mehrere Werte (sample) übergeben
	inline void handle( const std::vector<T>& values )
	{
		for( size_t i = 0; i < values.size( ); ++i )
			handle( values[i] );
	};

	//! Anzahl der übergebenen Werte zurück
	inline unsigned int samples( ) const { return m_uiSamples; };

	//! Kleinsten Wert zurückgeben
	/**
	 * \note Wurden noch keine Werte zur Analyse übergeben, ist der Rückgabewert 0
	 */
	inline T minimum( ) const { return ( m_uiSamples == 0 ? 0 : m_minimum ); };

	//! Größten Wert zurückgeben
	/**
	 * \note Wurden noch keine Werte zur Analyse übergeben, ist der Rückgabewert 0
	 */
	inline T maximum( ) const { return ( m_uiSamples == 0 ? 0 : m_maximum ); };

	//! Arithmetischer Mittelwert (mean) zurückgeben
	/**
	 * \return Arithmetischer Mittelwert (mean) aller übergebenen Werte
	 * \note Wurden noch keine Werte zur Analyse übergeben, ist der Rückgabewert 0
	 */
	inline double mean( ) const { return ( m_uiSamples == 0 ? 0 : m_dSum / (double)m_uiSamples ); };

	//! Varianz (Moment 2. Ordnung) zurückgeben
	/**
	 * Die Varianz (das Moment 2. Ordnung) aller übergebenen Werte berechnet
	 * sich zu omega = sqrt( 1/n * sum_over_x[i](mju - x[i]) ), wobei
	 * mju der arithmethische Mittelwert (mean, oder auch Erwartungswert)
	 * und die x[i] die bisher aufgenommenen Werte sind.
	 *
	 * \return Varianz
	 * \note Wurden noch keine Werte zur Analyse übergeben, ist der Rückgabewert 0
	 */
	inline double variance( ) const
	{
		if( m_uiSamples == 0 )
			return 0;
		// Formel: sigma = E(X^2) - E(X)^2
		double x = m_dSum / (double)m_uiSamples;
		return ( m_uiSamples == 0 ? 0 : m_dSquareSum / (double)m_uiSamples - x * x );
	};

	//! Standardabweichung aller aufgenommenen Werte zurückgeben
	/**
	 * Die Standardabweichung aller aufgenommenen Werte berechnet
	 * sich als Quadratwurzel der Varianz.
	 *
	 * \return Standardabweichung
	 * \note Wurden noch keine Werte zur Analyse übergeben, ist der Rückgabewert 0
	 */
	inline double std_deviation( ) const { return sqrt( variance( ) ); };

	//! Alle Informationen als 5-Tupel zurückgeben
	inline ITATimeseriesAnalyzerData<T> getData( )
	{
		ITATimeseriesAnalyzerData<T> data;
		data.minimum       = minimum( );
		data.maximum       = maximum( );
		data.dMean         = mean( );
		data.dVariance     = variance( );
		data.dStdDeviation = std_deviation( );
		return data;
	};

	//! Informationen über den Analysator als Zeichenkette zurückgeben
	inline std::string toString( )
	{
		std::stringstream ss;
		ss << "ITATimeseriesAnalyzer { samples: " << m_uiSamples << ", min: " << minimum( ) << ", max: " << maximum( ) << ", mean: " << mean( )
		   << ", var: " << variance( ) << ", stdder: " << std_deviation( ) << " }" << std::endl;
		return ss.str( );
	};

private:
	unsigned int m_uiSamples; // Anzahl übergebener Werte
	T m_minimum, m_maximum;
	double m_dSum;       // Summe aller Messwerte
	double m_dSquareSum; // Summe der Messwertquadrate für Berechnung der Varianz und StdDer.
};

#endif // INCLUDE_WATCHER_ITA_TIME_SERIES_ANALYZER
