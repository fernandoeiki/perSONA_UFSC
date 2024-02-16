#ifndef INCLUDE_WATCHER_IHTA_TRACKING_UTILS
#define INCLUDE_WATCHER_IHTA_TRACKING_UTILS

#include <IHTA/Tracking/tracking.h>

#define _USE_MATH_DEFINES
#include <math.h>

namespace IHTA::Tracking
{
	///
	/// \brief Convert a quaternion to euler angles
	///
	///	The rotation convention is ZYX; roll, pitch, yaw.
	///
	///	This implementation is form wikipedia (https://en.wikipedia.org/wiki/Conversion_between_quaternions_and_Euler_angles)
	/// \param q quaternion to convert.
	/// \return the euler angles for \p q (ZYX)
	///
	inline std::array<double, 3> ToEulerAngles( std::array<double, 4> q )
	{
		std::array<double, 3> angles { 0, 0, 0 };

		// roll (x-axis rotation)
		double sinr_cosp = 2 * ( q[3] * q[0] + q[1] * q[2] );
		double cosr_cosp = 1 - 2 * ( q[0] * q[0] + q[1] * q[1] );
		angles[0]        = std::atan2( sinr_cosp, cosr_cosp );

		// pitch (y-axis rotation)
		double sinp = 2 * ( q[3] * q[1] - q[2] * q[0] );
		if( std::abs( sinp ) >= 1 )
			angles[1] = std::copysign( M_PI / 2, sinp ); // use 90 degrees if out of range
		else
			angles[1] = std::asin( sinp );

		// yaw (z-axis rotation)
		double siny_cosp = 2 * ( q[3] * q[2] + q[0] * q[1] );
		double cosy_cosp = 1 - 2 * ( q[1] * q[1] + q[2] * q[2] );
		angles[2]        = std::atan2( siny_cosp, cosy_cosp );

		return angles;
	}
} // namespace IHTA::Tracking

///
/// \brief \p std::ostream overload for ITrackingInterface::STrackingDataPoint.
/// \param os \p std::ostream to write to
/// \param dataPoint ITrackingInterface::STrackingDataPoint to write to the \p std::ostream
/// \return \p std::ostream with the \p dataPoint written to.
///
inline std::ostream& operator<<( std::ostream& os, const IHTA::Tracking::ITrackingInterface::STrackingDataPoint& dataPoint )
{
	os << '{';

	os << "\"v\":" << ( dataPoint.bValid ? "1" : "0" ) << ',';
	os << "\"c\":[" << dataPoint.oLocation[0] << ',' << dataPoint.oLocation[1] << ',' << dataPoint.oLocation[2] << "],";

	auto euler = IHTA::Tracking::ToEulerAngles( dataPoint.oQuaternion );
	os << "\"e\":[" << euler[0] << ',' << euler[1] << ',' << euler[2] << "],";

	os << "\"q\":[" << dataPoint.oQuaternion[0] << ',' << dataPoint.oQuaternion[1] << ',' << dataPoint.oQuaternion[2] << ',' << dataPoint.oQuaternion[3] << "]";

	os << '}';
	return os;
}

#endif
