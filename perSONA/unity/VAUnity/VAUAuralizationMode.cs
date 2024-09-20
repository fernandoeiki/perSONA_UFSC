using UnityEngine;
using System.Collections;

public class VAUAuralizationMode : MonoBehaviour
{

	[Tooltip("Toggle direct sound")]
    public bool DirectSound = true;

	[Tooltip("Toggle early reflections")]
	public bool EarlyReflections = false;

	[Tooltip("Toggle diffuse decay")]
	public bool DiffuseDecay = false;

	[Tooltip("Toggle source directivity")]
	public bool SourceDirectivity = true;

	[Tooltip("Toggle air absorption")]
	public bool AirAbsorption = false;

	[Tooltip("Toggle atmospheric temporal variations")]
	public bool AtmosphericTemporalVariations = false;

	[Tooltip("Toggle scattering")]
	public bool Scattering = false;

	[Tooltip("Toggle diffraction")]
	public bool Diffraction = false;

	[Tooltip("Toggle hear-field effects")]
	public bool NearFieldEffects = false;

	[Tooltip("Toggle Doppler shifts")]
	public bool DopplerShifts = true;

	[Tooltip("Toggle spherical spreading loss")]
    public bool SphericalSpreadingLoss = true;

    protected class AuralizationMode : System.Object
    {
        public bool DirectSound = true;
        public bool EarlyReflections = true;
        public bool DiffuseDecay = true;
        public bool SourceDirectivity = true;
        public bool AirAbsorption = true;
        public bool AtmosphericTemporalVariations = true;
        public bool Scattering = true;
        public bool Diffraction = true;
        public bool NearFieldEffects = true;
        public bool DopplerShifts = true;
        public bool SphericalSpreadingLoss = true;

        public override bool Equals(System.Object other)
        {
            return (GetHashCode() == other.GetHashCode());
        }

        override public int GetHashCode()
        {
            int iCompare = 0;

            iCompare += DirectSound ? 1 << 1 : 0;
            iCompare += EarlyReflections ? 1 << 2 : 0;
            iCompare += DiffuseDecay ? 1 << 3 : 0;
            iCompare += SourceDirectivity ? 1 << 4 : 0;
            iCompare += AirAbsorption ? 1 << 5 : 0;
            iCompare += AtmosphericTemporalVariations ? 1 << 6 : 0;
            iCompare += Scattering ? 1 << 7 : 0;
            iCompare += Diffraction ? 1 << 8 : 0;
            iCompare += NearFieldEffects ? 1 << 9 : 0;
            iCompare += DopplerShifts ? 1 << 10 : 0;
            iCompare += SphericalSpreadingLoss ? 1 << 11 : 0;

            return iCompare;
        }

        public static bool operator ==(AuralizationMode left, AuralizationMode right)
        {
            return left.Equals(right);
        }

        public static bool operator !=(AuralizationMode left, AuralizationMode right)
        {
            return !(left.Equals(right));
        }
    }

    private AuralizationMode AuraModeShadow = new AuralizationMode();

    public delegate void OnAuraStringChangedDelegate(string sAuraString);
    public event OnAuraStringChangedDelegate AuraStringChanged;

