using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class VAUAudioReproduction : MonoBehaviour
{
	[Tooltip("Reproduction module identifier")]
	public string ID = "";

	[Tooltip("Mute/unmute reproduction output")]
	public bool OutputMuted = false;

	[Tooltip("Control reproduction output gain")]
	public double OutputGain = 1.0;

	private bool OutputMutedShadow;
	private double OutputGainShadow;

    void Start ()
    {
		VAUAdapter.VA.SetReproductionModuleMuted( ID, OutputMuted );
		VAUAdapter.VA.SetReproductionModuleGain( ID, OutputGain );
		
		OutputMutedShadow = OutputMuted;
        OutputGainShadow = OutputGain;
    }
	
	void Update()
	{
		if( OutputMuted != OutputMutedShadow )
		{
			VAUAdapter.VA.SetReproductionModuleMuted( ID, OutputMuted );
			OutputMutedShadow = OutputMuted;
		}
		if( OutputGain != OutputGainShadow )
		{
			VAUAdapter.VA.SetReproductionModuleGain( ID, OutputGain );
			OutputGainShadow = OutputGain;
		}
	}
}
