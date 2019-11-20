
#include "MessageQueue.h"
#include <assert.h>

namespace MQ
{
    CMessageQueue::CMessageQueue(CDispatcher* dispacher, int workeCount)
            : m_Dispatcher(dispacher), m_IsShutDown(false)
    {
        m_AvailableThreadCount = 0;
        m_ThreadCount = workeCount;
        assert(workeCount > 0);
        for (int i = 0; i < workeCount; i++)
        {
            m_Threads.push_back(new Worker(*this));
        }
    }

    CMessageQueue::~CMessageQueue()
    {
        for (std::vector<Worker*>::iterator i = m_Threads.begin(); i != m_Threads.end(); i++)
        {
            delete (*i);
        }
        m_Threads.clear();
    }

    int CMessageQueue::RegistDispatcher(CDispatcher* dispacher)
    {
        m_Dispatcher = dispacher;
        return 0;
    }

    int CMessageQueue::PushBack(const Message& message)
    {
        LOG_DEBUG("CMessageQueue::PushBack");
        {
            std::lock_guard<std::mutex> lock(m_Mutex);
            m_MessageList.push_back(message);
        }
        m_Condition.notify_one();   ///唤醒线程
        LOG_DEBUG("CMessageQueue::PushBack over");
        return 0;
    }

    void CMessageQueue::Join()
    {
        for (Worker* thread : m_Threads)
            thread->Join();
    }

    void CMessageQueue::ShutDown()
    {
        std::lock_guard<std::mutex> lock(m_Mutex);
        m_IsShutDown = true;
        m_Condition.notify_all();
    }
}