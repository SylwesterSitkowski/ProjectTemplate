///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

extern "C"
{
    #include "Logger.h"
}

#include "TcmsParserAndSerializerFixture.hxx"

///////////////////////////////////////////////////////////////////////////////
/////////////////////////// MACROS/DEFINITIONS ////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

static const char * Module = "TcmsParserAndSerializerFixture";

SHARE_LOGGER

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// FUNCTIONS ////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

////////////////////////////////// Parser /////////////////////////////////////

TEST_F (TcmsParserAndSerializerFixture, ParseInputs)
{
    LOGI (Module, "ParseInputs");
    gTcmsParserAndSerializer.Parse.Inputs (0x7);

    EXPECT_TRUE     (gSettings.Communication.Tcms.Input.IsClosedAndLockedDoorsState);
    EXPECT_TRUE     (gSettings.Communication.Tcms.Input.IsRetractionControlInhibition);
    EXPECT_TRUE     (gSettings.Communication.Tcms.Input.IsDoorClosedAndLockOutDoorState);

    Message message ("IsClosedAndLockedDoorsState     = ", gSettings.Communication.Tcms.Input.IsClosedAndLockedDoorsState);
    LOGD            (Module, message ().data ());

    message         ("IsRetractionControlInhibition   = ", gSettings.Communication.Tcms.Input.IsRetractionControlInhibition);
    LOGD            (Module, message ().data ());

    message         ("IsDoorClosedAndLockOutDoorState = ", gSettings.Communication.Tcms.Input.IsDoorClosedAndLockOutDoorState);
    LOGD            (Module, message ().data ());
}

TEST_F (TcmsParserAndSerializerFixture, ParseMpu)
{
    LOGI (Module, "ParseMpu");
    gTcmsParserAndSerializer.Parse.Mpu (0x1F);

    EXPECT_TRUE     (gSettings.Communication.Tcms.Input.IsMaintModeAuth);
    EXPECT_TRUE     (gSettings.Communication.Tcms.Input.IsReprogModeAuth);
    EXPECT_TRUE     (gSettings.Communication.Tcms.Input.IsOnDmdTestResume);
    EXPECT_TRUE     (gSettings.Communication.Tcms.Input.IsTrainOperational);
    EXPECT_TRUE     (gSettings.Communication.Tcms.Input.IsReducedPowerTest);

    Message message ("IsMaintModeAuth    = ", gSettings.Communication.Tcms.Input.IsMaintModeAuth);
    LOGD            (Module, message ().data ());

    message         ("IsReprogModeAuth   = ", gSettings.Communication.Tcms.Input.IsReprogModeAuth);
    LOGD            (Module, message ().data ());

    message         ("IsOnDmdTestResume  = ", gSettings.Communication.Tcms.Input.IsOnDmdTestResume);
    LOGD            (Module, message ().data ());

    message         ("IsTrainOperational = ", gSettings.Communication.Tcms.Input.IsTrainOperational);
    LOGD            (Module, message ().data ());

    message         ("IsReducedPowerTest = ", gSettings.Communication.Tcms.Input.IsReducedPowerTest);
    LOGD            (Module, message ().data ());
}

TEST_F (TcmsParserAndSerializerFixture, ParseRequest)
{
    LOGI (Module, "ParseRequest");
    gTcmsParserAndSerializer.Parse.Request (0xF);

    EXPECT_TRUE     (gSettings.Communication.Tcms.Input.IsSetParam);
    EXPECT_TRUE     (gSettings.Communication.Tcms.Input.IsLockParamSet);
    EXPECT_TRUE     (gSettings.Communication.Tcms.Input.IsEraseHistory);
    EXPECT_TRUE     (gSettings.Communication.Tcms.Input.IsOnDmdTestStart);

    Message message ("IsSetParam       = ", gSettings.Communication.Tcms.Input.IsSetParam);
    LOGD            (Module, message ().data ());

    message         ("IsLockParamSet   = ", gSettings.Communication.Tcms.Input.IsLockParamSet);
    LOGD            (Module, message ().data ());

    message         ("IsEraseHistory   = ", gSettings.Communication.Tcms.Input.IsEraseHistory);
    LOGD            (Module, message ().data ());

    message         ("IsOnDmdTestStart = ", gSettings.Communication.Tcms.Input.IsOnDmdTestStart);
    LOGD            (Module, message ().data ());
}

