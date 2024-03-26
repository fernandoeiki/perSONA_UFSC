using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class VAUTextToSpeechSignalSource : VAUSignalSource
{
    public string Name; // Versatile name

    [Tooltip("Text which should be read out.")]
    public string Text = "hi there, my name is rachel. virtual acoustics is a real-time auralization framework for scientific research in Virtual Reality created by the institute of technical acoustics, RWTH aachen university. thank you for testing the VA unity C sharp scripts for controlling a VA server.";
    public bool DirectPlayback = false;

    private string _TextIdentifier = "";

    void Awake()
    {
        if (!VAUAdapter.VA.IsConnected())
            return;

        _ID = VAUAdapter.VA.CreateSignalSourceTextToSpeech(Name);
    }

    void Start()
    {
        VAUAdapter.VA.TextToSpeechPrepareText(_ID, _TextIdentifier, Text);
        if (DirectPlayback)
            VAUAdapter.VA.TextToSpeechPlaySpeech(_ID, _TextIdentifier);
    }

    private void Update()
    {
        
    }

    void OnDestroy()
    {
        if (_ID.Length > 0)
            VAUAdapter.VA.DeleteSignalSource(_ID);
    }
}
