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

#ifndef INCLUDE_WATCHER_ITA_ASCII_TABLE
#define INCLUDE_WATCHER_ITA_ASCII_TABLE

#include <ITABaseDefinitions.h>
#include <ostream>
#include <string>
#include <vector>

/**
 * Diese Hilfsklasse ermöglicht die komfortable Ausgabe von Tabellendaten
 * als Text (wie z.B. auf der Konsole). Sie kapselt die Tabellendaten und
 * stellt eine Rendering-Methode zur Verfügung um die Zeichenketten-
 * Darstellung der Tabelle zu erhalten. Spaltenausrichtungen können gesetzt
 * werden und mehrzeile Spaltenüberschriften, sowie Felder werden unterstützt
 */

class ITA_BASE_API ITAASCIITable
{
public:
	//! Literal für Zeilen-/Spaltenenden
	static const unsigned int END = 0xFFFFFFFF;

	//! Literale für Ausrichtungen
	enum
	{
		LEFT   = 0,
		CENTER = 1,
		RIGHT  = 2
	};

	//! Formate
	enum
	{
		TEXT = 0, //!< Ausgabe als Text
		DAT,      //!< Datenformat
		CSV,      //!< CSV Format
	};
	static const int DEFAULT_FORMAT = TEXT;

	//! Konstruktor (leere Tabelle)
	ITAASCIITable( );

	//! Konstruktor (Vorgabe der Anzahl Zeilen/Spalten)
	ITAASCIITable( unsigned int uiRows, unsigned int uiColumns );

	//! Destruktor
	virtual ~ITAASCIITable( );

	//! Anzahl Zeilen zurückgeben
	unsigned int rows( ) const;

	//! Anzahl Zeilen zurückgeben
	unsigned int columns( ) const;

	//! Eine Zeile einfügen
	/**
	 * \param uiIndex Index der Zeile, nach der die neue Zeile eingefügt wird (optional)
	 */
	void addRow( unsigned int uiPosition = END );

	//! Eine Zeile entfernen
	/**
	 * \param uiIndex Index der Zeile die entfernt werden soll
	 */
	void removeRow( unsigned int uiRow );

	//! Eine Spalte einfügen
	/**
	 * \param uiIndex Index der Spalte, nach der die neue Spalte eingefügt wird (optional)
	 */
	void addColumn( unsigned int uiPosition = END );
	void addColumn( const std::string& sColumnTitle, unsigned int uiPosition = END );

	//! Eine Spalte entfernen
	/**
	 * \param uiIndex Index der Zeile die entfernt werden soll
	 */
	void removeColumn( unsigned int uiColumn );

	//! Ausrichtung einer Spalte zurückgeben
	unsigned int getColumnJustify( unsigned int uiColumn );

	//! Ausrichtung einer Spalte setzen
	void setColumnJustify( unsigned int uiColumn, unsigned int uiJustify );

	//! Titel einer Spalte zurückgeben
	std::string getColumnTitle( unsigned int uiColumn );

	//! Titel einer Spalte setzen
	void setColumnTitle( unsigned int uiColumn, const std::string& sTitle );

	//! Ausrichtung des Titels einer Spalte zurückgeben
	unsigned int getColumnTitleJustify( unsigned int uiColumn );

	//! Ausrichtung des Titels einer Spalte setzen
	void setColumnTitleJustify( unsigned int uiColumn, unsigned int uiJustify );

	//! Zelleinhalt zurückgeben
	std::string getContent( unsigned int uiRow, unsigned int uiColumn );

	//! Zellinhalt setzen
	void setContent( unsigned int uiRow, unsigned int uiColumn, const std::string& sContent );
	void setContent( unsigned int uiRow, unsigned int uiColumn, const char* pszContent );
	void setContent( unsigned int uiRow, unsigned int uiColumn, const bool& bContent );
	void setContent( unsigned int uiRow, unsigned int uiColumn, const unsigned int& uiContent );
	void setContent( unsigned int uiRow, unsigned int uiColumn, const int& iContent );
	void setContent( unsigned int uiRow, unsigned int uiColumn, const float& fContent, int iPrecision = -1 );
	void setContent( unsigned int uiRow, unsigned int uiColumn, const double& dContent, int iPrecision = -1 );

	//! Die ASCII-Tabelle rendern
	std::ostream& render( std::ostream& os, int iFormat = DEFAULT_FORMAT );
	std::ostream& renderText( std::ostream& os );
	std::ostream& renderDAT( std::ostream& os );
	std::ostream& renderCSV( std::ostream& os );

	//! Die ASCII-Tabelle rendern
	std::string toString( );

protected:
	class ITAASCIITableColumn
	{
	public:
		unsigned int uiTitleJustify;      // Ausrichtung des Titels
		std::string sTitle;               // Titel
		unsigned int uiJustify;           // Ausrichtung der Zellen
		std::vector<std::string> vsCells; // Inhalt der Zellen
		unsigned int uiMaxWidth;          // Maximale Zellenbreite

		ITAASCIITableColumn( )
		{
			uiJustify = uiTitleJustify = LEFT;
			uiMaxWidth                 = 0;
		}
	};

	std::vector<ITAASCIITableColumn> m_vColumns;

	void splitLines( const std::string& sText, std::vector<std::string>& vsDest );
};

#endif // INCLUDE_WATCHER_ITA_ASCII_TABLE
