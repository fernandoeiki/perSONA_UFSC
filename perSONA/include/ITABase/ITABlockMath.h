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

#ifndef INCLUDE_WATCHER_ITA_BLOCK_MATH
#define INCLUDE_WATCHER_ITA_BLOCK_MATH

#include <ITABaseDefinitions.h>

//! Komplexwertige, out-of-place Multiplikation auf Float-Arrays
/**
 * Komplexwertige, out-of-place Multiplikation auf Float-Arrays
 * Diese Funktion führt eine komplexwertige, Multiplikation der
 * Felder zweier komplexwertig interpretierter Float-Arrays durch und speichert
 * das Ergebnis in einem dritten, komplexwertig interpretierten Float-Array
 * Real und Imaginärteile sind nicht interleaved sondern jeweils für sich nacheinander in einem Block.
 * z.B.: Re[0], Re[1], .... Re[n-1] Im[0], Im[1], .... Re[n-1]
 *
 * \param dest Ziel-Array
 * \param Re1, Im1 Arrays der ersten komplexen Faktoren
 * \param Re1, Im1 Arrays der zweiten komplexen Faktoren
 * \param count Anzahl der zu bearbeitenden <u>komplexen</u> Felder (siehe Anmerkung)
 *
 * \note count bezieht sich hier auf die Anzahl der komplexen Zahlen die multipliziert
 *       werden sollen und <u>nicht</u> auf die Anzahl an Float-Feldern.
 */
void ITA_BASE_API bm_CMul( float* pfDestRe, float* pfDestIm, const float* pfRe1, const float* pfIm1, const float* pfRe2, const float* pfIm2, unsigned int uiCount );


//! Komplexwertige, out-of-place Multiplikation auf CSS Float-Arrays
/**
 * Komplexwertige, out-of-place Multiplikation auf Float-Arrays
 * Diese Funktion führt eine komplexwertige, Multiplikation der
 * Felder zweier komplexwertig interpretierter Float-Arrays durch und speichert
 * das Ergebnis in einem dritten, komplexwertig interpretierten Float-Array
 * Real und Imaginärteile sind im CSS Format jeweils für sich nacheinander in einem Block gespeichert.
 * z.B.: Re[0], Re[1], .... Re[n-1] Im[0], Im[1], .... Re[n-1]
 *
 * \param Dest Ziel-Array
 * \param Source1, Array der ersten komplexen Faktoren
 * \param Source2, Array der zweiten komplexen Faktoren
 * \param CssArraySize Anzahl der zu bearbeitenden Felder (siehe Anmerkung)
 *
 * \note CssArraySize bezieht sich hier auf die komplette Anzahl allocierter Float-Felder.
 */
void ITA_BASE_API bm_CMul_css( float* pfDest, const float* pfSource1, const float* pfSource2, unsigned int uiCssArraySize );


//! Einfache (reale), out-of-place Multiplikation auf Float-Arrays
/**
 * Diese Funktion führt eine Multiplikation von zwei Float-Arrays durch und speichert
 * das Ergebnis in einem dritten Float-Array
 *
 * \param Dest Ziel-Array
 * \param Source1, Array der ersten Faktoren
 * \param Source2, Array der zweiten Faktoren
 * \param uiCount Anzahl der zu bearbeitenden Felder
 */
void ITA_BASE_API bm_CMul( float* pfDest, const float* pfSrc1, const float* pfSrc2, unsigned int uiCount );


//! Komplexwertige, out-of-place Multiplikation auf CSS Float-Arrays
/**
 * Diese Funktion führt eine Multiplikation eines komplexwertigen Feldes mit einem realwertigen
 * Feld durch und speichert das Ergebnis in einem dritten, komplexwertig interpretierten Float-Array
 * Real und Imaginärteile sind im CSS Format jeweils für sich nacheinander in einem Block gespeichert.
 * z.B.: Re[0], Re[1], .... Re[n-1] Im[0], Im[1], .... Re[n-1]
 *
 * \param Dest Ziel-Array
 * \param pfSrcCmx, Array der komplexen Faktoren
 * \param pfSrcMag, Array der reellen Faktoren (Betrag)
 * \param CssArraySize Anzahl der zu bearbeitenden Felder (siehe Anmerkung)
 *
 * \note CssArraySize bezieht sich hier auf die komplette Anzahl allocierter Float-Felder.
 */
void ITA_BASE_API bm_CMulMag_css( float* pfDest, const float* pfSrcCmx, const float* pfSrcMag, unsigned int uiCssArraySize, float fFactor = 1.0f );


/*
void bm_CMulMag_css(float *pfDest,
                    const float	*pfSrcCmx,
                    const std::vector<float> &pvSrcMag,
                    unsigned int uiCssArraySize,
                    float fFactor = 1.0f);
*/


