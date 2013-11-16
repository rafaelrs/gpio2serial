#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QSettings>
#include "thread.h"
#include "myevent.h"
#include "mainwindow.h"
#include <QCoreApplication>

#define WAITFORPROC(waitSignal) if (!waitForGPIO(waitSignal)) continue

struct MyThread : public QThread { using QThread::msleep;};

Thread::Thread()
{
    readSettings();
}

void Thread::setAlgorithm(const int &number)
{
    algorithmNumber = number;
}

void Thread::run()
{
    stopped = false;

    qDebug() << "Selected algorithm " << algorithmNumber;
    switch (algorithmNumber) {
    case 1:
        while (!stopped) {
            WAITFORPROC(gpio128_path);
            //qDebug() << "GPIO state: " << readFromFile(gpio128_path);
            writeToFile(gpio128_path, "0");
            qDebug() << "Returning GPIO state: " << readFromFile(gpio128_path);
            sendSignal("gpio", 0, gpio128_1);

            qDebug() << "Waiting for " << delayAT1 <<" mseconds";
            MyThread::msleep(delayAT1);

            qDebug() << "Sending START to RS232SC0";
            writeToFile(RS232SC0_path, SC0_start_button1);
            sendSignal("gpio", 0, gpio128_0);
            sendSignal("rs232", 0, RS232SC0_start);
            qDebug() << "Sending START to RS232SC1";
            writeToFile(RS232SC1_path, SC1_start_button1);
            sendSignal("rs232", 1, RS232SC1_start);

            WAITFORPROC(gpio130_path);
            sendSignal("gpio", 2, gpio130_1);
            qDebug() << "Sending STOP to RS232SC0";
            writeToFile(RS232SC0_path, SC0_stop_button1);
            sendSignal("rs232", 0, RS232SC0_stop);
            writeToFile(gpio130_path, "0");
            qDebug() << "Returning GPIO state: " << readFromFile(gpio130_path);
            sendSignal("gpio", 2, gpio130_0);
        }
        break;

    case 2:
        while (!stopped) {
            WAITFORPROC(gpio128_path);
            //qDebug() << "GPIO state: " << readFromFile(gpio128_path);
            writeToFile(gpio128_path, "0");
            qDebug() << "Returning GPIO state: " << readFromFile(gpio128_path);
            sendSignal("gpio", 0, gpio128_1);
            qDebug() << "Sending START to RS232SC1";
            writeToFile(RS232SC1_path, SC1_start_button2);
            sendSignal("rs232", 1, RS232SC1_start);

            qDebug() << "Waiting for " << delayAT2 <<" mseconds";
            MyThread::msleep(delayAT2);

            sendSignal("gpio", 0, gpio128_0);
            qDebug() << "Sending START to RS232SC0";
            writeToFile(RS232SC0_path, SC0_start_button2);
            sendSignal("rs232", 0, RS232SC0_start);

            WAITFORPROC(gpio130_path);
            sendSignal("gpio", 2, gpio130_1);
            qDebug() << "Sending STOP to RS232SC0";
            writeToFile(RS232SC0_path, SC0_stop_button2);
            sendSignal("rs232", 0, RS232SC0_stop);
            writeToFile(gpio130_path, "0");
            qDebug() << "Returning GPIO state: " << readFromFile(gpio130_path);
            sendSignal("gpio", 2, gpio130_0);
        }
        break;
    case 3:
        while (!stopped) {
//            WAITFORPROC(gpio129_path);
//            qDebug() << "GPIO state: " << readFromFile(gpio130_path);
//            sendSignal("gpio", 2, gpio130_1);
//            writeToFile(gpio130_path, "0");
//            qDebug() << "Returning GPIO state: " << readFromFile(gpio130_path);

//            qDebug() << "Waiting for " << delayAT3 <<" mseconds";
//            MyThread::msleep(delayAT3);

//            qDebug() << "Sending START to RS232";
//            writeToFile(RS232SC2_path, SC0_start_button1);
//            sendSignal("gpio", 2, gpio130_0);
//            sendSignal("rs232", 2, RS232SC2_start);
        }
        break;
    }

}

bool Thread::waitForGPIO(const QString &gpio_path)
{
    //qDebug() << "Entering to wait loop for " << gpio_path;
    sendSignal("showStat", 0, "Entering to wait loop for " + gpio_path);
    while (readFromFile(gpio_path) == "0") {
        if (stopped) return false;
    }
    //sendSignal("showStat", 0, "");
    return true;
}

void Thread::sendSignal(const QString &op_type, const int &port_number, const QString &event_par)
{
    MyEvent* myEvent = new MyEvent(op_type, port_number, event_par);
    QCoreApplication::postEvent(parent(), myEvent);
}

QString Thread::readFromFile(const QString &filename)
{
    QFile gpioFile(filename);
    if (gpioFile.open(QIODevice::ReadOnly)) {
        QTextStream gpioStream(&gpioFile);
        QString fileContent = gpioStream.read(1);
        gpioFile.close();
        return fileContent;
    }

    return "";
}

void Thread::writeToFile(const QString &filename, const QString &fileContent)
{
    QFile gpioFile(filename);
    if (gpioFile.open(QIODevice::WriteOnly)) {
        QTextStream gpioStream(&gpioFile);
        gpioStream << fileContent;
        gpioFile.close();
    }
}

