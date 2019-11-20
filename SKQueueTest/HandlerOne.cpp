
#include "stdafx.h"
#include "HandlerOne.h"
#include "MessageQueue.h"
#include "Log.h"

namespace MQ {
    int CHandlerOne::Handle(const Message& message)
    {
        LOG_DEBUG("CListenerOne::Handle message : " << message.m_Content);
        delete[] message.m_Content;
        // m_result_queue->push_data (message);
        return 0;
    }
}