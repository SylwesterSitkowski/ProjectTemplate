#pragma once

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include <string.h>
#include <gtest/gtest.h>
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

class AppFixture : public ::testing::Test
{
    protected:
        void SetUp    () override { }
        void TearDown () override
        {
            gSettings.Communication.Modbus.IsConnected                           = false;
            gSettings.Communication.Tcms.Output.IsLockOutState                   = false;
            gSettings.Communication.Tcms.Output.IsManuallyReleased               = false;
            gSettings.Communication.Tcms.Output.IsRetractedDefault               = false;
            gSettings.Communication.Tcms.Output.IsDeploymentDefault              = false;
            gSettings.Communication.Tcms.Output.IsAccessNotGuaranteed            = false;
            gSettings.Communication.Tcms.Output.IsFailedToDeployBecauseObstacle  = false;
            gSettings.Communication.Tcms.Output.IsFailedToRetractBecauseObstacle = false;

            gSettings.Communication.Tcms.IsRequestToDelayTheDeployment           = false;
            gSettings.Communication.Tcms.Input.IsClosedAndLockedDoorsState       = false;
            gSettings.Communication.Tcms.Input.IsRetractionControlInhibition     = false;
            gSettings.Communication.Tcms.Input.IsDoorClosedAndLockOutDoorState   = false;

            gSettings.Io.Input.IsClutch.One                                      = false;
            gSettings.Io.Input.IsDoorClosed                                      = false;
            gSettings.Io.Input.IsLockOut.One                                     = false;
            gSettings.Io.Input.IsZeroVelocityTL                                  = false;
            gSettings.Io.Input.IsClosedPosition.One                              = false;
            gSettings.Io.Input.IsDoorOpeningAuthorisationTL.One                  = false;
            gSettings.Io.Input.IsDoorOpeningAuthorisationTL.Two                  = false;
        }

    public:
        struct
        {
            constexpr void SetOpen (const bool vIsEnabled)
            {
                gSettings.Io.Input.IsDoorClosed                                    = vIsEnabled;
                gSettings.Io.Input.IsDoorOpeningAuthorisationTL.One                = vIsEnabled;
                gSettings.Io.Input.IsDoorOpeningAuthorisationTL.Two                = vIsEnabled;
                gSettings.Communication.Tcms.Input.IsClosedAndLockedDoorsState     = vIsEnabled;
                gSettings.Communication.Tcms.Input.IsDoorClosedAndLockOutDoorState = vIsEnabled;
            }

            constexpr void SetClose (const bool vIsEnabled)
            {
                gSettings.Io.Input.IsDoorOpeningAuthorisationTL.One              = false;
                gSettings.Io.Input.IsDoorOpeningAuthorisationTL.Two              = false;
                gSettings.Communication.Tcms.Input.IsRetractionControlInhibition = false;

                if (vIsEnabled == true) { gSettings.Io.Input.IsDoorClosed = true;  }
                else                    { gSettings.Io.Input.IsDoorClosed = false; }
            }

            constexpr void SetEnable (const bool vIsEnabled)
            {
                gSettings.Io.Input.IsDoorClosed                     = vIsEnabled;
                gSettings.Io.Input.IsZeroVelocityTL                 = vIsEnabled;
                gSettings.Io.Input.IsDoorOpeningAuthorisationTL.One = vIsEnabled;
                gSettings.Io.Input.IsDoorOpeningAuthorisationTL.Two = vIsEnabled;
            }

            constexpr void SetDelayBeforeOpen (const bool vIsEnabled)
            {
                gSettings.Communication.Modbus.IsConnected                 = vIsEnabled;
                gSettings.Communication.Tcms.IsRequestToDelayTheDeployment = vIsEnabled;
            }
        } Nominal;

        constexpr void SetNominal (const bool vIsEnabled)
        {
            gSettings.Io.Input.IsLockOut.One = false;

            if (vIsEnabled) { gSettings.Io.Input.IsClutch.One = true;  }
            else            { gSettings.Io.Input.IsClutch.One = false; }
        }

        constexpr void SetManual (const bool vIsEnabled)
        {
            gSettings.Io.Input.IsClutch.One  = !vIsEnabled;
            gSettings.Io.Input.IsLockOut.One = !vIsEnabled;
        }

        constexpr void SetLockOut (const bool vIsEnabled)
        {
            gSettings.Io.Input.IsClutch.One         = vIsEnabled;
            gSettings.Io.Input.IsLockOut.One        = vIsEnabled;
            gSettings.Io.Input.IsClosedPosition.One = vIsEnabled;
        }
};

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////