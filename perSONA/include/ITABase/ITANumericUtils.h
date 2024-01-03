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

#ifndef INCLUDE_WATCHER_ITA_NUMERIC_UTILS
#define INCLUDE_WATCHER_ITA_NUMERIC_UTILS

#include <ITABaseDefinitions.h>
#include <VistaBase/VistaQuaternion.h>
#include <VistaBase/VistaTransformMatrix.h>
#include <VistaBase/VistaVector3D.h>
#include <algorithm>
#include <cmath>
#include <limits>
#include <vector>


// Ein Makro für die Berechnung von Prozentsätzen (Wieviel Prozent p sind P von G?)
// Wichtiges Feature: Behandlung des Falles G = 0. Rückgabewert in diesem Fall 0.
#define PERCENT_OF( P, G ) ( G == 0 ? 0 : 100 * (double)P / (double)G )

//! Zweierexponent einer natürlichen Zahl ermitteln
/**
 * Ermittelt die natürliche Zahl k, welche 2^k = x erfüllt.
 * Existiert keine solche, d.h. ist x keine Zweierpotenz, so
 * gibt die Funktion -1 zurück.
 */
ITA_BASE_API int getExp2( unsigned int x );

//! Test auf Zweierpotenz
ITA_BASE_API bool isPow2( unsigned int x );

//! Nächstgrößeres Zweierpotenz zurückgeben
ITA_BASE_API unsigned int nextPow2( unsigned int x );


//! Nächstkleineres Vielfaches von mul zu einer Zahl x zurückgeben
/**
 * Beispiele: lwrmul(10, 5) = 10
 *            lwrmul(10, 6) = 6
 *            lwrmul(-10, 5) = -10
 *            lwrmul(-10, -6) = -12 (Kleiner!)
 *            lwrmul(-10, 6) = -12
 *            lwrmul(10, -6) = 12
 */
ITA_BASE_API int lwrmul( const int x, const int mul );

//! Nächstgrößeres Vielfaches von mul zu einer Zahl x zurückgeben
/**
 * Beispiele: uprmul(10, 5) = 10
 *            uprmul(10, 6) = 12
 *            uprmul(-10, 5) = -10
 *            uprmul(-10, -6) = -6 (Größer!)
 *            uprmul(-10, 6) = -6
 *            uprmul(10, -6) = 12
 */
ITA_BASE_API int uprmul( const int x, const int mul );

//! Nächstkleineres Vielfaches von mul zu einer Zahl x zurückgeben
/**
 * Beispiele: lwrmulu(10, 5) = 10
 *            lwrmulu(10, 6) = 6
 */
ITA_BASE_API unsigned int lwrmulu( const unsigned int x, const unsigned int mul );

//! Nächstgrößeres Vielfaches von mul zu einer Zahl x zurückgeben
/**
 * Beispiele: uprmulu(10, 5) = 10
 *            uprmulu(10, 6) = 12
 */
ITA_BASE_API unsigned int uprmulu( const unsigned int x, const unsigned int mul );

//! Aufrundende Ganzzahl-Division
/**
 * Fährt die Ganzzahl-Division c=a/b durch. Falls b nicht a teil
 * (d.h. es bleibt ein Rest a mod b != 0 übrig), so wird c um
 * eins inkrementiert. Danach gibt die Funktion c zurück
 *
 * Anwendungen: Wieviele Blöcke der Länge b sind erforderlich
 *              um ein Signal der Länge l zu beschreiben: uprdiv(l, b)
 */
ITA_BASE_API int uprdiv( const int a, const int b );

//! Aufrundende Ganzzahl-Division
/**
 * Variante von uprdiv für vorzeichenlose Ganzzahlen.
 */
ITA_BASE_API unsigned int uprdivu( const unsigned int a, const unsigned int b );

//! Einen (beliebigen) Winkel ins Interval (-180,180] abbilden
/**
 * Beispiel: correctAngle(380°) = 20°
 * \note Der exakte Wert -180 wird durch die Funktion erhalten
 *       und nicht auf +180 abgebildet (Ästethik :-))
 */
ITA_BASE_API float correctAngle180( const float fPhiDeg );

//! Einen (beliebigen) Winkel ins Interval [0,360) abbilden
/**
 * Beispiel: correctAngle(380°) = 20°
 */
ITA_BASE_API float correctAngle360( const float fPhiDeg );

