///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include "ProcessFixture.hxx"

///////////////////////////////////////////////////////////////////////////////
/////////////////////////// MACROS/DEFINITIONS ////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

static const char * Module= "ProcessFixture";

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// FUNCTIONS ////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

TEST_F (ProcessFixture, CheckEntryIntoManualMode)
{
    gSettingsMock.Process.Loop.App.Enable  = true;
    gSettingsMock.Process.Loop.App.Counter = ONE;

    SetManual    (true);
    Process      ();

    EXPECT_EQ    (gApp.GetState (), eManual);
    EXPECT_TRUE  (gSettings.Communication.Tcms.Output.IsManuallyReleased);
}

TEST_F (ProcessFixture, CheckEntryIntoLockOutMode)
{
    gSettingsMock.Process.Loop.App.Enable                                = true;
    gSettingsMock.Process.Loop.App.Counter                               = ONE;
    gSettings.Communication.Tcms.Output.IsLockOutState                   = false;
    gSettings.Communication.Tcms.Output.IsRetractedDefault               = true;
    gSettings.Communication.Tcms.Output.IsDeploymentDefault              = true;
    gSettings.Communication.Tcms.Output.IsAccessNotGuaranteed            = false;
    gSettings.Communication.Tcms.Output.IsFailedToDeployBecauseObstacle  = true;
    gSettings.Communication.Tcms.Output.IsFailedToRetractBecauseObstacle = true;

    SetLockOut   (true);
    Process      ();

    EXPECT_EQ    (gApp.GetState (), eLockOut);
    EXPECT_TRUE  (gSettings.Communication.Tcms.Output.IsLockOutState);
    EXPECT_FALSE (gSettings.Communication.Tcms.Output.IsRetractedDefault);
    EXPECT_FALSE (gSettings.Communication.Tcms.Output.IsDeploymentDefault);
    EXPECT_TRUE  (gSettings.Communication.Tcms.Output.IsAccessNotGuaranteed);
    EXPECT_FALSE (gSettings.Communication.Tcms.Output.IsFailedToDeployBecauseObstacle);
    EXPECT_FALSE (gSettings.Communication.Tcms.Output.IsFailedToRetractBecauseObstacle);
}

TEST_F (ProcessFixture, CheckThatOpeningEndWithFoldBackWhenObstacleDetectedAbovedOrEqualDistance1AndBelowDistance2)
{
    gSettingsMock.Process.Loop.App.Enable  = true;
    gSettingsMock.Process.Loop.App.Counter = TEN;
    gSettingsMock.Encoder.Position         = DISTANCE_1 + FOLDBACK_LENGTH;
    gSettings.App.Motor.IsObstacleDetected = true;

    SetNominal        (true);
    Nominal.SetEnable (true);
    Nominal.SetOpen   (true);
    Process           ();

    EXPECT_EQ         (gApp.DetectObstaclesDuring.eOpening, eDelay);
    EXPECT_EQ         (gApp.DetectObstaclesDuring.ObstaclesNum, ZERO);
}

TEST_F (ProcessFixture, CheckMeasurementsControl)    // todo sylsit intention was to show extended tests possibilities (testing app algorithm with measurements simulation)
{
    SetNominal        (true);
    Nominal.SetEnable (true);
    Nominal.SetOpen   (true);

    for (uint16_t loopNum = ZERO; loopNum < ONE_HUNDRED; loopNum++)
    {
        MeasurementsUpdate    (TWO_HUNDRED * loopNum, TWENTY * loopNum, loopNum, ONE_HUNDRED - loopNum, 1500 - FIFTEEN * loopNum, 0.5* loopNum, false);
        gApp         .Process (&gApp);
        gMeasurements.Process (&gMeasurements);
    }
}

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////