//! Komplexwertige, out-of-place Multiplikation und Addition auf Float-Arrays
/**
 * Komplexwertige, Multiplikation und Addition auf das Ergebnisfeld
 * Diese Funktion führt eine komplexwertige, Multiplikation der
 * Felder zweier komplexwertig interpretierter Float-Arrays durch und addiert
 * das Ergebnis in einem dritten, komplexwertig interpretierten Float-Array
 * Real und Imaginärteile sind nicht interleaved sondern jeweils für sich nacheinander in einem Block.
 * z.B.: Re[0], Re[1], .... Re[n-1] Im[0], Im[1], .... Re[n-1]
 *
 * \param dest Ziel-Array
 * \param Re1, Im1 Arrays der ersten komplexen Faktoren
 * \param Re1, Im1 Arrays der ersten komplexen Faktoren
 * \param count Anzahl der zu bearbeitenden <u>komplexen</u> Felder (siehe Anmerkung)
 *
 * \note count bezieht sich hier auf die Anzahl der komplexen Zahlen die multipliziert
 *       werden sollen und <u>nicht</u> auf die Anzahl an Float-Feldern.
 */
void ITA_BASE_API bm_CMulAdd( float* pfDestRe, float* pfDestIm, const float* pfRe1, const float* pfIm1, const float* pfRe2, const float* pfIm2, unsigned int uiCount );


//! Komplexwertige, out-of-place Multiplikation und Addition auf Float-Arrays
/**
 * Komplexwertige, Multiplikation und Addition auf das Ergebnisfeld
 * Diese Funktion führt eine komplexwertige, Multiplikation der
 * Felder zweier komplexwertig interpretierter Float-Arrays durch und addiert
 * das Ergebnis in einem dritten, komplexwertig interpretierten Float-Array
 * Real und Imaginärteile sind im CSS Format jeweils für sich nacheinander in einem Block gespeichert.
 * z.B.: Re[0], Re[1], .... Re[n-1] Im[0], Im[1], .... Re[n-1]
 *
 * \param Dest Ziel-Array
 * \param Source1, Array der ersten komplexen Faktoren
 * \param Source2, Array der zweiten komplexen Faktoren
 * \param CssArraySize Anzahl der zu bearbeitenden Felder (siehe Anmerkung)
 *
 * \note CssArraySize bezieht sich hier auf die komplette Anzahl allocierter Float-Felder.
 */
void ITA_BASE_API bm_CMulAdd_css( float* pfDest, const float* pfSource1, const float* pfSource2, unsigned int uiCssArraySize );


//! Komplexwertige, out-of-place Multiplikation und Subtraktion auf Float-Arrays
/**
 * Komplexwertige, Multiplikation und Subtraktion vom Ergebnisfeld
 * Diese Funktion führt eine komplexwertige, Multiplikation der
 * Felder zweier komplexwertig interpretierter Float-Arrays durch und addiert
 * das Ergebnis in einem dritten, komplexwertig interpretierten Float-Array
 * Real und Imaginärteile sind nicht interleaved sondern jeweils für sich nacheinander in einem Block.
 * z.B.: Re[0], Re[1], .... Re[n-1] Im[0], Im[1], .... Re[n-1]
 *
 * \param dest Ziel-Array
 * \param Re1, Im1 Arrays der ersten komplexen Faktoren
 * \param Re1, Im1 Arrays der zweiten komplexen Faktoren
 * \param count Anzahl der zu bearbeitenden <u>komplexen</u> Felder (siehe Anmerkung)
 *
 * \note count bezieht sich hier auf die Anzahl der komplexen Zahlen die multipliziert
 *       werden sollen und <u>nicht</u> auf die Anzahl an Float-Feldern.
 */
void ITA_BASE_API bm_CMulSub( float* pfDestRe, float* pfDestIm, const float* pfRe1, const float* pfIm1, const float* pfRe2, const float* pfIm2, unsigned int uiCount );


//! Komplexwertige, out-of-place Multiplikation und Subtraktion auf Float-Arrays
/**
 * Komplexwertige, Multiplikation und Subtraktion vom Ergebnisfeld
 * Diese Funktion führt eine komplexwertige, Multiplikation der
 * Felder zweier komplexwertig interpretierter Float-Arrays durch und addiert
 * das Ergebnis in einem dritten, komplexwertig interpretierten Float-Array
 * Real und Imaginärteile sind im CSS Format jeweils für sich nacheinander in einem Block gespeichert.
 * z.B.: Re[0], Re[1], .... Re[n-1] Im[0], Im[1], .... Re[n-1]
 *
 * \param Dest Ziel-Array
 * \param Source1, Array der ersten komplexen Faktoren
 * \param Source2, Array der zweiten komplexen Faktoren
 * \param CssArraySize Anzahl der zu bearbeitenden Felder (siehe Anmerkung)
 *
 * \note CssArraySize bezieht sich hier auf die komplette Anzahl allocierter Float-Felder.
 */
