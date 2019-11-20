// SKQueueTest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include "HandlerOne.h"
#include <iostream>
#include "Log.h"
#include "SKQueue.h"
#include <windows.h>

#pragma comment(lib, "SKQueue.lib")

int main()
{
    std::cout << "====main begin===\n";
    MQ::SKQueue queue;

    MQ::IHandler* handler = new MQ::CHandlerOne();
    queue.RegistHandler(MQ::gMessageOne, handler);

    std::cout << "==== queue run===\n";

    for (int i = 0; ; i++)
    {
        MQ::Message message;
        message.m_Type = MQ::gMessageOne;
        char* content = new char[20];
        memset(content, 0, 20);
        snprintf(content, 20, "%d %s", i, "hello word");
        message.m_Content = content;
        LOG_DEBUG(" sender.Send(): " << message.m_Content);
        queue.Send(message);
        Sleep(1);
    }

    std::cout << "==== sender join===\n";
    queue.Join();
    std::cout << "==== sender stop===\n";
    queue.Stop();
    return 0;
}