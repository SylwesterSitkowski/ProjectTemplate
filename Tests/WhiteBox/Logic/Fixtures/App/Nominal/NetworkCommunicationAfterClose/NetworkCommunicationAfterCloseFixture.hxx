#pragma once

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include "AppFixture.hxx"

extern "C"
{
    #include "App.h"
    #include "Settings.h"
}

///////////////////////////////////////////////////////////////////////////////
/////////////////////////// MACROS/DEFINITIONS ////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

SHARE_APP
SHARE_SETTINGS

///////////////////////////////////////////////////////////////////////////////
/////////////////////////// CLASSES/STRUCTURES ////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

class NetworkCommunicationAfterCloseFixture : public AppFixture
{
    protected:
        void SetUp    () override { }
        void TearDown () override
        {
            gSettings.Io.Input.IsRetractedOrLockedOut              = false;
            gSettings.Communication.Tcms.Output.IsRetractedDefault = false;

            gApp.DetectObstaclesDuring.ObstaclesNum                = ZERO;
        }
};

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////