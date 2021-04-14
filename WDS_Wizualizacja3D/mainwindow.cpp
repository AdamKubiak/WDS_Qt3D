#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //objectWidget = ui->visualizationWidget;
    //objectScene = objectWidget->renderScene();
}

MainWindow::~MainWindow()
{
    delete ui;
}

