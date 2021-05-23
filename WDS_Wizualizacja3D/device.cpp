#include "device.h"
#include <QDebug>
#include "string.h"
#define M_PI 3.14159265358979323846
#include <math.h>

Device::Device(QObject *parent)
    : QObject(parent)
{
    dataContainer = new DataContainer(0,0,0,0);
    Check = 0;

}

Device::~Device()
{

}


QString &Device::getSerialPortName()
{
    return serialName;
}

QSerialPort *Device::get_SerialPortObject()
{
    return &serialPort;
}

void Device::resetDeviceValues()
{
    orientationVector = QVector3D(0,0,0);
    orientationQauternion = QQuaternion(0,orientationVector);
    positionVelocityVector = QVector3D(0,0,0);
    positionVector = QVector3D(0,0,0);
}



void Device::setSerialName(const QString name)
{
    qDebug()<< name;
    serialName = name;

}

void Device::getData()
{
   // uint8_t* buffer;
//int CRC;
    int character;
    std::string separator;

    /*std::string data;

    separator = data.find(' ');
    qDebug() << separator;*/

    if(data.find('\n')==std::string::npos)
    {
        data+=serialPort.readAll().toStdString();

    }
    else
    {
       if(data.at(0)=='G')
       {
           char id = data.at(0);



           data.erase(0,1);
           character = data.find(' ');
           separator = data.substr(0,character);
           int x = std::atoi(separator.c_str());//jak nie RPY to *0.0175



           data.erase(0,character+1);
           character = data.find(' ');
           separator = data.substr(0,character);
           int y = std::atoi(separator.c_str());


           data.erase(0,character+1);
           character = data.find(' ');
           separator = data.substr(0,character);
           int z = std::atoi(separator.c_str());

           data.erase(0,character+1);
           character = data.find(' ');
           separator = data.substr(0,character);
           //int crc = std::atoi(separator.c_str());

           //sprintf((char*)buffer,"%c%i %i %i", id,x, y,z);
           //uint16_t CRC = crc_16(buffer,strlen((char*)buffer));
           //qDebug()<<id<<x<<y<<z<<crc;
           //dataContainer = new DataContainer(id,x,y,z);
           dataContainer->setID(id);
           dataContainer->setX(x);
           dataContainer->setY(y);
           dataContainer->setZ(z);
           qDebug()<<dataContainer->getID()<<dataContainer->getX()<<dataContainer->getY()<<dataContainer->getZ();

       }

       if(data.at(0)=='A')
       {

           char id = data.at(0);



           data.erase(0,1);
           character = data.find(' ');
           separator = data.substr(0,character);
           int x = std::atoi(separator.c_str());



           data.erase(0,character+1);
           character = data.find(' ');
           separator = data.substr(0,character);
           int y = std::atoi(separator.c_str());


           data.erase(0,character+1);
           character = data.find(' ');
           separator = data.substr(0,character);
           int z = std::atoi(separator.c_str());

           data.erase(0,character+1);
           character = data.find(' ');
           separator = data.substr(0,character);
           //int crc = std::atoi(separator.c_str());



           //qDebug()<<id<<x<<y<<z<<crc;
           //dataContainer = new DataContainer(id,x,y,z);
           dataContainer->setID(id);
           dataContainer->setX(x);
           dataContainer->setY(y);
           dataContainer->setZ(z);
           qDebug()<<dataContainer->getID()<<dataContainer->getX()<<dataContainer->getY()<<dataContainer->getZ();
           emit sendAccDatatoChart(QVector3D(dataContainer->getX(),dataContainer->getY(),dataContainer->getZ()),dataContainer->getID());

       }

        emit newDeviceValues();
        data.clear();
    }

}