TEST_F (TcmsParserAndSerializerFixture, ParseDayTime)
{
    LOGI (Module, "ParseDayTime");
    gTcmsParserAndSerializer.Parse.DateTime (0x01);

    EXPECT_TRUE     (gSettings.Communication.Tcms.Input.IsTrainDateTimeS);

    Message message ("IsTrainDateTimeS = ", gSettings.Communication.Tcms.Input.IsTrainDateTimeS);
    LOGD            (Module, message ().data ());
}

TEST_F (TcmsParserAndSerializerFixture, ParseAll)
{
    LOGI (Module, "ParseAll");

    memset (gTcmsParserAndSerializer.MsgMaps.Input.Tcms, 0xFFFF, sizeof (gTcmsParserAndSerializer.MsgMaps.Input.Tcms) + ONE);

    gTcmsParserAndSerializer.Parse.All (&gTcmsParserAndSerializer);

    EXPECT_TRUE     (gSettings.Communication.Tcms.Input.IsSetParam);
    EXPECT_TRUE     (gSettings.Communication.Tcms.Input.IsLockParamSet);
    EXPECT_TRUE     (gSettings.Communication.Tcms.Input.IsEraseHistory);
    EXPECT_TRUE     (gSettings.Communication.Tcms.Input.IsMaintModeAuth);
    EXPECT_TRUE     (gSettings.Communication.Tcms.Input.IsOnDmdTestStart);
    EXPECT_TRUE     (gSettings.Communication.Tcms.Input.IsTrainDateTimeS);
    EXPECT_TRUE     (gSettings.Communication.Tcms.Input.IsReprogModeAuth);
    EXPECT_TRUE     (gSettings.Communication.Tcms.Input.IsOnDmdTestResume);
    EXPECT_TRUE     (gSettings.Communication.Tcms.Input.IsTrainOperational);
    EXPECT_TRUE     (gSettings.Communication.Tcms.Input.IsReducedPowerTest);
    EXPECT_TRUE     (gSettings.Communication.Tcms.Input.IsClosedAndLockedDoorsState);
    EXPECT_TRUE     (gSettings.Communication.Tcms.Input.IsRetractionControlInhibition);
    EXPECT_TRUE     (gSettings.Communication.Tcms.Input.IsDoorClosedAndLockOutDoorState);

    Message message ("IsSetParam                      = ", gSettings.Communication.Tcms.Input.IsSetParam);
    LOGD            (Module, message ().data ());

    message         ("IsLockParamSet                  = ", gSettings.Communication.Tcms.Input.IsLockParamSet);
    LOGD            (Module, message ().data ());

    message         ("IsMaintModeAuth                 = ", gSettings.Communication.Tcms.Input.IsMaintModeAuth);
    LOGD            (Module, message ().data ());

    message         ("IsReprogModeAuth                = ", gSettings.Communication.Tcms.Input.IsReprogModeAuth);
    LOGD            (Module, message ().data ());

    message         ("IsOnDmdTestStart                = ", gSettings.Communication.Tcms.Input.IsOnDmdTestStart);
    LOGD            (Module, message ().data ());

    message         ("IsTrainDateTimeS                = ", gSettings.Communication.Tcms.Input.IsTrainDateTimeS);
    LOGD            (Module, message ().data ());

    message         ("IsOnDmdTestResume               = ", gSettings.Communication.Tcms.Input.IsOnDmdTestResume);
    LOGD            (Module, message ().data ());

    message         ("IsTrainOperational              = ", gSettings.Communication.Tcms.Input.IsTrainOperational);
    LOGD            (Module, message ().data ());

    message         ("IsReducedPowerTest              = ", gSettings.Communication.Tcms.Input.IsReducedPowerTest);
    LOGD            (Module, message ().data ());

    message         ("IsClosedAndLockedDoorsState     = ", gSettings.Communication.Tcms.Input.IsClosedAndLockedDoorsState);
    LOGD            (Module, message ().data ());

    message         ("IsRetractionControlInhibition   = ", gSettings.Communication.Tcms.Input.IsRetractionControlInhibition);
    LOGD            (Module, message ().data ());

    message         ("IsDoorClosedAndLockOutDoorState = ", gSettings.Communication.Tcms.Input.IsDoorClosedAndLockOutDoorState);
    LOGD            (Module, message ().data ());
}

