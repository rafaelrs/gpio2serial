#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QThread>
#include <QGraphicsScene>
#include "myevent.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::unpressAllButtons()
{
    ui->pushButton1->setFlat(false);
    ui->pushButton2->setFlat(false);
    ui->pushButton3->setFlat(false);
    if (threadMain.isRunning()) {
        threadMain.stop();
        threadMain.wait();
    }
}

void MainWindow::showGPIOImage(const QString &imageFileName, const int &port_number)
{
    QGraphicsScene *scene = new QGraphicsScene;
    scene->addPixmap(imageFileName);
    switch (port_number) {
    case 0:
        ui->gpio128->setScene(scene);
        break;
    case 1:
        ui->gpio129->setScene(scene);
        break;
    case 2:
        ui->gpio130->setScene(scene);
        break;
    case 3:
        ui->gpio131->setScene(scene);
        break;
    case 4:
        ui->gpio132->setScene(scene);
        break;
    case 5:
        ui->gpio133->setScene(scene);
        break;
    case 6:
        ui->gpio134->setScene(scene);
        break;
    }
}

void MainWindow::showRS232Image(const QString &imageFileName, const int &port_number)
{
    QGraphicsScene *scene = new QGraphicsScene;
    scene->addPixmap(imageFileName);
    switch (port_number) {
    case 0:
        ui->RS232_0->setScene(scene);
        break;
    case 1:
        ui->RS232_1->setScene(scene);
        break;
    case 2:
        ui->RS232_2->setScene(scene);
        break;
    case 3:
        ui->RS232_3->setScene(scene);
        break;
    }

}

bool MainWindow::event(QEvent* event)
{
    if (event->type() == QEvent::User)
    {
        MyEvent* postedEvent = static_cast<MyEvent*>(event);

        if (postedEvent->type() == "gpio") {
            showGPIOImage(postedEvent->value(), postedEvent->port());
        } else if (postedEvent->type() == "rs232") {
            showRS232Image(postedEvent->value(), postedEvent->port());
        } else if (postedEvent->type() == "showStat") {
            qDebug() << postedEvent->value();
            ui->labelStatus->setText(postedEvent->value());
        }

        return true;
    }

    return QWidget::event(event);
}

void MainWindow::on_pushButton1_clicked()
{
    if (ui->pushButton1->isFlat() == false)
    {
        unpressAllButtons();
        threadMain.setParent(this);
        threadMain.setAlgorithm(1);
        threadMain.start();
        ui->pushButton1->setFlat(true);
    } else {
        unpressAllButtons();
    }
}

void MainWindow::on_pushButton2_clicked()
{
    if (ui->pushButton2->isFlat() == false)
    {
        unpressAllButtons();
        threadMain.setParent(this);
        threadMain.setAlgorithm(2);
        threadMain.start();
        ui->pushButton2->setFlat(true);
    } else {
        unpressAllButtons();
    }
}

void MainWindow::on_pushButton3_clicked()
{
    if (ui->pushButton3->isFlat() == false)
    {
        unpressAllButtons();
        threadMain.setParent(this);
        threadMain.setAlgorithm(3);
        threadMain.start();
        ui->pushButton3->setFlat(true);
    } else {
        unpressAllButtons();
    }
}
