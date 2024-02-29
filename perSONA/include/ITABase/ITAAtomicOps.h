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

#ifndef INCLUDE_WATCHER_ITA_ATOMIC_OPS
#define INCLUDE_WATCHER_ITA_ATOMIC_OPS

#include <ITABaseDefinitions.h>

//! Atomare Leseoperationen
/**
 * Diese Funktionen realisieren atomare Leseoperationen.
 * Sie lesen den Wert eines Speicherinhaltes und stellen sicher,
 * das w�hrend des Lesens kein anderweitiger Schreibzugriff
 * auf diesen Speicherinhalt erfolgt.
 */

ITA_BASE_API int atomic_read_int( volatile const int* src );
ITA_BASE_API long atomic_read_long( volatile const long* src );
ITA_BASE_API float atomic_read_float( volatile const float* src );
// extern inline double atomic_read_double(volatile double* dest);
ITA_BASE_API void* atomic_read_ptr( volatile const void** src );

//! Atomare Schreiboperationen
/**
 * Diese Funktionen realisieren atomare Schreiboperationen.
 * Sie schreiben einen neuen Wert in den gegebenen Speicherinhalt
 * und stellen sicher, das w�hrend des Schreibens kein anderweitiger
 * Lesezugriff auf diesen Speicherinhalt erfolgt.
 */

ITA_BASE_API void atomic_write_int( volatile int* dest, int value );
ITA_BASE_API void atomic_write_long( volatile long* dest, long value );
ITA_BASE_API void atomic_write_float( volatile float* dest, float value );
// void atomic_write_double(volatile double* dest, double value);
ITA_BASE_API void atomic_write_ptr( volatile void** dest, void* value );

//! Atomares Inkrement und Dekrement (Rückgabe: Wert nach Operation)
ITA_BASE_API int atomic_inc_int( volatile int* dest );
ITA_BASE_API int atomic_dec_int( volatile int* dest );

//! Atomares compare-and-swap (CAS)
/**
 * Diese Funktionen realisieren eine der wichtigsten Grundoperationen
 * f�r non-blocking Algorithmen: Atomares Compare-and-swap (CAS).
 *
 * Alle geben 'true' zur�ck falls der Wert ausgetauscht wurde.
 * \todo Doku
 */
// bool atomic_CAS_Ptr(void** dest, void* expected_value, void* new_value);
ITA_BASE_API bool atomic_cas_int( volatile int* dest, int expected_value, int new_value );
ITA_BASE_API bool atomic_cas_long( volatile long* dest, long expected_value, long new_value );
// bool atomic_cas_float(volatile float* dest, float expected_value, float new_value);
// bool atomic_cas_double(volatile double* dest, double expected_value, double new_value);
ITA_BASE_API bool atomic_cas_ptr( volatile void** dest, void* expected_value, void* new_value );

// --= Ungetypte Operationen =--

// Atomares Lesen für 32-Bit (4 Bytes)
ITA_BASE_API void atomic_read32( volatile void* src, void* dest );

// Atomares Schreiben für 32-Bit (4 Bytes)
ITA_BASE_API void atomic_write32( volatile void* dest, void* new_value );

// Atomares Compare-And-Swap (CAS) für 32-Bit (4 Bytes) - Rückgabe: true falls ausgetauscht wurde
ITA_BASE_API bool atomic_cas32( volatile void* dest, void* expected_value, void* new_value );

#endif // INCLUDE_WATCHER_ITA_ATOMIC_OPS
