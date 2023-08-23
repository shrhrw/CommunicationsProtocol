#include "tlm_parser.h"

Parser::Parser( Iface &iface ): iface( iface ) {}
Parser::~Parser() {}

bool Parser::detectPkt( uint8_t byte ) {
    if ( byte == 0xAB )
    {
        this->bytes[ PH_BYTE_1 ] = byte;
        for ( uint8_t i = PH_BYTE_1; i < NUMBER_OF_BYTES; ++i )
        {   
            this->bytes[ i ] = iface.getByte();
        }

        if ( ( this->bytes[ PH_BYTE_2 ] == 0xBA ) &&
             ( this->bytes[ PH_BYTE_3 ] == 0xCF ) &&
             ( this->bytes[ PH_BYTE_4 ] == 0xFC ) ) {
            return true;
        }
    }

    return false;
}

int  Parser::extractData( CompoTlm_t tlm ) {
    tlm.subsys_id = maskBits( 5, 4, SH_BYTE_1 );
    tlm.compo_id  = maskBits( 5, 0, SH_BYTE_2 );
}

uint8_t Parser::maskBits( uint8_t numBits, uint8_t startBit, uint8_t byteNumber ){
    uint8_t mask = ( ( 1 << numBits ) - 1) << startBit;
    return this->bytes[ byteNumber ] & mask;
}
