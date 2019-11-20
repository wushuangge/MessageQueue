#ifndef  _I_LISENER_H_
#define  _I_LISENER_H_

namespace MQ {
    class Message;

    class IHandler
    {
    public:
        virtual int Handle(const Message& message) = 0;
    };
}

#endif