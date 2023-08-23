
#ifndef __PARSER_H__
#define __PARSER_H__

#include <stdint.h>
#include <stdio.h>
#include <cstring>
#include "iface.h"
#include "tlm.h"

class Parser {

    /******************************************
     * Member Functions
     ******************************************/	
    public:

        Parser( Iface &iface );
        ~Parser();

        enum ByteMapping {
            PH_BYTE_1 = 0,    // Primary Header Byte 1 
            PH_BYTE_2,        // Primary Header Byte 2
            PH_BYTE_3,        // Primary Header Byte 3
            PH_BYTE_4,        // Primary Header Byte 4
            SH_BYTE_1,        // Secondary Header Byte 1
            SH_BYTE_2,        // Secondary Header Byte 2
            RS_BYTE_1,        // Reserved Byte 1
            PL_BYTE_1,        // Payload Byte 1
            PL_BYTE_2,        // Payload Byte 2
            PL_BYTE_3,        // Payload Byte 3
            PL_BYTE_4,        // Payload Byte 4
            CS_BYTE_1,        // Checksum Byte 1
            NUMBER_OF_BYTES
        };

        enum ErrorCodes {
            VALID_PACKET = 0,
            INVALID_PROTOCOL_VERSION,
            INVALID_SUBSYS_ID,
            INVALID_COMPO_ID,
            INVALID_TLM_TYPE,
            INVALID_RESERVED_VALUE,
            INVALID_PAYLOAD_VALUE,
            INVALID_CHECKSUM_VALUE
        };

        bool    detectPkt( uint8_t byte );
        int     extractData( CompoTlm_t &tlm );
        uint8_t reverseBits( uint8_t value );
        uint8_t maskBits( uint8_t numBits, uint8_t startBit );

    /******************************************
     * Member Variables
     ******************************************/	
    public:
        uint8_t bytes[12];
        uint8_t protocol_version;
        uint8_t subsys_id;
        uint8_t compo_id;
        uint8_t tlm_type;
        uint8_t reserved;
        uint8_t checksum;
        float   payload;

        Iface &iface;
};

#endif // __PARSER_H__
