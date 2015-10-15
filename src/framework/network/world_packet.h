/*
 * Not test
 **/
#ifndef __NETWORK_PACKET_H__
#define __NETWORK_PACKET_H__

#include "bytebuffer.h"

template <typename Head>
class Packet : public ByteBuffer<Head> {
    using ByteBuffer<Head>::clear();
    using ByteBuffer<Head>::_rpos;
    using ByteBuffer<Head>::_wpos;
    using ByteBuffer<Head>::_storage;

public:
    Packet() : ByteBuffer<Head>() {
        setOpcode(0);
    }

    explicit Packet(size_t res) : ByteBuffer<Head>(res) {
        setOpcode(0);
    }

    Packet(const Packet& packet) : ByteBuffer<Head>(packet) {
        setOpcode(packet.getOpcode());
    }

    // Initialize a specify-opcode packet
    void Initialize(const Head& opcode) {
        clear();
        setOpcode(opcode);
    }

    void Initialize(const void *packet, const size_t packet_size) {
        _rpos = _wpos = sizeof(Head);
        _storage.resize(packet_size);
        memcpy(&_storage[0], packet, packet_size);
    }

    void Initialize(const Head opcode, const void *data, const size_t data_size) {
        _rpos = _wpos = sizeof(Head);
        _storage.resize(data_size);
        setOpcode(opcode);

        if (data)
            memcpy(&_storage[sizeof(Head)], data, data_size);
    }

    const void* getData() {
        return &_storage[sizeof(Head)];
    }

    void setOpcode(const Head& opcode) {
        *((Head*)(&_storage[0])) = opcode;
    }

    Head getOpcode() const {
        return *((Head*)(&_storage[0]));
    }
};

typedef Packet<uint16> WorldPacket;

#endif // __NETWORK_PACKET_H__
