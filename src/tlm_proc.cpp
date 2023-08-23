#include "tlm_parser.h"

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
                    // Error Handling, etc.
                }
            }
        }
        system.time.sleep_ms( 100 );
    }
}