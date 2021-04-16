#ifndef OBJECT_SCENE_H
#define OBJECT_SCENE_H

#include "render_object.h"
#include<Qt3DRender/QSceneLoader>
#include <QVector3D>
#include <QWidget>
#include <QCheckBox>
#include <QPushButton>
#include <QLabel>
#include <Qt3DCore/QTransform>
#include <Qt3DExtras/QDiffuseMapMaterial>
#include <Qt3DRender/QCamera>
#include <Qt3DRender/QTextureImage>

class Object_Scene : public QWidget
{
    Q_OBJECT
public:
    explicit Object_Scene(QWidget *parent = nullptr);

    void createRenderObject();
    Render_Object *get_RenderObject();

public slots:
    // slots for xyz-rotation slider
    void setXRotation(int angle);
    //void setYRotation(int angle);
    //void setZRotation(int angle);

signals:
    // signaling rotation from mouse movement
    void xRotationChanged(int angle);
    //void yRotationChanged(int angle);
    //void zRotationChanged(int angle);

private:

    Qt3DCore::QEntity *rootEntity;

    Qt3DRender::QCamera *cameraEntity;

    Render_Object* objectEntity;



    QQuaternion orientation;

    QVector3D position;

};

#endif // OBJECT_VIEW_SCENE_H
