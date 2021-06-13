#ifndef DATACONTAINER_H
#define DATACONTAINER_H
#include <stdint.h>
#include <QDataStream>
class DataContainer
{
public:
    DataContainer();
    DataContainer(char _ID,int _X,int _Y,int _Z);

    /*!
     * \brief funkcja ustawia wartość pola ID
     * \param[in] ID_ - znak identyfikujący sensor
     */
    void setID(char &ID_);
    /*!
     * \brief funkcja ustawia wartość pola X
     * \param[in] X_ - wartość dla osi X
     */
    void setX(int &X_);
    /*!
     * \brief funkcja ustawia wartość pola Y
     * \param[in] Y_ -  wartość dla osi Y
     */
    void setY(int &Y_);
    /*!
     * \brief funkcja ustawia wartość pola Z
     * \param[in] Z_ - wartość dla osi Z
     */
    void setZ(int &Z_);

    /*!
     * \brief funkcja zwraca wartość pola X
     * \return wartość dla osi X
     */
    int getX();
    /*!
     * \brief funkcja zwraca wartość pola Y
     * \return wartość dla osi Y
     */
    int getY();
    /*!
     * \brief funkcja zwraca wartość pola Z
     * \return wartość dla osi Z
     */
    int getZ();
    /*!
     * \brief funkcja zwraca wartość pola ID
     * \return wartość identyfikatora
     */
    char getID();

private:
    char ID;//<! pole przechowujące id sensora
    int X;//<! pole przechowujące wartość prędkości/przyśpieszenia osi OX
    int Y;//<! pole przechowujące wartość prędkości/przyśpieszenia osi OY
    int Z;//<! pole przechowujące wartość prędkości/przyśpieszenia osi OZ

};

#endif // DATACONTAINER_H
