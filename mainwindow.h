#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "thread.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void unpressAllButtons();
    void showGPIOImage(const QString &imageFileName, const int &port_number);
    void showRS232Image(const QString &imageFileName, const int &port_number);

private slots:
    void on_pushButton1_clicked();

    void on_pushButton2_clicked();

    void on_pushButton3_clicked();

private:
    Thread threadMain;
    Ui::MainWindow *ui;

protected:
    bool event(QEvent* event);

};

#endif // MAINWINDOW_H
