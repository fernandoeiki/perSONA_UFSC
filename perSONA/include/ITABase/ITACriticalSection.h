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

#ifndef INCLUDE_WATCHER_ITA_CRITICALSECTION
#define INCLUDE_WATCHER_ITA_CRITICALSECTION

#include <ITABaseDefinitions.h>
#include <ITAUncopyable.h>

// Vorwärtsdeklarationen
class ITACriticalSectionImpl;

/*
 * Die Klasse ITACriticalSection ist eine Wrapper-Klasse zu
 * Win32 CRITICAL_SECTIONs. Die Klasse übernimmt im Konstruktor/Destruktor
 * das Initialisieren/Freigeben des kritischen Bereiches. Sinn der
 * Klasse ist es, die Verwendung von kritischen Bereichen, durch
 * Initialisieren/Freigeben im Konstruktor/Destruktor, zu vereinfachen.
 *
 * \note Der Unterschied zur Klasse ITAMutex entspricht dem Unterschied
 *       Mutex vs. CRITICAL_SECTION. Kritische Bereiche können nur innerhalb
 *       eines Threads benutzt werden, Mutexe hingegen prozessübergreifend.
 *       Dafür sind CRITICAL_SECTIONs laut Microsoft etwas effizienter.
 */

class ITA_BASE_API ITACriticalSection : public ITAUncopyable
{
public:
	//! Standardkonstruktor
	ITACriticalSection( );

	//! Kopierkonstruktor
	ITACriticalSection( const ITACriticalSection& cs );

	//! Destruktor
	virtual ~ITACriticalSection( );

	//! Versucht in den kritischen Bereich einzutreten ohne zu blocken
	/**
	 * Ist ein Eintritt möglich, wird der Bereich betreten und der
	 * Besitz übernommen (lock).
	 *
	 * \return True, wenn eintritt möglich war, false sonst
	 */
	virtual bool tryenter( ) const;
	virtual void enter( ) const;
	virtual void leave( ) const;

	ITACriticalSection& operator=( const ITACriticalSection& rhs );

private:
	ITACriticalSectionImpl* m_pImpl;
};

//! Schicke Klasse um einen kritischen Bereich deklarativ zu betreten und zu verlassen
class ITA_BASE_API ITACriticalSectionLock
{
public:
	//! Konstruktor. Betritt den kritischen Bereich.
	inline ITACriticalSectionLock( const ITACriticalSection& cs ) : m_cs( cs ) { m_cs.enter( ); };

	//! Destruktor. Verlässt den kritischen Bereich.
	~ITACriticalSectionLock( ) { m_cs.leave( ); };

private:
	const ITACriticalSection& m_cs;

	ITACriticalSectionLock& operator=( ITACriticalSectionLock& );
};

#endif // INCLUDE_WATCHER_ITA_CRITICALSECTION
