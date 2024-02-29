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

#ifndef INCLUDE_WATCHER_ITA_ATOMIC_PRIMITIVES
#define INCLUDE_WATCHER_ITA_ATOMIC_PRIMITIVES

#include <ITAAtomicOps.h>
#include <ITABaseDefinitions.h>
#include <ITATypes.h>
#include <assert.h>


class ITAAtomicInt
{
public:
	//! Standard-Konstruktor
	inline ITAAtomicInt( ) : m_iValue( 0 ) { };

	//! Initialisierungs-Konstruktor
	inline ITAAtomicInt( int iInitialValue ) : m_iValue( iInitialValue ) { };

	//! Getter
	inline int get( ) const { return atomic_read_int( (volatile const int*)&m_iValue ); };

	//! Setter
	inline void set( const int iValue ) { atomic_write_int( &m_iValue, iValue ); };

	//! Compare-and-swap (CAS)
	inline bool cas( int iExpectedValue, int iNewValue ) { return atomic_cas_int( &m_iValue, iExpectedValue, iNewValue ); };

	//! Assignment operator (required for assignments of the form 'ITAAtomicInt = ITAAtomicInt')
	inline ITAAtomicInt& operator=( const ITAAtomicInt& iNewValue )
	{
		set( iNewValue.get( ) );
		return *this;
	};

	//! Assignment operator (required for assignments of the form 'ITAAtomicInt = int')
	inline ITAAtomicInt& operator=( const int iNewValue )
	{
		set( iNewValue );
		return *this;
	};

	//! Cast to int operator (required for assignments of the form 'int = ITAAtomicInt')
	inline operator int( ) const { return get( ); }

	//! Increment
	inline ITAAtomicInt& operator++( )
	{
		atomic_inc_int( &m_iValue );
		return *this;
	};

	//! Decrement
	inline ITAAtomicInt& operator--( )
	{
		atomic_dec_int( &m_iValue );
		return *this;
	};

	// TODO: Mehr Operatoren nach Bedarf
	inline bool operator==( const ITAAtomicInt& rhs ) const { return ( get( ) == rhs.get( ) ); };
	inline bool operator!=( const ITAAtomicInt& rhs ) const { return ( get( ) != rhs.get( ) ); };

	inline bool operator==( const int& rhs ) const { return ( get( ) == rhs ); };
	inline bool operator!=( const int& rhs ) const { return ( get( ) != rhs ); };

private:
	volatile int m_iValue;
};

class ITAAtomicLong
{
public:
	//! Standard-Konstruktor
	inline ITAAtomicLong( ) : m_lValue( 0 ) { };

	//! Initialisierungs-Konstruktor
	inline ITAAtomicLong( long lInitialValue ) : m_lValue( lInitialValue ) { };

	//! Getter
	inline long get( ) const { return atomic_read_long( (volatile const long*)&m_lValue ); };

	//! Setter
	inline void set( const long lValue ) { atomic_write_long( (volatile long*)&m_lValue, lValue ); };

	//! Compare-and-swap (CAS)
	inline bool cas( long lExpectedValue, long lNewValue ) { return atomic_cas_long( (volatile long*)&m_lValue, lExpectedValue, lNewValue ); };

	//! Assignment operator (required for assignments of the form 'ITAAtomicLong = ITAAtomicLong')
	inline ITAAtomicLong& operator=( const ITAAtomicLong& lNewValue )
	{
		set( lNewValue.get( ) );
		return *this;
	};

	//! Assignment operator (required for assignments of the form 'ITAAtomicLong = long')
	inline ITAAtomicLong& operator=( const long lNewValue )
	{
		set( lNewValue );
		return *this;
	};

	//! Cast to long operator (required for assignments of the form 'long = ITAAtomicLong')
	inline operator long( ) const { return get( ); };

	// TODO: Mehr Operatoren nach Bedarf
	inline bool operator==( const ITAAtomicLong& rhs ) const { return ( get( ) == rhs.get( ) ); };
	inline bool operator!=( const ITAAtomicLong& rhs ) const { return ( get( ) != rhs.get( ) ); };

