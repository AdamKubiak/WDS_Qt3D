#include "render_object.h"

Render_Object::Render_Object(Qt3DCore::QNode *parent)
    : Qt3DCore::QEntity(parent)
    , local_transform(new Qt3DCore::QTransform()),local_mesh(new Qt3DRender::QMesh), local_material(new Qt3DExtras::QPhongMaterial(parent)), local_torusMesh(new Qt3DExtras::QTorusMesh), local_loader(new Qt3DRender::QSceneLoader(parent))
{
    addComponent(local_transform);
    //addComponent(local_mesh);
    addComponent(local_material);
    //addComponent(local_torusMesh);
    addComponent(local_material);
    addComponent(local_loader);
    qDebug()<<parent;
}


Qt3DCore::QTransform *Render_Object::transform()
{
    return local_transform;
}

Qt3DRender::QMesh *Render_Object::mesh()
{
    return local_mesh;
}

Qt3DRender::QMaterial *Render_Object::material()
{
    return local_material;
}

Qt3DExtras::QTorusMesh *Render_Object::torusMesh()
{
    return local_torusMesh;
}

Qt3DRender::QSceneLoader *Render_Object::loader()
{
    return local_loader;
}



