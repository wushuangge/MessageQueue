
#ifndef _HANDLER_FACTORY_
#define _HANDLER_FACTORY_
#include <map>

namespace MQ {
    class IHandler;

    class CHandlerFactory
    {
    public:
        CHandlerFactory();
        IHandler* GetHandler(int message_type);
        int RegistHandler(int message_type, IHandler* handler);
    private:
        std::map<int, IHandler*> m_HandlerMap;
    };
}

#endif