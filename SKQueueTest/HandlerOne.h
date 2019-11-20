
#ifndef  _LISTENER_ONE_H_
#define  _LISTENER_ONE_H_
#include "IHandler.h"

namespace MQ {
    class CHandlerOne : public IHandler
    {
    public:
        int Handle(const Message& message);
    private:

    };
}
#endif