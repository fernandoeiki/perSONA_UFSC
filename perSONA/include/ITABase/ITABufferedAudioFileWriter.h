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

#ifndef INCLUDE_WATCHER_ITA_BUFFERED_AUDIO_FILE_WRITER
#define INCLUDE_WATCHER_ITA_BUFFERED_AUDIO_FILE_WRITER

#include <ITAAudiofileWriter.h>
#include <ITABaseDefinitions.h>

//! Audio file writer that first buffers samples and exports on demand or destruction
/**
 * Klasse welche Schreiber von Audiodateien um Pufferung erweitert.
 * Dies ist u.A. wichtig in der Echtzeit-Verarbeitung, wobei keine
 * OS-Dateizugriffe innerhalb eines Audio-Streaming-Kontextes auftreten
 * sollten. Die Klasse verwendet die normalen AudiofileWriter mittels
 * uses-Beziehung und schaltet ihm eine Pufferung der Samples voraus.
 * Jeder Aufruf einer write-Methode wird dann nicht mehr zu einem
 * Dateisystem-Zugriff führen. Alle Daten werden erst mit dem Aufruf
 * des Destruktors geschrieben. Die initiale Puffergröße kann festgelegt
 * werden. Wird diese Aufgebraucht, wird der Puffer automatisch um die
 * angegebene Wachstumsgröße erweitert.
 */
class ITA_BASE_API ITABufferedAudiofileWriter : public ITAAudiofileWriter
{
public:
	//! Factory method. Erzeugt einen gepufferten Schreiber.
	static ITABufferedAudiofileWriter* create( const ITAAudiofileProperties& props, double dInitialBufferSizeSeconds = 60, double dGrowBufferSizeSeconds = 20 );

	//! Returns current file path or empty string
	/**
	 * @return Current file path or empty string
	 *
	 */
	virtual std::string GetFilePath( ) const = 0;

	//! Sets the export file path (without any checks)
	/**
	 * @param[in] sFilePath File path (make sure base folder exists)
	 *
	 */
	virtual void SetFilePath( const std::string& sFilePath ) = 0;
};

#endif // INCLUDE_WATCHER_ITA_BUFFERED_AUDIO_FILE_WRITER