	inline bool operator==( const long& rhs ) const { return ( get( ) == rhs ); };
	inline bool operator!=( const long& rhs ) const { return ( get( ) != rhs ); };

	inline bool operator==( const int& rhs ) const { return ( get( ) == rhs ); };
	inline bool operator!=( const int& rhs ) const { return ( get( ) != rhs ); };

private:
	volatile long m_lValue;
};

class ITAAtomicBool
{
public:
	/*
	 *  Hinweis: Boolesche Typen werden hier mittels Integers umgesetzt
	 */

	//! Standard-Konstruktor
	inline ITAAtomicBool( ) : m_iState( false ) { };

	//! Initialisierungs-Konstruktor
	inline ITAAtomicBool( bool bInitialState ) : m_iState( bInitialState ) { };

	//! Getter
	inline bool get( ) const { return ( atomic_read_int( (volatile const int*)&m_iState ) != 0 ); };

	//! Setter
	inline void set( const bool bState ) { atomic_write_int( &m_iState, bState ); }

	//! Compare-and-swap (CAS)
	inline bool cas( bool bExpectedState, bool bNewState ) { return atomic_cas_int( &m_iState, bExpectedState, bNewState ); };

	//! Assignment operator (required for assignments of the form 'ITAAtomicBool = ITAAtomicBool')
	inline ITAAtomicBool& operator=( const ITAAtomicBool& bNewState )
	{
		set( bNewState.get( ) );
		return *this;
	};

	//! Assignment operator (required for assignments of the form 'ITAAtomicBool = bool')
	inline ITAAtomicBool& operator=( const bool bNewState )
	{
		set( bNewState );
		return *this;
	};

	//! Cast to int operator (required for assignments of the form 'bool = ITAAtomicBool')
	inline operator bool( ) const { return get( ); };

	// TODO: Mehr Operatoren nach Bedarf
	inline bool operator==( const ITAAtomicBool& rhs ) const { return ( get( ) == rhs.get( ) ); };
	inline bool operator!=( const ITAAtomicBool& rhs ) const { return ( get( ) != rhs.get( ) ); };

	inline bool operator==( const bool& rhs ) const { return ( get( ) == rhs ); };
	inline bool operator!=( const bool& rhs ) const { return ( get( ) != rhs ); };

private:
	volatile int m_iState;
};

class ITAAtomicFloat
{
public:
	//! Standard-Konstruktor
	inline ITAAtomicFloat( ) : m_fValue( 0 ) { };

	//! Initialisierungs-Konstruktor
	inline ITAAtomicFloat( float fInitialValue ) : m_fValue( fInitialValue ) { };

	//! Getter
	inline float get( ) const { return atomic_read_float( (volatile const float*)&m_fValue ); };

	//! Setter
	inline void set( const float fValue ) { atomic_write_float( &m_fValue, fValue ); };

	/* TODO:
	//! Compare-and-swap (CAS)
	inline bool cas(float fExpectedValue, float fNewValue) {
	    return atomic_cas_float(&m_fValue, fExpectedValue, fNewValue);
	};
	*/

	//! Assignment operator (required for assignments of the form 'ITAAtomicFloat = ITAAtomicFloat')
	inline ITAAtomicFloat& operator=( const ITAAtomicFloat& fNewValue )
	{
		set( fNewValue.get( ) );
		return *this;
	};

	//! Assignment operator (required for assignments of the form 'ITAAtomicFloat = float')
	inline ITAAtomicFloat& operator=( const float fNewValue )
	{
		set( fNewValue );
		return *this;
	};

	//! Cast to float operator (required for assignments of the form 'float = ITAAtomicFloat')
	inline operator float( ) const { return get( ); };

	//! Compare operator (ITAAtomicFloat == ITAAtomicFloat)
	inline bool operator==( const ITAAtomicFloat& rhs ) const { return ( get( ) == rhs.get( ) ); };

	//! Complementary compare operator (ITAAtomicFloat != ITAAtomicFloat)
	inline bool operator!=( const ITAAtomicFloat& rhs ) const { return ( get( ) != rhs.get( ) ); };

