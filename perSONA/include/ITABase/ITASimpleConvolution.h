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

#ifndef INCLUDE_WATCHER_ITA_SIMPLE_CONVOLUTION
#define INCLUDE_WATCHER_ITA_SIMPLE_CONVOLUTION

#include <ITABaseDefinitions.h>

//! Diskrete Faltung im Zeitbereich durchführen
/**
 * Diese Funktion führt die diskrete Faltung zweier Signale A und B im
 * Zeitbereich durch. Diese Operation hat eine Laufzeitkomplexität von
 * O(M*N) und ist nur effizient für Signale geringer Länge. (Für längere
 * Signale sollen Blockfaltungsverfahren benutzt werden).
 *
 * Semantik: C(n) = sum( A(k)B(n-k), k=-inf..+inf )
 *
 * \param A Eingangssignal 1
 * \param M Anzahl Felder im Eingangssignal 1
 * \param B Eingangssignal 2
 * \param N Anzahl Felder im Eingangssignal 2
 * \param C Ausgangssignal
 * \param K Anzahl Felder im Ausgangssignal
 *
 * Hinweis: Das vollständige Ausgangssignal hat eine Länge von M+N-1 Feldern.
 *          Trotzdem darf die Anzahl Felder im Ausgangssignal geringer sein.
 *          In diesem Falle wird das Faltungsergebnis gekürzt.
 */
void ITA_BASE_API conv( const float *A, int M, const float *B, int N, float *C, int K );
void ITA_BASE_API conv( const double *A, int M, const double *B, int N, double *C, int K );

#endif // INCLUDE_WATCHER_ITA_SIMPLE_CONVOLUTION
