#include "tlm_parser.h"

Parser::Parser() {}
Parser::~Parser() {}

bool
Parser::detectPkt( uint8_t byte ) {
    return true;
}

int  
Parser::extractData( CompoTlm_t tlm ) {
    return 0;
}

void
Parser::validateSubsystemIds(){}

void
Parser::validateComponentIds(){}

void
Parser::validateTelemetryType(){}

void
Parser::validateChecksum(){}