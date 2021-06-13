#ifndef RENDER_OBJECT_H
#define RENDER_OBJECT_H

#include <Qt3DCore/QEntity>
#include <Qt3DCore/QTransform>
#include <Qt3DRender/QMesh>
#include <Qt3DRender/QTextureImage>
#include <QDiffuseMapMaterial>
#include <Qt3DRender/QMaterial>
#include <Qt3DExtras/QTorusMesh>
#include <Qt3DExtras/QPhongMaterial>
#include <Qt3DRender/QSceneLoader>
#include <Qt3DExtras/QDiffuseSpecularMapMaterial>

/*!
 * \class Render_Object
 * \brief Klasa posiada cechy obiektu 3D jak forma, orientacja, pozycja i inne
 */
class Render_Object : public Qt3DCore::QEntity
{
public:
    /*!
     * \brief Render_Object konstruktor
     * \param QEntity parent
     */
    Render_Object(Qt3DCore::QEntity *parent = nullptr);


    /*!
     * \brief Dostań local_tranform
     * \return pole typu QTranform
     */
    Qt3DCore::QTransform *transform();



    /*!
     * \brief Dostań local_mesh
     * \return pole typu QMesh
     */
    Qt3DRender::QTextureImage *texture();


    /*!
     * \brief Dostań local_material
     * \return pole typu QMaterial
     */
    Qt3DRender::QMaterial *material();
    Qt3DExtras::QTorusMesh *torusMesh();
    Qt3DExtras::QDiffuseSpecularMapMaterial *map();

    /*!
     * \brief Dostań local_loader
     * \return pole typu QSceneLoader
     */
    Qt3DRender::QSceneLoader *loader();

    Qt3DRender::QMesh *mesh();

private:
    Qt3DExtras::QDiffuseSpecularMapMaterial *local_map;
    Qt3DCore::QTransform *local_transform; //!< transformacja obiektu
    Qt3DRender::QTextureImage *local_texture;
    Qt3DRender::QMaterial *local_material;
    Qt3DExtras::QTorusMesh *local_torusMesh;
    Qt3DRender::QMesh *local_mesh;
    Qt3DRender::QSceneLoader *local_loader; //!< zawiera zaladowany obiekt 3D z pliku
};

#endif // RENDER_OBJECT_H
