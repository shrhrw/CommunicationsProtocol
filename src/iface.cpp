#include "../include/iface.h"

Iface::Iface() {}
Iface::~Iface() {}

static const uint8_t NUMBER_OF_BYTES = 12;

void Iface::setBytes( uint8_t bytes[ NUMBER_OF_BYTES ] ) {
    for ( uint8_t i = 0; i < NUMBER_OF_BYTES; ++i ) {
        this->bytes[ i ] = bytes[ i ];
    }
}

uint8_t Iface::getByte() {
    
    uint8_t returnByte = this->bytes[ this->counter ];
    this->counter++;
    if ( this->counter == NUMBER_OF_BYTES ) {
        this->counter = 0;
    }

    return returnByte;
}

bool Iface::existRcvData()
{
    return true;
}