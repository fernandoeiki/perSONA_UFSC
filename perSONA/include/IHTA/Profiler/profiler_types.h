/**
 * \file profiler_types.h
 * \brief Required public types for the IHTA Profiler library.
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

#ifndef INCLUDE_WATCHER_IHTA_PROFILER_TYPES
#define INCLUDE_WATCHER_IHTA_PROFILER_TYPES

// std includes

// API includes
#include <IHTA_profiler_export.h>
#include <chrono>

namespace IHTA::Profiler
{
	///
	/// \brief Types of data that can be stored as a value.
	///
	enum class DataType
	{
		Bool = 0,
		Char,
		Int,
		UnsignedInt,
		UnsignedLongInt,
		Float,
		Double,

		TypesCount
	};

	///
	/// \brief Helper for determining the type
	/// \{
	///
	template<DataType dataType>
	struct StdType;

	template<class T>
	struct StdToDataType
	{
		const static DataType eDataType = DataType::TypesCount;
	};

#define DATATYPE_CONVERSION( DataTypeName, StdTypeName ) \
	template<>                                           \
	struct StdType<DataTypeName>                         \
	{                                                    \
		using value_type = StdTypeName;                  \
	};                                                   \
	template<>                                           \
	struct StdToDataType<StdTypeName>                    \
	{                                                    \
		const static DataType eDataType = DataTypeName;  \
	}

	DATATYPE_CONVERSION( DataType::Bool, bool );
	DATATYPE_CONVERSION( DataType::Char, char );
	DATATYPE_CONVERSION( DataType::Int, int );
	DATATYPE_CONVERSION( DataType::UnsignedInt, unsigned int );
	DATATYPE_CONVERSION( DataType::UnsignedLongInt, unsigned long int );
	DATATYPE_CONVERSION( DataType::Float, float );
	DATATYPE_CONVERSION( DataType::Double, double );

	template<>
	struct StdToDataType<std::size_t>
	{
		const static DataType eDataType = DataType::UnsignedInt;
	};
	///
	/// \}
	///

	///
	/// \brief Data type to store the information about a value.
	///
	class IHTAPROFILER_EXPORT ValueData
	{
	public:
		ValueData( ) = default;

		///
		/// \brief Get the value.
		/// \return a void shared_ptr to the value.
		///
		std::shared_ptr<void> GetValue( ) const { return m_pData; }

		///
		/// \brief Set the value.
		/// \tparam T type of the value.
		/// \param value the value to be set.
		///
		template<class T>
		void SetValue( const T& value )
		{
			using Type = typename ::std::remove_reference<typename ::std::remove_cv<T>::type>::type;

			m_pData     = std::static_pointer_cast<void>( std::make_shared<T>( value ) );
			m_eDataType = StdToDataType<Type>::eDataType;
		}

		///
		/// \brief Get the DataType of the value.
		/// \return the DataType of the value.
		///
		DataType GetType( ) const { return m_eDataType; }

		///
		/// \brief Get the time stamp of the value.
		/// \return the time stamp of the value.
		///
		[[nodiscard]] std::chrono::high_resolution_clock::time_point GetTimeStamp( ) const { return m_dTimeStamp; }

	private:
		///
		/// \brief Void shared_ptr to the data.
		///
		std::shared_ptr<void> m_pData;

		///
		/// \brief Data type of the value.
		///
		DataType m_eDataType = DataType::TypesCount;

		///
		/// \brief Time stamp of the value.
		///
		std::chrono::high_resolution_clock::time_point m_dTimeStamp = std::chrono::high_resolution_clock::now( );
	};
} // namespace IHTA::Profiler

#endif // INCLUDE_WATCHER_IHTA_PROFILER_TYPES