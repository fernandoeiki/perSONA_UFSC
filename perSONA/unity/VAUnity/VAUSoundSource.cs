using UnityEngine;
using System.IO;
using System.Collections.Generic;
using VA;

public class VAUSoundSource : MonoBehaviour
{
    [Tooltip("Activate this if you want to validate & change volume and mute/unmute state on every update loop.")]
    public bool ContinuousGainObserver = false; 

    [Tooltip("Activate this if you dont want to pause the playback while the SoundSource is disabled but rather stop it.")]
    public bool stopOnDisable = false;

    [Tooltip("Insert a custom VAUDirectivity-Script.")] 
    public VAUDirectivity Directivity = null;

    [Tooltip("Insert a custom VAUSignalSource-Script.")]
    public VAUSignalSource SignalSource = null;

	[Tooltip("Set an explicit renderer for this source [todo]")]
	public VAUAudioRenderer Renderer = null;

	[Tooltip("Descriptive name")]
	public string Name = "SoundReceiver";

	[Tooltip("Sound power in Watts (default is 31mW)")]
	public double SoundPower = 0.0031;

    private VANet _VA = null;
    private int _ID;
    private Quaternion q;
    private Transform t;
    private string _AudiofileSignalSource = null;

    public int ID
    {
        get
        {
            return _ID;
        }
    }

	void OnEnable()
	{
		_VA = VAUAdapter.VA;

        if (!_VA.IsConnected())
		{
			Debug.LogError( "Could not create sound source, not connected to VA" );
            return;
		}

		// Add sound source
		_ID = _VA.CreateSoundSource(this.name);
		_VA.SetSoundSourceAuralizationMode(_ID, "all");
		_VA.SetSoundSourceSoundPower (_ID, SoundPower);
	}

    void Start()
    {
        // Connect to directivity, if linked or attached
        if (Directivity)
            _VA.SetSoundSourceDirectivity(_ID, Directivity.ID);
        else if (GetComponent<VAUDirectivity>())
            _VA.SetSoundSourceDirectivity(_ID, GetComponent<VAUDirectivity>().ID);

        // Connect to signal source, if linked or attached
		if (SignalSource)
		{
			_VA.SetSoundSourceSignalSource (_ID, SignalSource.ID);
		}
		else if (GetComponent<AudioSource>())
        {
            // Set gain control once
            _VA.SetSoundSourceMuted(_ID, GetComponent<AudioSource>().mute);
			_VA.SetSoundSourceSoundPower( _ID, GetComponent< AudioSource >().volume * 31.69e-3 ); // Volume of 1.0 results in default sound power: 31.67 mW -> 94 dB SPL @ 1m

            // Create and connect audio signal source
            if (GetComponent<AudioSource>().clip)
            {
                string FilePath = GetComponent<AudioSource>().clip.name + ".wav";
                string Name = this.name + "_signal";
                bool IsLooping = GetComponent<AudioSource>().loop;
                bool PlayOnAwake = GetComponent<AudioSource>().playOnAwake;

				_AudiofileSignalSource = _VA.CreateSignalSourceBufferFromFile(FilePath, Name);
                Debug.Assert(_AudiofileSignalSource.Length > 0, "Could not create integrated audio file signal source '" + Name + "' file from path " + FilePath);
				_VA.SetSignalSourceBufferLooping(_AudiofileSignalSource, IsLooping);
                if (PlayOnAwake)
					_VA.SetSignalSourceBufferPlaybackAction(_AudiofileSignalSource, "play");

                _VA.SetSoundSourceSignalSource(_ID, _AudiofileSignalSource);
            }
        }

        // Activate auralization mode, if available
        if (GetComponent<VAUAuralizationMode>())
            GetComponent<VAUAuralizationMode>().AuraStringChanged += OnSoundSourceAuralizationModeChanged;

        // Initially, set the pose (otherwise rendering module can not spatialize)
        SetSoundSourcePositionOrientation();
    }

    // Update is called once per frame
    void Update()
    {
        SetSoundSourcePositionOrientation();

        if (ContinuousGainObserver)
        {
            _VA.SetSoundSourceMuted(_ID, GetComponent<AudioSource>().mute);
			_VA.SetSoundSourceSoundPower(_ID, GetComponent<AudioSource>().volume * 31.69e-3 ); // Volume of 1.0 results in default sound power: 31.67 mW -> 94 dB SPL @ 1m
        }
    }

    void SetSoundSourcePositionOrientation()
    {
        // Convert left-handed Unity transform matrix to VA positions and orientations (right-handed, OpenGL)
        _VA = VAUAdapter.VA;
        t = GetComponent<Transform>();
        q = t.rotation;
        Vector3 up = q * Vector3.up;
        Vector3 view = q * Vector3.forward;
        Vector3 view_ogl = new Vector3(view.x, view.y, -view.z);
        Vector3 up_ogl = new Vector3(up.x, up.y, -up.z);
		_VA.SetSoundSourcePosition (_ID, new VAVec3 (t.transform.position.x, t.transform.position.y, -t.transform.position.z));
		_VA.SetSoundSourceOrientationVU(_ID, new VAVec3( view_ogl.x, view_ogl.y, view_ogl.z ), new VAVec3( up_ogl.x, up_ogl.y, up_ogl.z ));
    }

    void OnSoundSourceAuralizationModeChanged(string AuraMode)
    {
        _VA.SetSoundSourceAuralizationMode(_ID, AuraMode);
    }

    public void OnDisable()
    {
        if (GetComponent<VAUAuralizationMode>())
            GetComponent<VAUAuralizationMode>().AuraStringChanged -= OnSoundSourceAuralizationModeChanged;

		if (_AudiofileSignalSource != null) {
			if (stopOnDisable)
				_VA.SetSignalSourceBufferPlaybackAction (_AudiofileSignalSource, "stop");
			else
				_VA.SetSignalSourceBufferPlaybackAction (_AudiofileSignalSource, "pause");
		}
    }

    private void OnDestroy()
    {
        _VA = VAUAdapter.VA;
        if (_VA.IsConnected())
        {
			_VA.SetSoundSourceSignalSource(_ID, "");
            _VA.DeleteSoundSource(ID);

            // Temptative signal source deletion
			if (_AudiofileSignalSource != null)
				_VA.DeleteSignalSource (_AudiofileSignalSource);
        }
    }
}
