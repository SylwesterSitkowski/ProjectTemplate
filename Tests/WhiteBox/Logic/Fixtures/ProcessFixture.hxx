#pragma once

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include "Process.h"
#include "AppFixture.hxx"
#include "SettingsMock.h"

extern "C"
{
    #include "Settings.h"
    #include "Measurements.h"
}

///////////////////////////////////////////////////////////////////////////////
/////////////////////////// MACROS/DEFINITIONS ////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

SHARE_SETTINGS
SHARE_MEASUREMENTS
SHARE_SETTINGS_MOCK

///////////////////////////////////////////////////////////////////////////////
/////////////////////////// CLASSES/STRUCTURES ////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

constexpr bool hasChanged                   (struct Io * const vThis)  { return false; }
uint16_t       convertImpulsesToMilimeteres (const uint32_t vImpulses) { return gSettingsMock.Encoder.Position; }

class ProcessFixture : public AppFixture
{
    protected:
        void SetUp () override
        {
            gSettings.Process.IsThreadInProgress                      = true;

            gSettingsMock.Adc.Voltage                                 = 20000;
            gSettingsMock.Adc.Current                                 = 1800;
            gSettingsMock.Adc.Temperature.Mcu                         = 80;
            gSettingsMock.Adc.Temperature.Bridge                      = 120;
            gSettings.App.Motor.Speed.Pulses.TimeBetween              = 1500;

            gIo.Input.HasChanged                                      = hasChanged;
            gSettings.App.Motor.Position.ConvertImpulsesToMilimeteres = convertImpulsesToMilimeteres;
        }

