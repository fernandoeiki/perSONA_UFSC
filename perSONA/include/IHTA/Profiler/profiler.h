/**
 * \file profiler.h
 * \brief Main header file for the IHTA Profiler library.
 * \author Pascal Palenda ppa@akustik.rwth-aachen.de
 * \copyright
 * Copyright 2020-2022 Institute for Hearing Technology and Acoustics (IHTA) RWTH Aachen University
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#ifndef INCLUDE_WATCHER_IHTA_PROFILER
#define INCLUDE_WATCHER_IHTA_PROFILER

// std includes
#include <memory>
#include <string>
#include <valarray>
#include <vector>

// API includes
#include <IHTA/Profiler/profiler_types.h>
#include <IHTA_profiler_export.h>

///
/// \brief Helper functions for the profiler.
/// \{
///
#define IHTA_PROFILER_STRINGIFY( a )            #a
#define IHTA_PROFILER_STRINGIFICATION( a )      IHTA_PROFILER_STRINGIFY( a )
#define IHTA_PROFILER_TOKEN_JOIN( x, y )        x##y
#define IHTA_PROFILER_TOKEN_CONCATENATE( x, y ) IHTA_PROFILER_TOKEN_JOIN( x, y )
#define IHTA_PROFILER_UNIQUE_SECTION( x )       IHTA_PROFILER_TOKEN_CONCATENATE( unique_profiler_mark_name_, x )
///
/// \}
///

///
/// \brief Issue an event with the name \p NAME.
///
#define IHTA_PROFILER_EVENT_COUNT( NAME ) IHTA::Profiler::AddEventCount( NAME, __FUNCTION__, __FILE__ );

///
/// \brief Add the value \p VALUE to the profiler under the name \p NAME.
///
#define IHTA_PROFILER_VALUE( NAME, VALUE ) IHTA::Profiler::AddValue( NAME, VALUE, __FUNCTION__, __FILE__ );

///
/// \brief Start a section with the name \p NAME.
///
#define IHTA_PROFILER_SECTION( NAME )                                  \
	IHTA::Profiler::CSection IHTA_PROFILER_UNIQUE_SECTION( __LINE__ ); \
	IHTA::Profiler::StartSection( IHTA_PROFILER_UNIQUE_SECTION( __LINE__ ), NAME, __FUNCTION__, __FILE__ );

///
/// \brief Start a section with the name "Full".
///
#define IHTA_PROFILER_FUNCTION( ) IHTA_PROFILER_SECTION( "Full" );

///
/// \brief End the last opened section in this thread.
///
#define IHTA_PROFILER_END_SECTION( ) IHTA::Profiler::EndSection( );

///
/// \brief Name the current thread.
///
/// Only the first invocation of this has an effect.
///
#define IHTA_PROFILER_NAME_THREAD( NAME ) IHTA::Profiler::NameThread( NAME );

///
/// \brief Name the current thread "Main".
///
/// Only the first invocation of this has an effect.
///
#define IHTA_PROFILER_NAME_THREAD_MAIN( ) IHTA::Profiler::NameThread( "Main" );

///
/// \brief Namespace containing all classes and methods belonging to the IHTA Profiler library.
/// \remark There are some macros defined outside this namesace.
///
namespace IHTA::Profiler
{
	class ProfileSection;
	class CProfiler;

	///
	/// \brief Section object.
	///
	/// This class is used to time a section of code.
	/// It does not have to be ended manually, as the destruction of the object will register as the end of the section.
	/// However, the section can still be ended manually by calling ::EndSection().
	///
	class IHTAPROFILER_EXPORT CSection
	{
		friend CProfiler;
		friend ProfileSection;

		///
		/// \brief Start the timing for the section.
		///
		void Start( );

		///
		/// \brief End the timing for the section.
		///
		void End( );

		///
		/// \brief Returns true if the section was ended.
		///
		bool Finished( ) const;

		///
		/// \brief Start time of the section.
		///
		std::chrono::high_resolution_clock::time_point m_dBegin;

		///
		/// \brief End time of the section.
		///
		std::chrono::high_resolution_clock::time_point m_dEnd;

	public:
		CSection( ) = default;

		///
		/// \brief Destructor for CSection
		///
		/// This ends the section.
		///
		~CSection( );
	};

	///
	/// \brief Add the CSection \p oSection to the profiler and start the section.
	/// \param oSection the section object to add to the profiler.
	/// \param sName name of the section.
	/// \param sFunctionName name of the function that started the section.
	/// \param sFile name of the file in which the section was started.
	///
	void IHTAPROFILER_EXPORT StartSection( CSection& oSection, const std::string& sName, const std::string& sFunctionName, const std::string& sFile );

	///
	/// \brief End the last opened section in this thread.
	///
	void IHTAPROFILER_EXPORT EndSection( );

	///
	/// \brief End all currently open sections.
	///
	void IHTAPROFILER_EXPORT EndAllSections( );

	///
	/// \brief Add a EventCount to the profiler.
	/// \param sName name of the event.
	/// \param sFunctionName name of the function that issued the event.
	/// \param sFile name of the file in which the event was issued.
	///
	void IHTAPROFILER_EXPORT AddEventCount( const std::string& sName, const std::string& sFunctionName, const std::string& sFile );

	///
	/// \brief Add a value to the profiler.
	///
	/// The value must be of type: bool, char, int, float, double, string.
	/// \param sName name of the value.
	/// \param oValueData the untyped value data to be saved in the profiler.
	/// \param sFunctionName name of the function that issued the event.
	/// \param sFile name of the file in which the event was issued.
	///
	void IHTAPROFILER_EXPORT StoreValue( const std::string& sName, const ValueData& oValueData, const std::string& sFunctionName, const std::string& sFile );

	///
	/// \brief Add a value to the profiler.
	///
	/// The value must be of type: bool, char, int, float, double, string.
	/// \param sName name of the value.
	/// \param value the value to be saved in the profiler.
	/// \param sFunctionName name of the function that issued the event.
	/// \param sFile name of the file in which the event was issued.
	///
	template<class T>
	void AddValue( const std::string& sName, const T& value, const std::string& sFunctionName, const std::string& sFile )
	{
		ValueData valueData;
		valueData.SetValue( value );

		StoreValue( sName, valueData, sFunctionName, sFile );
	}

	///
	/// \brief Name the current thread.
	///
	/// Only the first invocation of this has an effect.
	///
	void IHTAPROFILER_EXPORT NameThread( const std::string& sName );

	///
	/// \brief Parse the profiler data as a json file.
	///
	std::stringstream IHTAPROFILER_EXPORT ProfilerToJson( );

} // namespace IHTA::Profiler

#endif // INCLUDE_WATCHER_IHTA_PROFILER