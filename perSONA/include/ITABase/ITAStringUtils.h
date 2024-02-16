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

#ifndef INCLUDE_WATCHER_ITA_STRING_UTILS
#define INCLUDE_WATCHER_ITA_STRING_UTILS

#include <ITABaseDefinitions.h>
#include <ITAException.h>
#include <ITATypes.h>
#include <sstream>
#include <string>
#include <vector>

// Konvertierungsklasse
class ITA_BASE_API ITAConversion
{
public:
	static const int STRICT_MODE      = ( 1 << 0 ); // Konvertierungen mittels Regex prüfen (sauber!)
	static const int THROW_EXCEPTIONS = ( 1 << 1 ); // ITAExceptios werfen wenn eine Konvertierung fehlschlägt

	static const int DEFAULT_OPTIONS = STRICT_MODE | THROW_EXCEPTIONS;

	inline ITAConversion( ) : m_iOpts( DEFAULT_OPTIONS ) { };
	inline ITAConversion( int iOpts ) : m_iOpts( iOpts ) { };

	bool StringToBool( const std::string& s, bool& b );
	bool StringToInt( const std::string& s, int& i );
	bool StringToUInt( const std::string& s, unsigned int& i );
	bool StringToInt64( const std::string& s, int64_t& i );
	bool StringToUInt64( const std::string& s, uint64_t& i );
	bool StringToFloat( const std::string& s, float& f );
	bool StringToDouble( const std::string& s, double& d );

	bool StringToIntVec( const std::string& s, std::vector<int>& v, std::string sSeparatorRegex = "\\s*,\\s*", bool bMatchCase = true );
	bool StringToUIntVec( const std::string& s, std::vector<unsigned int>& v, std::string sSeparatorRegex = "\\s*,\\s*", bool bMatchCase = true );
	bool StringToFloatVec( const std::string& s, std::vector<float>& v, std::string sSeparatorRegex = "\\s*,\\s*", bool bMatchCase = true );
	bool StringToDoubleVec( const std::string& s, std::vector<double>& v, std::string sSeparatorRegex = "\\s*,\\s*", bool bMatchCase = true );
	bool StringToStringVec( const std::string& s, std::vector<std::string>& v, std::string sSeparatorRegex = "\\s*,\\s*", bool bMatchCase = true );
	void StringToDoubleVecNoRegex( const std::string& s, std::vector<double>& v );

private:
	int m_iOpts;
};


//! Eine Zeichenkette in Kleinbuchstaben konvertieren
ITA_BASE_API std::string toLowercase( const std::string& s );

//! Eine Zeichenkette in Grossbuchstaben konvertieren
ITA_BASE_API std::string toUppercase( const std::string& s );

//! bool nach std::string konvertieren
ITA_BASE_API std::string BoolToString( bool bValue );

//! int nach std::string konvertieren
ITA_BASE_API std::string IntToString( const int iValue );

//! unsigned int nach std::string konvertieren
ITA_BASE_API std::string UIntToString( unsigned int uiValue );

//! long nach std::string konvertieren
ITA_BASE_API std::string LongToString( unsigned int lValue );

//! 64-Bit Integer mit Vorzeichen nach std::string konvertieren
ITA_BASE_API std::string Int64ToString( int64_t i64Value );

//! Vorzeichenlosen 64-Bit Integer nach std::string konvertieren
ITA_BASE_API std::string UInt64ToString( uint64_t ui64Value );

//! float nach std::string konvertieren
ITA_BASE_API std::string FloatToString( float fValue, int iPrecision = -1 );

//! double nach std::string konvertieren
ITA_BASE_API std::string DoubleToString( double dValue, int iPrecision = -1 );

//! Bitmaske nach std::string konvertieren
ITA_BASE_API std::string BitmaskToString( int iMask, int iNumBits = 32 );

//! Dezibelangabe (double) nach std::string konvertieren
ITA_BASE_API std::string DecibelToString( double dDecibelValue, std::string sMinusInfinity = "-inf", std::string sUnit = "dB" );

