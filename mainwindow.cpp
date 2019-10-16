#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtMath>

const double euler = 2.71828182845;

double sigmoid(double x){
    return (1.0/(1.0 + qPow(euler,x*(-1.0))));
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{   
    ui->setupUi(this);
    connect(ui->customPlot, SIGNAL(mousePress(QMouseEvent* )), SLOT(clickedGraph(QMouseEvent*)));
    Red.setFunction(sigmoid);
    //setting range
    ui->customPlot->xAxis->setRange(-1, 1);
    ui->customPlot->yAxis->setRange(-1, 1);

    ui->errorPlot->addGraph();
    ui->errorPlot->graph(0)->setPen(QPen(Qt::darkBlue));
    ui->errorPlot->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20)));
    ui->errorPlot->xAxis->setRange(0,1);
    ui->errorPlot->yAxis->setRange(0,0.6);

    ui->input_f->setText("0.7");
    ui->input_g->setText("5000");
    ui->input_e->setText("0.0008");
    ui->input_clases->setText("3");
    ui->input_capas->setText("2");
    ui->input_neuronas->setText("5");
    ui->text_class->setText("Clase " + QString::number(selectClass) + " seleccionada.");
    ui->text_neurona->setText("Capa "  + QString::number(CCaps));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addPoint(Point p,int clase)
{
    switch(clase)
    {
        case 0:
            cx0.push_back(p.x);
            cy0.push_back(p.y);
        break;
        case 1:
            cx1.push_back(p.x);
            cy1.push_back(p.y);
        break;
        case 2:
            cx2.push_back(p.x);
            cy2.push_back(p.y);
        break;
        case 3:
            cx3.push_back(p.x);
            cy3.push_back(p.y);
        break;
        case 4:
            cx4.push_back(p.x);
            cy4.push_back(p.y);
        break;
        case 5:
            cx5.push_back(p.x);
            cy5.push_back(p.y);
        break;
        case 6:
            cx6.push_back(p.x);
            cy6.push_back(p.y);
        break;
        case 7:
            cx7.push_back(p.x);
            cy7.push_back(p.y);
        break;
    }
    pointVector.push_back(p);
}

void MainWindow::plot()
{
    ui->customPlot->graph(0)->setData(cx0,cy0);
    ui->customPlot->graph(1)->setData(cx1,cy1);
    ui->customPlot->graph(2)->setData(cx2,cy2);
    ui->customPlot->graph(3)->setData(cx3,cy3);
    ui->customPlot->graph(4)->setData(cx4,cy4);
    ui->customPlot->graph(5)->setData(cx5,cy5);
    ui->customPlot->graph(6)->setData(cx6,cy6);
    ui->customPlot->graph(7)->setData(cx7,cy7);
    ui->customPlot->replot();
    ui->customPlot->update();
}

void MainWindow::plotError()
{
    ui->errorPlot->graph(0)->setData(errorX,errorY);
    ui->errorPlot->replot();
    ui->errorPlot->update();
}

void MainWindow::addExample(double x, double y, int c)
{
    std::vector<double> Cl(cantidadClases,0);

    Cl[c] = 1;

    Point myPoint(x,y,Cl);
    addPoint(myPoint,c);
}

void MainWindow::crearRed()
{

    numNeuroPorCapa.push_back(cantidadClases);

    Red.CreateRed(numNeuroPorCapa);
}

void MainWindow::PaintClass()
{
    double x = -1.1;
    double y = -1.1;
    for(int i = 0; i < 880; i++)
    {
        x += 0.0025;
        y = -1.1;
        for(int j = 0; j < 880; j++)
        {
            y += 0.0025;
            double mejor = 0;
            int index = 0;
            std::vector<double>resultado = Red.FeedForward({x,y});
            for(int k = 0; k < resultado.size(); k++)
            {

                if(resultado[k] > mejor)
                {
                    mejor = resultado[k];
                    index = k;
                }
                //std::cout << resultado[k] << " " << index << " " << x << " " << y << std::endl;
            }
            std::vector<double> Cl(cantidadClases,0);
            Cl[index] = 1;
            Point myPoint(x,y,Cl);
            addPoint(myPoint,index);
            //std::cout << resultado[index] << std::endl;
            //std::cout << index << std::endl;
        }
    }
}

