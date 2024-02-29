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

#ifndef INCLUDE_WATCHER_ITA_FADE
#define INCLUDE_WATCHER_ITA_FADE

// ITABase
#include <ITABaseDefinitions.h>

//! Signal blenden
/**
 * Multipliziert alle Werte im Array pfData mit den entsprechenden Blendkoeffizienten.
 * Diese werden anhand der Parameter definiert.
 *
 * \param pfData		Array mit den zu blendenden Werten
 * \param iFadeLength	Länge der Blendung (darf Länge von pfData nicht überschreiten)
 * @param iFadingSign  Fade in or out
 * @param iFadingFunction Fading function
 */
void ITA_BASE_API Fade( float* pfData, int iFadeLength, int iFadingSign, int iFadingFunction );

//! Signal blenden (erweitert)
/**
 * Erweiterte Blend-Funktion, welche auch die Durchführung einer Blendung in mehreren
 * Schritten erlaubt. Die Position in der Überblendung kann frei gewählt werden.
 *
 * \param pfData		Array mit den zu blendenden Werten
 * \param iFadeLength	Länge der Blendung (darf hier die Länge die  pfData nicht überschreiten)
 * @param iFadingSign  Fade in or out
 * @param iFadingFunction Fading function
 * \param iOffset		Start-Position in der gesamten Blendung
 *                      (benötigt für Blenden in mehreren Schritten)
 * \param iLength       Anzahl Samples die ab Beginn von pfData modifiziert werden.
 */
void ITA_BASE_API Fade( float* pfData, int iFadeLength, int iFadingSign, int iFadingFunction, int iOffset, int iLength );

//! Signale kreuzblenden
/**
 * Führt eine Kreuzblende von pfSrc1 nach pfSrc2 durch und speichert das Ergebnis in pfDest.
 * pfDest darf auch gleich pfSrc(1|2) sein.
 *
 * \param pfSrc1		Quellpuffer (von)
 * \param pfSrc2		Quellpuffer (nach)
 * \param pfDest		Zielpuffer (von)
 * \param iFadeLength	Länge der Kreuzblende (darf Längen der drei Puffer nicht überschreiten)
 * @param iFadingFunction	Fading function
 */
void ITA_BASE_API Crossfade( const float* pfSrc1, const float* pfSrc2, float* pfDest, int iFadeLength, int iFadingFunction );

#endif // INCLUDE_WATCHER_ITA_FADE
