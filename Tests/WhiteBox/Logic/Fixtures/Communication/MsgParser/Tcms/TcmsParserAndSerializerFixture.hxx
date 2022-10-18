#pragma once

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include <string.h>
#include <gtest/gtest.h>
#include "SettingsMock.h"

extern "C"
{
    #include "Settings.h"
    #include "TcmsParserAndSerializer.h"
}

///////////////////////////////////////////////////////////////////////////////
/////////////////////////// MACROS/DEFINITIONS ////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

SHARE_SETTINGS
SHARE_SETTINGS_MOCK
SHARE_TCMS_PARSER_AND_SERIALIZER

///////////////////////////////////////////////////////////////////////////////
/////////////////////////// CLASSES/STRUCTURES ////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

class TcmsParserAndSerializerFixture : public ::testing::Test
{
    protected:
        void SetUp    () override { }
        void TearDown () override
        {
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
            gSettings.Communication.Tcms.IsLockOutPositionSensorFailure          = false;
            gSettings.Communication.Tcms.IsRetractedPositionSensorFailure        = false;

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

            gSettings.Communication.Tcms.SerialNumber                            = ZERO;
            gSettings.Communication.Tcms.IsOnDmdTestStep                         = ZERO;

            memset (&gSettings.SystemMonitor.Params.Diag [ZERO].Data    , ZERO, sizeof (gSettings.SystemMonitor.Params.Diag          [ZERO].Data));
            memset (&gTcmsParserAndSerializer.MsgMaps.Output.Tcms [ZERO], ZERO, sizeof (gTcmsParserAndSerializer.MsgMaps.Output.Tcms [ZERO]));
        }

    public:
        class Message
        {
            public:
                std::string Msg;

                Message (const std::string & vMsg, const bool     vResult) { this->operator ()(vMsg, vResult); }
                Message (const std::string & vMsg, const uint16_t vResult) { this->operator ()(vMsg, vResult); }

                void operator() (const std::string & vMsg, const bool vResult)
                {
                    Msg.assign (vMsg);
                    if (vResult == true) { Msg.append ("true");  }
                    else                 { Msg.append ("false"); }
                }

                void operator() (const std::string & vMsg, const uint16_t vResult)
                {
                    Msg.assign (vMsg + std::to_string (vResult));
                }

                std::string & operator () () { return Msg; };    
        };
};

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////