    void Update()
    {
        AuralizationMode AuraMode = UpdateAuraModeSettings();

        if (AuraMode == AuraModeShadow)
            return;

        string AuraString = "";

        if (AuraMode.DirectSound != AuraModeShadow.DirectSound)
        {
            AuraString = AuraMode.DirectSound ? "+DS" : "-DS";
            AuraModeShadow.DirectSound = AuraMode.DirectSound;
            if (AuraStringChanged != null)
                AuraStringChanged(AuraString);
        }

        if (AuraMode.EarlyReflections != AuraModeShadow.EarlyReflections)
        {
            AuraString = AuraMode.EarlyReflections ? "+ER" : "-ER";
            AuraModeShadow.EarlyReflections = AuraMode.EarlyReflections;
            if (AuraStringChanged != null)
                AuraStringChanged(AuraString);
        }

        if (AuraMode.DiffuseDecay != AuraModeShadow.DiffuseDecay)
        {
            AuraString = AuraMode.DiffuseDecay ? "+DD" : "-DD";
            AuraModeShadow.DiffuseDecay = AuraMode.DiffuseDecay;
            if (AuraStringChanged != null)
                AuraStringChanged(AuraString);
        }

        if (AuraMode.SourceDirectivity != AuraModeShadow.SourceDirectivity)
        {
            AuraString = AuraMode.SourceDirectivity ? "+DIR" : "-DIR";
            AuraModeShadow.SourceDirectivity = AuraMode.SourceDirectivity;
            if (AuraStringChanged != null)
                AuraStringChanged(AuraString);
        }

        if (AuraMode.AirAbsorption != AuraModeShadow.AirAbsorption)
        {
            AuraString = AuraMode.AirAbsorption ? "+AA" : "-AA";
            AuraModeShadow.AirAbsorption = AuraMode.AirAbsorption;
            if (AuraStringChanged != null)
                AuraStringChanged(AuraString);
        }

        if (AuraMode.AtmosphericTemporalVariations != AuraModeShadow.AtmosphericTemporalVariations)
        {
            AuraString = AuraMode.AtmosphericTemporalVariations ? "+TV" : "-TV";
            AuraModeShadow.AtmosphericTemporalVariations = AuraMode.AtmosphericTemporalVariations;
            if (AuraStringChanged != null)
                AuraStringChanged(AuraString);
        }

        if (AuraMode.Scattering != AuraModeShadow.Scattering)
        {
            AuraString = AuraMode.Scattering ? "+SC" : "-SC";
            AuraModeShadow.Scattering = AuraMode.Scattering;
            if (AuraStringChanged != null)
                AuraStringChanged(AuraString);
        }

        if (AuraMode.Diffraction != AuraModeShadow.Diffraction)
        {
            AuraString = AuraMode.Diffraction ? "+DIF" : "-DIF";
            AuraModeShadow.Diffraction = AuraMode.Diffraction;
            if (AuraStringChanged != null)
                AuraStringChanged(AuraString);
        }

        if (AuraMode.NearFieldEffects != AuraModeShadow.NearFieldEffects)
        {
            AuraString = AuraMode.NearFieldEffects ? "+NF" : "-NF";
            AuraModeShadow.NearFieldEffects = AuraMode.NearFieldEffects;
            if (AuraStringChanged != null)
                AuraStringChanged(AuraString);
        }

        if (AuraMode.DopplerShifts != AuraModeShadow.DopplerShifts)
        {
            AuraString = AuraMode.DopplerShifts ? "+DP" : "-DP";
            AuraModeShadow.DopplerShifts = AuraMode.DopplerShifts;
            if (AuraStringChanged != null)
                AuraStringChanged(AuraString);
        }

        if (AuraMode.SphericalSpreadingLoss != AuraModeShadow.SphericalSpreadingLoss)
        {
            AuraString = AuraMode.SphericalSpreadingLoss ? "+SL" : "-SL";
            AuraModeShadow.SphericalSpreadingLoss = AuraMode.SphericalSpreadingLoss;
            if (AuraStringChanged != null)
                AuraStringChanged(AuraString);
        }
    }

    public void TriggerAuraStringChanged(string externAuraString)
    {
        if (externAuraString == "+DS") DirectSound = true;
        if (externAuraString == "-DS") DirectSound = false;
        if (externAuraString == "+ER") EarlyReflections = true;
        if (externAuraString == "-ER") EarlyReflections = false;
        if (externAuraString == "+DD") DiffuseDecay = true;
        if (externAuraString == "-DD") DiffuseDecay = false;
        if (externAuraString == "+DIR") SourceDirectivity = true;
        if (externAuraString == "-DIR") SourceDirectivity = false;
        if (externAuraString == "+AA") AirAbsorption = true;
        if (externAuraString == "-AA") AirAbsorption = false;
        if (externAuraString == "+TV") AtmosphericTemporalVariations = true;
        if (externAuraString == "-TV") AtmosphericTemporalVariations = false;
        if (externAuraString == "+SC") Scattering = true;
        if (externAuraString == "-SC") Scattering = false;
        if (externAuraString == "+DIF") Diffraction = true;
        if (externAuraString == "-DIF") Diffraction = false;
        if (externAuraString == "+NF") NearFieldEffects = true;
        if (externAuraString == "-NF") NearFieldEffects = false;
        if (externAuraString == "+DP") DopplerShifts = true;
        if (externAuraString == "-DP") DopplerShifts = false;
        if (externAuraString == "+SL") SphericalSpreadingLoss = true;
        if (externAuraString == "-SL") SphericalSpreadingLoss = false;
        AuraStringChanged(externAuraString);
    }

    protected AuralizationMode UpdateAuraModeSettings()
    {
        AuralizationMode am = new AuralizationMode();
        am.DirectSound = DirectSound;
        am.EarlyReflections = EarlyReflections;
        am.DiffuseDecay = DiffuseDecay;
        am.SourceDirectivity = SourceDirectivity;
        am.AirAbsorption = AirAbsorption;
        am.AtmosphericTemporalVariations = AtmosphericTemporalVariations;
        am.Scattering = Scattering;
        am.Diffraction = Diffraction;
        am.NearFieldEffects = NearFieldEffects;
        am.DopplerShifts = DopplerShifts;
        am.SphericalSpreadingLoss = SphericalSpreadingLoss;
        return am;
    }
}
