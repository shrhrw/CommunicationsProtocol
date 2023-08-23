
#ifndef __PARSER_H__
#define __PARSER_H__

#include <stdint.h>
#include "tlm.h"

class Parser {
    public:
        Parser();
        ~Parser();

        bool detectPkt( uint8_t byte );
        int  extractData( CompoTlm_t tlm );
        void validateSubsystemIds();
        void validateComponentIds();
        void validateTelemetryType();
        void validateChecksum();

    public:
        double var1;
        double var2;
        double var3;
        double var4;

};

#endif // __PARSER_H__
