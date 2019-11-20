#ifndef _MESSAGE_QUEUE_H_
#define _MESSAGE_QUEUE_H_
#include "Dispatcher.h"
#include "Log.h"
#include <list>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>


namespace MQ {
    class CDispatcher;
    class IHandler;
    class Worker;

    static const int gMessageOne = 0;

    template <typename T>
    class A
    {
    public:
        int m_Type;
        char* m_Content;
    };

    class Message
    {
    public:
        int m_Type;
        char* m_Content;
    };

    class CMessageQueue
    {
    public:
        CMessageQueue(CDispatcher* dispacher, int workerCount);
        ~CMessageQueue();
        int RegistDispatcher(CDispatcher* dispacher);
        int AddMsg(const Message& message);
        int AddMsg(const A<CMessageQueue>& message);
        void Join();
        void ShutDown();

        friend class Worker;

    private:
        CDispatcher* m_Dispatcher;
        std::list <Message> m_MessageList;
        std::list <A<CMessageQueue>> m_AList;

        std::mutex m_Mutex;
        std::condition_variable m_Condition;
        int m_AvailableThreadCount;
        int m_ThreadCount;
        bool m_IsShutDown;
        std::vector<Worker*> m_Threads;
    };

    class Worker
    {
    public:
        Worker(CMessageQueue& messageQueue, bool oneShot = false)
            : m_MessageQueue(messageQueue), m_OneShot(oneShot)
        {
            m_Thread = new std::thread(&Worker::Run, this);
        }

        /** Thread run method
        */
        void Run()
        {
            LOG_DEBUG("Worker::Run()");
            Message message;
            A<CMessageQueue> msg;

            while (true)
            {
                LOG_DEBUG("Worker::while");
                {
                    std::unique_lock<std::mutex> lock(m_MessageQueue.m_Mutex);
                    m_MessageQueue.m_AvailableThreadCount++;
                    LOG_DEBUG("available thread = " << m_MessageQueue.m_AvailableThreadCount);

//                    while (m_MessageQueue.m_MessageList.empty()) {
//                        m_MessageQueue.m_Condition.wait(lock);
//                    }

                    while (m_MessageQueue.m_AList.empty()) {
                        m_MessageQueue.m_Condition.wait(lock);
                    }

                    if (m_MessageQueue.m_IsShutDown) {
                        m_MessageQueue.m_AvailableThreadCount--;
                        return;
                    }

//                    message = m_MessageQueue.m_MessageList.front();
//                    m_MessageQueue.m_MessageList.pop_front();
//                    m_MessageQueue.m_AvailableThreadCount--;

                    msg = m_MessageQueue.m_AList.front();
                    m_MessageQueue.m_AList.pop_front();
                    m_MessageQueue.m_AvailableThreadCount--;
                }

                if (m_MessageQueue.m_Dispatcher != NULL) {
                    m_MessageQueue.m_Dispatcher->Dispatch(message);
                }

                if (m_OneShot) {
                    return;
                }
            }
            //HT_INFO("thread exit");  
        }

        void Join()
        {
            if (m_Thread->joinable())
                m_Thread->join();
        }

    private:

        /// Shared application queue state object  
        CMessageQueue& m_MessageQueue;

        /// Set to <i>true</i> if thread should exit after executing request  
        bool m_OneShot;
        std::thread* m_Thread;
    };
}




#endif