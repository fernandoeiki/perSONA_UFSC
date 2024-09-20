using UnityEngine;
using System.Linq;
using System.Collections;
using VA;


public class VAUSoundReceiverTracking : MonoBehaviour
{    
	[Tooltip("Set the corresponding receiver that should be updated")]
	public VAUSoundReceiver Receiver = null;

	[Tooltip("Updates position of user")]
	public bool PositionTracking = true;

	[Tooltip("Updates orientation of user")]
	public bool OrientationTracking = true;



    void Start()
    {
        if( Receiver && Receiver.ID > 0 )
			SetSoundReceiverRealWorldHeadPose();
    }

    void OnEnable()
    {
    }

    void Update()
    {
        if( Receiver && Receiver.ID > 0 )
			SetSoundReceiverRealWorldHeadPose();
    }

	protected void SetSoundReceiverRealWorldHeadPose()
    {
		Vector3 p = GetComponent<Transform>().transform.position; // Unity coordinate system
        VAVec3 v3PosOpenGL = new VAVec3(p.x, p.y, -p.z); // OpenGL coordinate system

		Quaternion q = GetComponent<Transform>().transform.rotation; // Unity coordinate system
		VAQuat qOrientOpenGL = new VAQuat( q.x, q.y, -q.z, q.w ); // OpenGL coordinate system

		if( !PositionTracking )
		{
			v3PosOpenGL = VAUAdapter.VA.GetSoundReceiverRealWorldPosition (Receiver.ID);
		}
		if( !OrientationTracking )
		{
			qOrientOpenGL = VAUAdapter.VA.GetSoundReceiverRealWorldOrientation (Receiver.ID);
		}

		VAUAdapter.VA.SetSoundReceiverRealWorldHeadPose (Receiver.ID, v3PosOpenGL, qOrientOpenGL);
    }

    private void OnDestroy()
    {
    }
}
