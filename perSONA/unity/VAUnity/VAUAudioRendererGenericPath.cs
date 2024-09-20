using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class VAUAudioRendererGenericPath : VAUAudioRenderer
{

	[Tooltip("Generic path renderer channel number")]
	public int NumberOfChannels = 2;

	[Tooltip("Generic path renderer channel number")]
	public int FilterLengthSamples = 88200;

	[Tooltip("Generic path renderer sampling rate")]
	public double SamplingRate = 44100;

	[Tooltip("Generic path renderer default impules response file")]
	public string IRFilePath = "";

	[Tooltip("Generic path sound source")]
	public VAUSoundSource SoundSource;

	[Tooltip("Generic path sound receiver")]
	public VAUSoundReceiver SoundReceiver;

	private bool UpdatePerformed = false;

    void Start ()
	{
    }
	
	void Update()
	{
		if (SoundSource && SoundReceiver && !UpdatePerformed) {
			VAUAdapter.VA.UpdateGenericPathFromFile (ID, SoundSource.ID, SoundReceiver.ID, IRFilePath);
			if( SoundSource.ID > 0 && SoundReceiver.ID > 0 )
				UpdatePerformed = true;
		}
	}
}
