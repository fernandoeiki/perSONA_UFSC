/*
 * ----------------------------------------------------------------
 *
 *		ITA geometrical acoustics
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

#ifndef INCLUDE_WATCHER_ITA_GEO_BASE
#define INCLUDE_WATCHER_ITA_GEO_BASE

// ITAGeo includes
#include <ITAGeo/Definitions.h>
#include <ITAGeo/Directivity/Base.h>
#include <ITAGeo/Directivity/Manager.h>
#include <ITAGeo/Material/Manager.h>
#include <ITAGeo/Material/Material.h>
#include <ITAGeo/ResourceManager.h>

// ITABase includes
#include <ITAException.h>

// Vista includes
#include <VistaBase/VistaQuaternion.h>
#include <VistaBase/VistaVector3D.h>
#pragma warning( disable : 4100 )
#include <VistaMath/VistaGeometries.h>
#pragma warning( default : 4100 )

// STL includes
#include <complex>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

namespace ITAGeo
{
	//! Culling switches
	enum ECulling
	{
		NONE      = -1, //!< Never consideres face normal
		BACKFACE  = 0,  //!< Skips / culls when direction faces backside of a polygon / face
		FRONTFACE = 1,  //!< Skips / culls when direction faces frontside of a polygon / face
	};

	enum EIntersecting
	{
		NOINTERSECTION = -1, //!< Line segment doesn't intersect
		ATSTART        = 0,  //!< Intersection at the start point of line segment
		ATEND          = 1,  //!< Intersection at the end point of line segment
		BETWEEN        = 2   //!< Intersection between the start and the end of line segment
	};

	enum ECoordinateSystemConvention
	{
		UNDEFINED = -1,
		OPENGL    = 0,
		ISO       = 1,
	};


	//! A boundary/interaction point in a geometrical acoustics context
	/*
	 * A geometrical propagation anchor defines a point in 3D space where acoustic interaction appears,
	 * like a surface with a specular or diffuse reflection, a point on an edge where diffraction occurs
	 * or simply an acoustic actuator (sound source) or sensor (microphone).
	 *
	 */
	class ITA_GEO_API CPropagationAnchor
	{
	public:
		enum EAnchorType
		{
			INVALID        = -1,               //!< Invalid anchor
			GENERIC_ANCHOR = 0,                //!< Propagation anchor without specified type
			ACOUSTIC_EMITTER,                  //!< Sound-emitting anchor (acoustic source, vibrating plane)
			ACOUSTIC_SENSOR,                   //!< Sound-sensing anchor (microphone, sensivitive area, listener, portal)
			SPECULAR_REFLECTION,               //!< Specular reflection occurrance point (on boundary surface)
			ITA_DIFFUSE_REFLECTION,            //!< Diffuse reflection occurrance point (on plane or virtual)
			TRANSMISSION_APEX,                 //!< Transmission occurrance point (e.g. through a solid wall)
			DIFFRACTION_OUTER_APEX,            //!< Diffraction occurrance point (at a boundary outer edge, e.g. house corner)
			DIFFRACTION_INNER_APEX,            //!< Diffraction occurrance point (at a boundary outer edge, e.g. room corner)
			MIRROR_IMAGE,                      //!< (Virtual) Mirror image in medium
			DETECTION_POINT,                   //!< Point of detection within detection volume (e.g. sphere) of receiver used in ray tracing
			INHOMOGENEITY,                     //!<  Point in inhomogeneous medium where refraction occurs. Used for curved sound paths in inhomogeneous media.
			INHOMOGENEITY_EMITTER,             //!< Source in inhomogeneous medium
			INHOMOGENEITY_SENSOR,              //!< Receiver in inhomogeneous medium
			INHOMOGENEITY_SPECULAR_REFLECTION, //!< Specular reflection occurrance point on boundary surface next to inhomogeneous medium

			LAST_ELEMENT //!< Last element of EAnchorType to iterate over EAnchorType
		} iAnchorType;   //! Type of anchor

		VistaVector3D v3InteractionPoint; //!< Point of geometric interaction, has to be further defined by deriving class

		CPropagationAnchor( );
		CPropagationAnchor( const VistaVector3D& v3Pos );
		virtual ~CPropagationAnchor( );

		//! Returns given anchor type as a string
		/**
		 * @param[in] iType Anchor type
		 */
		static std::string GetAnchorTypeStr( CPropagationAnchor::EAnchorType iType );
		static EAnchorType ParseAnchorType( const std::string& sTypeStr );
		inline std::string GetAnchorTypeStr( ) const { return GetAnchorTypeStr( iAnchorType ); }

		//! Returns type string of the class
		static std::string GetTypeStr( );

		//! Output stream operator for console formatting etc.
		friend std::ostream& operator<<( std::ostream&, const CPropagationAnchor& );

		//! Returns a string with the properties of the object
		virtual std::string ToString( ) const;
	};

	//! A sound source propagation anchor
	class ITA_GEO_API CEmitter : public CPropagationAnchor
	{
	public:
		std::string sName;       //!< Versatile source name (for debugging)
		VistaVector3D& vPos;     //!< Position point / geometric interaction point
		VistaQuaternion qOrient; //!< Orientation of object (if applicable)
		std::shared_ptr<Directivity::IDirectivity> pDirectivity;

		CEmitter( VistaVector3D vPos_ );
		CEmitter( const CEmitter& oSrc );
		CEmitter( );

		const CEmitter& operator=( const CEmitter& oOther );

		//! Returns number of channels from the directivity or "1" if no directivity has been assigned
		int GetNumChannels( ) const;

		//! Returns a string with the properties of the object
		virtual std::string ToString( ) const;
	};

	//! A sensor / sound receiver / listener
	class ITA_GEO_API CSensor : public CPropagationAnchor
	{
	public:
		std::string sName;   //! Versatile receiver name (for debugging)
		VistaVector3D& vPos; //!< Position point / geometric interaction point
		VistaQuaternion qOrient;
		std::shared_ptr<Directivity::IDirectivity> pDirectivity;

		CSensor( );
		CSensor( VistaVector3D vPos_ );

		const CSensor& operator=( const CSensor& oOther );

		//! Returns a string with the properties of the object
		virtual std::string ToString( ) const;

		int GetNumChannels( ) const;
	};

	//! Edge diffraction order with respect to source and listener
	enum DiffractionOrder
	{
		DIFFRACTION_ORDER_INF = -1, //!< Unkown /  infinit order, e.g. probably not reached
		DIFFRACTION_ORDER_0   = 0,  //!< Entity in same halfspace of halfedge, not a valid diffraction order
		DIFFRACTION_ORDER_1,        //!< Entities connected by first order diffraction path
		DIFFRACTION_ORDER_2,        //!< ... by second order ..
		DIFFRACTION_ORDER_3,        //!< ... and so on ...
		DIFFRACTION_ORDER_4,
		DIFFRACTION_ORDER_5,
	};

	//! Specular reflection order on a plane
	enum ReflectionOrder
	{
		SPECULAR_REFLECTION_ORDER_0 = 0, //!< Entity in same halfspace
		SPECULAR_REFLECTION_ORDER_1,     //!< Entities connected by first order specular reflection
		SPECULAR_REFLECTION_ORDER_2,     //! ... by second order ... and so on.
	};


	//! Specular reflection / diffraction order on a plane
	enum Order
	{
		ORDER_0 = 0, //!< Zero's or non-order (usually only direct paths recognized)
		ORDER_1,     //!< First order interaction, i.e one reflection or one diffraction
		ORDER_2,     //!< Second order interaction, i.e. one reflection and one diffraction
		ORDER_3,     //!< ...
		ORDER_4,     //!< ...
		ORDER_5,     //!< ...
		ORDER_6,     //!< ...
		ORDER_7,     //!< ...
		ORDER_8,     //!< ...
	};

	//! Mirror image
	/**
	 * @note Do not mix a mirror image (virtual point in medium) with a specular reflection (point on a boundary)
	 */
	class ITA_GEO_API CMirrorImage : public CPropagationAnchor
	{
	public:
		VistaVector3D v3MirrorNormal;          //!< If normal is zero vector, image is invalid / was not reflected
		const VistaVector3D& v3MirrorPosition; //!< Mirror image position (alias for interaction point)
		int iPolygonIndex;                     //!< Polygon index helper (for recursive audibility test)
		int iOrder;
		void* pUserData; //!< User data pointer (for future use)

		CMirrorImage( );
		explicit CMirrorImage( const CPropagationAnchor& oAnchor );
		inline virtual ~CMirrorImage( ) { };

		//! Copy data from another anchor (has to be overwritten by derived classes!)
		virtual void CopyFromAnchor( std::shared_ptr<const ITAGeo::CPropagationAnchor> pOther );

		//! Returns a string with the properties of the object
		virtual std::string ToString( ) const;

	private:
		inline const CMirrorImage operator=( const CMirrorImage& ) { ITA_EXCEPT1( INVALID_PARAMETER, "Copying not allowed" ); };
	};

	//! Geometrical propagation anchor with parameters of a specular reflection point
	/**
	 * A specular reflection point
	 */
	class ITA_GEO_API CSpecularReflection : public CPropagationAnchor
	{
	public:
		CSpecularReflection( );
		CSpecularReflection( const VistaVector3D& v3SpecularReflectionPoint );
		inline virtual ~CSpecularReflection( ) { };

		//! Returns a string with the properties of the object
		virtual std::string ToString( ) const;

		VistaVector3D v3FaceNormal; //!< Face normal of reflection plane
		int iPolygonID;             //!< Identifier of polygon in mesh

		std::shared_ptr<Material::IMaterial> pMaterial; //!< Acoustic material connection, i.e. absorption coefficient
	};

	//! Geometrical propagation anchor of the detection point inside the receiver's detection volume
	/**
	 * A detection point (used for sphere receivers in ray tracing algorithms)
	 */
	class ITA_GEO_API CDetectionPoint : public CPropagationAnchor // public CPropagationAnchor
	{
	public:
		CDetectionPoint( );
		CDetectionPoint( const VistaVector3D& v3DetectionPoint );
		inline virtual ~CDetectionPoint( ) { };

		//! Returns a string with the properties of the object
		virtual std::string ToString( ) const;
	};


	//! Extension of geometrical propagation anchor for inhomogeneous medium adding a wavefront normal and timestamp
	class ITA_GEO_API CInhomogeneousAnchorExtension
	{
	public:
		CInhomogeneousAnchorExtension( );
		CInhomogeneousAnchorExtension( const VistaVector3D& v3Normal, const double& dTimeStamp );
		inline virtual ~CInhomogeneousAnchorExtension( ) { };

		//! Returns a string with the properties of the object
		std::string ToString( ) const;

		VistaVector3D v3WavefrontNormal;
		double dTimeStamp;
	};

	//! Geometrical propagation anchor of a point of refraction in an inhomogeneous medium at a certain time
	class ITA_GEO_API CInhomogeneity
	    : public CPropagationAnchor
	    , public CInhomogeneousAnchorExtension
	{
	public:
		CInhomogeneity( );
		CInhomogeneity( const VistaVector3D& v3Pos, const VistaVector3D& v3Normal, const double& dTimeStamp );
		inline virtual ~CInhomogeneity( ) { };

		//! Returns a string with the properties of the object
		virtual std::string ToString( ) const;
	};

	//! A sound source in an inhomogeneous medium
	class ITA_GEO_API CEmitterInhomogeneous
	    : public CEmitter
	    , public CInhomogeneousAnchorExtension
	{
	public:
		CEmitterInhomogeneous( );
		CEmitterInhomogeneous( const VistaVector3D& v3Pos, const VistaVector3D& v3Normal );
		inline virtual ~CEmitterInhomogeneous( ) { };

		//! Returns a string with the properties of the object
		virtual std::string ToString( ) const;
	};

	//! A sound receiver in an inhomogeneous medium
	class ITA_GEO_API CSensorInhomogeneous
	    : public CSensor
	    , public CInhomogeneousAnchorExtension
	{
	public:
		CSensorInhomogeneous( );
		CSensorInhomogeneous( const VistaVector3D& v3Pos, const VistaVector3D& v3Normal, const double& dTimeStamp, const double& spreadingLoss = -1 );
		inline virtual ~CSensorInhomogeneous( ) { };

		//! Returns a string with the properties of the object
		virtual std::string ToString( ) const;

		bool bEigenray;
		bool bReceiverHit;
		double dSpreadingLoss;
	};

	//! Geometrical propagation anchor of a point of refraction in an inhomogeneous medium at a certain time
	class ITA_GEO_API CSpecularReflectionInhomogeneous
	    : public CSpecularReflection
	    , public CInhomogeneousAnchorExtension
	{
	public:
		CSpecularReflectionInhomogeneous( );
		CSpecularReflectionInhomogeneous( const VistaVector3D& v3Pos, const VistaVector3D& v3Normal, const double& dTimeStamp );
		inline virtual ~CSpecularReflectionInhomogeneous( ) { };

		//! Returns a string with the properties of the object
		virtual std::string ToString( ) const;
	};


	//! Propagation path list class
	/**
	 * Container to hold a list of propagation anchors, that form a propagation path.
	 * Supports file i/o, if XML or JSON is supported.
	 */
	class ITA_GEO_API CPropagationPath : public std::vector<std::shared_ptr<CPropagationAnchor> >
	{
	public:
		std::string sIdentifier; //!< Identifier hash

		static inline std::string GetTypeStr( ) { return "propagation_path"; };

		//! Calculates the propagation path lenghts
		double GetLength( ) const;

		//! Get number of anchors
		inline int GetNumAnchors( ) const { return (int)this->size( ); };
		//! Get number of reflections
		int GetNumReflections( ) const;
		//! Get number of ray steps
		int GetNumRaySteps( ) const;
		//! Get number of diffractions
		int GetNumDiffractions( ) const;

		//! Calculates accumulated angles over diffracting anchors in radiants
		/**
		 * @return Accumulated angle in radiants
		 *
		 * @note Throws ITAException on error
		 *
		 */
		double GetAccumulatedDiffractionAnglesRad( ) const;

		//! Outgoing wave front normal (normalized vector), directed away from source location
		VistaVector3D GetSourceWaveFrontNormal( ) const;

		//! Incoming wave front normal (normalized vector), directed towards receiver location
		VistaVector3D GetReceiverWaveFrontNormal( ) const;
	};


	//! List of propagation paths
	struct ITA_GEO_API CPropagationPathList : public std::vector<ITAGeo::CPropagationPath>
	{
		std::string sIdentifier; //!< Identifier hash

		//! Get type string of class.
		static inline std::string GetTypeStr( ) { return "propagation_path_list"; };

		inline int GetNumPaths( ) const { return (int)this->size( ); };
		double GetMaxLength( );
	};

	//! Geometrical propagation anchor with parameters of a diffraction wedge
	/**
	 * @todo: refactor: split into wedge class and aperturepoint class. wedge = geometrical definitions (not prop anchor), aperture point class is a combination of source
	 * and target prop anchors including apex point derived from anchor
	 */
	class ITA_GEO_API CITADiffractionWedgeApertureBase : public ITAGeo::CPropagationAnchor
	{
	public:
		VistaVector3D& v3AperturePoint;
		VistaVector3D v3VertextStart;
		VistaVector3D v3VertextEnd;
		VistaVector3D v3MainWedgeFaceNormal;
		VistaVector3D v3OppositeWedgeFaceNormal;
		int iMainWedgeFaceID;
		int iOppositeWedgeFaceID;

		CITADiffractionWedgeApertureBase( );
		virtual inline ~CITADiffractionWedgeApertureBase( ) { };

		//! Validates wedge face normals and angles (not facing same or opposite direction)
		/**
		 * @return True, if wedge is actually a wedge and not a plane or two-sided polygon
		 */
		bool IsValid( ) const;

		//! Returns the wedge angle (angle between faces within solid medium of wedge)
		/**
		 * @return Wedge angle in radiants
		 */
		virtual double GetWedgeAngleRad( ) const = 0;

		//! Returns the wedge angle (angle between faces outside (around?) wedge)
		/**
		 * @return Opening angle in radiants
		 */
		virtual double GetOpeningAngleRad( ) const = 0;

		//! Returns the direction from start to end as normalized vector
		VistaVector3D GetApertureDirection( ) const;

		//! Returns length of aperture
		float GetApertureLength( ) const;

		CITADiffractionWedgeApertureBase& operator=( const CITADiffractionWedgeApertureBase& oRHS );

		//! Checks if source and destination is occluded by wedge
		/**
		 * Calculates if source or receiver is in positive half-space of wedge planes
		 *
		 * @param[in] v3SourcePos Source position
		 * @param[in] v3TargetPos Target position
		 *
		 * @return True, if wedge is occluding and source and destination are not inside wedge
		 *
		 */
		bool IsOccluding( const VistaVector3D& v3SourcePos, const VistaVector3D& v3TargetPos ) const;

		//! Checks if source and destination is occluded by wedge
		/**
		 * Calculates if source or receiver is in positive half-space of wedge planes
		 *
		 * @param[in] pSource Source anchor
		 * @param[in] pDest Source anchor
		 *
		 * @return True, if wedge is occluding and source and destination are not inside wedge
		 *
		 */
		bool IsOccluding( std::shared_ptr<const ITAGeo::CPropagationAnchor> pSource, std::shared_ptr<const ITAGeo::CPropagationAnchor> pDest ) const;

		//! Checks if a point is outside the wedge (and not inside the solid structure)
		/**
		 * @param[in] Point in space to be checked
		 * @return True, if outside or on plane, false if inside
		 */
		bool IsOutsideWedge( const VistaVector3D& v3Pos ) const;

		//! Angle between edge vector and incident wave direction
		float GetIncidenceWaveAngleRad( const VistaVector3D& v3SourcePoint ) const;

		//! Angle between edge vector and reciprocal incident wave direction
		/**
		 * The counter-direction of wave propagation. Based on the reciprocity theorem of linear time-invariant
		 * systems, it is the same for the target direction
		 */
		float GetReciprocalIncidenceWaveAngleRad( const VistaVector3D& v3TargetPoint ) const;
		;

		//! Returns the ray from start vertex into end vertex direction
		VistaRay GetEdgeRay( ) const;

		//! Returns the shortest path length a geometrical wavefront would take over aperture (over shortest-path aperture point) from source to target
		/**	  *
		 * @param[in] v3SourcePoint Source point
		 * @param[in] v3TargetPoint Target point
		 * @return Shortest path length in meter
		 */
		float GetShortestPathLength( const VistaVector3D& v3SourcePoint, const VistaVector3D& v3TargetPoint ) const;

		//! Returns the minimum delay a geometrical wavefront arrives at target over aperture (over shortest-path aperture point) from source to target
		/**
		 * Before this time, no information can be propagated through the medium due to it's finite sound speed
		 *
		 * @param[in] v3SourcePoint Source point
		 * @param[in] v3TargetPoint Target point
		 * @param[in] fSpeedOfSound Sound speed in meter per second
		 * @return Minimum wavefront delay time in seconds
		 */
		float GetMinimumWavefrontDelayTime( const VistaVector3D& v3SourcePoint, const VistaVector3D& vTargev3TargetPointtPoint,
		                                    const float fSpeedOfSound = ITAConstants::DEFAULT_SPEED_OF_SOUND_F ) const;

		//! Returns the maximum delay a geometrical wavefront arrives at target over aperture (over one of the vertices) from source to target
		/**
		 * Before this time, no information can be propagated through the medium due to it's finite sound speed
		 *
		 * @param[in] v3SourcePoint Source point
		 * @param[in] v3TargetPoint Target point
		 * @param[in] fSpeedOfSound Sound speed in meter per second
		 * @return Minimum wavefront delay time in seconds
		 *
		 * @note Requires homogeneous medium
		 *
		 */
		float GetMaximumWavefrontDelayTime( const VistaVector3D& v3SourcePoint, const VistaVector3D& v3TargetPoint,
		                                    const float fSpeedOfSound = ITAConstants::DEFAULT_SPEED_OF_SOUND_F ) const;

		//! Returns a string with the properties of the object
		virtual std::string ToString( ) const;
	};

	//! Wedge class for an outer type (like a corner of a house)
	class ITA_GEO_API CITADiffractionOuterWedgeAperture : public ITAGeo::CITADiffractionWedgeApertureBase
	{
	public:
		CITADiffractionOuterWedgeAperture( ) : CITADiffractionWedgeApertureBase( ) { iAnchorType = ITAGeo::CPropagationAnchor::DIFFRACTION_OUTER_APEX; };
		inline ~CITADiffractionOuterWedgeAperture( ) { };

		double GetWedgeAngleRad( ) const;
		double GetOpeningAngleRad( ) const;
	};

	//! Wedge class for an inner type (like a corner in a room)
	class ITA_GEO_API CITADiffractionInnerWedgeAperture : public ITAGeo::CITADiffractionWedgeApertureBase
	{
	public:
		inline CITADiffractionInnerWedgeAperture( ) : CITADiffractionWedgeApertureBase( ) { iAnchorType = ITAGeo::CPropagationAnchor::DIFFRACTION_INNER_APEX; };
		inline ~CITADiffractionInnerWedgeAperture( ) { };

		double GetWedgeAngleRad( ) const;
		double GetOpeningAngleRad( ) const;
	};
}; // namespace ITAGeo


