///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include "DetectObstaclesDuringOpeningFixture.hxx"

///////////////////////////////////////////////////////////////////////////////
/////////////////////////// MACROS/DEFINITIONS ////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

static const char * Module = "DetectObstaclesDuringOpeningFixture";

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// FUNCTIONS ////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

// todo sylsit
// There is lack of test case for crossing timeout during obstacles detection

TEST_F (DetectObstaclesDuringOpeningFixture, CheckSwitchingFromDelayToDeployDuringOpening)
{
    gApp.DetectObstaclesDuring.eOpening = eDelay;

    gApp.DetectObstaclesDuring.IsOpening (&gApp);
    EXPECT_EQ                            (gApp.DetectObstaclesDuring.eOpening, eDeploy);
}

TEST_F (DetectObstaclesDuringOpeningFixture, CheckStopRetractionAfterAchievingStartPosition)
{
    gSettings.App.Motor.Position.Set     = ONE;
    gApp.DetectObstaclesDuring.eOpening  = eDeploy;
    gSettings.App.Motor.Position.Current = DISTANCE_2;

    gApp.DetectObstaclesDuring.IsOpening (&gApp);
    EXPECT_EQ                            (gApp.DetectObstaclesDuring.DelayInMs, ZERO);
    EXPECT_EQ                            (gApp.DetectObstaclesDuring.eOpening , eRetract);
    EXPECT_EQ                            (gSettings.App.Motor.Position.Set    , DISTANCE_0);
}

TEST_F (DetectObstaclesDuringOpeningFixture, CheckTheReturnToDelayWhenObstacleNotDetected)
{
    gSettings.App.Motor.Position.Set     = ONE;
    gApp.DetectObstaclesDuring.eOpening  = eDeploy;
    gSettings.App.Motor.Position.Current = DISTANCE_1;

    gApp.DetectObstaclesDuring.IsOpening (&gApp);
    EXPECT_EQ                            (gApp.DetectObstaclesDuring.eOpening , eDelay);
}

TEST_F (DetectObstaclesDuringOpeningFixture, CheckTheRetractionToTheStartWhenObstacleDetectedBelowOrEqualDeplWithdrawLength)
{
    gApp.DetectObstaclesDuring.eOpening    = eDeploy;
    gSettings.App.Motor.Position.Current   = DEPL_WITHDRAW_LENGTH;
    gSettings.App.Motor.IsObstacleDetected = true;

    gApp.DetectObstaclesDuring.IsOpening (&gApp);
    EXPECT_EQ                            (gSettings.App.Motor.Position.Set       , DISTANCE_0);
    EXPECT_EQ                            (gApp.DetectObstaclesDuring.eOpening    , eRetract);
    EXPECT_EQ                            (gApp.DetectObstaclesDuring.DelayInMs   , TIME_UNTIL_REDEPLOYMENT);
    EXPECT_EQ                            (gApp.DetectObstaclesDuring.ObstaclesNum, ONE);
}

TEST_F (DetectObstaclesDuringOpeningFixture, CheckTheRetractionWhenObstacleDetectedAbovedDeplWithdrawLengthAndBelowDistance1PlusFoldBackLength)
{
    gApp.DetectObstaclesDuring.eOpening    = eDeploy;
    gSettings.App.Motor.Position.Current   = DISTANCE_1 + FOLDBACK_LENGTH - ONE;
    gSettings.App.Motor.IsObstacleDetected = true;

    gApp.DetectObstaclesDuring.IsOpening (&gApp);
    EXPECT_EQ                            (gSettings.App.Motor.Position.Set       , gSettings.App.Motor.Position.Current - DEPL_WITHDRAW_LENGTH);
    EXPECT_EQ                            (gApp.DetectObstaclesDuring.eOpening    , eRetract);
    EXPECT_EQ                            (gApp.DetectObstaclesDuring.DelayInMs   , TIME_UNTIL_REDEPLOYMENT);
    EXPECT_EQ                            (gApp.DetectObstaclesDuring.ObstaclesNum, ONE);
}

TEST_F (DetectObstaclesDuringOpeningFixture, CheckTheRetractionWhenObstacleDetectedAbovedDistance1PlusFoldBackLength)
{
    gApp.DetectObstaclesDuring.eOpening    = eDeploy;
    gSettings.App.Motor.Position.Current   = DISTANCE_1 + FOLDBACK_LENGTH;
    gSettings.App.Motor.IsObstacleDetected = true;

    gApp.DetectObstaclesDuring.IsOpening (&gApp);
    EXPECT_EQ                            (gSettings.App.Motor.Position.Set       , gSettings.App.Motor.Position.Current - FOLDBACK_LENGTH);
    EXPECT_EQ                            (gApp.DetectObstaclesDuring.eOpening    , eRetract);
    EXPECT_EQ                            (gApp.DetectObstaclesDuring.DelayInMs   , ZERO);
    EXPECT_EQ                            (gApp.DetectObstaclesDuring.ObstaclesNum, ONE);
}

TEST_F (DetectObstaclesDuringOpeningFixture, CheckThatOpeningEndWhenObstacleNotDetected)
{
    gSettings.App.Motor.Position.Current   = DISTANCE_1 + FOLDBACK_LENGTH - ONE;
    gApp.DetectObstaclesDuring.eOpening    = eDeploy;
    gSettings.App.Motor.IsObstacleDetected = true;

    for (uint8_t loopNum = ZERO; loopNum < SEVEN; loopNum++)
    {
         EXPECT_FALSE (gApp.DetectObstaclesDuring.IsOpening (&gApp));
    }

    EXPECT_TRUE (gApp.DetectObstaclesDuring.IsOpening (&gApp));
    EXPECT_EQ   (gApp.DetectObstaclesDuring.eOpening, eDelay);
    EXPECT_EQ   (gApp.DetectObstaclesDuring.ObstaclesNum, THREE);
}

TEST_F (DetectObstaclesDuringOpeningFixture, CheckThatOpeningEndWithFoldBackWhenObstacleDetectedAbovedOrEqualDistance1AndBelowDistance2)
{
    gSettings.App.Motor.Position.Current   = DISTANCE_1 + FOLDBACK_LENGTH;
    gApp.DetectObstaclesDuring.eOpening    = eDeploy;
    gSettings.App.Motor.IsObstacleDetected = true;

    EXPECT_FALSE (gApp.DetectObstaclesDuring.IsOpening (&gApp));
    EXPECT_TRUE  (gApp.DetectObstaclesDuring.IsOpening (&gApp));
    EXPECT_EQ    (gApp.DetectObstaclesDuring.eOpening, eDelay);
    EXPECT_EQ    (gApp.DetectObstaclesDuring.ObstaclesNum, ONE);
}

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

