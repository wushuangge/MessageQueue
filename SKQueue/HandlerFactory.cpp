
#include "HandlerFactory.h"
#include "IHandler.h"

namespace MQ {
    CHandlerFactory::CHandlerFactory()
    {
    }

    IHandler * CHandlerFactory::GetHandler(int message_type)
    {
        std::map <int, IHandler*>::const_iterator cit
            = m_HandlerMap.find(message_type);
        if (cit != m_HandlerMap.end()) {
            return cit->second;
        }
        return NULL;
    }

    int CHandlerFactory::RegistHandler(int message_type, IHandler* handler)
    {
        std::map <int, IHandler*>::const_iterator cit
            = m_HandlerMap.find(message_type);
        if (cit != m_HandlerMap.end()) {
            return -1;
        }

        m_HandlerMap[message_type] = handler;

        return 0;
    }
}