void ITA_BASE_API bm_CMulSub_css( float* pfDest, const float* pfSource1, const float* pfSource2, unsigned int uiCssArraySize );


//! Komplexwertige, out-of-place Division auf Float-Arrays
/**
// Diese Funktion führt eine komplexwertige, Division der
// Felder zweier komplexwertig interpretierter Float-Arrays durch und speichert
// das Ergebnis in einem dritten, komplexwertig interpretiertem Float-Array
// Real und Imaginärteile sind nicht interleaved sondern jeweils für sich nacheinander in einem Block.
// z.B.: Re[0], Re[1], .... Re[n-1] Im[0], Im[1], .... Re[n-1]
 *
 * \param dest Ziel-Array
 * \param ZRe, ZRe Zähler
 * \param NRe, NRe Nenner
 * \param count Anzahl der zu bearbeitenden <u>komplexen</u> Felder (siehe Anmerkung)
 *
 * \note count bezieht sich hier auf die Anzahl der komplexen Zahlen die multipliziert
 *       werden sollen und <u>nicht</u> auf die Anzahl an Float-Feldern.
 */
void ITA_BASE_API bm_CDiv( float* pfDestRe, float* pfDestIm, const float* pfZRe, const float* pfZIm, const float* pfNRe, const float* pfNIm, unsigned int uiCount );


//! Komplexwertige, out-of-place Division auf Float-Arrays
/**
// Diese Funktion führt eine komplexwertige, Division der
// Felder zweier komplexwertig interpretierter Float-Arrays durch und speichert
// das Ergebnis in einem dritten, komplexwertig interpretiertem Float-Array
// Real und Imaginärteile sind nicht interleaved sondern jeweils für sich nacheinander in einem Block.
// z.B.: Re[0], Re[1], .... Re[n-1] Im[0], Im[1], .... Re[n-1]
 *
 * \param dest Ziel-Array
 * \param Z, ZRe Zähler
 * \param N, NRe Nenner
 * \param CssArraySize Anzahl der zu bearbeitenden Felder (siehe Anmerkung)
 *
 * \note CssArraySize bezieht sich hier auf die komplette Anzahl allocierter Float-Felder.
 */
void ITA_BASE_API bm_CDiv_css( float* pfDest, const float* pfZ, const float* pfN, unsigned int uiCssArraySize );


//! In-place Vektoraddition auf Float-Arrays
/**
 * Diese Funktion führt eine feldweise Addition zweier Float-Arrays durch
 * entsprechend folgender Vorschrift durch:
 *
 *   for i from 0 to count-1:
 *     dest[i] += summand[i]
 *
 * \param dest Ziel-Array
 * \param summand Summanden-Array
 * \param count Anzahl der zu bearbeitenden Felder
 */
void ITA_BASE_API bm_Add( float* pfDest, const float* pfSummand, unsigned int uiCount );


//! ContinueMagnitudePreservePhase auf Float-Arrays
/**
// Der Betrag der aller komplexen Zahlen wird mit dem Bertrag der aktuellen Zahl überschrieben,
// wobei allerdings die Phase der jeweiligen Komplexen Zahl erhalten bleibt.
// uiCount gibt die Anzahl der überschriebenen Felder an, also hinter dem aktuellen Feld, das übergeben wurde.
// Real und Imaginärteile sind nicht interleaved sondern jeweils für sich nacheinander in einem Block.
// z.B.: Re[0], Re[1], .... Re[n-1] Im[0], Im[1], .... Re[n-1]
 *
 * \param pfRe Zeiger auf den Realteil
 * \param pfIm Zeiger auf den Imaginärteil
 * \param count Anzahl der zu bearbeitenden Felder
 */
void ITA_BASE_API bm_ContinueMagnitudePreservePhase( float* pfRe, float* pfIm, unsigned int uiCount );


