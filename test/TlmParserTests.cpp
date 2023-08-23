#include <gtest/gtest.h>
#include "tlm_parser.h"

class TlmParserTest : public ::testing::Test {
    protected:
        Parser parser;
};

TEST_F( TlmParserTest, InitialTest ) {
    EXPECT_TRUE(true)
}

int main( int argc, char **argv ) {
    ::testing::InitGoogleTest( &argc, argv );
    return RUN_ALL_TESTS();
}