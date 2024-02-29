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

#ifndef IW_ITA_BASE_LINEAR_ALGEBRA
#define IW_ITA_BASE_LINEAR_ALGEBRA

#include <ITABaseDefinitions.h>
#include <vector>

namespace ITABase
{
	namespace Math
	{
		//! Solves a Tridiagonal n x n Bandmatrix Problem with Thomas algorithm. Expects the 3 diagonals (lower,middle and upper) and the excitation vector.
		/**
		 * Problems following the structure: e = M * x will be solved with this function.
		 * with M is a Matrix with only the 3 main diagonals nonequal zero, e the known excitation vector and x the vector of unknown variables.
		 * Since the matrix dimension is n x n the excitatio, the middle and the returned vector are n elements big. Therefore the lower and the upper diagonale needs to
		 * have a length of n-1.
		 */
		ITA_BASE_API std::vector<double> BandmatrixSolver( const std::vector<double>& vdLower, const std::vector<double>& vdMiddle, const std::vector<double>& vdUpper,
		                                                   const std::vector<double>& vdExcitation );
	} // namespace Math
} // namespace ITABase

#endif // IW_ITA_BASE_LINEAR_ALGEBRA
