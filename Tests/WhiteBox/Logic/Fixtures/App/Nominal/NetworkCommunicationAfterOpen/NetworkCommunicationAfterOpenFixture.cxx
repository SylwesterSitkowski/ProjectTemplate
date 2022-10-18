///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include "NetworkCommunicationAfterOpenFixture.hxx"

///////////////////////////////////////////////////////////////////////////////
/////////////////////////// MACROS/DEFINITIONS ////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

static const char * Module = "NetworkCommunicationAfterOpenFixture";

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// FUNCTIONS ////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

TEST_F (NetworkCommunicationAfterOpenFixture, CheckTcmsSettingsWhenObstacleDetectedInDistance2)
{
    gSettings.App.Motor.Position.Current                                = DISTANCE_1 + ONE;
    gSettings.Communication.Tcms.Output.IsFailedToDeployBecauseObstacle = true;

    gApp.NetworkCommunicationAfter.Open (&gApp);
    EXPECT_TRUE  (gSettings.Communication.Tcms.Output.IsDeployedState);
    EXPECT_FALSE (gSettings.Communication.Tcms.Output.IsFailedToDeployBecauseObstacle);
}

TEST_F (NetworkCommunicationAfterOpenFixture, CheckTcmsSettingsWhenObstacleDetectedInDistance1)
{
    gSettings.App.Motor.Position.Current = DISTANCE_1;

    gApp.NetworkCommunicationAfter.Open (&gApp);
    EXPECT_TRUE  (gSettings.Communication.Tcms.Output.IsFailedToDeployBecauseObstacle);
}

TEST_F (NetworkCommunicationAfterOpenFixture, CheckTcmsSettingsAfterCrossingObstacles)
{
    gApp.DetectObstaclesDuring.ObstaclesNum = DEPLOYMENT_ATTEMPTS + ONE;

    gApp.NetworkCommunicationAfter.Open (&gApp);
    EXPECT_TRUE (gSettings.Communication.Tcms.Output.IsFailedToDeployBecauseObstacle);
}

TEST_F (NetworkCommunicationAfterOpenFixture, CheckTcmsSettingsWhenObstacleDetectedInDistance3)
{
    gSettings.App.Motor.Position.Current = DISTANCE_2 + ONE;

    gApp.NetworkCommunicationAfter.Open (&gApp);
    EXPECT_TRUE (gSettings.Communication.Tcms.Output.IsAccessNotGuaranteed);
}

TEST_F (NetworkCommunicationAfterOpenFixture, CheckTcmsSettingsWhenObstacleDetectedOutsideDistance1)
{
    gSettings.App.Motor.Position.Current = DISTANCE_1;

    gApp.NetworkCommunicationAfter.Open (&gApp);
    EXPECT_TRUE (gSettings.Communication.Tcms.Output.IsDeploymentDefault);
}

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////