//! STL stream output operator

// inline std::ostream& operator<<( std::ostream& os, const ITAGeo::CPropagationAnchor& oAnchor )
//{
//	os << "[ " << std::setw( 18 ) << ITAGeo::CPropagationAnchor::GetAnchorTypeStr( oAnchor.iAnchorType ) << " ] " << oAnchor.v3InteractionPoint;
//	return os;
//};
// inline std::ostream & ITAGeo::operator<<(std::ostream & os, const CPropagationAnchor & oAnchor)
//{
//	os << oAnchor.ToString();
//	return os;
//}
inline std::ostream& operator<<( std::ostream& os, const ITAGeo::CPropagationAnchor& oAnchor )
{
	os << oAnchor.ToString( );
	return os;
};

inline std::ostream& operator<<( std::ostream& os, const ITAGeo::CPropagationPath& oPath )
{
	os << "GeoPropagationPath [" << oPath.sIdentifier << "]: num anchors " << oPath.size( ) << std::endl;
	for( size_t i = 0; i < oPath.size( ); i++ )
	{
		auto pAnchor( oPath[i] );
		os << "  GeoAnchor #" << std::setw( 3 ) << 1 + i << ": " << pAnchor->ToString( ) << std::endl;
	}
	return os;
};

inline std::ostream& operator<<( std::ostream& os, const ITAGeo::CPropagationPathList& oPathList )
{
	os << "GeoPropagationPathList [" << oPathList.sIdentifier << "]: num paths " << oPathList.size( ) << std::endl;
	for( size_t i = 0; i < oPathList.size( ); i++ )
	{
		auto oPath( oPathList[i] );
		os << "  GeoPropagationPath #" << std::setw( 3 ) << 1 + i << ": " << oPath << std::endl;
	}
	return os;
};

#endif // INCLUDE_WATCHER_ITA_GEO_BASE
