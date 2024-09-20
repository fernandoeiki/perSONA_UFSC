using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class VAUConfig : MonoBehaviour {

	[Tooltip("Name or IP address where the VA server is running.")]
	public string Server = VAUAdapter.Server;

	[Tooltip("TCP/IP port where the VA server is communicating.")]
	public int Port = VAUAdapter.Port;

	[Tooltip("Add an additional path where to find files")]
	public string AdditionalSearchPath = "";

	[Tooltip("Resets server on startup")]
	public bool ResetOnStart = true;

	[Tooltip("Resets server when stopping")]
	public bool ResetOnStop = true;

	// Use this for initialization
	void Awake()
	{
		VAUAdapter.Server = Server;
		VAUAdapter.Port = Port;
		VAUAdapter.ResetOnStart = ResetOnStart;
		VAUAdapter.ResetOnStop = ResetOnStop;
	}
}
