
#ifndef __PARSER_H__
#define __PARSER_H__

#include <stdint.h>
#include <stdio.h>
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

        bool detectPkt( uint8_t byte );
        int  extractData( CompoTlm_t tlm );
        uint8_t maskBits( uint8_t numBits, uint8_t startBit, uint8_t byteNumber );

    /******************************************
     * Member Variables
     ******************************************/	
    public:
        uint8_t bytes[12];
        Iface &iface;
};

#endif // __PARSER_H__
