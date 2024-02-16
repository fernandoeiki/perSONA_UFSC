#ifndef INCLUDE_WATCHER_ITA_SIMULATION_SCHEDULER_UTILS_JSON_CONFIG_UTILS
#define INCLUDE_WATCHER_ITA_SIMULATION_SCHEDULER_UTILS_JSON_CONFIG_UTILS

// std includes
#include <array>
#include <complex>
#include <fstream>
#include <valarray>

// API includes
#include <ITA/SimulationScheduler/definitions.h>
#include <ITAException.h>
#include <VistaAspects/VistaPropertyList.h>
#include <VistaTools/VistaBase64.h>
#include <nlohmann/json.hpp>


namespace ITA
{
	namespace SimulationScheduler
	{
		namespace Utils
		{
			struct ITA_SIMULATION_SCHEDULER_API JSONConfigUtils
			{
				static nlohmann::json WriteVistaPropertyToJSON( const VistaProperty& oProperty )
				{
					if( oProperty.GetPropertyType( ) == VistaProperty::PROPT_STRING )
					{
						std::string sValue;
						VistaConversion::FromString( oProperty.GetValue( ), sValue );

						nlohmann::json jn;
						jn[oProperty.GetNameForNameable( )] = sValue;
						return jn;
					}
					if( oProperty.GetPropertyType( ) == VistaProperty::PROPT_INT )
					{
						int iValue;
						VistaConversion::FromString( oProperty.GetValue( ), iValue );

						nlohmann::json jn;
						jn[oProperty.GetNameForNameable( )] = iValue;
						return jn;
					}
					if( oProperty.GetPropertyType( ) == VistaProperty::PROPT_BOOL )
					{
						bool bValue;
						VistaConversion::FromString( oProperty.GetValue( ), bValue );

						nlohmann::json jn;
						jn[oProperty.GetNameForNameable( )] = bValue;
						return jn;
					}
					if( oProperty.GetPropertyType( ) == VistaProperty::PROPT_DOUBLE )
					{
						double dValue;
						VistaConversion::FromString( oProperty.GetValue( ), dValue );

						nlohmann::json jn;
						jn[oProperty.GetNameForNameable( )] = dValue;
						return jn;
					}
					if( oProperty.GetPropertyType( ) == VistaProperty::PROPT_LIST )
					{
						std::vector<float> vfValue;
						VistaConversion::FromString( oProperty.GetValue( ), vfValue );

						nlohmann::json jn;
						jn[oProperty.GetNameForNameable( )] = vfValue;
						return jn;
					}
					if( oProperty.GetPropertyType( ) == VistaProperty::PROPT_PROPERTYLIST )
					{
						nlohmann::json jnRoot = nlohmann::json::object( );

						for( const auto& oProp: oProperty.GetPropertyListConstRef( ) )
						{
							auto jnTmp = WriteVistaPropertyToJSON( oProp.second );
							jnRoot.insert( jnTmp.begin( ), jnTmp.end( ) );
						}

						nlohmann::json jnReturn;
						jnReturn[oProperty.GetNameForNameable( )] = jnRoot;

						return jnReturn;
					}
					else
					{
						ITA_EXCEPT_NOT_IMPLEMENTED;
					}
				}

				static VistaProperty ReadVistaPropertyFromJSON( const nlohmann::json::const_iterator& oJsonNode )
				{
					VistaProperty oProp;
					if( oJsonNode.value( ).is_boolean( ) )
					{
						oProp.SetNameForNameable( oJsonNode.key( ) );
						oProp.SetPropertyType( VistaProperty::PROPT_BOOL );

						std::string sValue;
						VistaConversion::ToString( static_cast<bool>( oJsonNode.value( ) ), sValue );
						oProp.SetValue( sValue );
					}
					else if( oJsonNode.value( ).is_string( ) )
					{
						oProp.SetNameForNameable( oJsonNode.key( ) );
						oProp.SetPropertyType( VistaProperty::PROPT_STRING );

						oProp.SetValue( static_cast<std::string>( oJsonNode.value( ) ) );
					}
					else if( oJsonNode.value( ).is_number( ) )
					{
						oProp.SetNameForNameable( oJsonNode.key( ) );
						std::string sValue;

						const auto value = static_cast<double>( oJsonNode.value( ) );
						if( oJsonNode.value( ).is_number_float( ) ) // double
						{
							oProp.SetPropertyType( VistaProperty::PROPT_DOUBLE );
							VistaConversion::ToString( value, sValue );
						}
						else // int
						{
							oProp.SetPropertyType( VistaProperty::PROPT_INT );
							VistaConversion::ToString( static_cast<int>( value ), sValue );
						}
						oProp.SetValue( sValue );
					}
					else if( oJsonNode.value( ).is_array( ) )
					{
						oProp.SetNameForNameable( oJsonNode.key( ) );
						oProp.SetPropertyType( VistaProperty::PROPT_LIST );

						const std::vector<float> values = oJsonNode.value( );

						std::string sValue;
						VistaConversion::ToString( values, sValue );
						oProp.SetValue( sValue );
					}
					else if( oJsonNode.value( ).is_object( ) )
					{
						oProp.SetNameForNameable( oJsonNode.key( ) );
						oProp.SetPropertyType( VistaProperty::PROPT_PROPERTYLIST );

						VistaPropertyList oPropertyList;

						for( auto&& iter = oJsonNode.value( ).cbegin( ); iter != oJsonNode.value( ).cend( ); ++iter )
						{
							oPropertyList.SetProperty( ReadVistaPropertyFromJSON( iter ) );
						}

						oProp.SetPropertyListValue( oPropertyList );
					}
					else
						ITA_EXCEPT_NOT_IMPLEMENTED;

					return oProp;
				}

