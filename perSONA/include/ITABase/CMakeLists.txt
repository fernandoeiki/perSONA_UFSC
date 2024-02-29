target_sources (
	${PROJECT_NAME}
	PRIVATE ITAAudiofileCommon.h
			ITABaseDefinitions.h
			ITABlockMath.h
			ITAClock.h
			ITAConstants.h
			ITACriticalSection.h
			ITADataLog.h
			ITADebug.h
			ITAEndianness.h
			ITAException.h
			ITAFade.h
			ITAFastMath.h
			ITAFileSystemUtils.h
			ITAFunctors.h
			ITAISO9613.h
			ITALog.h
			ITAMagnitudeSpectrum.h
			ITANumericUtils.h
			ITASampleTypeConversion.h
			ITASimpleConvolution.h
			ITASpectrum.h
			ITAStopWatch.h
			ITAStringUtils.h
			ITAThirdOctaveMagnitudeSpectrum.h
			ITATimeSeriesAnalyzer.h
			ITATypes.h
			ITAUncopyable.h
			ITAWholeOctaveMagnitudeSpectrum.h
			ITAWinPCClock.h
)

if (WIN32)
	target_sources (${PROJECT_NAME} PRIVATE ITAHPT.h ITAMutex.h ITATimer.h)
endif ()

if (TARGET SndFile::sndfile AND ITA_BASE_WITH_SNDFILE)
	target_sources (
		${PROJECT_NAME}
		PRIVATE ITAAudiofileReader.h
				ITAAudiofileWriter.h
				ITABufferedAudioFileWriter.h
				ITAHDFTSpectra.h
				ITAHDFTSpectrum.h
				ITASampleBuffer.h
				ITASampleFrame.h
				ITAFiniteImpulseResponse.h
				ITAInterpolation.h
				ITAMultichannelFiniteImpulseResponse.h
	)

	if (TARGET SampleRate::samplerate AND ITA_BASE_WITH_SAMPLERATE)
		target_sources (${PROJECT_NAME} PRIVATE ITAAudioSample.h)
	endif ()
endif ()

if (ITA_BASE_WITH_OLD_ATOMICS)
	target_sources (${PROJECT_NAME} PRIVATE ITAAtomicOps.h ITAAtomicPrimitives.h)
endif ()

if (ITA_BASE_WITH_OLD_RAVEN_OPS)
	target_sources (${PROJECT_NAME} PRIVATE ITAOps.h)
endif ()

if (VPCRE_FOUND AND ITA_BASE_WITH_REGULAR_EXPRESSIONS)
	target_sources (${PROJECT_NAME} PRIVATE ITAASCIITable.h)
endif ()

if (ITA_BASE_WITH_CONFIG_OLD_IMPL AND NOT ITA_BASE_WITH_CONFIG_SIMPLE_INI)
	target_sources (${PROJECT_NAME} PRIVATE ITAConfigUtils.h)
endif ()

file (RELATIVE_PATH INCLUDE_PATH ${PROJECT_SOURCE_DIR} ${CMAKE_CURRENT_LIST_DIR})
target_include_directories (
	${PROJECT_NAME} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>
						   $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/ITABase>
)

add_subdirectory (ITABase)
