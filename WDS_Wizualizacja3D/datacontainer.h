#ifndef DATACONTAINER_H
#define DATACONTAINER_H
#include <stdint.h>
#include <QDataStream>
class DataContainer
{
public:
    DataContainer();
    DataContainer(char _ID,int _X,int _Y,int _Z);
    void setID(char &ID_);
    void setX(int &X_);
    void setY(int &Y_);
    void setZ(int &Z_);


    int getX();
    int getY();
    int getZ();
    char getID();

private:
    char ID;
    int X;
    int Y;
    int Z;

};

#endif // DATACONTAINER_H
