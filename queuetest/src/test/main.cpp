#include <iostream>
#include <string.h>
#include <unistd.h>

int main()
{
//    std::cout << "====main begin===\n";
//    MQ::SKQueue skqueue;
//
//    MQ::IHandler* handler = new MQ::CHandlerOne();
//    skqueue.RegistHandler(MQ::gMessageOne, handler);
//
//    std::cout << "==== queue run===\n";
//
//    for (int i = 0; ; i++)
//    {
//        MQ::Message message;
//        message.m_Type = MQ::gMessageOne;
//        char* content = new char[20];
//        memset(content, 0, 20);
//        snprintf(content, 20, "%d %s", i, "hello word");
//        message.m_Content = content;
//        LOG_DEBUG(" sender.Send(): " << message.m_Content);
//        skqueue.AddMsg(message);
//        sleep(1);
//    }
//
//    std::cout << "==== sender join===\n";
//    skqueue.Join();
//    std::cout << "==== sender stop===\n";
//    skqueue.Stop();
    return 0;
}