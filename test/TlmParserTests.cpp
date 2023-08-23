#include <gtest/gtest.h>
#include "../include/tlm_parser.h"

TEST( TlmParserTest, DetectPktTestTrue ) {
    Iface iface;
    uint8_t bytes[12] = { 
        0xAB, 0xBA, 0xCF, 0xFC,
        0x21, 0xA1,
        0xFF,
        0x00, 0x00, 0x00, 0x00,
        0x7F
     };
    iface.setBytes( bytes );
    Parser parser( iface );
    EXPECT_TRUE( parser.detectPkt( iface.getByte() ) );
}

TEST( TlmParserTest, DetectPktTestFalse ) {
    Iface iface;
    uint8_t bytes[12] = { 
        0xAA, 0xAA, 0xAA, 0xAA,
        0x21, 0xA1,
        0xFF,
        0x00, 0x00, 0x00, 0x00,
        0x7F
     };
    iface.setBytes( bytes );
    Parser parser( iface );
    EXPECT_FALSE( parser.detectPkt( iface.getByte() ) );
}

TEST( TlmParserTest, extractData_valid_packet ) {
    Iface iface;
    uint8_t bytes[12] = { 
        0xAB, 0xBA, 0xCF, 0xFC,
        0x21, 0xA1,
        0xFF,
        0x00, 0x00, 0x00, 0x00,
        0x7F
    };

    iface.setBytes( bytes );
    Parser parser( iface );
    parser.detectPkt( iface.getByte() );

    CompoTlm_t tlm = {};
    int returnValue = parser.extractData( tlm );

    EXPECT_EQ( returnValue, 0 );
    EXPECT_EQ( tlm.subsys_id, 0x01 );
    EXPECT_EQ( tlm.compo_id, 0xA0 );
}

TEST( TlmParserTest, extractData_invalid_SH ) {
    Iface iface;
    uint8_t bytes[12] = { 
        0xAB, 0xBA, 0xCF, 0xFC,
        0xFF, 0xFF,
        0xFF,
        0x00, 0x00, 0x00, 0x00,
        0x7F
    };
    iface.setBytes( bytes );
    Parser parser( iface );
    parser.detectPkt( iface.getByte() );
    CompoTlm_t tlm = {};
    parser.extractData( tlm );

    EXPECT_EQ( parser.extractData( tlm ), Parser::INVALID_PROTOCOL_VERSION );
}

TEST( TlmParserTest, extractData_invalid_reserve_byte ) {
    Iface iface;
    uint8_t bytes[12] = { 
        0xAB, 0xBA, 0xCF, 0xFC,
        0x21, 0xA1,
        0x00,
        0x00, 0x00, 0x00, 0x00,
        0x7F
    };
    iface.setBytes( bytes );
    Parser parser( iface );
    parser.detectPkt( iface.getByte() );
    CompoTlm_t tlm = {};
    parser.extractData( tlm );

    EXPECT_EQ( parser.extractData( tlm ), Parser::INVALID_RESERVED_VALUE );
}

TEST( TlmParserTest, extractData_invalid_checksum ) {
    Iface iface;
    uint8_t bytes[12] = { 
        0xAB, 0xBA, 0xCF, 0xFC,
        0x21, 0xA1,
        0xFF,
        0x00, 0x00, 0x00, 0x00,
        0x44
    };
    iface.setBytes( bytes );
    Parser parser( iface );
    parser.detectPkt( iface.getByte() );
    CompoTlm_t tlm = {};
    parser.extractData( tlm );

    EXPECT_EQ( parser.extractData( tlm ), Parser::INVALID_CHECKSUM_VALUE );
}

int main( int argc, char **argv ) {
    ::testing::InitGoogleTest( &argc, argv );
    return RUN_ALL_TESTS();
}
