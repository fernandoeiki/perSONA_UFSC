#ifndef INCLUDE_WATCHER_ITA_SIMULATION_SCHEDULER_UTILS_DATA_TYPE_UTILS
#define INCLUDE_WATCHER_ITA_SIMULATION_SCHEDULER_UTILS_DATA_TYPE_UTILS

// std includes
#include <array>
#include <complex>
#include <fstream>
#include <type_traits>
#include <valarray>

// API includes
#include <ITA/SimulationScheduler/definitions.h>
#include <ITAFiniteImpulseResponse.h>
#include <ITAHDFTSpectra.h>
#include <ITAHDFTSpectrum.h>
#include <ITAMultichannelFiniteImpulseResponse.h>
#include <ITASampleBuffer.h>
#include <ITASampleFrame.h>
#include <VistaAspects/VistaPropertyList.h>
#include <VistaTools/VistaBase64.h>

namespace ITA
{
	namespace SimulationScheduler
	{
		namespace Utils
		{
			struct ITA_SIMULATION_SCHEDULER_API DataTypeUtils
			{
				static std::valarray<float> ConvertToValueArray( const ITASampleBuffer& buffer )
				{
					return std::valarray<float>( buffer.GetData( ), buffer.GetLength( ) );
				}

				static std::vector<std::valarray<float>> ConvertToValueArray( const ITASampleFrame& frame )
				{
					std::vector<std::valarray<float>> retVec;

					for( auto i = 0; i < frame.GetNumChannels( ); ++i )
						retVec.push_back( ConvertToValueArray( frame[i] ) );

					return retVec;
				}

				static std::valarray<std::complex<float>> ConvertToComplexValueArray( const ITABase::CHDFTSpectrum& spectrum )
				{
					std::valarray<std::complex<float>> data( spectrum.GetSize( ) );

					for( auto i = 0; i < spectrum.GetSize( ); ++i )
						data[i] = spectrum.GetCoeff( i );

					return data;
				}

				static std::valarray<float> ConvertToValueArray( const ITABase::CHDFTSpectrum& spectrum )
				{
					const auto complexData = ConvertToComplexValueArray( spectrum );
					auto absData           = std::valarray<float>( complexData.size( ) );

					for( auto i = 0; i < complexData.size( ); ++i )
						absData[i] = std::abs( complexData[i] );

					return absData;
				}

				static std::vector<std::valarray<float>> ConvertToValueArray( const ITABase::CHDFTSpectra& spectra )
				{
					std::vector<std::valarray<float>> retVec;

					for( auto i = 0; i < spectra.GetNumChannels( ); ++i )
						retVec.push_back( ConvertToValueArray( *spectra[i] ) );

					return retVec;
				}

				static ITABase::CMultichannelFiniteImpulseResponse Convert( const ITASampleFrame& frame, double sampleRate = 44100.0 )
				{
					ITABase::CMultichannelFiniteImpulseResponse irs( frame.GetNumChannels( ), frame.GetLength( ), sampleRate );

					for( auto i = 0; i < frame.GetNumChannels( ); ++i )
					{
						irs[i].WriteSamples( frame[i].GetData( ), frame.GetLength( ) );
					}

					return irs;
				}

				static ITASampleFrame Convert( const ITABase::CMultichannelFiniteImpulseResponse& irs )
				{
					ITASampleFrame frame( irs.GetNumChannels( ), irs.GetLength( ), true );

					for( auto i = 0; i < frame.GetNumChannels( ); ++i )
					{
						frame[i].WriteSamples( irs[i].GetData( ), irs.GetLength( ) );
					}

					return frame;
				}

				static ITABase::CFiniteImpulseResponse Convert( const ITASampleBuffer& buffer, double sampleRate = 44100.0 )
				{
					ITABase::CFiniteImpulseResponse ir( buffer.GetLength( ), float( sampleRate ) );

					ir.WriteSamples( buffer.GetData( ), buffer.GetLength( ) );

					return ir;
				}

				static ITASampleBuffer Convert( const ITABase::CFiniteImpulseResponse& ir )
				{
					ITASampleBuffer buffer( ir.GetLength( ) );

					buffer.WriteSamples( ir.GetData( ), ir.GetLength( ) );

					return buffer;
				}

				static void MakeSameLength( ITASampleBuffer& first, ITASampleBuffer& second )
				{
					if( first.GetLength( ) < second.GetLength( ) )
					{
						auto buffer = first;
						first.Init( second.GetLength( ) );
						first.WriteSamples( buffer.GetData( ), buffer.GetLength( ) );
					}
					if( first.GetLength( ) > second.GetLength( ) )
					{
						auto buffer = second;
						second.Init( first.GetLength( ) );
						second.WriteSamples( buffer.GetData( ), buffer.GetLength( ) );
					}
				}

