#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
#include "object_widget.h"
#include "device.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
/*!
 * \class MainWindow
 * \brief Klasa MainWindow zarządza wszystkimi operacjami na obiektach sceny i elementami GUI
 *
  */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

    /*!
     * \brief Funkcja dodaje znaleziony porty COM do paska narzędzi, gdzie użytkownik może wybrać
     *  z którego z nich będę pobierane dane
     */
    void menuAvailablePorts();

    /*!
     * \brief Funkcja ustawia wartość rotacji wzdłuż osi OX w stopniach w GUI użytkownika
     */
    void setXRotationValue(float value);
    /*!
     * \brief Funkcja ustawia wartość rotacji wzdłuż osi OY w stopniach w GUI użytkownika
     * \param[in] value - wartość rotacji
     */
    void setYRotationValue(float value);
    /*!
     * \brief Funkcja ustawia wartość rotacji wzdłuż osi OZ w stopniach w GUI użytkownika
     * \param[in] value - wartość rotacji
     */
    void setZRotationValue(float value);

    /*!
     * \brief Funkcja ustawia wartość translacji wzdłuż osi OX w stopniach w GUI użytkownika
     * \param[in] value - wartość rotacji
     */
    void setXTranslationValue(float value);

    /*!
     * \brief Funkcja ustawia wartość translacji wzdłuż osi OY w stopniach w GUI użytkownika
     * \param[in] value - wartość translacji
     */
    void setYTranslationValue(float value);

    /*!
     * \brief Funkcja ustawia wartość translacji wzdłuż osi OZ w stopniach w GUI użytkownika
     * \param[in] value - wartość translacji
     */
    void setZTranslationValue(float value);

    /*!
     * \brief Funkcja ustawia połączenie między sygnałami i slotami
     */
    void addConnections();




public slots:
    /*!
     * \brief Slot przyjmuje Quaternion z którego zostają wyliczone kąty
     *  dla każdej z osi i następuje przekazanie tych wartości do GUI
     *  \param[in] value - wartość rotacji obiektu w quaternionach
     */
    void setRotationValue(const QQuaternion &value);

    /*!
     * \brief Slot przyjmuje QVector3D który zostaje rozbity na wartości kątów
     *  dla każdej z osi i następuje przekazanie tych wartości do GUI
     *  \param[in] value - wartość translacji przekazywana w formie wektora
     */
    void setTranslationValue(const QVector3D &value);
    /*!
     * \brief Slot odpowiedzialny za przypisanie nazwy wybranego portu do pola klasy Device
     * \param[in] trigger - nazwa portu wybrana przez użytkownika
     */
    void selectPort(QAction *trigger);

    /*!
     * \brief Slot inicjalizuje widgety z wykresami z pomocą funkcji dostarczonych w bibliotece qcustomplot
     */
    void makePlot();

    /*!
     * \brief Slot ustawia połaczonia odpowiedzialnych za przesył danych do konkretnych slotów po kalibracji żyroskopu
     */
    void gyroCalibrated();

    /*!
     * \brief Slot odpowiedzialny za wyświetlenie danych na odpowiednich wykresach
     * \param[in] Axis - surowe wartości odebrane z sensorów w formie wektora3D
     * \param[in] ID - identyfikator sensora z którego odbierane są dane
     */
    void setChartsValue(const QVector3D &Axis,char ID);
    //void setChartsValueAccelerometer(const QVector3D &Axis, char ID);


private slots:
    /*!
     * \brief Slot odpowiedzialny za zresetowanie pozycji i orientacji obiektu za pomocą
     * przycisku RESET
     */
    void on_resetViewButton_clicked();

private:
    Ui::MainWindow *ui;
    Object_Scene *objectScene; //!< Wskaźnik na scene 3D
    Object_Widget *objectWidget;//!< Wskaźnik na widget sceny
    Device *device; //<! Wskaźnik na urządzenie z którego są zbierane dane

    QVector<double>    Xgyro_y,Ygyro_y,Zgyro_y, dtTime; //!< wektory z danymi do wyświetlenia na wykresach
    QVector<double>    Xacc_y,Yacc_y,Zacc_y; //!< wektory z danymi do wyświetlenia na wykresach
    double Time;
    float dt; //!< wartość używana do reprezentcji czasu na osiach X wykresów

};
#endif // MAINWINDOW_H
