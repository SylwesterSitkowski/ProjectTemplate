///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

extern "C"
{
    #include "App.h"
}

#include "AppFixture.hxx"

///////////////////////////////////////////////////////////////////////////////
/////////////////////////// MACROS/DEFINITIONS ////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

static const char * Module = "AppFixture";

SHARE_APP

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// FUNCTIONS ////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

TEST_F (AppFixture, CheckEntryIntoManualMode)
{
    EXPECT_TRUE  (true);
}

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////