void MainWindow::clearData()
{
    numNeuroPorCapa.clear();
    cantidadClases = 0;
    selectClass = 0;
    ContCapas = 0;
    CCaps = 0;
    pointVector.clear();

    cx0.clear();
    cx1.clear();
    cx2.clear();
    cx3.clear();
    cx4.clear();
    cx5.clear();
    cx6.clear();
    cx7.clear();
    cy0.clear();
    cy1.clear();
    cy2.clear();
    cy3.clear();
    cy4.clear();
    cy5.clear();
    cy6.clear();
    cy7.clear();
    ui->input_f->setText("0.7");
    ui->input_g->setText("5000");
    ui->input_e->setText("0.0008");
    ui->input_clases->setText("3");
    ui->input_capas->setText("2");
    ui->input_neuronas->setText("5");
    ui->text_class->setText("Clase " + QString::number(selectClass) + " seleccionada.");
    ui->text_clases->setText("#Clases ");
    ui->text_capas->setText("#Capas Ocultas");
    ui->text_neurona->setText("Capa "  + QString::number(CCaps));

    ui->customPlot->graph(0)->data()->clear();
    ui->customPlot->graph(1)->data()->clear();
    ui->customPlot->graph(2)->data()->clear();
    ui->customPlot->graph(3)->data()->clear();
    ui->customPlot->graph(4)->data()->clear();
    ui->customPlot->graph(5)->data()->clear();
    ui->customPlot->graph(6)->data()->clear();
    ui->customPlot->graph(7)->data()->clear();

    ui->customPlot->replot();
    ui->customPlot->update();
    ui->sliderClases->setValue(0);

    ui->errorPlot->graph(0)->data()->clear();
    ui->errorPlot->replot();
    ui->errorPlot->update();

    errorX.clear();
    errorY.clear();
    ui->text_resultados->setText(" ");
}

void MainWindow::clickedGraph(QMouseEvent *event)
{
    QPoint point = event->pos();
    std::vector<double> Cl(cantidadClases,0);

    Cl[selectClass] = 1;

    Point myPoint(ui->customPlot->xAxis->pixelToCoord(point.x()),ui->customPlot->yAxis->pixelToCoord(point.y()),Cl);
    addPoint(myPoint,selectClass);
    plot();
}

void MainWindow::on_sliderClases_valueChanged()
{
    selectClass = ui->sliderClases->value();
    ui->text_class->setText("Clase " + QString::number(selectClass) + " seleccionada.");
}

void MainWindow::on_pushButton_6_clicked()
{
    QString cString = ui->input_clases->text();
    cantidadClases = cString.toInt();
    if(cantidadClases < 9)
    {
        ui->sliderClases->setRange(0,cantidadClases-1);
        numNeuroPorCapa.push_back(2);
        ui->text_clases->setText("LISTO");
        qDebug() << "#Clases Listo";

        for(int i = 0; i < 8; i++)
        {
            ui->customPlot->addGraph();
            switch(i)
            {
                case 0:
                    ui->customPlot->graph(i)->setPen(QPen(Qt::red));
                break;
                case 1:
                    ui->customPlot->graph(i)->setPen(QPen(Qt::blue));
                break;
                case 2:
                    ui->customPlot->graph(i)->setPen(QPen(Qt::green));
                break;
                case 3:
                    ui->customPlot->graph(i)->setPen(QPen(Qt::black));
                break;
                case 4:
                    ui->customPlot->graph(i)->setPen(QPen(Qt::darkGray));
                break;
                case 5:
                    ui->customPlot->graph(i)->setPen(QPen(Qt::darkMagenta));
                break;
                case 6:
                    ui->customPlot->graph(i)->setPen(QPen(Qt::darkYellow));
                break;
                case 7:
                    ui->customPlot->graph(i)->setPen(QPen(Qt::darkCyan));
                break;
            }

            ui->customPlot->graph(i)->setScatterStyle(QCPScatterStyle::ssDisc);
            ui->customPlot->graph(i)->setLineStyle(QCPGraph::lsNone);
        }
    }
}

void MainWindow::on_capasOcultas_btn_clicked()
{
    QString cString = ui->input_capas->text();
    ContCapas = cString.toInt();
    ui->text_capas->setText("LISTO");
    qDebug() << "#Capas Ocultas Listo";
    ui->text_neurona->setText("Oculta " + QString::number(CCaps));
}

void MainWindow::on_neuronasPorCapa_btn_clicked()
{
    if(CCaps < ContCapas)
    {
        qDebug() << "Capa Oculta " + QString::number(CCaps) + " lista.";
        QString x = ui->input_neuronas->text();
        numNeuroPorCapa.push_back(x.toInt());
        CCaps++;
        if(CCaps < ContCapas)
        {
            ui->text_neurona->setText("Capa "  + QString::number(CCaps));
        }
        else
        {
            ui->text_neurona->setText("LISTO");
        }
    }
}

