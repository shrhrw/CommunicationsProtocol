#ifndef __IFACE_H__
#define __IFACE_H__

#include <stdint.h>

class Iface {
    public:
        Iface();
        ~Iface();

        void setBytes( uint8_t bytes[12] );
        uint8_t getByte();
        bool existRcvData();

        uint8_t bytes[12];
        uint8_t counter;
};

#endif // __IFACE_H__