#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "object_widget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void menuAvailablePorts();

    void setXRotationValue(float value);

    void setYRotationValue(float value);

    void setZRotationValue(float value);

    void setXTranslationValue(float value);

    void setYTranslationValue(float value);

    void setZTranslationValue(float value);

public slots:
    void selectPortMenuOptions(QAction* action);
    void setRotationValue(const QQuaternion &value);
    void setTranslationValue(const QVector3D &value);


private:
    Ui::MainWindow *ui;
    Object_Scene *objectScene;
    Object_Widget *objectWidget;
};
#endif // MAINWINDOW_H