				static nlohmann::json WriteVistaPropertyListToJSON( const VistaPropertyList& oProperties )
				{
					nlohmann::json jnRoot = nlohmann::json::object( );

					for( const auto& oProp: oProperties )
					{
						auto jnTmp = WriteVistaPropertyToJSON( oProp.second );
						jnRoot.insert( jnTmp.begin( ), jnTmp.end( ) );
					}

					return jnRoot;
				}

				static VistaPropertyList ReadVistaPropertyListFromJSON( const nlohmann::json& oJsonNode )
				{
					VistaProperty oProp;

					oProp.SetNameForNameable( "" );
					oProp.SetPropertyType( VistaProperty::PROPT_PROPERTYLIST );

					VistaPropertyList oPropertyList;

					for( auto&& iter = oJsonNode.cbegin( ); iter != oJsonNode.cend( ); ++iter )
					{
						oPropertyList.SetProperty( ReadVistaPropertyFromJSON( iter ) );
					}

					oProp.SetPropertyListValue( oPropertyList );

					return oProp.GetPropertyListConstRef( );
				}

				static VistaPropertyList LoadJSONConfig( const std::string& sFileName, const std::string& sVariableSectionName = "Variables" )
				{
					std::ifstream fConfigFile( sFileName );

					const std::string sContent( ( std::istreambuf_iterator<char>( fConfigFile ) ), ( std::istreambuf_iterator<char>( ) ) );

					fConfigFile.close( );

					try
					{
						auto jnRoot = nlohmann::json::parse( sContent );

						ReplaceVariables( jnRoot, sVariableSectionName );

						return ReadVistaPropertyListFromJSON( jnRoot );
					}
					catch( const nlohmann::json::exception& e )
					{
						throw ITAException( ITAException::PARSE_ERROR, __FUNCTION__, e.what( ) );
					}
				}

				static void ReplaceVariables( nlohmann::json& jnRoot, const std::string& sVariableSectionName = "Variables" )
				{
					const auto jnVariableIterator = jnRoot.find( sVariableSectionName );

					if( jnVariableIterator != jnRoot.end( ) )
					{
						std::map<std::string, nlohmann::json> mVariables;

						for( auto&& jnNode: jnVariableIterator.value( ).items( ) )
						{
							mVariables[jnNode.key( )] = jnNode.value( );
						}

						ReplaceVariablesHelper( jnRoot, mVariables );

						jnRoot.erase( jnVariableIterator );
					}
				}

			private:
				static void ReplaceVariablesHelper( nlohmann::json& jnRoot, const std::map<std::string, nlohmann::json>& mVariables )
				{
					for( auto& jnNode: jnRoot )
					{
						if( jnNode.is_object( ) )
						{
							ReplaceVariablesHelper( jnNode, mVariables );
						}
						if( jnNode.is_string( ) )
						{
							auto sString      = static_cast<std::string>( jnNode );
							const auto nStart = sString.find( "${" );
							if( nStart == std::string::npos )
								continue;
							const auto nEnd = sString.find( '}', nStart );
							if( nEnd == std::string::npos )
								continue;

							std::string sVariableName = sString.substr( nStart + 2, nEnd - nStart - 2 );

							auto replacementIterator = mVariables.find( sVariableName );

							if( replacementIterator != mVariables.end( ) )
							{
								jnNode = replacementIterator->second;
							}
						}
					}
				}
			};
		} // namespace Utils
	}     // namespace SimulationScheduler
} // namespace ITA

#endif // INCLUDE_WATCHER_ITA_SIMULATION_SCHEDULER_UTILS_JSON_CONFIG_UTILS