#ifndef DEVICE_H
#define DEVICE_H


#include <QSerialPort>
#include <QObject>
#include <QQueue>
#include <datacontainer.h>
#include <checksum.h>
#include <fstream>
#include <QVector3D>
#include <QQuaternion>
#include <QTime>

class Device : public QObject
{
    Q_OBJECT
public:

    Device(QObject* parent = nullptr);
    ~Device();
    QString& getSerialPortName();
    bool getIsConnected() const;
    QSerialPort *get_SerialPortObject();
    void resetDeviceValues();
public slots:
    void setSerialName(const QString name);
    void getData();
    void startCommunication();
    void rawToData();
    void calculateRPY();
    void gyroCalibration();
    void accCalibration();

signals:
    void dataReceived();
    void newDeviceValues();
    void gyroCalibrated();
    void orientationChanged(const QQuaternion&);
    void positionChanged(const QVector3D&);
    void accCalibrated();
    void sendGyroDatatoChart(const QVector3D&);
    void sendAccDatatoChart(const QVector3D&,float dt);

private:
    int XgyroMAX;
    int XgyroMIN;
    int YgyroMAX;
    int YgyroMIN;
    int ZgyroMAX;
    int ZgyroMIN;

    int XgyroERROR;
    int YgyroERROR;
    int ZgyroERROR;

    int XaccMAX;
    int XaccMIN;
    int YaccMAX;
    int YaccMIN;
    int ZaccMAX;
    int ZaccMIN;

    int XaccERROR;
    int YaccERROR;
    int ZaccERROR;

    QString serialName;
    QSerialPort serialPort;
    DataContainer *dataContainer;
    std::string data;
    int Check;

    QVector3D orientationVector;
    QVector3D orientationAccVector;
    QVector3D gyroscopeData;
    QVector3D accelerometerData;
    QVector3D positionVector;
    QVector3D positionVelocityVector;
    QQuaternion orientationQauternion;




};

#endif // DEVICE_H
