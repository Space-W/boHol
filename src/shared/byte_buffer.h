/* 
* Copyright (C) 2005,2006,2007 MaNGOS <http://www.mangosproject.org/>
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the Free Software
* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#ifndef __SHARED_BYTEBUFFER_H__
#define __SHARED_BYTEBUFFER_H__

#include "common.h"

class ByteBuffer {
public:
    const static size_t DEFAULT_SIZE = 0x1000;

    ByteBuffer(): _rpos(0), _wpos(0) { _storage.reserve(DEFAULT_SIZE); }
    explicit ByteBuffer(size_t res): _rpos(0), _wpos(0) { _storage.reserve(res); }
    ByteBuffer(const ByteBuffer &buf): _rpos(buf._rpos), _wpos(buf._wpos), _storage(buf._storage) { }

    void clear() {
        _storage.clear();
        _rpos = _wpos = 0;
    }

    uint8 operator[](size_t pos) { return read<uint8>(pos); }

    size_t rpos() const { return _rpos; };
    size_t rpos(size_t rpos_) {
        _rpos = rpos_;
        return _rpos;
    };

    size_t wpos() const { return _wpos; }
    size_t wpos(size_t wpos_) {
        _wpos = wpos_;
        return _wpos;
    }

    const uint8 *contents() const { return &_storage[0]; }
    size_t size() const { return _storage.size(); }
    bool empty() const { return _storage.empty(); }

    void resize(size_t newsize) {
        _storage.resize(newsize);
        _rpos = 0;
        _wpos = size();
    }

    void reserve(size_t ressize) {
        if (ressize > size()) 
            _storage.reserve(ressize);
    }

    /************************************************************************/
    /*                                                                      */
    /************************************************************************/
    template <typename T> void append(T value) {
        append((uint8 *)&value, sizeof(value));
    }

    void append(const std::string& str) {
        append((const uint8*)str.c_str(),str.size() + 1);
    }

    void append(const char *src, size_t cnt) {
        append((const uint8*)src, cnt);
    }

    void append(const uint8 *src, size_t cnt) {
        if (!cnt) return;

        assert(size() < 10000000);
        if (_storage.size() < _wpos + cnt)
            _storage.resize(_wpos + cnt);

        memcpy(&_storage[_wpos], src, cnt);
        _wpos += cnt;
    }

    void append(const ByteBuffer& buffer) {
        if(buffer.size()) append(buffer.contents(),buffer.size());
    }

    template <typename T> void put(size_t pos,T value) {
        put(pos,(uint8 *)&value,sizeof(value));
    }

    void put(size_t pos, const uint8 *src, size_t cnt) {
        assert(pos + cnt <= size());
        memcpy(&_storage[pos], src, cnt);
    }
    /*****************************************************************************/

    ByteBuffer &operator<<(bool value) {
        append<char>((char)value);
        return *this;
    }

    ByteBuffer &operator<<(uint8 value) {
        append<uint8>(value);
        return *this;
    }

    ByteBuffer &operator<<(uint16 value) {
        append<uint16>(value);
        return *this;
    }

    ByteBuffer &operator<<(uint32 value) {
        append<uint32>(value);
        return *this;
    }

    ByteBuffer &operator<<(uint64 value) {
        append<uint64>(value);
        return *this;
    }

    // signed as in 2e complement
    ByteBuffer &operator<<(int8 value) {
        append<int8>(value);
        return *this;
    }

    ByteBuffer &operator<<(int16 value) {
        append<int16>(value);
        return *this;
    }

    ByteBuffer &operator<<(int32 value) {
        append<int32>(value);
        return *this;
    }
    
    ByteBuffer &operator<<(int64 value) {
        append<int64>(value);
        return *this;
    }

    // floating points
    ByteBuffer &operator<<(float value) {
        append<float>(value);
        return *this;
    }

    ByteBuffer &operator<<(double value) {
        append<double>(value);
        return *this;
    }

    ByteBuffer &operator<<(const std::string &value) {
        append((uint8 const *)value.c_str(), value.length());
        append((uint8)0);
        return *this;
    }

    ByteBuffer &operator<<(const char *str) {
        append((uint8 const *)str, str ? strlen(str) : 0);
        append((uint8)0);
        return *this;
    }

    /************************************************************************/
    /*                                                                      */
    /************************************************************************/
    template <typename T> T read() {
        T r=read<T>(_rpos);
        _rpos += sizeof(T);
        return r;
    }

    template <typename T> T read(size_t pos) const {
        assert(pos + sizeof(T) <= size());
        return *((const T*)&_storage[pos]);
    }

    void read(uint8 *dest, size_t len) {
        assert(_rpos  + len  <= size());
        memcpy(dest, &_storage[_rpos], len);
        _rpos += len;
    }

    /*****************************************************************************/
    ByteBuffer &operator>>(bool &value) {
        value = read<char>() > 0 ? true : false;
        return *this;
    }

    ByteBuffer &operator>>(uint8 &value) {
        value = read<uint8>();
        return *this;
    }

    ByteBuffer &operator>>(uint16 &value) {
        value = read<uint16>();
        return *this;
    }

    ByteBuffer &operator>>(uint32 &value) {
        value = read<uint32>();
        return *this;
    }

    ByteBuffer &operator>>(uint64 &value) {
        value = read<uint64>();
        return *this;
    }

    //signed as in 2e complement
    ByteBuffer &operator>>(int8 &value) {
        value = read<int8>();
        return *this;
    }

    ByteBuffer &operator>>(int16 &value) {
        value = read<int16>();
        return *this;
    }

    ByteBuffer &operator>>(int32 &value) {
        value = read<int32>();
        return *this;
    }

    ByteBuffer &operator>>(int64 &value) {
        value = read<int64>();
        return *this;
    }

    ByteBuffer &operator>>(float &value) {
        value = read<float>();
        return *this;
    }

    ByteBuffer &operator>>(double &value) {
        value = read<double>();
        return *this;
    }

    ByteBuffer &operator>>(std::string& value) {
        value.clear();
        while (rpos() < size()) {
            char c = read<char>();
            if (c == 0)
                break;
            value += c;
        }
        return *this;
    }

