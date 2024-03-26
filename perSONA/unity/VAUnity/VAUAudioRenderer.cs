using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class VAUAudioRenderer : MonoBehaviour
{
	[Tooltip("Rendering module identifier")]
	public string ID = "";

	[Tooltip("Mute/unmute rendering output")]
	public bool OutputMuted = false;

	[Tooltip("Control rendering output gain")]
	public double OutputGain = 1.0;
	
	private bool OutputMutedShadow;
	private double OutputGainShadow;

    void Start ()
    {
		VAUAdapter.VA.SetRenderingModuleMuted( ID, OutputMuted );
		VAUAdapter.VA.SetRenderingModuleGain( ID, OutputGain );
		
		OutputMutedShadow = OutputMuted;
        OutputGainShadow = OutputGain;
    }
	
	void Update()
	{
		if( OutputMuted != OutputMutedShadow )
		{
			VAUAdapter.VA.SetRenderingModuleMuted( ID, OutputMuted );
			OutputMutedShadow = OutputMuted;
		}
		if( OutputGain != OutputGainShadow )
		{
			VAUAdapter.VA.SetRenderingModuleGain( ID, OutputGain );
			OutputGainShadow = OutputGain;
		}
	}
}