//! Verhältnis in Dezibel (Energie) (im 10er-Logarithmus) umrechnen
/**
 * \param db Dezibel (Wertebereich: -Unendlich..+Unendlich)
 * \return Verhältnis (Wertebereich: 0..+Unendlich)
 *
 * \note Für die symbolische Konstante DECIBEL_MINUS_INFINITY gibt die
 *       Funktion den Wert 0 zurück.
 */
ITA_BASE_API double db10_to_ratio( const double db );

//! Dezibel (Energie) (im 10er-Logarithmus) in Verhältnis umrechnen
/**
 * \param Verhältnis (Wertebereich: 0..+Unendlich)
 * \return db Dezibel (Wertebereich: -Unendlich..+Unendlich)
 *
 * \note Für den Wert 0 gibt die Funktion die die symbolische Konstante
 *       DECIBEL_MINUS_INFINITY zurück.
 *
 * \important Negative Verhältnisse sind nicht erlaubt. In diesem
 *            Falle wird eine ITAException (INVALID_PARAMETER) ausgelöst!
 */
ITA_BASE_API double ratio_to_db10( const double r );


//! Verhältnis in Dezibel (Spannung) (im 10er-Logarithmus) umrechnen
/**
 * \param db Dezibel (Wertebereich: -Unendlich..+Unendlich)
 * \return Verhältnis (Wertebereich: 0..+Unendlich)
 *
 * \note Für die symbolische Konstante DECIBEL_MINUS_INFINITY gibt die
 *       Funktion den Wert 0 zurück.
 */
ITA_BASE_API double db20_to_ratio( const double db );

//! Dezibel (Spannung) (im 10er-Logarithmus) in Verhältnis umrechnen
/**
 * \param Verhältnis (Wertebereich: 0..+Unendlich)
 * \return db Dezibel (Wertebereich: -Unendlich..+Unendlich)
 *
 * \note Für den Wert 0 gibt die Funktion die die symbolische Konstante
 *       DECIBEL_MINUS_INFINITY zurück.
 *
 * \important Negative Verhältnisse sind nicht erlaubt. In diesem
 *            Falle wird eine ITAException (INVALID_PARAMETER) ausgelöst!
 */
ITA_BASE_API double ratio_to_db20( const double r );

/* +------------------------------------+
   |                                    |
   |   Funktionen für komplexe Zahlen   |
   |                                    |
   +------------------------------------+ */

//! Betrag einer komplexen Zahl berechnen
/**
 * @param[in] fReal Real part
 * @param[in] fImag Imaginary part
 */
ITA_BASE_API float cabsf( const float fReal, const float fImag );

//! Phase einer komplexen Zahl berechnen
ITA_BASE_API float canglef( const float fReal, const float fImag );

//! Betrag einer komplexen Zahl setzen, deren Phase aber erhalten (auch in-place)
ITA_BASE_API void csabsparg( const float fInReal, const float fInImag, const float fTargetAbs, float& fOutReal, float& fOutImag );

//! Winkel einer komplexen Zahl setzen, deren Betrag aber erhalten (auch in-place)
ITA_BASE_API void csargpabs( const float fInReal, const float fInImag, const float fTargetAbs, float& fOutReal, float& fOutImag );

//! Winkel im Bogenmaß in Grad [°] umrechnen
ITA_BASE_API float rad2gradf( const float fPhiRad );

//! Winkel im Bogenmaß in Grad [°] umrechnen
ITA_BASE_API double rad2grad( const double dPhiRad );

//! Winkel in Grad [°] ins Bogenmaß umrechnen
ITA_BASE_API float grad2radf( const float fPhiDeg );

//! Winkel im Bogenmaß in Grad [°] umrechnen
ITA_BASE_API double grad2rad( const double dPhiDeg );


/* ---------- RAD ----------- */

//! Einen Winkel (rad) in das Intervall [0, 2PI) projezieren
/**
 * Projeziert einen Winkel in Rad [rad] (nicht Grad) in das Intervall [0,2*PI) und
 * setzt somit negative Winkel (gegen den UZS) in positive (im UZS) um und entfernt
 * Mehrfachumdrehungen.
 *
 * Beispiele: 0->0, 2*PI->0, (-2*PI)->0, (2*PI+0.1)->0.1, (-0.1)->(2*PI-0.1)
 */
