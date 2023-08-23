#include "tlm_parser.h"

Parser::Parser( Iface &iface ): iface( iface ) {}
Parser::~Parser() {}

bool Parser::detectPkt( uint8_t byte ) {
    if ( byte == 0xAB )
    {
        this->bytes[ PH_BYTE_1 ] = byte;
        for ( uint8_t i = PH_BYTE_2; i < NUMBER_OF_BYTES; ++i )
        {   
            this->bytes[ i ] = iface.getByte();
        }

        if ( ( this->bytes[ PH_BYTE_2 ] != 0xBA ) ||
             ( this->bytes[ PH_BYTE_3 ] != 0xCF ) ||
             ( this->bytes[ PH_BYTE_4 ] != 0xFC ) ) {
            return false;
        }
    }
    else
    {
        return false;
    }

    return true;
}

int Parser::extractData( CompoTlm_t &tlm ) {

    this->protocol_version = reverseBits( maskBits( 3, 5 ) & this->bytes[ SH_BYTE_1 ] );
    if ( ( 0x01 != this->protocol_version ) && ( 0x02 != this->protocol_version ) )
    {
        return INVALID_PROTOCOL_VERSION;
    }
    
    this->subsys_id = maskBits( 5, 0 ) & this->bytes[ SH_BYTE_1 ];
    if ( ( 0x01 != this->subsys_id ) &&
         ( 0x03 != this->subsys_id ) &&
         ( 0x05 != this->subsys_id ) ) 
    {
        return INVALID_SUBSYS_ID;
    }
    else
    {
        tlm.subsys_id = this->subsys_id;
    }
    
    this->compo_id = maskBits( 5, 3 ) & this->bytes[ SH_BYTE_2 ];
    if ( ( 0x01 != this->compo_id ) && 
         ( 0x02 != this->compo_id ) &&
         ( 0xA0 != this->compo_id ) &&
         ( 0x14 != this->compo_id ) &&
         ( 0x15 != this->compo_id ) &&
         ( 0x16 != this->compo_id ) &&
         ( 0x17 != this->compo_id ) &&
         ( 0x1E != this->compo_id ) &&
         ( 0x1F != this->compo_id ) )
    {
        return INVALID_COMPO_ID;
    }
    else
    {
        tlm.compo_id = this->compo_id;
    }

    this->tlm_type = maskBits( 3, 0 ) & this->bytes[ SH_BYTE_2 ];
    if ( 0x01 != this->tlm_type ) 
    {
        return INVALID_TLM_TYPE;
    }

    this->reserved = this->bytes[ RS_BYTE_1 ];
    if ( 0xFF != this->reserved ) 
    {
        return INVALID_RESERVED_VALUE;
    }

    uint8_t payload_bytes[4] = { 
        this->bytes[ PL_BYTE_1 ],
        this->bytes[ PL_BYTE_2 ],
        this->bytes[ PL_BYTE_3 ],
        this->bytes[ PL_BYTE_4 ] 
    };
    memcpy( &this->payload, payload_bytes, sizeof( this->payload ) );

    this->checksum = this->bytes[ SH_BYTE_1 ] ^ this->bytes[ SH_BYTE_2 ];
    for ( uint8_t i = RS_BYTE_1; i < CS_BYTE_1; ++i ) {
        this->checksum = this->checksum ^ this->bytes[ i ];
    } 

    if ( this->checksum != this->bytes[ CS_BYTE_1 ] )
    {
        return INVALID_CHECKSUM_VALUE;
    }

    return VALID_PACKET;
}

uint8_t Parser::reverseBits( uint8_t value ) {
    uint8_t reversedBits = 0;
    while( value > 0 ) {
        reversedBits <<= 1;
        if ( value & 1 == 1 ){
            reversedBits ^= 1;
        }
        value >>= 1;
    }

    return reversedBits;
}

uint8_t Parser::maskBits( uint8_t numBits, uint8_t startBit ) {
    return ( ( 1 << numBits ) - 1 ) << startBit;
}