//! ContinueMagnitudePreservePhase auf Float-Arrays
/**
// Der Betrag der aller komplexen Zahlen  ab der Startfrequenz wird mit dem Bertrag
// bei dieser Frequenz überschrieben, wobei allerdings die Phase der jeweiligen
// Komplexen Zahl erhalten bleibt.
// fStartFrequency gibt an, ab wann die Fortsetzung gelten soll.
// Real und Imaginärteile sind nicht interleaved sondern jeweils für sich nacheinander in einem Block.
// z.B.: Re[0], Re[1], .... Re[n-1] Im[0], Im[1], .... Re[n-1]
 *
 * \param pfData Zeiger auf die Daten
 * \param fStartFrequency: Ab dieser Frequenz fortsetzen
 * \param fSamplerate Abtastrate mit der die Daten vorliegen
 * \param CssArraySize Anzahl der zu bearbeitenden Felder (siehe Anmerkung)
 *
 * \note CssArraySize bezieht sich hier auf die komplette Anzahl allocierter Float-Felder.
 */
void ITA_BASE_API bm_ContinueMagnitudePreservePhase_css( float* pfData, float fStartFrequency, float fSamplerate, unsigned int uiCssArraySize );

//! MaxMag auf Float-Arrays
/**
// Es wird das absolute Maximum gesucht und der Wert (hier jetzt nicht Betrag) sowie die Position zurückgegeben
// Hat nur Sinn bei Zeitbereichsdaten
 *
 * \param pfData Zeiger auf das Array
 * \param uiCount Anzahl der zu bearbeitenden Felder
 * \param fValue enthält den Maximalen Wert
 * \param uiPosition enthält die Position des Maximums
 */
void ITA_BASE_API bm_MaxMag( float* pfData, unsigned int uiCount, float& fValue, unsigned int& uiPosition );


//! Max auf Float-Arrays
/**
// Es wird das Maximum gesucht und der Wert sowie die Position zurückgegeben
// Hat nur Sinn bei Zeitbereichsdaten
 *
 * \param pfData Zeiger auf das Array
 * \param uiCount Anzahl der zu bearbeitenden Felder
 * \param fValue enthält den Maximalen Wert
 * \param uiPosition enthält die Position des Maximums
 */
void ITA_BASE_API bm_Max( float* pfData, unsigned int uiCount, float& fValue, unsigned int& uiPosition );


//! CyclicMove auf Float-Arrays
/**
// Die vorder und hintere Hälfte des Filters werden getauscht
// Hat nur Sinn bei Zeitbereichsdaten
 *
 * \param pfData Zeiger auf das Array
 * \param uiCount Anzahl der zu bearbeitenden Felder
 */
void ITA_BASE_API bm_CyclicMove( float* pfData, unsigned int uiCount );


//! FreqIdent auf Float-Arrays
/**
// Ein EinsSpektrum erzeugen (Realteile=1 Imaginärteile=0)
// Hat nur Sinn bei Frequenzdaten
 *
 * \param pfData Zeiger auf das Array
 * \param CssArraySize Anzahl der zu bearbeitenden Felder (siehe Anmerkung)
 *
 * \note CssArraySize bezieht sich hier auf die komplette Anzahl allocierter Float-Felder.
 */
void ITA_BASE_API bm_FreqIdent_css( float* pfData, unsigned int uiCssArraySize );


//! SubSampleShift auf Float-Arrays
/**
// Das Signal wird im Sub-Samplebereich nach rechts geschoben
// Dies geschieht durch Manipulation der Pase im Frequenzbereich
// Hat nur Sinn bei Frequenzdaten
 *
 * \param pfData Zeiger auf das Array. Frequenzdaten!!
 * \param SubSampleShift: Verschiebung in Samples ( <1 )
 * \param CssArraySize: Anzahl der zu bearbeitenden Felder (siehe Anmerkung)
 *
 * \note CssArraySize bezieht sich hier auf die komplette Anzahl allocierter Float-Felder.
 */
void ITA_BASE_API bm_SubSampleShift_css( float* pfData, float fSubSampleShift, unsigned int uiCssArraySize );


//! SubSampleShift auf symetrischen Half-Size DFT-Spektren (interleaved format)
/**
 * Identisch zur Funktion bm_SubSampleShift_css. Datenformat allerdings Interleaved (Re, Im,  Re, Im, ...)
 *
 * \param pfData           Datenarray mit den komplexwertigen DFT-Koeffizienten
 * \param fSubSampleShift  Verschiebung in Samples (<1)
 * \param uiCoeffs         Anzahl komplexwertiger DFT-Koeffizienten (!) im Datenarray
 */
void ITA_BASE_API bm_SubSampleShift_SHDI( float* pfData, float fSubSampleShift, unsigned int uiCoeffs );


//! GetNextFFTLength
/**
// Gibt die nächstgrößere FFT-Länge zur Basis 2 zurück
 *
 * \param uiLength:  Länge, zu der die nächste FFT-Länge gesucht ist
 */
unsigned int ITA_BASE_API bm_GetNextFFTLength( unsigned int uiLength );

#endif // INCLUDE_WATCHER_ITA_BLOCK_MATH
