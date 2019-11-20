#include "IHandler.h"
#include "HandlerFactory.h"
#include "Dispatcher.h"
#include "MessageQueue.h"
#include "Log.h"

namespace MQ {
    CDispatcher::CDispatcher(CHandlerFactory* handlerFactory)
        : m_HandlerFactory(handlerFactory)
    {

    }

    int CDispatcher::Dispatch(const Message& message)
    {
        IHandler* handler = m_HandlerFactory->GetHandler(message.m_Type);
        if (handler == NULL) {
            return -1;
        }
        LOG_DEBUG("CDispatcher::Dispatch GetHandler success");
        return handler->Handle(message);
    }
}