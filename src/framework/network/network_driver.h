/*
 * Network base class
 **/

#ifndef __NETWORK_DRIVER_H__
#define __NETWORK_DRIVER_H__

class NetworkDriver {
public:
    virtual ~NetworkDriver() = 0;

    virtual bool Initialize() = 0;
    virtual bool Shutdown() = 0;

    virtual bool Connect()  = 0;
    virtual bool Listen() = 0;

    virtual bool Send() = 0;
    virtual bool Recv() = 0;

    virtual void Update() = 0;
};

#endif // __NETWORK_DRIVER_H__
