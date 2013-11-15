#ifndef MYEVENT_H
#define MYEVENT_H
#include <QEvent>

class MyEvent : public QEvent
{
public:
    MyEvent(const QString& op_type, const int& port_number, const QString& event_par) : QEvent(QEvent::User)
    {
        operationType = op_type;
        eventParameter = event_par;
        portNumber = port_number;
    }
    ~MyEvent() {}

    QString value()
    {
        return eventParameter;
    }

    QString type()
    {
        return operationType;
    }

    int port()
    {
        return portNumber;
    }

private:
    QString operationType;
    QString eventParameter;
    int portNumber;
};

#endif // MYEVENT_H