/////////////////////////////// Serializer ////////////////////////////////////

TEST_F (TcmsParserAndSerializerFixture, SerializeOutputs)
{
    LOGI (Module, "SerializeOutputs");
    
    gSettings.Communication.Tcms.Output.IsOperational                    = true;
    gSettings.Communication.Tcms.Output.IsModuleFault                    = true;
    gSettings.Communication.Tcms.Output.IsDeployedState                  = true;
    gSettings.Communication.Tcms.Output.IsZeroVelocityTL                 = true;
    gSettings.Communication.Tcms.Output.IsRetractedDefault               = true;
    gSettings.Communication.Tcms.Output.IsManuallyReleased               = true;
    gSettings.Communication.Tcms.Output.IsDeploymentDefault              = true;
    gSettings.Communication.Tcms.Output.IsAccessNotGuaranteed            = true;
    gSettings.Communication.Tcms.Output.IsOpeningAuthorisationTL         = true;
    gSettings.Communication.Tcms.Output.IsRetractedAndLockedState        = true;
    gSettings.Communication.Tcms.Output.IsFailedToDeployBecauseObstacle  = true;
    gSettings.Communication.Tcms.Output.IsFailedToRetractBecauseObstacle = true;

    gTcmsParserAndSerializer.Serialize.Outputs (&gTcmsParserAndSerializer);
    EXPECT_EQ       (gTcmsParserAndSerializer.MsgMaps.Output.Tcms [ZERO], 0xFFF);

    Message message ("Outputs: = ", gTcmsParserAndSerializer.MsgMaps.Output.Tcms [ZERO]);
    LOGD            (Module, message ().data ());
}

TEST_F (TcmsParserAndSerializerFixture, SerializeInternal)
{
    LOGI (Module, "SerializeInternal");

    gSettings.SystemMonitor.Params.Error.Regs.Data.Infos0     = ONE;
    gSettings.SystemMonitor.Params.Error.Regs.Data.Alarms0    = ONE;
    gSettings.SystemMonitor.Params.Error.Regs.Data.Warnings0  = ONE;
    gSettings.SystemMonitor.Params.Error.Regs.Data.Fault.Zero = true;
    gSettings.SystemMonitor.Params.Error.Regs.Data.Fault.One  = true;
    gSettings.SystemMonitor.Params.Error.Regs.Data.Fault.Two  = true;

    gTcmsParserAndSerializer.Serialize.Internal (&gTcmsParserAndSerializer);

    EXPECT_TRUE     (gSettings.Communication.Tcms.IsMinorFltPresent);
    EXPECT_TRUE     (gSettings.Communication.Tcms.IsMajorFltPresent);
    EXPECT_TRUE     (gSettings.Communication.Tcms.IsInformFltPresent);
    EXPECT_TRUE     (gSettings.Communication.Tcms.IsCriticalFltPresent);
    EXPECT_EQ       (gSettings.Communication.Tcms.IsOperational, ONE);

    Message message ("IsMinorFltPresent:    = ", gSettings.Communication.Tcms.IsMinorFltPresent);
    LOGD            (Module, message ().data ());

    message         ("IsMajorFltPresent:    = ", gSettings.Communication.Tcms.IsMajorFltPresent);
    LOGD            (Module, message ().data ());

    message         ("IsInformFltPresent:   = ", gSettings.Communication.Tcms.IsInformFltPresent);
    LOGD            (Module, message ().data ());

    message         ("IsCriticalFltPresent: = ", gSettings.Communication.Tcms.IsCriticalFltPresent);
    LOGD            (Module, message ().data ());

    message         ("IsOperational:        = ", static_cast<uint16_t>(ONE));
    LOGD            (Module, message ().data ());
}

