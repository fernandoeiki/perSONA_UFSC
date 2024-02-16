/**
 * \file tracking.h
 * \brief Main header file for the IHTA Tracking library.
 * \author Pascal Palenda ppa@akustik.rwth-aachen.de
 * \copyright
 * Copyright 2021-2022 Institute for Hearing Technology and Acoustics (IHTA) RWTH Aachen University
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

#ifndef INCLUDE_WATCHER_IHTA_TRACKING
#define INCLUDE_WATCHER_IHTA_TRACKING

#include <IHTA_tracking_export.h>
#include <array>
#include <functional>
#include <iostream>

///
/// \brief Namespace containing all classes and methods belonging to the IHTA Tracking library.
///
namespace IHTA::Tracking
{
	///
	/// \brief Abstract base interface for all tracking implementations.
	///
	/// The CTrackingFactory returns specialized instances of this interface for different tracking back-ends.
	/// This instance can then be used to get the tracking data via a callback function.
	///
	class IHTATRACKING_EXPORT ITrackingInterface
	{
	public:
		///
		/// \brief Data structure representing a tracking sample point for one rigid body.
		/// \todo Define the coordinate system for the location.
		///
		struct STrackingDataPoint
		{
			bool bValid = false;
			std::array<double, 3> oLocation { 0., 0., 0. };       // Location in cartesian coordinates; unit: 1m
			std::array<double, 4> oQuaternion { 0., 0., 0., 0. }; // Quaternion as {x, y, z, w}
		};

		///
		/// \brief Destructor for ITrackingInterface.
		///
		virtual ~ITrackingInterface( );

		///
		/// \brief Initialize the tracking backend.
		///
		/// This method initializes the tracking backend, so that it can be used.
		/// \remark Currently, this method assumes, that the tracking backend uses UDP/TCP communication.
		/// \remark sLocalAddress is needed for Optitrack's NatNet SDK.
		/// \param sLocalAddress The IP address of the system, this tracking interface is running.
		/// \param sServerAddress The IP address of the system that streams the tracking data.
		/// \param port Optional port for a command interface from this system to the streaming system.
		/// \return true, if initialization was successful.
		///
		virtual bool Initialize( const std::string& sLocalAddress, const std::string& sServerAddress, int port = -1 ) = 0;

		///
		/// \brief Register the callback function to the tracking interface.
		///
		/// The callback function is called on a separate thread every time, a new tracking data packet is received.
		/// The callback function should accept a (const ref) vector containing STrackingDataPoint%s.
		///
		/// \todo Switch the vector to a map to solve issue #1.
		/// \param callback Function or callable object, accepting a (const ref) vector containing STrackingDataPoint%s.
		/// \return true, if callback registration was successful.
		///
		virtual bool RegisterCallback( std::function<void( const std::vector<STrackingDataPoint>& oDataPoints )> callback ) = 0;
	};

	///
	/// \brief Factory for generating a tracking interface using a specific backend.
	///
	class IHTATRACKING_EXPORT CTrackingFactory
	{
	public:
		///
		/// \brief Enum with all available tracking backend types.
		///
		enum class Types
		{
			Optitrack,
			ART
		};

		///
		/// \brief Create a tracking interface with a specific backend
		/// \param type #CTrackingFactory::Types specifying the tracking backend.
		/// \return a unique tracking interface pointer with the specified tracking backend implementation.
		///
		static std::unique_ptr<ITrackingInterface> CreateTrackingClass( Types type );
	};
} // namespace IHTA::Tracking

#endif