void Device::startCommunication()
{

    if(serialName == 0) {
      return;
    }


    serialPort.setPortName(serialName);

    // OTWÓRZ I SKONFIGURUJ PORT:
    if(!serialPort.isOpen())
    {
    if(serialPort.open(QSerialPort::ReadWrite)) {
      serialPort.setBaudRate(QSerialPort::Baud115200);
      serialPort.setDataBits(QSerialPort::Data8);
      serialPort.setParity(QSerialPort::NoParity);
      serialPort.setStopBits(QSerialPort::OneStop);
      serialPort.setFlowControl(QSerialPort::NoFlowControl);
      qDebug()<<"Otwarcie portu szeregowego się powiodło!";
      disconnect(&serialPort,&QSerialPort::readyRead, this, &Device::getData);
      disconnect(this,&Device::newDeviceValues,this,&Device::gyroCalibration);
      disconnect(this,&Device::newDeviceValues,this,&Device::accCalibration);
      QMessageBox::StandardButton reply = QMessageBox::question(NULL,"Kalibracja", "Aby dokonać kalibracji trzymaj płytkę nieruchomo, proces trwa 8 s,chcesz kontynuować?",
                                                                QMessageBox::Yes|QMessageBox::No);
      if(reply == QMessageBox::Yes)
      {
      connect(&serialPort,&QSerialPort::readyRead, this, &Device::getData);
      connect(this,&Device::newDeviceValues,this,&Device::gyroCalibration);
      connect(this,&Device::newDeviceValues,this,&Device::accCalibration);
      }
      else
      {
      connect(&serialPort,&QSerialPort::readyRead, this, &Device::getData);
      connect(this,&Device::newDeviceValues,this,&Device::calculateRPY);
      }


    } else {
      qDebug()<<"Otwarcie portu szeregowego się nie powiodło!";
    }
    }

    else
    {
        qDebug()<<"Port już otwarty";
        return;
    }
}

void Device::rawToData()
{
    if(dataContainer->getID()=='G')
    {
        static QTime substractTime = QTime::currentTime();
        float dt = (float)substractTime.msecsTo(QTime::currentTime())/1000.0;
        substractTime = QTime::currentTime();

        orientationVector += QVector3D(dataContainer->getX()*dt,dataContainer->getY()*dt,dataContainer->getZ()*dt);

       // orientationQauternion = QQuaternion::fromEulerAngles(orientationVector.x(),orientationVector.y(),orientationVector.z());
        //emit orientationChanged(orientationQauternion);

    }

    if(dataContainer->getID()=='A')
    {
        orientationAccVector.setX((atan(dataContainer->getY()*2.0/32183 / sqrt(pow(dataContainer->getX()*2.0/32183, 2) + pow(dataContainer->getZ()*2.0/32183, 2))) * 180 / M_PI));
        orientationAccVector.setY(atan(-1 * dataContainer->getX()*2.0/32183 / sqrt(pow(dataContainer->getY()*2.0/32183, 2) + pow(dataContainer->getZ()*2.0/32183, 2))) * 180 / M_PI);
        static QTime substractTime = QTime::currentTime();
        float dt = (float)substractTime.msecsTo(QTime::currentTime())/1000.0;
        substractTime = QTime::currentTime();




        positionVector.setX(positionVector.x() + dataContainer->getX()*2.0/32183*dt);
        positionVector.setY(positionVector.y() + dataContainer->getY()*2.0/32183*dt);
        positionVector.setZ(positionVector.z() + dataContainer->getZ()*2.0/32183*dt);
                //positionVector.setX(positionVector.x() +  1*dataContainer->getX()*2.0/32183*dt*dt);
                //positionVector.setY(positionVector.y() +  1*dataContainer->getY()*2.0/32183*dt*dt);
                //positionVector.setZ(positionVector.z() +  1*dataContainer->getZ()*2.0/32183*dt*dt);
        //emit positionChanged(positionVector);
    }

    orientationQauternion = QQuaternion::fromEulerAngles(0.96*orientationVector.x()+0.04*orientationAccVector.x(),0.96*orientationVector.y()+0.04*orientationAccVector.y(),orientationVector.z());
    emit orientationChanged(orientationQauternion);
}

