using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class VAUController : MonoBehaviour
{
	[Tooltip("Mute global input (audio in)")]
	public bool InputMuted = false;

	[Tooltip("Control global input gain (audio in level)")]
	public double InputGain = 1.0;

	[Tooltip("Mute global output (audio out)")]
	public bool OutputMuted = false;

	[Tooltip("Control global output gain (audio out level)")]
	public double OutputGain = 1.0;
	
	private bool InputMutedShadow;
	private double InputGainShadow;
	private bool OutputMutedShadow;
	private double OutputGainShadow;

    void Start ()
    {
		VAUAdapter.VA.SetInputMuted( InputMuted );
		VAUAdapter.VA.SetInputGain( InputGain );
		VAUAdapter.VA.SetOutputMuted( OutputMuted );
		VAUAdapter.VA.SetOutputGain( OutputGain );
		
		InputMutedShadow = InputMuted;
		InputGainShadow = InputGain;
		OutputMutedShadow = OutputMuted;
        OutputGainShadow = OutputGain;
    }
	
	void Update()
	{
		if( InputMuted != InputMutedShadow )
		{
			VAUAdapter.VA.SetInputMuted( InputMuted );	
			InputMutedShadow = InputMuted;
		}
		if( InputGain != InputGainShadow )
		{
			VAUAdapter.VA.SetInputGain( InputGain );	
			InputGainShadow = InputGain;
		}
		if( OutputMuted != OutputMutedShadow )
		{
			VAUAdapter.VA.SetOutputMuted( OutputMuted );	
			OutputMutedShadow = OutputMuted;
		}
		if( OutputGain != OutputGainShadow )
		{
			VAUAdapter.VA.SetOutputGain( OutputGain );	
			OutputGainShadow = OutputGain;
		}
	}
}
