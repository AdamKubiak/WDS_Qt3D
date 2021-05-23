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
     * \brief funckaj ustawia wartość pola ID
     * \param[in] ID_ - znak identyfikujący sensor
     */
    void setID(char &ID_);
    /*!
     * \brief funckaj ustawia wartość pola X
     * \param[in] X_ - wartość dla osi X
     */
    void setX(int &X_);
    /*!
     * \brief funckaj ustawia wartość pola Y
     * \param[in] Y_ -  wartość dla osi Y
     */
    void setY(int &Y_);
    /*!
     * \brief funckaj ustawia wartość pola Z
     * \param[in] Z_ - wartość dla osi Z
     */
    void setZ(int &Z_);

    /*!
     * \brief funckaj zwraca wartość pola X
     * \return wartość dla osi X
     */
    int getX();
    /*!
     * \brief funckaj zwraca wartość pola Y
     * \return wartość dla osi Y
     */
    int getY();
    /*!
     * \brief funckaj zwraca wartość pola Z
     * \return wartość dla osi Z
     */
    int getZ();
    /*!
     * \brief funckaj zwraca wartość pola ID
     * \return wartość identyfikatora
     */
    char getID();

private:
    char ID;//<! pole przechowujące id sensora
    int X;//<! pole przechowujące wartość osi X
    int Y;//<! pole przechowujące wartość osi Y
    int Z;//<! pole przechowujące wartość osi Z

};

#endif // DATACONTAINER_H
