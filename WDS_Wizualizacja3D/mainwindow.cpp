#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    objectWidget = ui->visualizationWidget;
    objectScene = objectWidget->renderScene();
    connect(objectScene, SIGNAL(xRotationChanged(int)), ui->rotXSlider, SLOT(setValue(int)));
    qDebug()<<"babuszka";
    objectScene->get_RenderObject()->transform()->setRotationX(45);
}

MainWindow::~MainWindow()
{
    delete ui;
}

