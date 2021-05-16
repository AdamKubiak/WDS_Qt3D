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


/*!
 * \class Object_Scene
 * \brief Klasa ma na celu stworzenie scene, kamerę, oświetlenie dla wybranego modelu 3D
 */
class Object_Scene : public QWidget
{
    Q_OBJECT
public:
    /*!
     * \brief Object_Scene konstruktor
     * \param QWidget parent
     */
    explicit Object_Scene(QWidget *parent = nullptr);

    /*!
     * \brief Funkcja renderuje obiekt który aktualnie znajduję się w zmiennej
     * local_loader obiektu klasy Render_Object
     */
    void createRenderObject();

    /*!
     * \brief Funkcja odpowiedzialna za przypisywanie wartości pola typu QUrl i wyrenderowanie
     * obiektu z podanej ścieżki
     * \param renderFile - zmienna typu QUrl która przechowuje ścieżkę do obiektu 3D
     */
    void setRenderFile(QUrl renderFile);

    /*!
     * \brief Funkcja zwraca pole wskaźnik do pola klasy Object_Scene
     * \return pole typu Render_Object
     */
    Render_Object *get_RenderObject();

    void setTextureFile(QUrl textureFile);


    void setSceneLoader(QUrl renderFile);

    Render_Object* getObjectEntity(){return objectEntity;};

public slots:
    /*!
     * \brief Slot zmienia orientacje obiektu na podstawie otrzymanych danych
     * \param orientation - zmienna typu QQuaternion
     */
    void setOrientation(const QQuaternion &orientation);

    /*!
     * \brief Slot zmienia pozycje obiektu na podstawie otrzymanych danych
     * \param position - zmienna typu QVector3D
     */
    void setPosition(const QVector3D &position);

signals:

    /*!
     * \brief Sygnał jest emitowany gdy orientacja obiektu ulega zmianie
     * \param Aktualna pozycja obiektu typu QQuaternion
     */
    void orientationChanged(const QQuaternion&);


    /*!
     * \brief Sygnał jest emitowany gdy pozycja obiektu ulega zmianie
     * \param Aktualna pozycja obiektu typu QVector
     */
    void positionChanged(const QVector3D&);




private:

    Qt3DCore::QEntity *rootEntity; //!< Główny obiekt sceny do której podpięte są wszystkie elementy Qt3D

    Qt3DRender::QCamera *cameraEntity;//!<Kamera sceny

    Render_Object* objectEntity;//!<obiekt do wyrenderowania


    QQuaternion orientation; //!< aktualna orientacja obiektu

    QVector3D position;//!< aktualna pozycja obiektu

    QUrl renderFile; //!< Ścieżka do pliku który zawiera obiekt 3D

    QUrl textureFile;

};

#endif // OBJECT_VIEW_SCENE_H
