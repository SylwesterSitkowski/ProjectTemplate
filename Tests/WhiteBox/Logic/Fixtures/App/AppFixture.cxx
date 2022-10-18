///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

extern "C"
{
    #include "App.h"
    #include "Utils.h"
}

#include "AppFixture.hxx"

///////////////////////////////////////////////////////////////////////////////
/////////////////////////// MACROS/DEFINITIONS ////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

static const char * Module = "AppFixture";

SHARE_APP

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// FUNCTIONS ////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

TEST_F (AppFixture, CheckEntryIntoManualMode)
{
    SetManual    (true);
    gApp.Process (&gApp);

    EXPECT_EQ    (gApp.GetState (), eManual);
    EXPECT_TRUE  (gSettings.Communication.Tcms.Output.IsManuallyReleased);
}

TEST_F (AppFixture, CheckEntryIntoLockOutMode)
{
    gSettings.Communication.Tcms.Output.IsLockOutState                   = false;
    gSettings.Communication.Tcms.Output.IsRetractedDefault               = true;
    gSettings.Communication.Tcms.Output.IsDeploymentDefault              = true;
    gSettings.Communication.Tcms.Output.IsAccessNotGuaranteed            = false;
    gSettings.Communication.Tcms.Output.IsFailedToDeployBecauseObstacle  = true;
    gSettings.Communication.Tcms.Output.IsFailedToRetractBecauseObstacle = true;

    SetLockOut   (true);
    gApp.Process (&gApp);

    EXPECT_EQ    (gApp.GetState (), eLockOut);
    EXPECT_TRUE  (gSettings.Communication.Tcms.Output.IsLockOutState);
    EXPECT_FALSE (gSettings.Communication.Tcms.Output.IsRetractedDefault);
    EXPECT_FALSE (gSettings.Communication.Tcms.Output.IsDeploymentDefault);
    EXPECT_TRUE  (gSettings.Communication.Tcms.Output.IsAccessNotGuaranteed);
    EXPECT_FALSE (gSettings.Communication.Tcms.Output.IsFailedToDeployBecauseObstacle);
    EXPECT_FALSE (gSettings.Communication.Tcms.Output.IsFailedToRetractBecauseObstacle);
}

TEST_F (AppFixture, CheckEntryIntoNominalMode)
{
    SetNominal (true);
    EXPECT_EQ  (gApp.GetState (), eNominal);
}

TEST_F (AppFixture, CheckEntryIntoUnknownMode)
{
    gSettings.Io.Input.IsLockOut.One        = true;
    gSettings.Io.Input.IsClosedPosition.One = false;

    EXPECT_EQ (gApp.GetState (), eUnknown);
}

TEST_F (AppFixture, CheckBackToEnableModeAtNonZeroSpeed)
{
    gApp.eNominal                          = eDetectObstaclesDuringOpening;
    gApp.DetectObstaclesDuring.eOpening    = eDeploy;
    gSettings.Io.Input.IsZeroVelocityTL    = false;
    gSettings.App.Motor.IsObstacleDetected = false;

    SetNominal   (true);
    gApp.Process (&gApp);
    EXPECT_EQ    (gApp.eNominal, eEnable);
}

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////