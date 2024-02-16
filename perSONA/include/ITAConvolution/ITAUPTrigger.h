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

#ifndef INCLUDE_WATCHER_ITA_UP_TRIGGER
#define INCLUDE_WATCHER_ITA_UP_TRIGGER

#include <ITAConvolutionDefinitions.h>
#include <ITAUncopyable.h>

// Lightweight atomic trigger for synchronized filter exchanges
class ITAUPTrigger : public ITAUncopyable
{
public:
	inline ITAUPTrigger( ) : m_iState( 0 ) { };

	// Returns the current state
	inline int getState( ) const { return m_iState; };

	// Pull the trigger. Update/alter the state.
	void trigger( ) { ++m_iState; };

private:
	volatile int m_iState;
};

// Simple watcher class, realization update checks on a trigger
class ITAUPTriggerWatch
{
public:
	inline ITAUPTriggerWatch( ) : m_pTrigger( 0 ), bFirst( true ), m_iPrevTriggerState( 0 ) { };

	inline const ITAUPTrigger* GetWatchedTrigger( ) const { return m_pTrigger; };

	inline void SetWatchedTrigger( const ITAUPTrigger* pNewTrigger )
	{
		m_pTrigger = pNewTrigger;
		bFirst     = true;
	};

	// Logic: We always fire, if there is no trigger associated. This is needed in the convolver.
	inline bool Fire( )
	{
		if( !m_pTrigger )
			return true;

		int iNewTriggerState = m_pTrigger->getState( );
		if( ( iNewTriggerState != m_iPrevTriggerState ) || bFirst )
		{
			m_iPrevTriggerState = iNewTriggerState;
			bFirst              = false;
			return true;
		}

		return false;
	};

private:
	const ITAUPTrigger* m_pTrigger;
	bool bFirst;
	int m_iPrevTriggerState;
};

#endif // INCLUDE_WATCHER_ITA_UP_TRIGGER