//! std::vector<Enum_Type> nach std::string konvertieren
template<typename TEnum>
inline std::string EnumVecToString( std::vector<TEnum> veValues, std::string sSeparator = ", " )
{
	std::stringstream s;
	if( !veValues.empty( ) )
	{
		s << static_cast<int>( veValues.front( ) );
		for( unsigned int i = 1; i < veValues.size( ); i++ )
			s << sSeparator << static_cast<int>( veValues[i] );
	}
	return s.str( );
};

//! std::vector<int> nach std::string konvertieren
ITA_BASE_API std::string IntVecToString( std::vector<int> viValues, std::string sSeparator = ", " );

//! std::vector<unsigned int> nach std::string konvertieren
ITA_BASE_API std::string UIntVecToString( std::vector<unsigned int> vuiValues, std::string sSeparator = ", " );

//! std::vector<float> nach std::string konvertieren
ITA_BASE_API std::string FloatVecToString( std::vector<float> vfValues, int iPrecision = -1, std::string sSeparator = ", " );

//! std::vector<double> nach std::string konvertieren
ITA_BASE_API std::string DoubleVecToString( std::vector<double> vdValues, int iPrecision = -1, std::string sSeparator = ", " );

//! std::vector<std::string> nach std::string konvertieren
ITA_BASE_API std::string StringVecToString( std::vector<std::string> vsValues, std::string sSeparator = ", " );

//! int-Array nach std::string konvertieren
ITA_BASE_API std::string IntArrayToString( const int* piValues, size_t count, std::string sSeparator = ", " );

//! unsigned int-Array nach std::string konvertieren
ITA_BASE_API std::string UIntArrayToString( const unsigned int* puiValues, size_t count, std::string sSeparator = ", " );

//! float-Array nach std::string konvertieren
ITA_BASE_API std::string FloatArrayToString( const float* pfValues, size_t count, int iPrecision = -1, std::string sSeparator = ", " );

//! Komplexwertiges float-Array nach std::string konvertieren
ITA_BASE_API std::string ComplexFloatArrayToString( const float* pfValues, size_t count, int iPrecision = -1, std::string sSeparator = ", " );

//! double-Array nach std::string konvertieren
ITA_BASE_API std::string DoubleArrayToString( const double* pdValues, size_t count, int iPrecision = -1, std::string sSeparator = ", " );

//! String-Array nach std::string konvertieren
ITA_BASE_API std::string StringArrayToString( const char** ppcValues, size_t count, std::string sSeparator = ", " );

/* +-------------------------------------------------------------+
   |                                                             |
   |   Konvertierungsfunktionen der Form:  String -> Objekt(e)   |
   |                                                             |
   +-------------------------------------------------------------+ */

//! std::string nach bool parsen (Parse-Fehler werden in ITAExceptions umgesetzt)
ITA_BASE_API bool StringToBool( const std::string& s );

//! std::string nach int parsen (Parse-Fehler werden in ITAExceptions umgesetzt)
ITA_BASE_API int StringToInt( const std::string& s );

//! std::string nach unsigned int parsen (Parse-Fehler werden in ITAExceptions umgesetzt)
ITA_BASE_API unsigned int StringToUInt( const std::string& s );

//! std::string nach int64_t parsen (Parse-Fehler werden in ITAExceptions umgesetzt)
// ITA_BASE_API int64_t StringToInt64(const std::string& s);

//! std::string nach uint64_t parsen (Parse-Fehler werden in ITAExceptions umgesetzt)
// uint64_t StringToUInt64(const std::string& s);

//! std::string nach float parsen (Parse-Fehler werden in ITAExceptions umgesetzt)
ITA_BASE_API float StringToFloat( const std::string& s );

//! std::string nach double parsen (Parse-Fehler werden in ITAExceptions umgesetzt)
ITA_BASE_API double StringToDouble( const std::string& s );

//! Alle folgenden Operationen arbeiten Case-Sensitive?