ITA_BASE_API float anglef_proj_0_2PI( const float fAlphaRad );

//! Einen Winkel (rad) in das Intervall (-PI, PI] projezieren
/**
 * Projeziert einen Winkel in Rad [rad] (nicht Grad) in das Intervall (-PI,PI] und
 * setzt somit negative Winkel über -PI (gegen den UZS) in positive (im UZS) um sowie
 * positive Winkel über PI (im UZS) in negative (gegen UZS) und entfernt Mehrfachumdrehungen.
 * Bemerkung: -PI wird auf PI abgebildet.
 *
 * Beispiele: 0->0, 2*PI->0, (-2*PI)->0, (PI+0.1)->(-PI+0.1), (-PI-0.1)->(PI-0.1)
 */
ITA_BASE_API float anglef_proj_NPI_PI( const float fAlphaRad );

//! (Gerichtete) minimale Winkeldifferenz für zwei Winkel [rad] (nicht Grad) im Intervall [0,2PI)
/**
 * Für zwei gegebene Winkel 0<=alpha, beta<2*PI im Interval [0,2*PI) berechnet
 * die Funktion den betragskleinsten Winkel gamma, um den der Winkel alpha (weiter)gedreht
 * werden muss, um den Wert des Winkels beta zu erreichen. Dies kann durch Linksdrehung
 * (im UZS, positiver Drehwinkel gamma) oder Rechtsdrehung (gegen UZS, negativer Drehwinkel gamma)
 * geschehen. Die Funktion berechnet den betragskleinsten Drehwinkel (im UZS oder gegen den UZS)
 * und gibt ihn zurück. Das Ergebnis ist also die Drehung um den geringstmöglichen Winkel um
 * alpha in beta zu überführen.
 *
 * \return Minimaler Differenzwinkel (negatives Vorzeichen = Linksdrehung, positives Vorzeichen = Rechtsdrehung)
 *
 * \note Im Gegensatz zur Funktion anglef_mindiff_abs_0_2PI gibt hier das Vorzeichen die
 *       Drehrichtung an.
 *
 * \note Die Funktion ist nicht kommutativ: f(a,b) != f(b,a)
 *
 * Beispiele: (0,PI/2) -> PI/2, (PI/5,PI/4) -> PI/20, (PI/3,PI/4) -> -PI/12, (0,2*PI-0.1) -> -0.1
 */
ITA_BASE_API float anglef_mindiff_0_2PI( const float alpha, const float beta );

//! Absolute minimale Winkeldifferenz für zwei Winkel [rad] im Intervall [0,2PI)
/**
 * Für zwei gegebene Winkel 0<=alpha, beta<2*PI im Interval [0,2*PI) berechnet
 * die Funktion den minimalen Differenzwinkel. Dieser Winkel ist der kleinste Winkel
 * um den einer der beiden Winkel rotiert werden muss, um den Wert des anderen Winkels
 * zu erreichen. Hierbei wird keine Drehrichtung beachtet und der Rückgabewert ist
 * stets positiv.
 *
 * \note Die Funktion ist kommutativ: f(a,b) = f(b,a)
 *
 * Beispiele: (0,PI/2) -> PI/2, (PI/2,PI/3) -> PI/6, (PI/3,PI/2) -> PI/6, (0,2*PI-0.1) -> 0.1
 */
ITA_BASE_API float anglef_mindiff_abs_0_2PI( const float alpha, const float beta );

/* ---------- GRAD ---------- */

//! Einen Winkel [°] in das Intervall [0°,360°) projezieren
/**
 * Projeziert einen Winkel in Grad [°] (nicht Bogenmaß) in das Intervall [0°,360°) und
 * setzt somit negative Winkel (gegen den UZS) in positive (im UZS) um und entfernt
 * Mehrfachumdrehungen.
 *
 * Beispiele: 0°->0°, 360°->0°, -360°->0°, 361°->1°, -1°->359°
 */
ITA_BASE_API float anglef_proj_0_360_DEG( const float alpha );

//! Einen Winkel (°) in das Intervall (-180°, 180°] projezieren
/**
 * Projeziert einen Winkel in Grad [°] (nicht Bogenmaß) in das Intervall (-180°,180°] und
 * setzt somit negative Winkel über -PI (gegen den UZS) in positive (im UZS) um sowie
 * positive Winkel über PI (im UZS) in negative (gegen UZS) und entfernt Mehrfachumdrehungen.
 * Bemerkung: -180° wird auf 180° abgebildet.
 *
 * Beispiele: 0°->0°, 360°->0°, -360°->0°, 181°->-179°, -181°->179°
 */
