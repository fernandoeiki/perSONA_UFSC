using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class VAUDirectivity : MonoBehaviour
{
    [Tooltip("Absolute or relative path (relative to Assets folder), also use AddSearchPath for special folders.")]
	public string FilePath = "";

	[Tooltip("Versatile name for this directivity")]
    public string Name = "";

	protected int _ID = -1; // Stores the internal id that is assigned by VA

    public int ID
    {
        get
        {
            return _ID;
        }
    }
    
    void OnEnable()
    {
        if (!VAUAdapter.VA.IsConnected())
            return;

        if (FilePath.Length > 0)
			_ID = VAUAdapter.VA.CreateDirectivityFromFile(FilePath);
	}

    private void OnDestroy()
    {
		if (!VAUAdapter.VA.IsConnected())
            return;

        if (_ID != -1)
			VAUAdapter.VA.DeleteDirectivity(_ID);
        _ID = -1;
    }
}