				static void MakeSameLength( ITABase::CMultichannelFiniteImpulseResponse& first, ITABase::CMultichannelFiniteImpulseResponse& second )
				{
					if( first.GetNumChannels( ) != second.GetNumChannels( ) )
						ITA_EXCEPT_INVALID_PARAMETER( "Number of channels do not match" );

					if( first.GetLength( ) < second.GetLength( ) )
					{
						auto tmp = first;
						first.Init( first.GetNumChannels( ), second.GetLength( ), first.GetSampleRate( ) );
						for( auto i = 0; i < first.GetNumChannels( ); ++i )
						{
							first[i].WriteSamples( tmp[i].GetData( ), tmp[i].GetLength( ) );
						}
					}
					if( first.GetLength( ) > second.GetLength( ) )
					{
						auto tmp = second;
						second.Init( second.GetNumChannels( ), first.GetLength( ), second.GetSampleRate( ) );
						for( auto i = 0; i < second.GetNumChannels( ); ++i )
						{
							second[i].WriteSamples( tmp[i].GetData( ), tmp[i].GetLength( ) );
						}
					}
				}

				static std::valarray<double> Float2double( const std::valarray<float>& in )
				{
					std::valarray<double> retVal( in.size( ) );

					for( auto i = 0; i < in.size( ); ++i )
					{
						retVal[i] = in[i];
					}

					return retVal;
				}

				template<class T>
				static std::array<VistaType::byte, sizeof( T )> ConvertToByteArray( T value )
				{
					union ConversionHelper
					{
						T val;
						std::array<VistaType::byte, sizeof( T )> bytes;
					} uHelper;

					uHelper.val = value;

					return uHelper.bytes;
				}

				template<class T>
				static std::vector<VistaType::byte> ConvertToByteArray( const std::vector<T>& values )
				{
					std::vector<VistaType::byte> returnVector;

					for( const auto& value: values )
					{
						auto bytes = ConvertToByteArray( value );
						returnVector.insert( returnVector.end( ), bytes.begin( ), bytes.end( ) );
					}

					return returnVector;
				}

				template<class T>
				static T ConvertFormByteArray( const std::array<VistaType::byte, sizeof( T )>& data )
				{
					return *reinterpret_cast<const T*>( data.data( ) );
				}

				template<class T>
				static std::vector<T> ConvertFormByteArray( const std::vector<VistaType::byte>& data )
				{
					std::vector<T> returnVector;

					for( auto i = 0; i < data.size( ); i += sizeof( T ) )
					{
						std::array<VistaType::byte, sizeof( T )> bytes;
						for( auto j = 0; j < sizeof( T ); ++j )
						{
							bytes[j] = data[i + j];
						}

						returnVector.push_back( ConvertFormByteArray<T>( bytes ) );
					}

					return returnVector;
				}

				template<class T>
				static std::string ConvertToBase64( const std::vector<T>& data )
				{
					return VistaBase64::Encode( ConvertToByteArray( data ) );
				}

				template<class T>
				static std::vector<T> ConvertFromBase64( const std::string& data )
				{
					std::vector<VistaType::byte> decoded;
					VistaBase64::Decode( data, decoded );

					return ConvertFormByteArray<T>( decoded );
				}

				template<class T>
				static std::string ConvertToString( const std::vector<T>& data, int iPrecision = 8, const std::string& sSeperator = ", " )
				{
					std::stringstream ss;

					ss.precision( iPrecision );
					ss << std::scientific;

					ss << data.front( );

					std::for_each( data.begin( ) + 1, data.end( ), [&]( const T& val ) { ss << sSeperator << val; } );

					return ss.str( );
				}
			};
		} // namespace Utils
	}     // namespace SimulationScheduler
} // namespace ITA

template<typename Enumeration>
auto AsInteger( Enumeration const value ) -> typename std::underlying_type<Enumeration>::type
{
	return static_cast<typename std::underlying_type<Enumeration>::type>( value );
}

///
/// The use of scoped enums for bit flags requires some additional overloads.
/// The ideas for this implementation were taken from
/// - http://blog.bitwigglers.org/using-enum-classes-as-type-safe-bitmasks/
/// - https://github.com//grisumbras/enum-flags
/// To work correctly this need C++17!! Update the compiler?
///

template<class Enum>
struct EnableBitMaskOperators : public std::false_type
{
};