        void TearDown () override
        {
            gSettings.Process.IsThreadInProgress                                 = false;

            gSettings.Io.Output.IsLed.Red                                        = false;
            gSettings.Io.Output.IsLed.Green                                      = false;
            gSettings.Io.Output.IsLed.Yellow                                     = false;
            gSettings.Io.Output.IsLed.HeartBeat                                  = false;

            gSettings.Io.Input.IsClutch.One                                      = false;
            gSettings.Io.Input.IsDoorClosed                                      = false;
            gSettings.Io.Input.IsLockOut.One                                     = false;
            gSettings.Io.Input.IsZeroVelocityTL                                  = false;
            gSettings.Io.Input.IsClosedPosition.One                              = false;
            gSettings.Io.Input.IsRetractedOrLockedOut                            = false;
            gSettings.Io.Input.IsDoorOpeningAuthorisationTL.One                  = false;
            gSettings.Io.Input.IsDoorOpeningAuthorisationTL.Two                  = false;

            gSettings.Communication.Tcms.IsOperational                           = false;
            gSettings.Communication.Tcms.IsEraseHistOK                           = false;
            gSettings.Communication.Tcms.IsOnDmdTestOK                           = false;
            gSettings.Communication.Tcms.IsParamSetDone                          = false;
            gSettings.Communication.Tcms.IsEncoderFault                          = false;
            gSettings.Communication.Tcms.IsMotorFailure                          = false;
            gSettings.Communication.Tcms.IsOnDmdTestDone                         = false;
            gSettings.Communication.Tcms.IsEraseHistDone                         = false;
            gSettings.Communication.Tcms.IsSensorFailure                         = false;
            gSettings.Communication.Tcms.IsParamSetRsltOK                        = false;
            gSettings.Communication.Tcms.IsEqInMaintenance                       = false;
            gSettings.Communication.Tcms.IsMajorFltPresent                       = false;
            gSettings.Communication.Tcms.IsMinorFltPresent                       = false;
            gSettings.Communication.Tcms.IsInformFltPresent                      = false;
            gSettings.Communication.Tcms.IsParamSetInProgress                    = false;
            gSettings.Communication.Tcms.IsCriticalFltPresent                    = false;
            gSettings.Communication.Tcms.IsOnDmdTestInProgress                   = false;
            gSettings.Communication.Tcms.IsManualModeSensorFailure               = false;
            gSettings.Communication.Tcms.IsMotorFailureInDeployment              = false;
            gSettings.Communication.Tcms.IsRequestToDelayTheDeployment           = false;
            gSettings.Communication.Tcms.IsLockOutPositionSensorFailure          = false;
            gSettings.Communication.Tcms.IsRetractedPositionSensorFailure        = false;

            gSettings.Communication.Tcms.SerialNumber                            = ZERO;
            gSettings.Communication.Tcms.IsOnDmdTestStep                         = ZERO;

            gSettings.Communication.Tcms.Input.IsSetParam                        = false;
            gSettings.Communication.Tcms.Input.IsLockParamSet                    = false;
            gSettings.Communication.Tcms.Input.IsEraseHistory                    = false;
            gSettings.Communication.Tcms.Input.IsMaintModeAuth                   = false;
            gSettings.Communication.Tcms.Input.IsOnDmdTestStart                  = false;
            gSettings.Communication.Tcms.Input.IsTrainDateTimeS                  = false;
            gSettings.Communication.Tcms.Input.IsReprogModeAuth                  = false;
            gSettings.Communication.Tcms.Input.IsTrainOperational                = false;
            gSettings.Communication.Tcms.Input.IsReducedPowerTest                = false;
            gSettings.Communication.Tcms.Input.IsOnDmdTestResume                 = false;
            gSettings.Communication.Tcms.Input.IsClosedAndLockedDoorsState       = false;
            gSettings.Communication.Tcms.Input.IsRetractionControlInhibition     = false;
            gSettings.Communication.Tcms.Input.IsDoorClosedAndLockOutDoorState   = false;

            gSettings.Communication.Tcms.Output.IsOperational                    = false;
            gSettings.Communication.Tcms.Output.IsModuleFault                    = false;
            gSettings.Communication.Tcms.Output.IsLockOutState                   = false;
            gSettings.Communication.Tcms.Output.IsDeployedState                  = false;
            gSettings.Communication.Tcms.Output.IsZeroVelocityTL                 = false;
            gSettings.Communication.Tcms.Output.IsRetractedDefault               = false;
            gSettings.Communication.Tcms.Output.IsDeploymentDefault              = false;
            gSettings.Communication.Tcms.Output.IsManuallyReleased               = false;
            gSettings.Communication.Tcms.Output.IsAccessNotGuaranteed            = false;
            gSettings.Communication.Tcms.Output.IsOpeningAuthorisationTL         = false;
            gSettings.Communication.Tcms.Output.IsRetractedAndLockedState        = false;
            gSettings.Communication.Tcms.Output.IsFailedToDeployBecauseObstacle  = false;
            gSettings.Communication.Tcms.Output.IsFailedToRetractBecauseObstacle = false;

            gSettings.LedSignaling.IsFailure                                     = false;
            gSettings.App.Motor.IsObstacleDetected                               = false;
            gSettings.Communication.Modbus.IsConnected                           = false;

            gSettings.App.Motor.Position.Set                                     = ZERO;
            gSettings.App.Motor.Position.Last                                    = ZERO;
            gSettings.App.Motor.Position.Current                                 = ZERO;

            gSettingsMock.Process.Loop.App.Enable                                = false;
            gSettingsMock.Process.Loop.App.Counter                               = ZERO;
            gSettingsMock.Process.Loop.Measurements.Enable                       = false;
            gSettingsMock.Process.Loop.Measurements.Counter                      = ZERO;

            gSettingsMock.Encoder.Position                                       = ZERO;
            gSettingsMock.Encoder.Direction                                      = ZERO;

            gSettingsMock.Adc.Current                                            = ZERO;
            gSettingsMock.Adc.Voltage                                            = ZERO;
            gSettingsMock.Adc.Temperature.Mcu                                    = ZERO;
            gSettingsMock.Adc.Temperature.Bridge                                 = ZERO;

            gApp.DetectObstaclesDuring.DelayInMs                                 = ONE;
            gApp.DetectObstaclesDuring.ObstaclesNum                              = ZERO;

            memset (&gSettings.SystemMonitor.Params.Diag [ZERO].Data    , ZERO, sizeof (gSettings.SystemMonitor.Params.Diag          [ZERO].Data));
            memset (&gTcmsParserAndSerializer.MsgMaps.Output.Tcms [ZERO], ZERO, sizeof (gTcmsParserAndSerializer.MsgMaps.Output.Tcms [ZERO]));
        }

    public:
        void MeasurementsUpdate (const uint32_t vVoltage, const int16_t vCurrent, const uint16_t vMcuTemp, const uint16_t vBridgeTemp, const uint32_t vTimeBetween, const int16_t vCurrentPosition, const bool vIsObstacleDetected)
        {
            gSettingsMock.Adc.Voltage                    = vVoltage;
            gSettingsMock.Adc.Current                    = vCurrent;
            gSettingsMock.Adc.Temperature.Mcu            = vMcuTemp;
            gSettingsMock.Adc.Temperature.Bridge         = vBridgeTemp;
            gSettings.App.Motor.Speed.Pulses.TimeBetween = vTimeBetween;
            gSettings.App.Motor.Position.Current         = vCurrentPosition;
            gSettings.App.Motor.IsObstacleDetected       = vIsObstacleDetected;
        }
};

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////