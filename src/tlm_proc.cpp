#include "iface.h"
#include "tlm_parser.h"

Iface iface;
Parser parser;

int main() {
    while ( 1 ) {
        while ( iface.existRcvData() ) {
            uint8_t byte = iface.getByte();
            // Parse incoming bytes and detect packet
            if ( parser.detectPkt(byte) ) {
                // One correct packet has been detected
                CompoTlm_t tlm = {};
                int err = parser.extractData( tlm );
                if ( err = 0 ) {
                    // Pass telemetry info to the upper layer
                    system.tlm.update( tlm );
                } else {
                    if ( err = Parser::INVALID_PROTOCOL_VERSION )
                    {
                        system.alert( "Error [%d]: Invalid Protocol Version found in packet", err );
                    }
                    if ( err = Parser::INVALID_SUBSYS_ID )
                    {
                        system.alert( "Error [%d]: Invalid Subsys ID found in packet", err );
                    }
                    if ( err = Parser::INVALID_COMPO_ID )
                    {
                        system.alert( "Error [%d]: Invalid Compo ID found in packet", err );
                    }
                    if ( err = Parser::INVALID_TLM_TYPE )
                    {
                        system.alert( "Error [%d]: Invalid TLM Type found in packet", err );
                    }
                    if ( err = Parser::INVALID_RESERVED_VALUE )
                    {
                        system.alert( "Error [%d]: Invalid Reserved Byte found in packet", err );
                    }
                    if ( err = Parser::INVALID_CHECKSUM_VALUE )
                    {
                        system.alert( "Error [%d]: Invalid Checksum found in packet", err );
                    }
                }
            }
        }
        system.time.sleep_ms( 100 );
    }
}