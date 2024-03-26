using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class VAURendererArtificialReverb : VAUAudioRenderer
{
	public double RoomReverberationTime = 1.2; // s
	public double RoomSurfaceArea = 220.0; // m^2
	public double RoomVolume = 600.0; // m^3
	
	private double RoomReverberationTimeShadow;
	private double RoomSurfaceAreaShadow;
	private double RoomVolumeShadow;

    void Start ()
    {
		VAUAdapter.VA.SetArtificialReverberationTime( ID, RoomReverberationTime );
		VAUAdapter.VA.SetArtificialSurfaceArea( ID, RoomSurfaceArea );
		VAUAdapter.VA.SetArtificialRoomVolume( ID, RoomVolume );
		
		RoomReverberationTimeShadow = RoomReverberationTime;
        RoomSurfaceAreaShadow = RoomSurfaceArea;
        RoomVolumeShadow = RoomVolume;
    }
	
	void Update()
	{
		if( RoomReverberationTime != RoomReverberationTimeShadow )
		{
	    	VAUAdapter.VA.SetArtificialReverberationTime( ID, RoomReverberationTime );
			RoomReverberationTimeShadow = RoomReverberationTime;
		}
		if( RoomSurfaceArea != RoomSurfaceAreaShadow )
		{
			VAUAdapter.VA.SetArtificialSurfaceArea( ID, RoomSurfaceArea );
			RoomSurfaceAreaShadow = RoomSurfaceArea;
		}
		if( RoomVolume != RoomVolumeShadow )
		{
			VAUAdapter.VA.SetArtificialRoomVolume( ID, RoomVolume );
			RoomVolumeShadow = RoomVolume;
		}
	}
}
