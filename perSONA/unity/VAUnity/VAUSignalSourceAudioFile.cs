using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class VAUSignalSourceAudioFile : VAUSignalSource
{
    [Tooltip("Absolute or relative file path (relative to Assets folder or any folder added to search path using AddSearchPath)")]
    public string FilePath;
    public string Name; // Versatile name
    [Tooltip("Will loop the audio signal source.")]
    public bool IsLooping = true;  
    [Tooltip("Will immediately start the signal source payback.")]
    public bool PlayOnStart = true; 
    
    void Awake()
    {
        if (!VAUAdapter.VA.IsConnected())
		{
			Debug.LogError( "Could not awake signal source '" + FilePath + "', not connected to VA" );
            return;
		}
	}
	
    void OnEnable()
	{		
		if (!VAUAdapter.VA.IsConnected())
		{
			Debug.LogError( "Could not enable signal source '" + FilePath + "', not connected to VA" );
			return;
		}
		_ID = VAUAdapter.VA.CreateSignalSourceBufferFromFile (FilePath, Name);
		Debug.Assert (_ID.Length > 0, "Could not create audio file signal source '" + Name + "' from file path " + FilePath);
		VAUAdapter.VA.SetSignalSourceBufferLooping (_ID, IsLooping);
	}

	void Start()
	{
        if (PlayOnStart)
            VAUAdapter.VA.SetSignalSourceBufferPlaybackAction(_ID, "PLAY");
    }

    void OnDestroy()
    {
        if (_ID.Length > 0)
            VAUAdapter.VA.DeleteSignalSource(_ID);
    }
}
