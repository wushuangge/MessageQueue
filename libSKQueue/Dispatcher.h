

#ifndef _DISPATCHER_H_
#define _DISPATCHER_H_

namespace MQ {
    class CHandlerFactory;
    class Message;

    class CDispatcher
    {
    public:
        CDispatcher(CHandlerFactory* handlerFactory);
        int Dispatch(const Message& message);
    private:
        CHandlerFactory* m_HandlerFactory;
    };
}
#endif