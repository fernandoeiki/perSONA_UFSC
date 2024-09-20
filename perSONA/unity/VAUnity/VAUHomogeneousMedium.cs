using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using VA;

public class VAUHomogeneousMedium : MonoBehaviour
{
	[Tooltip("Speed of sound [m/s]")]
	public double SpeedOfSound = 341;

	[Tooltip("Relative humidity [percent]")]
	public double RelativeHumidity = 20;

	[Tooltip("Temperature [degree celsius]")]
	public double Temperature = 20;

	[Tooltip("Static pressure [Pascal]")]
	public double StaticPressure = 101125;

	[Tooltip("Shift speed / wind speed [m/s]")]
	public Vector3 ShiftSpeed = new Vector3( 0, 0, 0 );

	[Tooltip("If set to true, the initial values will be received from server and will override the manually set values")]
	public bool OverrideFromServer = false;

	private double SpeedOfSoundShadow;
	private Vector3 ShiftSpeedShadow;
	private double RelativeHumidityShadow;
	private double StaticPressureShadow;
	private double TemperatureShadow;

    void Start ()
    {
		if (OverrideFromServer) {
			SpeedOfSound = VAUAdapter.VA.GetHomogeneousMediumSoundSpeed();
			VAVec3 _ShiftSpeed = VAUAdapter.VA.GetHomogeneousMediumShiftSpeed ();
			ShiftSpeed.Set ((float)_ShiftSpeed.x, (float)_ShiftSpeed.y, (float)_ShiftSpeed.z);
			RelativeHumidity = VAUAdapter.VA.GetHomogeneousMediumRelativeHumidity ();
			StaticPressure = VAUAdapter.VA.GetHomogeneousMediumStaticPressure ();
			Temperature = VAUAdapter.VA.GetHomogeneousMediumTemperature ();
		}
		else
		{
			VAUAdapter.VA.SetHomogeneousMediumSoundSpeed (SpeedOfSound);
			VAVec3 _ShiftSpeed = new VAVec3 (ShiftSpeed.x, ShiftSpeed.y, ShiftSpeed.z);
			VAUAdapter.VA.SetHomogeneousMediumShiftSpeed (_ShiftSpeed);
			VAUAdapter.VA.SetHomogeneousMediumRelativeHumidity (RelativeHumidity);
			VAUAdapter.VA.SetHomogeneousMediumStaticPressure (StaticPressure);
			VAUAdapter.VA.SetHomogeneousMediumTemperature (Temperature);
		}

		SpeedOfSoundShadow = SpeedOfSound;
		ShiftSpeedShadow = ShiftSpeed;
		RelativeHumidityShadow = RelativeHumidity;
		StaticPressureShadow = StaticPressure;
		TemperatureShadow = Temperature;
    }
	
	void Update()
	{
		if( SpeedOfSound != SpeedOfSoundShadow )
		{
			VAUAdapter.VA.SetHomogeneousMediumSoundSpeed( SpeedOfSound );	
			SpeedOfSoundShadow = SpeedOfSound;
		}
		if( ShiftSpeed != ShiftSpeedShadow )
		{
			VAVec3 _ShiftSpeed = new VAVec3 (ShiftSpeed.x, ShiftSpeed.y, ShiftSpeed.z);
			VAUAdapter.VA.SetHomogeneousMediumShiftSpeed( _ShiftSpeed );	
			ShiftSpeedShadow = ShiftSpeed;
		}
		if( RelativeHumidity != RelativeHumidityShadow )
		{
			VAUAdapter.VA.SetHomogeneousMediumRelativeHumidity( RelativeHumidity );	
			RelativeHumidityShadow = RelativeHumidity;
		}
		if( StaticPressure != StaticPressureShadow )
		{
			VAUAdapter.VA.SetHomogeneousMediumStaticPressure( StaticPressure );	
			StaticPressureShadow = StaticPressure;
		}
		if( Temperature != TemperatureShadow )
		{
			VAUAdapter.VA.SetHomogeneousMediumTemperature( Temperature );	
			TemperatureShadow = Temperature;
		}
	}
}
