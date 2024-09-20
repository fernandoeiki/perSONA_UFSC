using UnityEngine;
using System.Linq;
using System.Collections;
using VA;


public class VAUSoundReceiver : MonoBehaviour {

    [Tooltip("Descriptive name")]
    public string Name = "SoundReceiver";
    
    [Tooltip("Set an explicit renderer for this receiver [todo]")]
    public VAUAudioRenderer Renderer = null;

    [Tooltip("Connect an directivity to this receiver")]
    public VAUDirectivity Directivity = null;

	[Tooltip("Internal VA identifier")]
    protected int _ID;

    private Quaternion q;
    private Transform t;
    
    public int ID
    {
        get
        {
            return _ID;
        }
    }
    
    void Start()
    {
		_ID = VAUAdapter.VA.CreateSoundReceiver(Name);
        VAUAdapter.VA.SetSoundReceiverAuralizationMode(_ID, "all");
		if (Directivity)
			VAUAdapter.VA.SetSoundReceiverDirectivity(_ID, Directivity.ID);
        
        SetSoundReceiverPositionOrientation();
    }

    void OnEnable()
    {
        if (GetComponent<VAUAuralizationMode>() != null)
            GetComponent<VAUAuralizationMode>().AuraStringChanged += OnSoundReceiverAuralizationModeChanged;
    }

    void Update()
    {
        SetSoundReceiverPositionOrientation();
    }

    // Uses the View- and Up-Vector to transmit the position of the listener to VA
    protected void SetSoundReceiverPositionOrientation()
    {
        t = GetComponent<Transform>();
        q = t.rotation;
        Vector3 up = q * Vector3.up;
        Vector3 view = q * Vector3.forward;
        Vector3 view_ogl = new Vector3(view.x, view.y, -view.z);
        Vector3 up_ogl = new Vector3(up.x, up.y, -up.z);
        VAUAdapter.VA.SetSoundReceiverPosition(_ID, new VAVec3(t.transform.position.x, t.transform.position.y, -t.transform.position.z));
        VAUAdapter.VA.SetSoundReceiverOrientationVU(_ID, new VAVec3(view_ogl.x, view_ogl.y, view_ogl.z), new VAVec3(up_ogl.x, up_ogl.y, up_ogl.z));
    }

    protected void OnSoundReceiverAuralizationModeChanged(string AuraMode)
    {
        VAUAdapter.VA.SetSoundReceiverAuralizationMode(_ID, AuraMode);
    }

    private void OnDestroy()
    {
        if (GetComponent<VAUAuralizationMode>() != null)
            GetComponent<VAUAuralizationMode>().AuraStringChanged -= OnSoundReceiverAuralizationModeChanged;
		
		VAUAdapter.VA.DeleteSoundReceiver(ID);
    }
}