protected:
    size_t _rpos, _wpos;
    std::vector<uint8> _storage;
};

template <typename T> ByteBuffer &operator<<(ByteBuffer &b, std::vector<T> v) {
    b << (uint32)v.size();
    for (typename std::vector<T>::iterator i = v.begin(); i != v.end(); i++) {
        b << *i;
    }
    return b;
}

template <typename T> ByteBuffer &operator>>(ByteBuffer &b, std::vector<T> &v) {
    uint32 vsize;
    b >> vsize;
    v.clear();
    while(vsize--) {
        T t;
        b >> t;
        v.push_back(t);
    }
    return b;
}

template <typename T> ByteBuffer &operator<<(ByteBuffer &b, std::list<T> v) {
    b << (uint32)v.size();
    for (typename std::list<T>::iterator i = v.begin(); i != v.end(); i++) {
        b << *i;
    }
    return b;
}

template <typename T> ByteBuffer &operator>>(ByteBuffer &b, std::list<T> &v) {
    uint32 vsize;
    b >> vsize;
    v.clear();
    while(vsize--) {
        T t;
        b >> t;
        v.push_back(t);
    }
    return b;
}

template <typename K, typename V> ByteBuffer &operator<<(ByteBuffer &b, std::map<K, V> &m) {
    b << (uint32)m.size();
    for (typename std::map<K, V>::iterator i = m.begin(); i != m.end(); i++) {
        b << i->first << i->second;
    }
    return b;
}

template <typename K, typename V> ByteBuffer &operator>>(ByteBuffer &b, std::map<K, V> &m) {
    uint32 msize;
    b >> msize;
    m.clear();
    while(msize--) {
        K k;
        V v;
        b >> k >> v;
        m.insert(make_pair(k, v));
    }
    return b;
}

#endif // __BYTEBUFFER_H__
