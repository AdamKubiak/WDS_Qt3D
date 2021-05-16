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
 * \brief Klasa MainWindow zarządza wszystkimi operacjami na obiektach sceny i na elementach GUI
 *
  */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /*!
     * \brief Konstruktor MainWindow
     * \param QWidget parent
     */
    MainWindow(QWidget *parent = nullptr);


    /*!
     * \brief Destruktor MainWindow
     */
    ~MainWindow();

    /*!
     * \brief Funkcja dodaje znaleziony porty COM do paska narzędzi, gdzie użytkownik może wybrać
     *  z jakiego będę pobierane dane
     */
    void menuAvailablePorts();

    /*!
     * \brief Funkcja ustawia wartość rotacji wzdłóż osi X w postaci stopni w GUI użytkownika
     */
    void setXRotationValue(float value);
    /*!
     * \brief Funkcja ustawia wartość rotacji wzdłóż osi Y w postaci stopni w GUI użytkownika
     */
    void setYRotationValue(float value);
    /*!
     * \brief Funkcja ustawia wartość rotacji wzdłóż osi Z w postaci stopni w GUI użytkownika
     */
    void setZRotationValue(float value);

    /*!
     * \brief Funkcja ustawia wartość translacji wzdłóż osi X w postaci stopni w GUI użytkownika
     */
    void setXTranslationValue(float value);

    /*!
     * \brief Funkcja ustawia wartość translacji wzdłóż osi Y w postaci stopni w GUI użytkownika
     */
    void setYTranslationValue(float value);

    /*!
     * \brief Funkcja ustawia wartość translacji wzdłóż osi Z w postaci stopni w GUI użytkownika
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
     */
    void setRotationValue(const QQuaternion &value);

    /*!
     * \brief Slot przyjmuje QVector3D który zostaje rozbity na wartości kątów
     *  dla każdej z osi i następuje przekazanie tych wartości do GUI
     */
    void setTranslationValue(const QVector3D &value);
    /*!
     * \brief Slot odpowiedzialny za przypisanie nazwy wybranego portu do pola klasy Device
     */
    void selectPort(QAction *trigger);

    void makePlot();

    void gyroCalibrated();

    void setChartsValue(const QVector3D &Axis);


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

    QVector<double>    Xgyro_y,Ygyro_y,Zgyro_y, dtTime;
    double Time;

};
#endif // MAINWINDOW_H