//! std::string nach int-Liste parsen (Parse-Fehler werden in ITAExceptions umgesetzt)
ITA_BASE_API std::vector<int> StringToIntVec( const std::string& s, std::string sSeparatorRegex = "\\s*,\\s*", bool bMatchCase = true );

//! std::string nach unsigned int-Liste parsen (Parse-Fehler werden in ITAExceptions umgesetzt)
ITA_BASE_API std::vector<unsigned int> StringToUIntVec( const std::string& s, std::string sSeparatorRegex = "\\s*,\\s*", bool bMatchCase = true );

//! std::string nach float-Liste parsen (Parse-Fehler werden in ITAExceptions umgesetzt)
ITA_BASE_API std::vector<float> StringToFloatVec( const std::string& s, std::string sSeparatorRegex = "\\s*,\\s*", bool bMatchCase = true );

//! std::string nach double-Liste parsen (Parse-Fehler werden in ITAExceptions umgesetzt)
ITA_BASE_API std::vector<double> StringToDoubleVec( const std::string& s );

//! std::string nach String-Liste parsen (Parse-Fehler werden in ITAExceptions umgesetzt)
ITA_BASE_API std::vector<std::string> StringToStringVec( const std::string& s, std::string sSeparatorRegex = "\\s*,\\s*", bool bMatchCase = true );

/* +-------------------------------------+
   |                                     |
   |   Weitere Zeichenkettenfunktionen   |
   |                                     |
   +-------------------------------------+ */

//! Einen String n-Mal aneinander hängen
ITA_BASE_API std::string nTimes( std::string s, unsigned int n );

//! Zeichenkette in Teile zerlegen die durch das angebenene Zeichen getrennt sind
ITA_BASE_API std::vector<std::string> splitString( const std::string& s, char cSeparator );

//! Zeichenkette in Teile zerlegen die durch die angebenene Zeichenkette getrennt sind
ITA_BASE_API std::vector<std::string> splitString( const std::string& s, const std::string& sSeparator );

//! Zeichenkette in Teile zerlegen die durch das angebenene Zeichen getrennt sind
ITA_BASE_API void regexSplitString( const std::string& src, std::vector<std::string>& dest, const std::string& regex, bool bMatchCase = true );


//! Entfernt alle Leerzeichen am Anfang und Ende einer Zeichenkette
ITA_BASE_API std::string stripSpaces( const std::string& s );

//! Verhältnis als dB-Angabe (Leistungs-/Energiepegel, 10*log10(...)) formattieren
ITA_BASE_API std::string ratio_to_db10_str( double r, std::string sSuffix = "" );

//! Verhältnis als dB-Angabe (Schalldruckpegel, 20*log10(...)) formattieren
ITA_BASE_API std::string ratio_to_db20_str( double r, std::string sSuffix = "" );

//! Einen Verstärkungsfaktor (reiner Faktor oder Dezibel) aus Zeichenkette lesen
/**
 * Ließt einen Verstärkungsfaktor aus der angegebenen Zeichenkette und
 * interpretiert ihn als reinen Faktor bzw. als Angabe in Dezibel,
 * sofern er mit dem Suffix dB endet. Der Faktor Null entspricht
 * der Zeichenkette "-inf db". Zurückgegeben wird der Wert als reiner Faktor.
 *
 * Im Fehlerfall wird eine ITAException ausgelöst.
 */
ITA_BASE_API double str_to_amp_ratio_db10( const std::string& s );
ITA_BASE_API double str_to_amp_ratio_db20( const std::string& s );

//! Zeit [s] in eine Zeichenkette konvertieren
// (Alias für altes convertTimeToHumanReadableString in HPT)
ITA_BASE_API std::string timeToString( const double dSeconds );

//! Substituiert das erste Makro der Form $(MAKRONAME) mit dem Makro-Wert und liefert das Ergebnis zurück
ITA_BASE_API std::string SubstituteMacro( const std::string& sInput, const std::string& sMacroName, const std::string& sMacroValue );

#endif // INCLUDE_WATCHER_ITA_STRING_UTILS
