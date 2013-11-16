#include "mainwindow.h"
#include <QApplication>
#include <QSettings>
#include <QFile>
#include <QDebug>

int main(int argc, char *argv[])
{
    qputenv("QT_QPA_FONTDIR", "/usr/share/fonts/gnu-free");
    QApplication a(argc, argv);

    QSettings conf("gpio2serial", "gpio2serial");
    QFile confFile(conf.fileName());
    if (!confFile.open(QIODevice::ReadOnly)) {
        qDebug() << "Error reading config file from " << conf.fileName();
        qDebug() << "Use gpio2serial --init to create it";
        return -1;
    }

    MainWindow w;
    w.showFullScreen();

    return a.exec();
}
