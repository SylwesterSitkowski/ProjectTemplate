///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

extern "C"
{
    #include "App.h"
}

#include "NominalFixture.hxx"

///////////////////////////////////////////////////////////////////////////////
/////////////////////////// MACROS/DEFINITIONS ////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

static const char * Module = "NominalFixture";

SHARE_APP

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// FUNCTIONS ////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

TEST_F (NominalFixture, CheckSwitchingFromEnableToOpen)
{
    gApp.eNominal = eEnable;

    SetNominal        (true);
    Nominal.SetEnable (true);

    gApp.Process      (&gApp);
    EXPECT_EQ         (gApp.eNominal, eOpen);
}

TEST_F (NominalFixture, CheckSwitchingFromOpenToDetectObstaclesDuringOpening)
{
    gApp.eNominal = eOpen;

    SetNominal        (true);
    Nominal.SetEnable (true);
    Nominal.SetOpen   (true);

    gApp.Process      (&gApp);
    EXPECT_EQ         (gApp.eNominal, eDetectObstaclesDuringOpening);
}

TEST_F (NominalFixture, CheckSwitchingFromOpenToDetectObstaclesDuringOpeningWithDelay)
{
    gApp.eNominal = eOpen;

    SetNominal                 (true);
    Nominal.SetEnable          (true);
    Nominal.SetOpen            (true);
    Nominal.SetDelayBeforeOpen (true);

    gApp.Process               (&gApp);
    EXPECT_TRUE                (gSettingsMock.Rtos.IsDelayBeforeOpening);
    EXPECT_EQ                  (gApp.eNominal, eDetectObstaclesDuringOpening);
}

TEST_F (NominalFixture, CheckSwitchingFromDetectObstaclesDuringOpeningToNetworkCommunicationAfterOpen)
{
    gApp.eNominal = eDetectObstaclesDuringOpening;

    SetNominal        (true);
    Nominal.SetEnable (true);

    gApp.DetectObstaclesDuring.eOpening     = eRetract;
    gSettings.App.Motor.Position.Current    = DISTANCE_2 - ONE;
    gApp.DetectObstaclesDuring.DelayInMs    = ZERO;
    gApp.DetectObstaclesDuring.ObstaclesNum = ZERO;

    gApp.Process (&gApp);
    EXPECT_FALSE (gSettings.Io.Relay.IsOne);
    EXPECT_TRUE  (gSettings.Io.Relay.IsTwo);
    EXPECT_EQ    (gApp.DetectObstaclesDuring.ObstaclesNum, ZERO);
    EXPECT_EQ    (gApp.eNominal, eNetworkCommunicationAfterOpen);
}

TEST_F (NominalFixture, CheckSwitchingFromNetworkCommunicationAfterOpenToClose)
{
    gApp.eNominal = eNetworkCommunicationAfterOpen;

    SetNominal        (true);
    Nominal.SetEnable (true);

    gApp.Process      (&gApp);
    EXPECT_EQ         (gApp.eNominal, eClose);
}

TEST_F (NominalFixture, CheckSwitchingFromCloseToDetectObstaclesDuringClosing)
{
    gApp.eNominal = eClose;

    SetNominal        (true);
    Nominal.SetEnable (true);
    Nominal.SetClose  (true);

    gApp.Process      (&gApp);
    EXPECT_EQ         (gApp.eNominal, eDetectObstaclesDuringClosing);
}

TEST_F (NominalFixture, CheckSwitchingFromDetectObstaclesDuringClosingToNetworkCommunicationAfterClose)
{
    gApp.eNominal                           = eDetectObstaclesDuringClosing;
    gApp.DetectObstaclesDuring.eOpening     = eDeploy;
    gSettings.Io.Input.IsClosedPosition.One = true;

    SetNominal        (true);
    Nominal.SetEnable (true);

    gApp.Process (&gApp);
    gApp.Process (&gApp);
    EXPECT_FALSE (gSettings.Io.Relay.IsOne);
    EXPECT_FALSE (gSettings.Io.Relay.IsTwo);
    EXPECT_EQ    (gApp.DetectObstaclesDuring.ObstaclesNum, ZERO);
    EXPECT_EQ    (gApp.eNominal, eNetworkCommunicationAfterClose);
}

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