ITA_BASE_API float anglef_proj_N180_180_DEG( const float alpha );

//! Project an angle into interval of -90 and 90 degree
ITA_BASE_API float anglef_proj_N90_90_DEG( const float alpha );

//! (Gerichtete) minimale Winkeldifferenz für zwei Winkel [°] im Intervall [0°,360°)
/**
 * Für zwei gegebene Winkel 0°<= alpha, beta < 360° im Interval [0°,360°) berechnet
 * die Funktion den betragskleinsten Winkel gamma, um den der Winkel alpha (weiter)gedreht
 * werden muss, um den Wert des Winkels beta zu erreichen. Dies kann durch Linksdrehung
 * (im UZS, positiver Drehwinkel gamma) oder Rechtsdrehung (gegen UZS, negativer Drehwinkel gamma)
 * geschehen. Die Funktion berechnet den betragskleinsten Drehwinkel (im UZS oder gegen den UZS)
 * und gibt ihn zurück. Das Ergebnis ist also die Drehung um den geringstmöglichen Winkel um
 * alpha in beta zu überführen.
 *
 * \return Minimaler Differenzwinkel (negatives Vorzeichen = Linksdrehung, positives Vorzeichen = Rechtsdrehung)
 *
 * \note Im Gegensatz zur Funktion anglef_mindiff_abs_0_360_DEG gibt hier das Vorzeichen die
 *       Drehrichtung an.
 *
 * \note Die Funktion ist nicht kommutativ: f(a,b) != f(b,a)
 *
 * Beispiele: (0°,90°) -> 90°, (45°,70°) -> 25°, (70°,45°) -> -25°, (0°,359°) -> -1°
 */
ITA_BASE_API float anglef_mindiff_0_360_DEG( const float alpha, const float beta );

//! Absolute minimale Winkeldifferenz für zwei Winkel [°] im Intervall [0°,360°)
/**
 * Für zwei gegebene Winkel 0°<= alpha, beta < 360° im Interval [0°,360°) berechnet
 * die Funktion den minimalen Differenzwinkel. Dieser Winkel ist der kleinste Winkel
 * um den einer der beiden Winkel rotiert werden muss, um den Wert des anderen Winkels
 * zu erreichen. Hierbei wird keine Drehrichtung beachtet und der Rückgabewert ist
 * stets positiv.
 *
 * \note Die Funktion ist kommutativ: f(a,b) = f(b,a)
 *
 * Beispiele: (0°,90°) -> 90°, (45°,70°) -> 25°, (70°,45°) -> 25°, (0°,359°) -> 1°
 */
ITA_BASE_API float anglef_mindiff_abs_0_360_DEG( const float alpha, const float beta );


//! Orientierung in Yaw-Pitch-Roll Winkeln in View-Up-Vektor umrechnen (Alle Winkel in Bogenmaß)
ITA_BASE_API void convertYPR2VU( const double yaw, const double pitch, const double roll, double& vx, double& vy, double& vz, double& ux, double& uy, double& uz );

//! Orientierung in Yaw-Pitch-Roll Winkeln in View-Up-Vektor umrechnen (Alle Winkel in Bogenmaß)
ITA_BASE_API void convertYPR2VU( const float yaw, const float pitch, const float roll, float& vx, float& vy, float& vz, float& ux, float& uy, float& uz );

// Orientierung in View-Up-Vektor in Yaw-Pitch-Roll Winkeln umrechnen (Alle Winkel in Bogenmaß)
ITA_BASE_API void convertVU2YPR( const double vx, const double vy, const double vz, const double ux, const double uy, const double uz, double& yaw, double& pitch,
                                 double& roll );

//! Orientierung in View-Up-Vektor in Yaw-Pitch-Roll Winkeln umrechnen (Alle Winkel in Bogenmaß)
ITA_BASE_API void convertVU2YPR( const float vx, const float vy, const float vz, const float ux, const float uy, const float uz, float& yaw, float& pitch, float& roll );


