#ifndef OBJECT_VIEW_H
#define OBJECT_VIEW_H


#include <QWidget>
#include "object_scene.h"

namespace Ui {
class Object_Widget;
}


class Object_Widget : public QWidget
{
    Q_OBJECT

public:

    explicit Object_Widget(QWidget *parent = nullptr);

    ~Object_Widget();

    Object_Scene *renderScene();
public slots:


private:
    Ui::Object_Widget *ui;
};

#endif // OBJECT_VIEW_H
