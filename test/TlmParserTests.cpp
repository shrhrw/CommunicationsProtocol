#include <gtest/gtest.h>
#include "../include/tlm_parser.h"

/* Test to see if detectPkts resolves true */
TEST( TlmParserTest, DetectPktTestTrue ) {
    Iface iface;
    uint8_t bytes[12] = { 0xAB, 0xBA, 0xCF, 0xFC };
    iface.setBytes( bytes );
    Parser parser( iface );
    EXPECT_TRUE( parser.detectPkt( 0xAB ) );
}

/* Test to see if detectPkts resolves false */
TEST( TlmParserTest, DetectPktTestFalse ) {
    Iface iface;
    uint8_t bytes[12] = { 0xAA, 0xAA, 0xAA, 0xAA };
    iface.setBytes( bytes );
    Parser parser( iface );
    EXPECT_FALSE( parser.detectPkt( 0xAB ) );
}

int main( int argc, char **argv ) {
    ::testing::InitGoogleTest( &argc, argv );
    return RUN_ALL_TESTS();
}
