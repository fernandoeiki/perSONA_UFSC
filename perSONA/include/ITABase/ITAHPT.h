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

#ifndef INCLUDE_WATCHER_ITA_HPT
#define INCLUDE_WATCHER_ITA_HPT

#include <ITABaseDefinitions.h>
#include <string>
#ifdef WIN32
#	ifndef _WIN32_WINNT // @todo: remove
#		define _WIN32_WINNT 0x0501
#	endif
#	include <windows.h>
#else
#	include <linux/types.h>
#	include <stdio.h>
#	define __int64 int64_t
#endif

// Definition des Datentyps für Timerticks
typedef __int64 ITATimerTicks;

//! Timerfunktionalität initialisieren
/**
 * Initialisiert die Timerfunktionalität.
 * Ein expliziter Aufruf dieser Funktion ist nicht nötig.
 * Alle anderen HPT-Funktionen führen automatisch eine
 * Initialisierung durch, sofern diese noch nicht erfolgte.
 * Der Grund das diese Funktion dennoch frei zugänglich ist,
 * ist der das in manchen Fällen der Zeitpunkt der Initialisierung
 * frei gewählt werden muss, da das Einmessen der Timer ein
 * wenig Laufzeit benötigt.
 */
ITA_BASE_API void ITAHPT_init( );

//! Aktuellen Stand des Tickzählers ermitteln
ITA_BASE_API ITATimerTicks ITAHPT_now( );

//! Gibt die Frequenz des Zeitmessers zurück [Einheit: Hertz]
/** Die Frequenz ist die Anzahl der Ticks pro Sekunde */
ITA_BASE_API double ITAHPT_frequency( );

//! Gibt die Auflösung des Zeitmessers zurück [Einheit: Sekunden]
/** Die Auflösung ist Periodendauer eines Ticks. */
ITA_BASE_API double ITAHPT_resolution( );

//! Konvertierung einer allgemeinen Zeit (in Sekunden) in Ticks
ITA_BASE_API ITATimerTicks toTimerTicks( double t );

//! Konvertierung von Ticks in eine Zeit in Sekunden
ITA_BASE_API double toSeconds( ITATimerTicks n );

//! Konvertierung einer Zeit in Ticks in einen String
ITA_BASE_API std::string toString( ITATimerTicks n );

//! Schöne Formatierung einer Zeitangabe in Sekunden (Menschen lesbar)
/**
 * \note [stienen] Code nach ITAStringUtils \timeToString() kopiert ...
 */
ITA_BASE_API std::string convertTimeToHumanReadableString( double dSeconds );

#endif //