	//! Compare operator (ITAAtomicFloat == float)
	inline bool operator==( const float& rhs ) const { return ( get( ) == rhs ); }

	//! Complementary compare operator (ITAAtomicFloat != float)
	inline bool operator!=( const float& rhs ) const { return ( get( ) != rhs ); };

	//! Add and Assign operator (ITAAtomicFloat += ITAAtomicFloat)
	inline ITAAtomicFloat& operator+=( const ITAAtomicFloat& rhs )
	{
		set( get( ) + rhs.get( ) );
		return *this;
	};

	//! Add and Assign operator (ITAAtomicFloat += float)
	inline ITAAtomicFloat& operator+=( const float& rhs )
	{
		set( get( ) + rhs );
		return *this;
	};

	//! Subtract and Assign operator (ITAAtomicFloat -= ITAAtomicFloat)
	inline ITAAtomicFloat& operator-=( const ITAAtomicFloat& rhs )
	{
		set( get( ) - rhs.get( ) );
		return *this;
	};

	//! Subtract and Assign operator (ITAAtomicFloat -= float)
	inline ITAAtomicFloat& operator-=( const float& rhs )
	{
		set( get( ) - rhs );
		return *this;
	};

	//! Devide and Assign operator (ITAAtomicFloat /= ITAAtomicFloat)
	inline ITAAtomicFloat& operator/=( const ITAAtomicFloat& rhs )
	{
		assert( rhs.get( ) != 0.0f ); // Give hint on devision-by-zero in debug mode
		set( get( ) / rhs.get( ) );
		return *this;
	};

	//! Devide and Assign operator (ITAAtomicFloat /= float)
	inline ITAAtomicFloat& operator/=( const float& rhs )
	{
		assert( rhs != 0.0f ); // Give hint on devision-by-zero in debug mode
		set( get( ) / rhs );
		return *this;
	};

private:
	volatile float m_fValue;
};

template<class T>
class ITAAtomicPtr
{
public:
	//! Standard-Konstruktor
	inline ITAAtomicPtr( ) : m_pPtr( NULL ) { };

	//! Initialisierungs-Konstruktor
	inline ITAAtomicPtr( T* pInitialPtr ) : m_pPtr( pInitialPtr ) { };

	//! Getter
	inline T* get( ) const { return (T*)atomic_read_ptr( (volatile const void**)&m_pPtr ); };

	//! Setter
	inline void set( const T* pPtr ) { atomic_write_ptr( &m_pPtr, (void*)pPtr ); };

	//! Compare-and-swap (CAS)
	inline bool compareAndSwap( T* iExpectedPtr, T* iNewPtr ) { return atomic_cas_ptr( &m_pPtr, iExpectedPtr, iNewPtr ); };

	inline //! Assignment operator (required for assignments of the form 'ITAAtomicPtr = ITAAtomicPtr')
	    ITAAtomicPtr&
	    operator=( const ITAAtomicPtr& pNewPtr )
	{
		set( pNewPtr.get( ) );
		return *this;
	};

	//! Assignment operator (required for assignments of the form 'ITAAtomicPtr = int')
	inline ITAAtomicPtr& operator=( const T* pNewPtr )
	{
		set( pNewPtr );
		return *this;
	};

	//! Cast to int operator (required for assignments of the form 'int = ITAAtomicPtr')
	inline operator T*( ) const { return get( ); };

	// TODO: Mehr Operatoren nach Bedarf
	inline bool operator==( const ITAAtomicPtr& rhs ) const { return ( get( ) == rhs.get( ) ); };
	inline bool operator!=( const ITAAtomicPtr& rhs ) const { return ( get( ) != rhs.get( ) ); };

	inline bool operator==( const void*& rhs ) const { return ( get( ) == rhs ); };
	inline bool operator!=( const void*& rhs ) const { return ( get( ) != rhs ); };

	inline const T& operator*( ) const { return *get( ); };
	inline T& operator*( ) { return *get( ); };
	inline const T* operator->( ) const { return get( ); };
	inline T* operator->( ) { return get( ); };

private:
	volatile void* m_pPtr;
};


#endif // INCLUDE_WATCHER_ITA_ATOMIC_PRIMITIVES