void Device::calculateRPY()
{
    float gyroDT=0;
    if(dataContainer->getID() == 'G')
    {
        int zero = 0;
        if(dataContainer->getX() >= XgyroERROR && dataContainer->getX() <= XgyroERROR)
        {
            dataContainer->setX(zero);
        }


        if(dataContainer->getY() >= YgyroERROR && dataContainer->getY() <= YgyroERROR)
        {
            dataContainer->setY(zero);
        }


        if(dataContainer->getZ() >= ZgyroERROR && dataContainer->getZ() <= ZgyroERROR)
        {
            dataContainer->setZ(zero);
        }
    }


    if(Check == 2)
    {

        static QTime substractTime = QTime::currentTime();
        float dt = gyroDT = (float)substractTime.msecsTo(QTime::currentTime())/1000.0;
        substractTime = QTime::currentTime();
        orientationVector.setX(orientationVector.x()+gyroscopeData.x()*dt);
        orientationVector.setY(orientationVector.y()+gyroscopeData.y()*dt);
        orientationVector.setZ(orientationVector.z()+gyroscopeData.z()*dt);

        orientationAccVector.setX((atan(accelerometerData.y() / sqrt(pow(accelerometerData.x(), 2) + pow(accelerometerData.z(), 2))) * 180 / M_PI));
        orientationAccVector.setY(atan(-1 * accelerometerData.x() / sqrt(pow(accelerometerData.y(), 2) + pow(accelerometerData.z(), 2))) * 180 / M_PI);
        orientationQauternion = QQuaternion::fromEulerAngles(0.96*orientationVector.x()+0.04*orientationAccVector.x(),0.96*orientationVector.y()+0.04*orientationAccVector.y(),orientationVector.z());


        Check = 0;
        emit orientationChanged(orientationQauternion);
    }
    else if(dataContainer->getID()=='A')
    {

        static QTime substractTime = QTime::currentTime();
        float dt = (float)substractTime.msecsTo(QTime::currentTime())/1000.0;
        substractTime = QTime::currentTime();
        rawAccelerometer.setX(dataContainer->getX());
        rawAccelerometer.setY(dataContainer->getY());
        rawAccelerometer.setZ(dataContainer->getZ());


            correctionX = correctionX*0.6 + dataContainer->getX()*0.4;
            correctionY = correctionY*0.6 + dataContainer->getY()*0.4;
            correctionZ = correctionZ*0.6 + dataContainer->getZ()*0.4;

        int X,Y,Z;
        X = (dataContainer->getX()-correctionX)*9.81*2/32183;
        Y = (dataContainer->getY()-correctionY)*9.81*2/32183;
        Z = -(dataContainer->getZ()-correctionZ)*9.81*2/32183;

        positionVelocityVector.setX(positionVelocityVector.x()*0.7 + X*dt);
        positionVelocityVector.setY(positionVelocityVector.y()*0.7 + Y*dt);
        positionVelocityVector.setZ(positionVelocityVector.z()*0.7 + Z*dt);

        positionVector.setX(positionVector.x() + positionVelocityVector.x()*dt+X*dt*dt);
        positionVector.setY(positionVector.y() + positionVelocityVector.y()*dt+Y*dt*dt);
        positionVector.setZ(positionVector.z() + positionVelocityVector.z()*dt+Z*dt*dt);



        //positionVector.setX(positionVector.x() + X*dt);
        //positionVector.setY(positionVector.y() + Y*dt);
        //positionVector.setZ(positionVector.z() + Z*dt);


        accelerometerData.setX((dataContainer->getX()-XaccERROR)*2.0*32183);
        accelerometerData.setY((dataContainer->getY()-YaccERROR)*2.0*32183);
        accelerometerData.setZ((dataContainer->getZ()-ZaccERROR)*2.0*32183);

        emit positionChanged(positionVector*40);


        if(Check == 1)
        Check++;
        //emit sendAccDatatoChart(rawAccelerometer,dataContainer->getID());
        //emit sendAccDatatoChart(QVector3D(dataContainer->getX(),dataContainer->getY(),dataContainer->getZ()),dataContainer->getID());



    }
    else if(dataContainer->getID() == 'G')
    {
        gyroscopeData.setX((dataContainer->getX()-XgyroERROR)*0.0175);
        gyroscopeData.setY((dataContainer->getY()-YgyroERROR)*0.0175);
        gyroscopeData.setZ((dataContainer->getZ()-ZgyroERROR)*0.0175);
        Check++;
        emit sendGyroDatatoChart(QVector3D(dataContainer->getX(),dataContainer->getY(),dataContainer->getZ()),dataContainer->getID());
        //emit sendAccDatatoChart(rawAccelerometer,'A');
    }
}

