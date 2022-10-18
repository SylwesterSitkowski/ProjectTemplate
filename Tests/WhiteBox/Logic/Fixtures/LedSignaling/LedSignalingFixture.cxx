///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

extern "C"
{
    #include "Utils.h"
    #include "Logger.h"
    #include "LedSignaling.h"
}

#include <gtest/gtest.h>
#include "LedSignalingFixture.hxx"

///////////////////////////////////////////////////////////////////////////////
/////////////////////////// MACROS/DEFINITIONS ////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

static const char * Module = "LedSignalingFixture";

SHARE_LOGGER
SHARE_LED_SIGNALING

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// FUNCTIONS ////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

TEST_F (LedSignalingFixture, CheckIfStateTriggerWorking)
{
    for (auto triggerNum : {ZERO, ONE, TWO, THREE})
    {
        for (auto falseNum : { ZERO, ONE, TWO }) { EXPECT_FALSE (gLedSignaling.Timer.IsLedOn ()); }
        for (auto trueNum  : { ZERO, ONE, TWO }) { EXPECT_TRUE  (gLedSignaling.Timer.IsLedOn ()); }
    }
}

TEST_F (LedSignalingFixture, CheckIfTheRedLedIsSetAndClear)
{
    gSettings.Io.Output.IsLed.Red = false;
    gLedSignaling.TurnLed (eRed, true);
    EXPECT_TRUE           (gSettings.Io.Output.IsLed.Red);

    gSettings.Io.Output.IsLed.Red = true;
    gLedSignaling.TurnLed (eRed, false);
    EXPECT_FALSE          (gSettings.Io.Output.IsLed.Red);
}

TEST_F (LedSignalingFixture, CheckIfTheGreenLedIsSetAndClear)
{
    gSettings.Io.Output.IsLed.Green = false;
    gLedSignaling.TurnLed (eGreen, true);
    EXPECT_TRUE           (gSettings.Io.Output.IsLed.Green);

    gSettings.Io.Output.IsLed.Green = true;
    gLedSignaling.TurnLed (eGreen, false);
    EXPECT_FALSE          (gSettings.Io.Output.IsLed.Green);
}

TEST_F (LedSignalingFixture, CheckIfTheYellowLedIsSetAndClear)
{
    gSettings.Io.Output.IsLed.Yellow = false;
    gLedSignaling.TurnLed (eYellow, true);
    EXPECT_TRUE           (gSettings.Io.Output.IsLed.Yellow);

    gSettings.Io.Output.IsLed.Yellow = true;
    gLedSignaling.TurnLed (eYellow, false);
    EXPECT_FALSE          (gSettings.Io.Output.IsLed.Yellow);
}

TEST_F (LedSignalingFixture, CheckIfLedYellowOffAndGreenBlinkingDuringModeNominal)
{
    gSettings.App.eApp = eNominal;

    for (auto triggerNum : { ZERO, ONE, TWO, THREE, FOUR, FIVE })
    {
        gLedSignaling.Process (&gLedSignaling);
        EXPECT_TRUE           (gSettings.Io.Output.IsLed.Yellow);

        if (triggerNum < THREE) { EXPECT_FALSE (gSettings.Io.Output.IsLed.Green); }
        else                    { EXPECT_TRUE  (gSettings.Io.Output.IsLed.Green); }
    }
}

TEST_F (LedSignalingFixture, CheckIfLedsYellowIsSolidAndGreenBlinkingDuringModeLockOut)
{
    gSettings.App.eApp = eLockOut;

    for (auto triggerNum : { ZERO, ONE, TWO, THREE, FOUR, FIVE })
    {
        gLedSignaling.Process (&gLedSignaling);
        EXPECT_FALSE           (gSettings.Io.Output.IsLed.Yellow);

        if (triggerNum < THREE) { EXPECT_FALSE (gSettings.Io.Output.IsLed.Green); }
        else                    { EXPECT_TRUE  (gSettings.Io.Output.IsLed.Green); }
    }
}

TEST_F (LedSignalingFixture, CheckIfLedsYellowAndGreenBothBlinkingDuringModeManual)
{
    gSettings.App.eApp = eManual;

    for (auto triggerNum : { ZERO, ONE, TWO, THREE, FOUR, FIVE })
    {
        gLedSignaling.Process (&gLedSignaling);

        if (triggerNum < THREE)
        {
            EXPECT_FALSE (gSettings.Io.Output.IsLed.Green);
            EXPECT_FALSE (gSettings.Io.Output.IsLed.Yellow);
        }
        else
        {
            EXPECT_TRUE (gSettings.Io.Output.IsLed.Green);
            EXPECT_TRUE (gSettings.Io.Output.IsLed.Yellow);
        }
    }
}

TEST_F (LedSignalingFixture, CheckIfLedRedIsBlinkingDuringFailureInNormalMode)
{
    gSettings.App.eApp               = eManual;
    gSettings.LedSignaling.IsFailure = true;

    for (auto triggerNum : { ZERO, ONE, TWO, THREE, FOUR, FIVE })
    {
        gLedSignaling.Process (&gLedSignaling);

        if (triggerNum < THREE) { EXPECT_FALSE (gSettings.Io.Output.IsLed.Red); }
        else                    { EXPECT_TRUE  (gSettings.Io.Output.IsLed.Red); }
    }
}

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

