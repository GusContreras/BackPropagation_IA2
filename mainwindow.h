#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include "nn.h"
#include "point.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void addPoint(Point,int);
    void plot();
    void crearRed();
    void PaintClass();

    void clearData();

private slots:
    void clickedGraph(QMouseEvent *event);

    void on_sliderClases_valueChanged();

    void on_pushButton_6_clicked();

    void on_capasOcultas_btn_clicked();

    void on_neuronasPorCapa_btn_clicked();

    void on_backPropagation_clicked();

    void on_pushButton_3_clicked();

    void on_circulo_clicked();

    void on_centro_clicked();

    void on_gato_clicked();

private:
    Ui::MainWindow *ui;
    std::vector<int> numNeuroPorCapa;
    NN Red;
    int cantidadClases;
    int selectClass = 0;
    int ContCapas;
    int CCaps = 0;

    std::vector<Point> pointVector;

    QVector<double> cx0,cx1,cx2,cx3,cx4,cx5,cx6,cx7;
    QVector<double> cy0,cy1,cy2,cy3,cy4,cy5,cy6,cy7;
    QVector<double> errorX,errorY;

    void plotError();

    void addExample(double, double,int);
};

#endif // MAINWINDOW_H