void Thread::stop()
{
    stopped = true;
    sendSignal("showStat", 0, "");
}

void Thread::writeSettings()
{
//    QSettings conf("gpio2serial", "GPIO2Serial");

//    conf.beginGroup("General");
//    conf.setValue("gpio128_path", "/sys/class/gpio/gpio128/value");
//    conf.setValue("gpio129_path", "/sys/class/gpio/gpio129/value");
//    conf.setValue("gpio130_path", "/sys/class/gpio/gpio130/value");
//    conf.setValue("gpio131_path", "/sys/class/gpio/gpio131/value");
//    conf.setValue("gpio132_path", "/sys/class/gpio/gpio132/value");
//    conf.setValue("gpio133_path", "/sys/class/gpio/gpio133/value");
//    conf.setValue("gpio134_path", "/sys/class/gpio/gpio134/value");
//    conf.endGroup();
}

void Thread::readSettings()
{
    QSettings conf("gpio2serial", "gpio2serial");

    conf.beginGroup("General");
    qDebug() << "Path to configuration file: " << conf.fileName();
    gpio128_path = conf.value("gpio128_path").toString();
    gpio129_path = conf.value("gpio129_path").toString();
    gpio130_path = conf.value("gpio130_path").toString();
    gpio131_path = conf.value("gpio131_path").toString();
    gpio132_path = conf.value("gpio132_path").toString();
    gpio133_path = conf.value("gpio133_path").toString();
    gpio134_path = conf.value("gpio134_path").toString();

    gpio128_0 = conf.value("gpio128_0").toString();
    gpio129_0 = conf.value("gpio129_0").toString();
    gpio130_0 = conf.value("gpio130_0").toString();
    gpio131_0 = conf.value("gpio131_0").toString();
    gpio132_0 = conf.value("gpio132_0").toString();
    gpio133_0 = conf.value("gpio133_0").toString();
    gpio134_0 = conf.value("gpio134_0").toString();

    gpio128_1 = conf.value("gpio128_1").toString();
    gpio129_1 = conf.value("gpio129_1").toString();
    gpio130_1 = conf.value("gpio130_1").toString();
    gpio131_1 = conf.value("gpio131_1").toString();
    gpio132_1 = conf.value("gpio132_1").toString();
    gpio133_1 = conf.value("gpio133_1").toString();
    gpio134_1 = conf.value("gpio134_1").toString();

    RS232SC0_path = conf.value("RS232SC0_path").toString();
    RS232SC1_path = conf.value("RS232SC1_path").toString();
    RS232SC2_path = conf.value("RS232SC2_path").toString();
    RS232SC3_path = conf.value("RS232SC3_path").toString();

    RS232SC0_start = conf.value("RS232SC0_start").toString();
    RS232SC1_start = conf.value("RS232SC1_start").toString();
    RS232SC2_start = conf.value("RS232SC2_start").toString();
    RS232SC3_start = conf.value("RS232SC3_start").toString();

    RS232SC0_stop = conf.value("RS232SC0_stop").toString();
    RS232SC1_stop = conf.value("RS232SC1_stop").toString();
    RS232SC2_stop = conf.value("RS232SC2_stop").toString();
    RS232SC3_stop = conf.value("RS232SC3_stop").toString();

    SC0_start_button1 = conf.value("SC0_start_button1").toString();
    SC1_start_button1 = conf.value("SC1_start_button1").toString();
    SC2_start_button1 = conf.value("SC2_start_button1").toString();
    SC3_start_button1 = conf.value("SC3_start_button1").toString();

    SC0_stop_button1 = conf.value("SC0_stop_button1").toString();
    SC1_stop_button1 = conf.value("SC1_stop_button1").toString();
    SC2_stop_button1 = conf.value("SC2_stop_button1").toString();
    SC3_stop_button1 = conf.value("SC3_stop_button1").toString();

    SC0_start_button2 = conf.value("SC0_start_button2").toString();
    SC1_start_button2 = conf.value("SC1_start_button2").toString();
    SC2_start_button2 = conf.value("SC2_start_button2").toString();
    SC3_start_button2 = conf.value("SC3_start_button2").toString();

    SC0_stop_button2 = conf.value("SC0_stop_button2").toString();
    SC1_stop_button2 = conf.value("SC1_stop_button2").toString();
    SC2_stop_button2 = conf.value("SC2_stop_button2").toString();
    SC3_stop_button2 = conf.value("SC3_stop_button2").toString();

    SC0_start_button3 = conf.value("SC0_start_button3").toString();
    SC1_start_button3 = conf.value("SC1_start_button3").toString();
    SC2_start_button3 = conf.value("SC2_start_button3").toString();
    SC3_start_button3 = conf.value("SC3_start_button3").toString();

    SC0_stop_button3 = conf.value("SC0_stop_button3").toString();
    SC1_stop_button3 = conf.value("SC1_stop_button3").toString();
    SC2_stop_button3 = conf.value("SC2_stop_button3").toString();
    SC3_stop_button3 = conf.value("SC3_stop_button3").toString();

    delayAT1 = conf.value("delayAT1").toULongLong();
    delayAT2 = conf.value("delayAT2").toULongLong();
    delayAT3 = conf.value("delayAT3").toULongLong();

    conf.endGroup();
}