//! Orientation in Quaternion: calculate Yaw-Pitch-Roll angles (all angles in radian)
ITA_BASE_API void calculateYPRAnglesFromQuaternion( VistaQuaternion q, double& dRoll, double& dPitch, double& dYaw );


//! Datenklasse für Fehlerwerte
template<typename T>
class ITA_BASE_API ErrorValues
{
public:
	T minAbsError;
	T avgAbsError;
	T maxAbsError;

	int indexMaxAbsError; // Index of element where max abs error

	inline ErrorValues( ) : minAbsError( 0 ), avgAbsError( 0 ), maxAbsError( 0 ), indexMaxAbsError( 0 ) { };
};

//! Fehler zwischen zwei Vektoren berechnen
template<typename Tc, typename Ta, typename Tb>
inline ErrorValues<Tc> computeErrorValues( const Ta* A, const Tb* B, const int size )
{
	ErrorValues<Tc> v;
	if( size == 0 )
		return v;

	Tb absErr     = std::abs( (Tc)A[0] - (Tc)B[0] );
	v.minAbsError = v.avgAbsError = v.maxAbsError = absErr;

	for( int i = 1; i < size; ++i )
	{
		absErr        = std::abs( (Tc)A[i] - (Tc)B[i] );
		v.minAbsError = std::min( v.minAbsError, absErr );

		if( absErr > v.maxAbsError )
		{
			v.maxAbsError      = absErr;
			v.indexMaxAbsError = i;
		}

		v.avgAbsError += absErr;
	}
	v.avgAbsError /= size;

	return v;
};


//! Fills a vector with numbers dest = { a+n*s < b | n in N }
template<typename T>
inline void linspace( std::vector<T>& dest, T a, T b, T s = 1 )
{
	dest.clear( );
	if( s == 0 )
	{
		dest.push_back( a );
		return;
	}

	if( s < 0 )
	{
		if( a < b )
			return; // No elements contained
		dest.reserve( ( a - b ) / s + 1 );
		for( T x = a; x >= b; x += s )
			dest.push_back( x );
	}
	else
	{
		if( a > b )
			return; // No elements contained
		dest.reserve( ( b - a ) / s + 1 );
		for( T x = a; x <= b; x += s )
			dest.push_back( x );
	}
};

//! Fills a vector with powers of two in the range a=2^i <= 2^j <= 2^k=b
/**
 * @note a and b must be powers of two, otherwise an exception is thrown)
 */
ITA_BASE_API void pow2space( std::vector<int>& dest, const int a, const int b );

//! Returns the elevation angle (0 = frontal direction) in radians from a polar angle theta (0 = above)
ITA_BASE_API double theta2elevation( const double dThetaRAD );

//! returns the polar angle theta (0 = above) in radians from a given elevation angle (0 = frontal direction)
ITA_BASE_API double elevation2theta( const double dElevationRAD );

// Calculates the factorial of an positive integer m
ITA_BASE_API int factorial( const int m );

/// <summary>
/// Calculates the real-valued base functions of SH for e.g. Ambisonics
/// </summary>
/// <param name="thetaRAD">Elevation in rad. 0 refers to north pole and PI to south pole.</param>
/// <param name="azimuthRAD">Azimuth in rad. 0 refers to front and PI/2 refers to left.</param>
/// <param name="maxOrder">Ambisonics truncation order</param>
ITA_BASE_API double SHNormalizeConst( const int m, const int n );

//! Calculates the Kronecker delta
ITA_BASE_API int SHKronecker( const int m );

//! Returns the linear index of a basefunction with degree m and order n, linear indexing starts with 0
ITA_BASE_API int SHDegreeOrder2Linear( const int m, const int n );

//! Returns degree and order of a basefunctions from a linear index, linear indexing starts with 0
ITA_BASE_API void SHLinear2DegreeOrder( const int iLinear, int& m, int& n );

//! Calculates the remax weightings up to a given order
ITA_BASE_API std::vector<double> HOARemaxWeights( int iTruncationOrder );

//! Calculates the realvalued Basefunctions of SH for e.g. Ambisonics
ITA_BASE_API std::vector<double> SHRealvaluedBasefunctions( const double thetaRAD, const double azimuthRAD, const int maxOrder );

//! Calculates the associated legendre polynomials
ITA_BASE_API std::vector<double> SHAssociatedLegendre( const int N, const double mu );

#endif // INCLUDE_WATCHER_ITA_NUMERIC_UTILS
