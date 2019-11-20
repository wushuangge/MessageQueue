
#ifndef _SK_QUEUE_H
#define _SK_QUEUE_H

#include "Dispatcher.h"
#include "HandlerFactory.h"
#include "MessageQueue.h"
#include <memory>
#include <algorithm>

namespace MQ
{
    class SKQueue
    {
    public:
        SKQueue();
        int Send(const Message& message);
        int RegistHandler(int type, IHandler* handler);
        int Join();
        int Stop();
    protected:
    private:
        std::auto_ptr <CHandlerFactory> m_HandlerFactory;
        std::auto_ptr <CMessageQueue> m_MessageQueue;
        std::auto_ptr <CDispatcher> m_Dispatcher;
    };
}

#endif