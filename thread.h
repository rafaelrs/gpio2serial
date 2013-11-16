#ifndef THREAD_H
#define THREAD_H

#include <QThread>

class Thread : public QThread
{
    Q_OBJECT

public:
    Thread();

    void setAlgorithm(const int &number);
    void run();
    void stop();

    void writeSettings();
    void readSettings();

    QString readFromFile(const QString &filename);
    void writeToFile(const QString &filename, const QString &fileContent);

private:
    int algorithmNumber;
    volatile bool stopped;

    QString gpio128_path;
    QString gpio129_path;
    QString gpio130_path;
    QString gpio131_path;
    QString gpio132_path;
    QString gpio133_path;
    QString gpio134_path;

    QString gpio128_0;
    QString gpio129_0;
    QString gpio130_0;
    QString gpio131_0;
    QString gpio132_0;
    QString gpio133_0;
    QString gpio134_0;

    QString gpio128_1;
    QString gpio129_1;
    QString gpio130_1;
    QString gpio131_1;
    QString gpio132_1;
    QString gpio133_1;
    QString gpio134_1;

    QString RS232SC0_path;
    QString RS232SC1_path;
    QString RS232SC2_path;
    QString RS232SC3_path;

    QString RS232SC0_start;
    QString RS232SC1_start;
    QString RS232SC2_start;
    QString RS232SC3_start;

    QString RS232SC0_stop;
    QString RS232SC1_stop;
    QString RS232SC2_stop;
    QString RS232SC3_stop;

    QString SC0_start_button1;
    QString SC1_start_button1;
    QString SC2_start_button1;
    QString SC3_start_button1;

    QString SC0_stop_button1;
    QString SC1_stop_button1;
    QString SC2_stop_button1;
    QString SC3_stop_button1;

    QString SC0_start_button2;
    QString SC1_start_button2;
    QString SC2_start_button2;
    QString SC3_start_button2;

    QString SC0_stop_button2;
    QString SC1_stop_button2;
    QString SC2_stop_button2;
    QString SC3_stop_button2;

    QString SC0_start_button3;
    QString SC1_start_button3;
    QString SC2_start_button3;
    QString SC3_start_button3;

    QString SC0_stop_button3;
    QString SC1_stop_button3;
    QString SC2_stop_button3;
    QString SC3_stop_button3;

    unsigned long delayAT1;
    unsigned long delayAT2;
    unsigned long delayAT3;

    void sendSignal(const QString &op_type, const int &port_number, const QString &event_par);
    bool waitForGPIO(const QString &gpio_path);
};

#endif // THREAD_H
