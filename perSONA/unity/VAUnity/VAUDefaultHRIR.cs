using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class VAUDefaultHRIR : VAUDirectivity
{   
	// The default HRIR create a HRIR database using the default macro $(DefaultHRIR), which is usually defined in the server configuration"
    VAUDefaultHRIR()
    {
        FilePath = "$(DefaultHRIR)";
        Name = "Default head-related transfer function";
    }
}
