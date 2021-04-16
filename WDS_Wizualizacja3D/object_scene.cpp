#include "object_scene.h"

#include <Qt3DExtras/QCuboidMesh>
#include <Qt3DExtras/QTorusMesh>
#include <Qt3DExtras/QPhongMaterial>
#include <Qt3DCore/QEntity>
#include <QTransform>
#include <QScreen>
#include <QLayout>
#include <QCheckBox>
#include <QScreen>
#include <Qt3DCore/QTransform>
#include <Qt3DRender/QPointLight>
#include <Qt3DExtras/Qt3DWindow>
#include <Qt3DExtras/QOrbitCameraController>
#include <Qt3DExtras/QForwardRenderer>

#include <QPushButton>
#include <QLabel>
#include <Qt3DExtras/QForwardRenderer>


Object_Scene::Object_Scene(QWidget *parent)
    : QWidget(parent), objectEntity(nullptr)
{

    Qt3DExtras::Qt3DWindow *view = new Qt3DExtras::Qt3DWindow();
    view->defaultFrameGraph()->setClearColor(QColor(QRgb(0xFFDFD3)));
    QWidget *container = QWidget::createWindowContainer(view);


    QSize screenSize = view->screen()->size();
    container->setMinimumSize(QSize(400, 400));
    container->setMaximumSize(screenSize);
    container->setFocusPolicy(Qt::NoFocus);

    // Root entity
    rootEntity = new Qt3DCore::QEntity();

    // Camera
    cameraEntity = view->camera();

    // For the Blender model:
        // X+ -> right
        // Y+ -> away
        // Z+ -> up
        cameraEntity->lens()->setPerspectiveProjection(45.0f, 16.0f/9.0f, 0.1f, 1000.0f);
        cameraEntity->setPosition(QVector3D(0, -5, 5.0f));
        cameraEntity->setUpVector(QVector3D(0, 0, 1));
        cameraEntity->setViewCenter(QVector3D(0, 0, 0));
    Qt3DExtras::QOrbitCameraController *camController = new Qt3DExtras::QOrbitCameraController(rootEntity);//moje
    camController->setCamera(cameraEntity);//moje

    Qt3DCore::QEntity *lightEntity = new Qt3DCore::QEntity(rootEntity);
    Qt3DRender::QPointLight *light = new Qt3DRender::QPointLight(lightEntity);
    light->setColor("white");
    light->setIntensity(1);
    lightEntity->addComponent(light);
    Qt3DCore::QTransform *lightTransform = new Qt3DCore::QTransform(lightEntity);
    //lightTransform->setTranslation(cameraEntity->position());
    //lightEntity->addComponent(lightTransform);
    lightTransform->setTranslation(QVector3D(30,-100, -20));
    lightEntity->addComponent(lightTransform);

      // Torus
    /*
     Qt3DCore::QEntity *torusEntity = new Qt3DCore::QEntity(rootEntity);
     Qt3DRender::QMaterial *material = new Qt3DExtras::QPhongMaterial(rootEntity);
    Qt3DExtras::QTorusMesh *torusMesh = new Qt3DExtras::QTorusMesh;
    torusMesh->setRadius(5);
    torusMesh->setMinorRadius(1);
    torusMesh->setRings(100);
    torusMesh->setSlices(20);
    //3DCore::QTransform *torusTransform = new Qt3DCore::QTransform;
    objectEntity->transform()->setScale3D(QVector3D(1.5, 1, 0.5));
    objectEntity->transform()->setRotation(QQuaternion::fromAxisAndAngle(QVector3D(1, 0, 0), 45.0f));
    torusEntity->addComponent(torusMesh);
    objectEntity->transform()->setRotationY(95);
    //torusEntity->addComponent(torusTransform);
    torusEntity->addComponent(material);
    torusEntity->addComponent(objectEntity->transform());
    objectEntity->transform()->setRotationZ(90);*/


    /*sceneLoaderEntity = new Qt3DCore::QEntity(rootEntity);
    loader = new Qt3DRender::QSceneLoader(sceneLoaderEntity);
    objectEntity = new Render_Object(rootEntity);
    objectEntity->transform()->setRotationY(45);
    objectEntity->transform()->setScale(0.1f);
    objectEntity->transform()->setTranslation(QVector3D(0, -2, 0));
    loader->setObjectName("object1.dae");
    sceneLoaderEntity->addComponent(loader);
    loader->setSource(QUrl(QString("file:C:/Users/john/OneDrive/Pulpit/Dragon.dae")));*/

   // torusTransform->setRotationY(45);
    //sceneLoaderEntity->addComponent(objectEntity->transform());




    // Set root object of the scene
    createRenderObject();
    view->setRootEntity(rootEntity);
    //createRenderableObject(rootEntity);
    this->setLayout(new QGridLayout);
    layout()->addWidget(container);



}



void Object_Scene::createRenderObject()
{
    if(objectEntity)
    {
        delete objectEntity;
    }

    objectEntity = new Render_Object(rootEntity);
    //dzialajace wczytywanie obiektu
    objectEntity->loader()->setSource(QUrl(QString("file:C:/Users/john/OneDrive/Pulpit/Dragon.dae")));

    //dzialajacy torus
    /*objectEntity->torusMesh()->setRadius(5);
    objectEntity->torusMesh()->setMinorRadius(1);
    objectEntity->torusMesh()->setRings(100);
    objectEntity->torusMesh()->setSlices(20);

    objectEntity->transform()->setScale3D(QVector3D(1.5, 1, 0.5));
    objectEntity->transform()->setRotation(QQuaternion::fromAxisAndAngle(QVector3D(1, 0, 0), 45.0f));
    objectEntity->transform()->setScale(0.3);*/
}

Render_Object *Object_Scene::get_RenderObject()
{
    return objectEntity;
}



static void qNormalizeAngle(int &angle)
{
    while (angle < 0)
        angle += 360 * 16;
    while (angle > 360)
        angle -= 360 * 16;
}

void Object_Scene::setXRotation(int angle)
{
    qNormalizeAngle(angle);
        objectEntity->transform()->setRotationX(angle);
        emit xRotationChanged(angle);
}


