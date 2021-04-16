#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSerialPort>
#include <QSerialPortInfo>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    objectWidget = ui->visualizationWidget;
    objectScene = objectWidget->renderScene();
    //connect(objectScene, SIGNAL(xRotationChanged(int)), ui->rotXSlider, SLOT(setValue(int)));
    qDebug()<<"babuszka";

    menuAvailablePorts();

    connect(objectScene, &Object_Scene::orientationChanged,this, &MainWindow::setRotationValue);

    connect(objectScene, &Object_Scene::positionChanged, this, &MainWindow::setTranslationValue);

    connect(objectScene, &Object_Scene::orientationChanged, objectScene, &Object_Scene::setOrientation);
    connect(objectScene, &Object_Scene::positionChanged, objectScene, &Object_Scene::setPosition);

    objectScene->setPosition(QVector3D(-1,2,-10));
    objectScene->setOrientation(QQuaternion(QVector4D(QVector3D(0,0,1),0.269)));
    //objectScene->setOrientation(QfromEulerAngles(QVector3D(45,0,0)));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::menuAvailablePorts()
{
    QList<QSerialPortInfo> serialPorts = QSerialPortInfo::availablePorts();
    for(auto &x: serialPorts)
    {
        ui->menuWybierz_port->addAction(new QAction(x.portName(), this));
    }
    connect(ui->menuWybierz_port, &QMenu::triggered, this, &MainWindow::selectPortMenuOptions);
}

void MainWindow::selectPortMenuOptions(QAction *action)
{
    //receiver->setSerialPortName(action->iconText());
}

void MainWindow::setXRotationValue(float value)
{
    ui->xRotationValue->setText(QString::number(value));
    ui->xRotationValue->update();
}

void MainWindow::setYRotationValue(float value)
{
    ui->yRotationValue->setText(QString::number(value));
}

void MainWindow::setZRotationValue(float value)
{
    ui->zRotationValue->setText(QString::number(value));
}

void MainWindow::setXTranslationValue(float value)
{
    ui->xTranslationValue->setText(QString::number(value));
}

void MainWindow::setYTranslationValue(float value)
{
    ui->yTranslationValue->setText(QString::number(value));
}

void MainWindow::setZTranslationValue(float value)
{
    ui->zTranslationValue->setText(QString::number(value));
}

void MainWindow::setRotationValue(const QQuaternion &value)
{
    QVector3D eulerAngles = value.toEulerAngles();

        setXRotationValue(eulerAngles.x());
        setYRotationValue(eulerAngles.y());
        setZRotationValue(eulerAngles.z());
}

void MainWindow::setTranslationValue(const QVector3D &value)
{
    setXTranslationValue(value.x());
    setYTranslationValue(value.y());
    setZTranslationValue(value.z());
}
