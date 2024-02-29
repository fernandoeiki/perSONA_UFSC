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

#ifndef IW_ITA_BASE_SPLINE
#define IW_ITA_BASE_SPLINE

#include <ITABase/Math/PiecewisePolynomial.h>
#include <ITABaseDefinitions.h>
#include <vector>

namespace ITABase
{
	namespace Math
	{
		//! Uses cubic splines to create a piecewise polynomial (order 3) for the given supporting and data points. The supporting points need to be sorted in ascending
		//! order.
		ITA_BASE_API CPiecewisePolynomial CubicSpline( const std::vector<double>& vdSupportingPoints, const std::vector<double>& vdDataPoints );

		// All other permutations of data types

		//! Uses cubic splines to create a piecewise polynomial (order 3) for the given supporting and data points. The supporting points need to be sorted in ascending
		//! order. BEWARE of the internal conversion to from float double!
		ITA_BASE_API CPiecewisePolynomial CubicSpline( const std::vector<float>& vfSupportingPoints, const std::vector<float>& vfDataPoints );
		//! Uses cubic splines to create a piecewise polynomial (order 3) for the given supporting and data points. The supporting points need to be sorted in ascending
		//! order. BEWARE of the internal conversion to from float double!
		ITA_BASE_API CPiecewisePolynomial CubicSpline( const std::vector<float>& vfSupportingPoints, const std::vector<double>& vdDataPoints );
		//! Uses cubic splines to create a piecewise polynomial (order 3) for the given supporting and data points. The supporting points need to be sorted in ascending
		//! order. BEWARE of the internal conversion to from float double!
		ITA_BASE_API CPiecewisePolynomial CubicSpline( const std::vector<double>& vdSupportingPoints, const std::vector<float>& vfDataPoints );

		//! Uses cubic splines to interpolate the function defined by the given supporting and data points to a vector of evaluation points
		ITA_BASE_API std::vector<double> CubicSpline( const std::vector<double>& vdSupportingPoints, const std::vector<double>& vdDataPoints,
		                                              const std::vector<double>& vdEvalPoints );
		//! Uses cubic splines to interpolate the function defined by the given supporting and data points to a vector of evaluation points. BEWARE of the internal
		//! conversion to from float double!
		ITA_BASE_API std::vector<double> CubicSpline( const std::vector<float>& vfSupportingPoints, const std::vector<float>& vfDataPoints,
		                                              const std::vector<float>& vfEvalPoints );

		//! Uses cubic splines to interpolate the function defined by the given supporting and data points to a single evaluation points
		ITA_BASE_API double CubicSpline( const std::vector<double>& vdSupportingPoints, const std::vector<double>& vdDataPoints, double dEvalPoint );
		//! Uses cubic splines to interpolate the function defined by the given supporting and data points to a single evaluation points. BEWARE of the internal
		//! conversion to from float double!
		ITA_BASE_API float CubicSpline( const std::vector<float>& vfSupportingPoints, const std::vector<float>& vfDataPoints, float dEvalPoint );

	} // namespace Math
} // namespace ITABase

#endif // IW_ITA_BASE_SPLINE
