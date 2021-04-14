#ifndef RENDER_OBJECT_H
#define RENDER_OBJECT_H

#include <Qt3DCore/QEntity>
#include <Qt3DCore/QTransform>
#include <Qt3DRender/QMesh>
#include <Qt3DRender/QMaterial>
#include <Qt3DExtras/QTorusMesh>
#include <Qt3DExtras/QPhongMaterial>
#include <Qt3DRender/QSceneLoader>
class Render_Object : public Qt3DCore::QEntity
{
public:
    Render_Object(Qt3DCore::QNode *parent = nullptr);

    Qt3DCore::QTransform *transform();
    Qt3DRender::QMesh *mesh();
    Qt3DRender::QMaterial *material();
    Qt3DExtras::QTorusMesh *torusMesh();
    Qt3DRender::QSceneLoader *loader();

private:
    Qt3DCore::QTransform *local_transform;
    Qt3DRender::QMesh *local_mesh;
    Qt3DRender::QMaterial *local_material;
    Qt3DExtras::QTorusMesh *local_torusMesh;
    Qt3DRender::QSceneLoader *local_loader;
};

#endif // RENDER_OBJECT_H