void MainWindow::on_backPropagation_clicked()
{
    crearRed();

    double error = 0;
    double error2 = 0;
    int generaciones = ui->input_g->text().toInt();
    double factor = ui->input_f->text().toDouble();
    double desired = ui->input_e->text().toDouble();

    bool done = false;
    int iteraciones = generaciones;

    for(int g = 0; g < generaciones; g++)
    {
        error2 = 0;
        for(const Point& i : pointVector)
        {
            Red.Delta(Red.FeedForward({i.x,i.y}),i.Class,factor);

            double mejor = 0;
            int index = 0;
            std::vector<double>obtenidos = Red.FeedForward({i.x,i.y});
            for(int k = 0; k < obtenidos.size(); k++)
            {

                if(obtenidos[k] > mejor)
                {
                    mejor = obtenidos[k];
                    index = k;
                }
            }
            error = i.Class[index] - obtenidos[index];
            error2 += error*error;
        }
        error2 = error2/pointVector.size();
        errorX.push_back(g);
        errorY.push_back(error2);
        if(error2 <= desired)
        {
            done = true;
            iteraciones = g;
            break;
        }
    }
    ui->errorPlot->xAxis->setRange(0,iteraciones);
    PaintClass();
    plotError();
    plot();

    if(done)
    {
        QString respuesta = "Se alcanzó el error deseado en " + QString::number(iteraciones) + " iteraciones, el error obtenido es " + QString::number(error2);
        ui->text_resultados->setText(respuesta);
    }
    else
    {
        QString respuesta = "La Red No alcanzó el error deseado, el error alcanzado es de: " + QString::number(error2);
        ui->text_resultados->setText(respuesta);
    }
}

void MainWindow::on_pushButton_3_clicked()
{
    clearData();
}

void MainWindow::on_circulo_clicked()
{
    on_pushButton_6_clicked();
    double x = -0.25;
    double y = -0.25;
    for(int i = 0; i < 50; i++)
    {
        x += 0.01;
        addExample(x,y,0);
    }
    for(int i = 0; i < 50; i++)
    {
        y += 0.01;
        addExample(x,y,0);
    }
    for(int i = 0; i < 50; i++)
    {
        x -= 0.01;
        addExample(x,y,0);
    }
    for(int i = 0; i < 50; i++)
    {
        y -= 0.01;
        addExample(x,y,0);
    }
    x = -0.5;
    y = -0.5;
    for(int i = 0; i < 100; i++)
    {
        x += 0.01;
        addExample(x,y,1);
    }
    for(int i = 0; i < 100; i++)
    {
        y += 0.01;
        addExample(x,y,1);
    }
    for(int i = 0; i < 100; i++)
    {
        x -= 0.01;
        addExample(x,y,1);
    }
    for(int i = 0; i < 100; i++)
    {
        y -= 0.01;
        addExample(x,y,1);
    }

    x = -0.75;
    y = -0.75;
    for(int i = 0; i < 150; i++)
    {
        x += 0.01;
        addExample(x,y,2);
    }
    for(int i = 0; i < 150; i++)
    {
        y += 0.01;
        addExample(x,y,2);
    }
    for(int i = 0; i < 150; i++)
    {
        x -= 0.01;
        addExample(x,y,2);
    }
    for(int i = 0; i < 150; i++)
    {
        y -= 0.01;
        addExample(x,y,2);
    }
    plot();
}

void MainWindow::on_centro_clicked()
{
    ui->input_clases->setText("4");
    on_pushButton_6_clicked();
    double x = -0.25;
    double y = -0.25;
    for(int i = 0; i < 50; i++)
    {
        x += 0.01;
        addExample(x,y,0);
    }
    for(int i = 0; i < 50; i++)
    {
        y += 0.01;
        addExample(x,y,1);
    }
    for(int i = 0; i < 50; i++)
    {
        x -= 0.01;
        addExample(x,y,2);
    }
    for(int i = 0; i < 50; i++)
    {
        y -= 0.01;
        addExample(x,y,3);
    }
    plot();
}

void MainWindow::on_gato_clicked()
{
    on_pushButton_6_clicked();
    double x = 0;
    double y = -1;
    for(int i = 0; i < 100; i++)
    {
        y += 0.02;
        addExample(x,y,0);
    }

    x = -1;
    y = 0;
    for(int i = 0; i < 45; i++)
    {
        x += 0.02;
        addExample(x,y,1);
    }
    x = 1;
    y = 0;
    for(int i = 0; i < 45; i++)
    {
        x -= 0.02;
        addExample(x,y,1);
    }

    x = -1;
    y = -0.5;
    for(int i = 0; i < 45; i++)
    {
        x += 0.02;
        addExample(x,y,2);
    }
    x = 1;
    y = -0.5;
    for(int i = 0; i < 45; i++)
    {
        x -= 0.02;
        addExample(x,y,2);
    }

    x = -1;
    y = 0.5;
    for(int i = 0; i < 45; i++)
    {
        x += 0.02;
        addExample(x,y,2);
    }
    x = 1;
    y = 0.5;
    for(int i = 0; i < 45; i++)
    {
        x -= 0.02;
        addExample(x,y,2);
    }
    plot();
}