TEST_F (TcmsParserAndSerializerFixture, SerializeOutState)
{
    LOGI (Module, "SerializeOutState");

    gSettings.Communication.Tcms.IsOperational        = true;
    gSettings.Communication.Tcms.IsMajorFltPresent    = true;
    gSettings.Communication.Tcms.IsMinorFltPresent    = true;
    gSettings.Communication.Tcms.IsEqInMaintenance    = true;
    gSettings.Communication.Tcms.IsInformFltPresent   = true;
    gSettings.Communication.Tcms.IsCriticalFltPresent = true;

    gTcmsParserAndSerializer.Serialize.OutState (&gTcmsParserAndSerializer);
    EXPECT_EQ       (gTcmsParserAndSerializer.MsgMaps.Output.Tcms [NINE], 0x3F);

    Message message ("OutState: = ", gTcmsParserAndSerializer.MsgMaps.Output.Tcms [NINE]);
    LOGD            (Module, message ().data ());
}

TEST_F (TcmsParserAndSerializerFixture, SerializeFailures)
{
    LOGI (Module, "SerializeFailures");

    gSettings.Communication.Tcms.IsEncoderFault                   = true;
    gSettings.Communication.Tcms.IsMotorFailure                   = true;
    gSettings.Communication.Tcms.IsSensorFailure                  = true;
    gSettings.Communication.Tcms.IsManualModeSensorFailure        = true;
    gSettings.Communication.Tcms.IsMotorFailureInDeployment       = true;
    gSettings.Communication.Tcms.IsLockOutPositionSensorFailure   = true;
    gSettings.Communication.Tcms.IsRetractedPositionSensorFailure = true;

    gTcmsParserAndSerializer.Serialize.Failures (&gTcmsParserAndSerializer);
    EXPECT_EQ       (gTcmsParserAndSerializer.MsgMaps.Output.Tcms [ONE], 0x7F);

    Message message ("Failures: = ", gTcmsParserAndSerializer.MsgMaps.Output.Tcms [ONE]);
    LOGD            (Module, message ().data ());
}

TEST_F (TcmsParserAndSerializerFixture, SerializeOutResults)
{
    LOGI (Module, "SerializeOutResults");

    gSettings.Communication.Tcms.IsOnDmdTestOK         = true;
    gSettings.Communication.Tcms.IsEraseHistOK         = true;
    gSettings.Communication.Tcms.IsParamSetDone        = true;
    gSettings.Communication.Tcms.IsOnDmdTestDone       = true;
    gSettings.Communication.Tcms.IsEraseHistDone       = true;
    gSettings.Communication.Tcms.IsParamSetRsltOK      = true;
    gSettings.Communication.Tcms.IsParamSetInProgress  = true;
    gSettings.Communication.Tcms.IsOnDmdTestInProgress = true;

    gTcmsParserAndSerializer.Serialize.OutResults (&gTcmsParserAndSerializer);
    EXPECT_EQ       (gTcmsParserAndSerializer.MsgMaps.Output.Tcms [ONE], 0x7F);

    Message message ("OutResults: = ", gTcmsParserAndSerializer.MsgMaps.Output.Tcms [ONE]);
    LOGD            (Module, message ().data ());
}

