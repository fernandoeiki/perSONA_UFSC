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

#ifndef INCLUDE_WATCHER_ITA_FUNCTORS
#define INCLUDE_WATCHER_ITA_FUNCTORS

#include <algorithm>
#include <functional>
#include <vector>

// Freigabe-Funktor für einzelne Instanzen
template<class T>
inline void deleteFunctor( T* pInstance )
{
	delete pInstance;
}

// Freigabe-Funktor für Arrays
template<class T>
inline void arrayDeleteFunctor( T* pArray )
{
	delete[] pArray;
}

// Freigabe-Functor für std:maps
template<class T1, class T2>
inline void mapDeleteFunctor( const std::pair<T1, T2>& elem )
{
	delete elem.second;
}

// --= Erweiterte for_each Funktionen =--

// o Container speichert Zeiger auf Instanzen der Klasse T
// o for_each ruft auf allen Instanzen eine Methode der Klasse T auf
/* Beispiel:

   class Auto() { void Hupe(); }

   std::vector<Auto*> cars;
   for_each(cars, &Auto::Hupe);
*/
template<class S, class T>
inline void for_each( std::vector<T*>& v, S ( T::*f )( ) )
{
	std::for_each( v.begin( ), v.end( ), std::mem_fun( f ) );
}

#endif // INCLUDE_WATCHER_ITA_FUNCTORS
