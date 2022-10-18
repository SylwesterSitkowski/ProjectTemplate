#pragma once

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include "AppFixture.hxx"
#include "SettingsMock.h"

extern "C"
{
    #include "Settings.h"
}

///////////////////////////////////////////////////////////////////////////////
/////////////////////////// MACROS/DEFINITIONS ////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

SHARE_SETTINGS
SHARE_SETTINGS_MOCK

///////////////////////////////////////////////////////////////////////////////
/////////////////////////// CLASSES/STRUCTURES ////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

class NominalFixture : public AppFixture
{
    protected:
        void SetUp    () override { }
        void TearDown () override
        {
            gSettings.Io.Relay.IsOne                                             = false;
            gSettings.Io.Relay.IsTwo                                             = false;
            gSettings.Io.Input.IsClutch.One                                      = false;
            gSettings.Io.Input.IsLockOut.One                                     = false;

            gSettings.Io.Input.IsDoorClosed                                      = false;
            gSettings.Io.Input.IsZeroVelocityTL                                  = false;
            gSettings.Io.Input.IsClosedPosition.One                              = false;
            gSettings.Io.Input.IsDoorOpeningAuthorisationTL.One                  = false;
            gSettings.Io.Input.IsDoorOpeningAuthorisationTL.Two                  = false;

            gSettings.Communication.Tcms.Input.IsClosedAndLockedDoorsState       = false;
            gSettings.Communication.Tcms.Input.IsDoorClosedAndLockOutDoorState   = false;

            gSettings.Communication.Tcms.Output.IsLockOutState                   = false;
            gSettings.Communication.Tcms.Output.IsManuallyReleased               = false;
            gSettings.Communication.Tcms.Output.IsRetractedDefault               = false;
            gSettings.Communication.Tcms.Output.IsDeploymentDefault              = false;
            gSettings.Communication.Tcms.Output.IsAccessNotGuaranteed            = false;
            gSettings.Communication.Tcms.Output.IsFailedToDeployBecauseObstacle  = false;
            gSettings.Communication.Tcms.Output.IsFailedToRetractBecauseObstacle = false;

            gSettings.App.Motor.Position.Current                                 = ZERO;
            gSettingsMock.Rtos.IsDelayBeforeOpening                              = false;
        }
};

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////