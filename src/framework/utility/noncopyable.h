/*
 * Non copyable base class
 **/

#ifndef __UTILITY_NONCOPYALBE_H__
#define __UTILITY_NONCOPYALBE_H__

class Noncopyable {
protected:
    Noncopyable() {}
    ~Noncopyable() {}
private:
    Noncopyable(const Noncopyable&) {}
    const Noncopyable& operator=(const Noncopyable&) {}
}

#endif // __UTILITY_NONCOPYALBE_H__
