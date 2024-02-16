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

#ifndef __ANGULAR_RANGE_H__
#define __ANGULAR_RANGE_H__

#include <string>

/**
 * Diese Klasse bildet Winkelbereiche ab und stellt Methoden zur Arbeit mit diesen bereit.
 * Der Winkelbereich ist [Startwinkel, Endwinkel] markiert durch einen Start- und Endwinkel,
 * d.h. es werden ausschließlich geschlossene Intervalle unterstützt. Wird ein Intervall
 * mit gleichem Start- und Endwinkel spezifiziert, so wird dies als vollständiges Intervall
 * [0°, 360°) interpretiert. Als Konsequenz kann die Klasse keine leeren Intervalle darstellen.
 * Der Standardkonstruktor erzeugt immer ein vollständiges Intervall.
 *
 * Wichtig: Alle Winkelangaben sind in Grad (nicht Bogengrad)
 */
class AngularRange
{
public:
	//! Standardkonstruktor
	AngularRange( );

	//! Initialisierungskonstruktor (geschlossenes Winkelintervall)
	AngularRange( float fLower, float fUpper );

	//! Unteren Bereichswinkel zurückgeben
	float getLowerAngle( ) const;

	//! Oberen Bereichswinkel zurückgeben
	float getUpperAngle( ) const;

	//! Unteren Bereichswinkel setzen
	void setLowerAngle( float fLower );

	//! Unteren Bereichswinkel setzen
	void setUpperAngle( float fUpper );

	//! Winkelbereich setzen (geschlossenes Winkelintervall)
	void setRange( float fLower, float fUpper );

	//! Zurückgeben ob ein Winkel im Intervall liegt
	bool contains( float fAngle ) const;

	//! Zurückgeben ob das Intervall ein anderes Intervall schneidet
	bool intersects( const AngularRange& dest ) const;

	//! Zurückgeben ob das Intervall den vollständigen Bereich [0°, 360°) abdeckt
	bool complete( ) const;

	//! Repräsentation als Zeichenkette zurückgeben
	std::string toString( ) const;

protected:
	float m_fLower, m_fUpper;
};

#endif // __ANGULAR_RANGE_H__