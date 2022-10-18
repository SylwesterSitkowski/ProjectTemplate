///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include "NetworkCommunicationAfterCloseFixture.hxx"

///////////////////////////////////////////////////////////////////////////////
/////////////////////////// MACROS/DEFINITIONS ////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

static const char * Module = "NetworkCommunicationAfterCloseFixture";

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// FUNCTIONS ////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

TEST_F (NetworkCommunicationAfterCloseFixture, CheckTcmsSettingsWhenRetractedOrLockOut)
{
    gSettings.Io.Input.IsRetractedOrLockedOut = true;

    gApp.NetworkCommunicationAfter.Close (&gApp);
    EXPECT_TRUE (gSettings.Communication.Tcms.IsRetractedOrLockOutState);
}

TEST_F (NetworkCommunicationAfterCloseFixture, CheckTcmsSettingsWhenRetractedOrLockOutAndRetarctedDefault)
{
    gSettings.Io.Input.IsRetractedOrLockedOut              = true;
    gSettings.Communication.Tcms.Output.IsRetractedDefault = false;

    gApp.NetworkCommunicationAfter.Close (&gApp);
    EXPECT_TRUE (gSettings.Communication.Tcms.IsRetractedOrLockOutState);
    EXPECT_TRUE (gSettings.Communication.Tcms.Output.IsRetractedAndLockedState);
}

TEST_F (NetworkCommunicationAfterCloseFixture, CheckTcmsSettingsWhenNotRetractedOrLockOut)
{
    gSettings.Io.Input.IsRetractedOrLockedOut = false;

    gApp.NetworkCommunicationAfter.Close (&gApp);
    EXPECT_TRUE (gSettings.Communication.Tcms.Output.IsRetractedDefault);
}

TEST_F (NetworkCommunicationAfterCloseFixture, CheckTcmsSettingsAfterCrossingTheObstacles)
{
    gApp.DetectObstaclesDuring.ObstaclesNum = RETRACTION_ATTEMPTS + ONE;

    gApp.NetworkCommunicationAfter.Close (&gApp);
    EXPECT_TRUE (gSettings.Communication.Tcms.Output.IsFailedToDeployBecauseObstacle);
}

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////