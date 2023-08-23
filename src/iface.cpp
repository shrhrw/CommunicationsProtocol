#include "../include/iface.h"

Iface::Iface() {}
Iface::~Iface() {}

static const uint8_t NUMBER_OF_BYTES = 12;

void Iface::setBytes( uint8_t bytes[12] ) {
    for ( uint8_t i = 0; i < NUMBER_OF_BYTES; ++i ) {
        this->bytes[ i ] = bytes[ i ];
    }
}

uint8_t Iface::getByte() {
    
    uint8_t returnByte = this->bytes[ this->counter ];
    this->counter++;
    return returnByte;
}