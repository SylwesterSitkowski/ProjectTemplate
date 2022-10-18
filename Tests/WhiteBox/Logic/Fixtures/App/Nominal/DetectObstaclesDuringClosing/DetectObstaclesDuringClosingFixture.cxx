///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include "DetectObstaclesDuringClosingFixture.hxx"

///////////////////////////////////////////////////////////////////////////////
/////////////////////////// MACROS/DEFINITIONS ////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

static const char * Module = "DetectObstaclesDuringClosingFixture";

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// FUNCTIONS ////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

// todo sylsit
// There is lack of test case for crossing timeout during obstacles detection

TEST_F (DetectObstaclesDuringClosingFixture, CheckSwitchingFromDelayToRetractDuringClosing)
{
    gApp.DetectObstaclesDuring.eClosing  = eDelay;
    gSettings.App.Motor.Position.Current = TEN;

    gApp.DetectObstaclesDuring.IsClosing (&gApp);

    EXPECT_EQ (gApp.DetectObstaclesDuring.eClosing, eRetract);
    EXPECT_EQ (gSettings.App.Motor.Position.Current, gSettings.App.Motor.Position.Last);
}

TEST_F (DetectObstaclesDuringClosingFixture, CheckStopClosingAfterRetractionToStartPosition)
{
    gApp.DetectObstaclesDuring.eClosing     = eDelay;
    gSettings.App.Motor.Position.Current    = TEN;
    gSettings.Io.Input.IsClosedPosition.One = true;

    gApp.DetectObstaclesDuring.IsClosing (&gApp);

    EXPECT_TRUE (gApp.DetectObstaclesDuring.IsClosing (&gApp));
    EXPECT_EQ   (gApp.DetectObstaclesDuring.eClosing, eDelay);
    EXPECT_EQ   (gSettings.App.Motor.Position.Current, gSettings.App.Motor.Position.Last);
}

TEST_F (DetectObstaclesDuringClosingFixture, CheckForContinuationOfRetractionWhenObstacleIsNotDetected)
{
    gApp.DetectObstaclesDuring.eClosing  = eDelay;
    gSettings.App.Motor.Position.Current = TEN;

    for (uint8_t loopNum = ZERO; loopNum < TWO; loopNum++)
    {
        gApp.DetectObstaclesDuring.IsClosing (&gApp);
    }

    EXPECT_EQ (gApp.DetectObstaclesDuring.eClosing, eRetract);
    EXPECT_EQ (gSettings.App.Motor.Position.Current, gSettings.App.Motor.Position.Last);
}
TEST_F (DetectObstaclesDuringClosingFixture, CheckDeploymentWhenObstacleDetectedInPositionLongerOrEqualThanRetrWithdrawLength)
{
    gSettings.App.Motor.Position.Last      = DISTANCE_2;
    gApp.DetectObstaclesDuring.eClosing    = eRetract;
    gSettings.App.Motor.Position.Current   = ZERO;
    gSettings.App.Motor.IsObstacleDetected = true;

    gApp.DetectObstaclesDuring.IsClosing (&gApp);
    EXPECT_EQ (gApp.DetectObstaclesDuring.eClosing, eDeploy);
    EXPECT_EQ (gApp.DetectObstaclesDuring.DelayInMs, TIME_UNTIL_RERETRACTION);
    EXPECT_EQ (gSettings.App.Motor.Position.Set, gSettings.App.Motor.Position.Current + RETR_WITHDRAW_LENGTH);
}

TEST_F (DetectObstaclesDuringClosingFixture, CheckDeploymentWhenObstacleDetectedInPositionShorterThanRetrWithdrawLength)
{
    gSettings.App.Motor.Position.Last      = DISTANCE_2;
    gApp.DetectObstaclesDuring.eClosing    = eRetract;
    gSettings.App.Motor.Position.Current   = DISTANCE_2 - ONE;
    gSettings.App.Motor.IsObstacleDetected = true;

    gApp.DetectObstaclesDuring.IsClosing (&gApp);
    EXPECT_EQ (gApp.DetectObstaclesDuring.eClosing, eDeploy);
    EXPECT_EQ (gApp.DetectObstaclesDuring.DelayInMs, TIME_UNTIL_RERETRACTION);
    EXPECT_EQ (gSettings.App.Motor.Position.Set, gSettings.App.Motor.Position.Last);
}

TEST_F (DetectObstaclesDuringClosingFixture, CheckClosingStopAfterExceedingRetractAttempts)
{
    gSettings.App.Motor.Position.Last      = DISTANCE_2;
    gApp.DetectObstaclesDuring.eClosing    = eRetract;
    gSettings.App.Motor.Position.Current   = DISTANCE_2 - ONE;
    gSettings.App.Motor.IsObstacleDetected = true;

    for (uint8_t loopNum = ZERO; loopNum < TEN; loopNum++)
    {
        gApp.DetectObstaclesDuring.IsClosing (&gApp);
    }

    EXPECT_TRUE (gApp.DetectObstaclesDuring.IsClosing (&gApp));
    EXPECT_EQ   (gApp.DetectObstaclesDuring.eClosing, eDelay);
}

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

