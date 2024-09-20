using UnityEngine;
using System;
using System.Collections;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using VA;

// Adapter to VA (singleton)
/**
 *  Drop this file onto any GameObject. Add a VAUConfig script to the same object for special settings. Add VAUControl to control the running core.
 * */
public class VAUAdapter : MonoBehaviour
{
    public static string Server = "localhost";
    public static int Port = 12340;

    public static string AdditionalSearchPath = ""; // Provide further paths where VA should look for audio files, directivities and HRIRs.
	public static bool ResetOnStart = true;
	public static bool ResetOnStop = true;
	public static bool DeactivateUnitySoundOnAwake = true;

    private static VANet _VA = null;

    // No public construction allowed
    private VAUAdapter() { }

    public static VANet VA
    {
        get
        {
            if (_VA == null)
            {
                _VA = new VANet();
				Init (); // Try to connect as early as possible
            }
            return _VA;
        }
    }

    private static void Init()
    {
		if (!VA.Connect(Server, Port))
        {
            Debug.LogError("Could not connect to VA server on " + Server + " using port " + Port);
            return;
        }

		if( ResetOnStart )
			VA.Reset ();

        // Add Asset folder as search path for VA (only works if VA is running on same host PC)
        if (!VA.AddSearchPath(Application.dataPath))
            Debug.LogError("Could not add application assets folder to VA search path, VA server running on remote host?");

        if (AdditionalSearchPath.Length > 0)
        {
            VA.AddSearchPath(AdditionalSearchPath);
            // ... append more if required.
        }
    }

	// Use this for initialization
	void OnEnable()
    {
        if (DeactivateUnitySoundOnAwake)
            DeactivateUnitySound();
    
        if (GetComponent<VAUAuralizationMode>() != null)
            GetComponent<VAUAuralizationMode>().AuraStringChanged += OnGlobalAuralizationModeChanged;
    }

    void OnGlobalAuralizationModeChanged(string AuraMode)
    {
        VA.SetGlobalAuralizationMode(AuraMode);
    }

    void OnDestroy()
	{
		if( ResetOnStop )
			VA.Reset ();
        VA.Disconnect();
    }

    void DeactivateUnitySound()
    {
        AudioSource[] audioSources = FindObjectsOfType(typeof(AudioSource)) as AudioSource[];
        foreach (AudioSource audioSource in audioSources)
        {
            audioSource.enabled = false;
        }

        AudioListener[] audioListeners = FindObjectsOfType(typeof(AudioListener)) as AudioListener[];
        foreach (AudioListener audioListener in audioListeners)
        {
            audioListener.enabled = false;
        }
    }
}
