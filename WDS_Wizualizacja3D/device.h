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
#include <QMessageBox>

class Device : public QObject
{
    Q_OBJECT
public:

    Device(QObject* parent = nullptr);
    ~Device();

    /*!
     * \brief Funkcja umożliwia dostanie się do pola serialName poza klasą Device
     * \return Zwraca string z nazwą portu
     */
    QString& getSerialPortName();
    bool getIsConnected();

    /*!
     * \brief Funkcja umożliwia dostanie się do pola serialPort klasy Device
     * \return Wskaźnik na pole serialPort klasy Device
     */
    QSerialPort *get_SerialPortObject();
    /*!
     * \brief Funkcja resetuje wartości pól przechowujących aktualną pozycję obiektu do pozycji zerowej
     */
    void resetDeviceValues();
public slots:

    /*!
     * \brief Slot ustawia wartość pola serialName
     *
     * \param[in] name - string z nazwą portu szeregowego
     */
    void setSerialName(const QString name);

    /*!
     * \brief Slot odpowiedzialny za odbieranie danych z portu szeregowego
     */
    void getData();
    /*!
     * \brief Slot odpowiedzialny za rozpoczęcie komunikacji z wybranym portem szeregowym
     */
    void startCommunication();

    void rawToData();
    /*!
     * \brief Slot odpowiedzialny za przeliczenie surowych danych z sensorów na użyteczne wartości transformacji i rotacji obiektu 3D
     */
    void calculateRPY();
    /*!
     * \brief Slot odpowiedzialny za kalibracje żyroskopu
     */
    void gyroCalibration();
    /*!
     * \brief Slot odpowiedzialny za kalibracje akcelerometru
     */
    void accCalibration();

signals:

    void dataReceived();
    /*!
     * \brief Sygnał wysyłany przy odebraniu i sprawdzeniu poprawności przesyłu danych
     */
    void newDeviceValues();
    /*!
     * \brief Sygnał wysyłany po zakończeniu kalibracji żyroskopu
     */
    void gyroCalibrated();
    /*!
     * \brief Sygnał po obliczeniu orientacji obiektu z otrzymanych danych
     * \param[in] QQuaternion - wyliczone dane w postaci quaternionu
     *
     */
    void orientationChanged(const QQuaternion&);
    /*!
     * \brief Sygnał po obliczeniu translacji obiektu z otrzymanych danych
     * \param[in] QVector3D - wyliczone dane w postaci wektora3D
     */
    void positionChanged(const QVector3D&);
    /*!
     * \brief Sygnał wysyłany po zakończeniu kalibracji akcelerometru
     */
    void accCalibrated();

    /*!
     * \brief Sygnał wysyłana surowe dane z żyroskopu do odpowiednich wykresów
     * \param[in] QVector3D - surowe dane w postaci wektora3D
     * \param[in] char - identyfikator sensora
     */
    void sendGyroDatatoChart(const QVector3D&,char);

    /*!
     * \brief Sygnał wysyłana surowe dane z akcelerometru do odpowiednich wykresów
     * \param[in] QVector3D - surowe dane w postaci wektora3D
     * \param[in] char - identyfikator sensora
     */
    void sendAccDatatoChart(const QVector3D&,char);

private:
    int XgyroMAX; //!< maks przedziału pomijalnej wartości obliczonej z  kalibracji dla osi X
    int XgyroMIN; //!< minimum przedziału pomijalnej wartości obliczonej z  kalibracji dla osi X
    int YgyroMAX;//!< maks przedziału pomijalnej wartości obliczonej z  kalibracji dla osi Y
    int YgyroMIN;//!< minimum przedziału pomijalnej wartości obliczonej z  kalibracji dla osi Y
    int ZgyroMAX;//!< maks przedziału pomijalnej wartości obliczonej z  kalibracji dla osi Z
    int ZgyroMIN;//!< minimum przedziału pomijalnej wartości obliczonej z  kalibracji dla osi Z

    int XgyroERROR;//!< wartość wyliczona z kalibracji żyroskopu, która jest odejmowana od otrzymanych danych z osi X
    int YgyroERROR;//!< wartość wyliczona z kalibracji żyroskopu, która jest odejmowana od otrzymanych danych z osi Y
    int ZgyroERROR;//!< wartość wyliczona z kalibracji żyroskopu, która jest odejmowana od otrzymanych danych z osi Z

    int XaccMAX;
    int XaccMIN;
    int YaccMAX;
    int YaccMIN;
    int ZaccMAX;
    int ZaccMIN;

    float correctionX,correctionY,correctionZ;

    int XaccERROR;//!< wartość wyliczona z kalibracji akcelerometru, która jest odejmowana od otrzymanych danych z osi X
    int YaccERROR;//!< wartość wyliczona z kalibracji akcelerometru, która jest odejmowana od otrzymanych danych z osi Y
    int ZaccERROR;//!< wartość wyliczona z kalibracji akcelerometru, która jest odejmowana od otrzymanych danych z osi Z

    QString serialName;//!< pole przechowuje nazwę portu z którym użytkownik chce się połaczyć
    QSerialPort serialPort;//!< pole klasy QSerialPort odpowiedzialne za komunikację z portem szeregowym
    DataContainer *dataContainer;//!< pole klasy DataContainer odpowiedzialne za przechowywanie odebranych wartości z sensorów
    std::string data;//!< pole odpowiedzialne za tymczasowe przechowywanie odebranych danych w formie stringa
    int Check;//!< pole pełniące rolę flagi do sprawdzania wartunków
    QMessageBox info;

    QVector3D rawAccelerometer;
    QVector3D orientationVector;//!< pole wykorzystywane do obliczenia orientacji obiektu przy pomocy reprezentacji Roll-Pitch-Yaw z danych z żyroskopu
    QVector3D orientationAccVector;//!< pole wykorzystywane do obliczenia orientacji obiektu przy pomocy reprezentacji Roll-Pitch-Yaw z danych z akcelerometru
    QVector3D gyroscopeData;//!< pole przechowujące najświeższe odebrane dane z żyroskopu
    QVector3D accelerometerData;//!< pole przechowujące najświeższe odebrane dane z akcelerometru
    QVector3D positionVector;//!< pole przechowujące aktualą pozycję obiektu w postaci Quaternionu
    QVector3D positionVelocityVector;//!< pole przechowujące obliczone prędkości z akcelerometru w postaci wektora3D
    QQuaternion orientationQauternion;//!< pole przechowujące aktualą orientacje obiektu w postaci Quaternionu




};

#endif // DEVICE_H
