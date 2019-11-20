#include "Log.h"
#include "SKQueue.h"
#include <iostream>

using namespace MQ;

SKQueue::SKQueue()
{
    m_HandlerFactory.reset(new CHandlerFactory());
    m_Dispatcher.reset(new CDispatcher(m_HandlerFactory.get()));
    m_MessageQueue.reset(new CMessageQueue(m_Dispatcher.get(), 5));
}

int SKQueue::Send(const Message& message)
{
    LOG_DEBUG("CSender::Send");
    m_MessageQueue->PushBack(message);
    return 0;
}

int SKQueue::RegistHandler(int type, IHandler* handler)
{
    return m_HandlerFactory->RegistHandler(type, handler);
}

int SKQueue::Join()
{
    std::cout << "CSender::Join()\n";

    m_MessageQueue->Join();
    return 0;
}

int SKQueue::Stop()
{
    m_MessageQueue->ShutDown();
    return 0;
}