/*struct empty_t
{
    explicit empty_t ( ) = default;
};

template <class Enum> class Flag
{
public:
    static_assert( EnableBitMaskOperators<Enum>::value,
                   "Flags are not allowed for this type; "
                   "use ENABLE_BITMASK_OPERATORS macro." );

    using enum_t = typename std::decay<Enum>::type;
    using underlying_t = typename std::underlying_type_t<enum_t>;
    using impl_t = typename std::make_unsigned<underlying_t>::type;

    Flag ( ) = default;
    Flag ( const Flag& fl ) = default;
    Flag& operator=( const Flag& fl ) = default;

    explicit Flag ( empty_t t ) : underlyingVal ( 0 )
    { }

    Flag ( enum_t e )
        : underlyingVal ( static_cast< impl_t >( e ) )
    { }

    Flag& operator=( enum_t e )
    {
        underlyingVal = static_cast< impl_t >( e );
        return *this;
    }

    explicit operator bool ( ) const
    {
        return underlyingVal != 0;
    }

    bool operator!( ) const
    {
        return !underlyingVal;
    }

    friend bool operator==( Flag fl1, Flag fl2 )
    {
        return fl1.underlyingVal == fl2.underlyingVal;
    }

    friend bool operator!=( Flag fl1, Flag fl2 )
    {
        return fl1.underlyingVal != fl2.underlyingVal;
    }

    Flag operator~( )
    {
        return Flag ( ~underlyingVal );
    }

    Flag& operator|=( const Flag& fl )
    {
        underlyingVal |= fl.underlyingVal;
        return *this;
    }

    Flag& operator&=( const Flag& fl )
    {
        underlyingVal &= fl.underlyingVal;
        return *this;
    }

    Flag& operator^=( const Flag& fl )
    {
        underlyingVal ^= fl.underlyingVal;
        return *this;
    }

    Flag& operator|=( enum_t e )
    {
        underlyingVal |= static_cast< underlying_t >( e );
        return *this;
    }

    Flag& operator&=( enum_t e )
    {
        underlyingVal &= static_cast< underlying_t >( e );
        return *this;
    }

    Flag& operator^=( enum_t e )
    {
        underlyingVal ^= static_cast< underlying_t >( e );
        return *this;
    }

    friend Flag operator|( Flag f1, Flag f2 )
    {
        return static_cast< enum_t > ( static_cast< underlying_t >( f1.underlyingVal | f2.underlyingVal ) );
    }

    friend Flag operator&( Flag f1, Flag f2 )
    {
        return static_cast< enum_t > ( static_cast< underlying_t >( f1.underlyingVal & f2.underlyingVal ) );
    }

    friend  Flag operator^( Flag f1, Flag f2 )
    {
        return static_cast< enum_t > ( static_cast< underlying_t >( f1.underlyingVal ^ f2.underlyingVal ) );
    }

private:
    explicit Flag ( impl_t val )  : underlyingVal ( val )
    { }

    impl_t underlyingVal;
};*/

template<typename Enum>
auto operator|( Enum lhs, Enum rhs ) -> typename std::enable_if<EnableBitMaskOperators<Enum>::value, Enum>::type
{
	using Underlying = typename std::underlying_type<Enum>::type;
	return static_cast<Enum>( static_cast<Underlying>( lhs ) | static_cast<Underlying>( rhs ) );
}

template<typename Enum>
auto operator&( Enum lhs, Enum rhs ) -> typename std::enable_if<EnableBitMaskOperators<Enum>::value, Enum>::type
{
	using Underlying = typename std::underlying_type<Enum>::type;
	return static_cast<Enum>( static_cast<Underlying>( lhs ) & static_cast<Underlying>( rhs ) );
}

template<typename Enum>
auto operator|=( Enum& lhs, const Enum& rhs ) -> typename std::enable_if<EnableBitMaskOperators<Enum>::value, Enum>::type&
{
	using Underlying = typename std::underlying_type<Enum>::type;
	auto lhsTmp      = static_cast<Underlying>( lhs ) | static_cast<Underlying>( rhs );
	return lhs       = static_cast<Enum>( lhsTmp );
}

template<typename Enum>
auto operator&=( Enum& lhs, const Enum& rhs ) -> typename std::enable_if<EnableBitMaskOperators<Enum>::value, Enum>::type&
{
	using Underlying = typename std::underlying_type<Enum>::type;
	auto lhsTmp      = static_cast<Underlying>( lhs ) & static_cast<Underlying>( rhs );
	return lhs       = static_cast<Enum>( lhsTmp );
}

template<typename Enum>
auto IsSet( const Enum& enumToTest, const Enum& enumForTest ) -> typename std::enable_if<EnableBitMaskOperators<Enum>::value, bool>::type
{
	return ( enumToTest & enumForTest ) == enumForTest;
}

#define ENABLE_BITMASK_OPERATORS( x )                 \
	template<>                                        \
	struct EnableBitMaskOperators<x> : std::true_type \
	{                                                 \
	};


struct pair_hash
{
	template<class T1, class T2>
	std::size_t operator( )( const std::pair<T1, T2>& pair ) const
	{
		return std::hash<T1>( )( pair.first ) ^ std::hash<T2>( )( pair.second );
	}
};

#endif // INCLUDE_WATCHER_ITA_SIMULATION_SCHEDULER_UTILS_DATA_TYPE_UTILS