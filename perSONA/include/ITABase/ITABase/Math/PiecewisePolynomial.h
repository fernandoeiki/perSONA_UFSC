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

#ifndef IW_ITA_BASE_PIECEWISEPOLYNOMIAL
#define IW_ITA_BASE_PIECEWISEPOLYNOMIAL

#include <ITABaseDefinitions.h>
#include <vector>

namespace ITABase
{
	namespace Math
	{
		//! This class represents a piecewise polynomial of order M
		/**
		 * A piecewise polynomial persists of a series of N break points which from N-1 intervals. For each interval, there is a polynom of order M represented by M+1
		 * coefficients. See "Piecewise Polynomials and Splines" by University of Lundt for more information:
		 * https://www.google.com/url?sa=t&rct=j&q=&esrc=s&source=web&cd=&cad=rja&uact=8&ved=2ahUKEwjcofWO_IrqAhUux4sKHT52AigQFjABegQIBRAB&url=http%3A%2F%2Fwww.maths.lth.se%2Fna%2Fcourses%2FFMN050%2Fmedia%2Fmaterial%2Fpart8.pdf&usg=AOvVaw068JsSpsLz4z2yUAK9Vkd0
		 *
		 * This class is inspired by the piecewise polynomials of MATLAB:
		 * The coefficients are arranged in groups for each interval (piece) starting the coefficient of highest order. Example:
		 * Coefficients [a0, b0, c0, d0, a1, b1, c1, d1] belong to interval 0 [x0, x1] and interval 1 [x1, x2] respectively.
		 * The coefficients for interval 1 represent the following polynomial of order 3:
		 * f(x) = a1(x−x1)^3 + b1(x−x1)^2 + c1(x−x1) + d1
		 *
		 * All data is internally computed as values of type double. Nevertheless there are overloaded functions for input of type float. These are converted internally.
		 */
		class ITA_BASE_API CPiecewisePolynomial
		{
		public:
			//! Main constructor using double vectors of break points and coefficients for the intervals between breakpoints to define a piecewise polynomial
			CPiecewisePolynomial( const std::vector<double>& vdBreakPoints, const std::vector<double>& vdCoeffs, const int iOrder );
			//! Constructor using float vectors, which are internally converted to double vectors
			CPiecewisePolynomial( const std::vector<float>& vdBreakPoints, const std::vector<float>& vdCoeffs, const int iOrder );
			//! Returns the polynomial order
			inline int Order( ) const { return iOrder; };
			//! Returns the number of intervals (pieces) between break points
			inline int NumIntervals( ) const { return int( vdBreakPoints.size( ) - 1 ); };
			//! Returns the number of coefficients for a single polynomial
			inline int NumCoefficients( ) const { return Order( ) + 1; };
			//! Returns the break points defining the intervals for the polynomials
			inline const std::vector<double>& BreakPoints( ) const { return vdBreakPoints; };
			//! Returns the Coefficients of that Polynom. Sorted according to ascending intervals [a0, b0, c0, d0, a1, b1, c1, d1]
			inline const std::vector<double>& Coefficients( ) const { return vdCoefficients; };

			//! Evaluates the piecewise polynomial at a given x value. If desired, xValues from outsite the breakpoints can be extrapolated linearly.
			double Evaluate( const double& xValue, bool bExtrapolate = false ) const;

			//! Evaluates the piecewise polynomial at all given x values. If desired, xValues from outsite the breakpoints can be extrapolated linearly.
			std::vector<double> Evaluate( const std::vector<double>& vdXValues, bool bExtrapolate = false ) const;
			//! Evaluates the piecewise polynomial at all given x values. If desired, xValues from outsite the breakpoints can be extrapolated linearly.
			std::vector<double> Evaluate( const std::vector<float>& vfXValues, bool bExtrapolate = false ) const;


			//! Finds the index of Interval at a given x value. If extrapolation is desired, it will return -1 for xValue outsite the breakpoints
			int IntervalIndex( const double xValue, bool bExtrapolate = false ) const;
			//! Finds the index of Interval at a given x value. If extrapolation is desired, it will return -1 for xValue outsite the breakpoints
			int IntervalIndex( const float xValue, bool bExtrapolate = false ) const;

			//! Return a piecewise polynomial containing the derivations of the polynomials of this one
			CPiecewisePolynomial Derivation( ) const;

		private:
			//! Returns the iterator to the first coefficient of the interval with given index
			/**
			 * The iterator ending this set of coefficients is then:
			 * std::vector<float>::const_iterator itEnd = itStart + NumCoefficients();
			 */
			std::vector<double>::const_iterator CoefficientsOfInterval( const int idxInterval ) const;

		private:
			//! Order of polynomials
			int iOrder;
			//! Vector with break points. Defines the interval for each polynomial.
			std::vector<double> vdBreakPoints;
			//! Vector with all coefficients. Represents a 2D matrix: First dimension = number of intervals (pieces), second dimension = number of coefficients (order+1).
			/**
			 * The Coefficients are arranged in groups for each interval (piece) starting the coefficient of highest order. Example:
			 * coefficients [a1, b1, c1, d1, a2, b2, c2, d2] belong to interval 1 [x1, x2] and interval2 [x2, x3] respectively.
			 * The coefficients for interval 1 represent the following polynomial:
			 * f(x) = a1(x−x1)^3 + b1(x−x1)^2 + c1(x−x1) + d1
			 */
			std::vector<double> vdCoefficients;
		};
	} // namespace Math
} // namespace ITABase

#endif // IW_ITA_BASE_PIECEWISEPOLYNOMIAL