void Device::gyroCalibration()
{
    //static QMessageBox *info;
    if(dataContainer->getID()=='G')
    {
    qDebug()<<"KALIBRUJE";
    static int c = 0;
    int samples = 300;
    if(c ==0)
    {

    //info.information(NULL,"Proces kalibracji", "Kalibracja...");
    XgyroMAX = INT_MIN;
    XgyroMIN = INT_MAX;
    YgyroMAX = INT_MIN;
    YgyroMIN = INT_MAX;
    ZgyroMAX = INT_MIN;
    ZgyroMIN = INT_MAX;
    XgyroERROR = 0;
    YgyroERROR = 0;;
    ZgyroERROR = 0;;
    }



    if(c<samples)
    {
        XgyroERROR += dataContainer->getX();
        YgyroERROR += dataContainer->getY();
        ZgyroERROR += dataContainer->getZ();

       XgyroMAX = std::max(XgyroMAX,dataContainer->getX());
       YgyroMAX = std::max(YgyroMAX,dataContainer->getY());
       ZgyroMAX = std::max(ZgyroMAX,dataContainer->getZ());

       XgyroMIN = std::min(XgyroMIN,dataContainer->getX());
       YgyroMIN = std::min(YgyroMIN,dataContainer->getY());
       ZgyroMIN = std::min(ZgyroMIN,dataContainer->getZ());
       c++;
    }

    if(c == samples)
    {
    XgyroERROR = XgyroERROR/samples;
    YgyroERROR = YgyroERROR/samples;
    ZgyroERROR = ZgyroERROR/samples;
    c = 0;
    //info.close();
    //delete info;

    emit gyroCalibrated();
    }
}
}


void Device::accCalibration()
{
    if(dataContainer->getID()=='A')
    {
    qDebug()<<"KALIBRUJE";
    static int c = 0;
    int samples = 300;
    if(c ==0)
    {
    XaccMAX = INT_MIN;
    XaccMIN = INT_MAX;
    YaccMAX = INT_MIN;
    YaccMIN = INT_MAX;
    ZaccMAX = INT_MIN;
    ZaccMIN = INT_MAX;
    XaccERROR = 0;
    YaccERROR = 0;;
    ZaccERROR = 0;;
    }

    if(c<samples)
    {
        XaccERROR += dataContainer->getX();
        YaccERROR += dataContainer->getY();
        ZaccERROR += dataContainer->getZ();

      // XaccMAX = std::max(XaccMAX,dataContainer->getX());
      // YaccMAX = std::max(YaccMAX,dataContainer->getY());
      // ZaccMAX = std::max(ZaccMAX,dataContainer->getZ());

      // XaccMIN = std::min(XaccMIN,dataContainer->getX());
      // YaccMIN = std::min(YaccMIN,dataContainer->getY());
      // ZaccMIN = std::min(ZaccMIN,dataContainer->getZ());
       c++;
    }

    if(c == samples)
    {
    XaccERROR = XaccERROR/samples;
    YaccERROR = YaccERROR/samples;
    ZaccERROR = ZaccERROR/samples;
    c=0;
    emit accCalibrated();
    }
}
}