TEST_F (TcmsParserAndSerializerFixture, SerializeSwHwVersion)
{
    LOGI (Module, "SerializeSwHwVersion");

    gTcmsParserAndSerializer.Serialize.SwHwVersion (&gTcmsParserAndSerializer);
    EXPECT_EQ       (gTcmsParserAndSerializer.MsgMaps.Output.Tcms [TWO]  , ONE);
    EXPECT_EQ       (gTcmsParserAndSerializer.MsgMaps.Output.Tcms [THREE], ZERO);
    EXPECT_EQ       (gTcmsParserAndSerializer.MsgMaps.Output.Tcms [FOUR] , ZERO);
    EXPECT_EQ       (gTcmsParserAndSerializer.MsgMaps.Output.Tcms [FIVE] , ONE);
    EXPECT_EQ       (gTcmsParserAndSerializer.MsgMaps.Output.Tcms [SIX]  , ZERO);
    EXPECT_EQ       (gTcmsParserAndSerializer.MsgMaps.Output.Tcms [SEVEN], ZERO);
    EXPECT_EQ       (gSettings.Communication.Tcms.SerialNumber, ZERO);

    Message message ("Sw.X: = ", gTcmsParserAndSerializer.MsgMaps.Output.Tcms [TWO]);
    LOGD            (Module, message ().data ());

    message         ("Sw.Y: = ", gTcmsParserAndSerializer.MsgMaps.Output.Tcms [THREE]);
    LOGD            (Module, message ().data ());

    message         ("Sw.Z: = ", gTcmsParserAndSerializer.MsgMaps.Output.Tcms [FOUR]);
    LOGD            (Module, message ().data ());

    message         ("Hw.X: = ", gTcmsParserAndSerializer.MsgMaps.Output.Tcms [FIVE]);
    LOGD            (Module, message ().data ());

    message         ("Hw.Y: = ", gTcmsParserAndSerializer.MsgMaps.Output.Tcms [SIX]);
    LOGD            (Module, message ().data ());

    message         ("Hw.Z: = ", gTcmsParserAndSerializer.MsgMaps.Output.Tcms [SEVEN]);
    LOGD            (Module, message ().data ());

    message         ("SerialNumber: = ", gSettings.Communication.Tcms.SerialNumber);
    LOGD            (Module, message ().data ());
}

TEST_F (TcmsParserAndSerializerFixture, SerializeOnDmdTestStep)
{
    LOGI (Module, "SerializeOnDmdTestStep");

    gSettings.Communication.Tcms.IsOnDmdTestStep = true;

    gTcmsParserAndSerializer.Serialize.OnDmdTestStep (&gTcmsParserAndSerializer);
    EXPECT_EQ       (gTcmsParserAndSerializer.MsgMaps.Output.Tcms [ELEVEN], ONE);

    Message message ("OnDmdTestStep: = ", gTcmsParserAndSerializer.MsgMaps.Output.Tcms [ELEVEN]);
    LOGD            (Module, message ().data ());
}

TEST_F (TcmsParserAndSerializerFixture, SerializeWriteDiag)
{
    LOGI (Module, "WriteDiag");

    gSettings.Communication.Tcms.IsOnDmdTestStep = true;

    for (uint8_t diagId = THIRTEEN; diagId < THIRTEEN + DIAG_PARAM_LEN; diagId++)
    {
        gTcmsParserAndSerializer.Serialize.WriteDiag (&gTcmsParserAndSerializer, diagId, diagId * TWO);

        EXPECT_EQ (gSettings.SystemMonitor.Params.Diag [diagId - THIRTEEN].Data    , diagId * TWO);
        EXPECT_EQ (gTcmsParserAndSerializer.MsgMaps.Output.Diag [diagId - THIRTEEN], diagId * TWO);

        Message message    ("DiagId:= "    , static_cast<uint16_t>(diagId));
        message.Msg.append (" WriteDiag: = ");
        message            (message.Msg.data (), static_cast<uint16_t>(gSettings.SystemMonitor.Params.Diag [diagId - THIRTEEN].Data));
        LOGD               (Module, message ().data ());
    }
}

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////