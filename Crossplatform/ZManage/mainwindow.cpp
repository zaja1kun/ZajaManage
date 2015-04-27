#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "logics.h"
#include <algorithm>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //plot data
    graphX = new QVector<double>(1200);
    for (int i=0; i<graphX->size(); ++i)
        (*graphX)[i] = i;
    procPlotY = new QVector<double>(1200);
    memPlotY = new QVector<double>(1200);
    processPlotY = new QVector<double>(1200);
    threadPlotY = new QVector<double>(1200);

    graph1Y = processPlotY;
    graph2Y = threadPlotY;
    plotRange = &greaterOfTwoRange;

    //plot
    ui->resPlot->addGraph();
    ui->resPlot->graph(0)->setPen(QPen(QColor(100, 100, 200), 2));
    ui->resPlot->addGraph();
    ui->resPlot->graph(1)->setPen(QPen(QColor(100, 200, 100), 2));
    ui->resPlot->xAxis->setRange(0, graphX->size());
    ui->resPlot->xAxis->setVisible(false);
    ui->resPlot->yAxis->setOffset(20);

    //statusBar
    procStat = new QLabel();
    ui->statusBar->addPermanentWidget(procStat);
    threadStat = new QLabel();
    ui->statusBar->addPermanentWidget(threadStat);
    memoryStat = new QLabel();
    ui->statusBar->addPermanentWidget(memoryStat);
    processorStat = new QLabel();
    ui->statusBar->addPermanentWidget(processorStat);

    procStat->setText("Processes: ");
    threadStat->setText("Threads: ");
    memoryStat->setText("RAM: ");
    processorStat->setText("CPU: ");

    //treeWidget data
    QStringList qStrL1;
     qStrL1 << "Init" << "1" << "" << "256" << "15";
    QTreeWidgetItem *QTopLevelItem1 = new QTreeWidgetItem(qStrL1);
    QStringList qStrL1_1;
     qStrL1_1 << "" << "" << "1" << "256" << "15";
    QTreeWidgetItem *QSecondLevelItem1 = new QTreeWidgetItem(qStrL1_1);
    QTopLevelItem1->addChild(QSecondLevelItem1);

    QStringList qStrL2;
     qStrL2 << "Qt Creator" << "2" << "" << "1024" << "41";
    QTreeWidgetItem *QTopLevelItem2 = new QTreeWidgetItem(qStrL2);

    QStringList qStrL2_1;
     qStrL2_1 << "" << "" << "2" << "512" << "28";
    QTreeWidgetItem *QSecondLevelItem2 = new QTreeWidgetItem(qStrL2_1);
    QTopLevelItem2->addChild(QSecondLevelItem2);

    QStringList qStrL2_2;
     qStrL2_2 << "" << "" << "3" << "512" << "13";
    QTreeWidgetItem *QSecondLevelItem3 = new QTreeWidgetItem(qStrL2_2);
    QTopLevelItem2->addChild(QSecondLevelItem3);


    QList<QTreeWidgetItem*> treeItems;
    treeItems.push_back(QTopLevelItem1);
    treeItems.push_back(QTopLevelItem2);

    ui->treeWidget->addTopLevelItems(treeItems);

    //timer
    timer = new QTimer;
    QObject::connect(timer,SIGNAL(timeout()), this, SLOT(timer_overflow()));
    timer->start(100);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete procStat;
}

double MainWindow::getMaxItem(QVector<double>* vector)
{
    double vectorMax=0;
    for(int i = 0; i < vector->size(); i++)
      if ((*vector)[i] > vectorMax)
        vectorMax = (*vector)[i];
    return vectorMax;
}


void MainWindow::timer_overflow()
{    
    //update process info
    _procsInfo = getProcsInfo();

    //update process tree
    if(ui->tabWidget->currentIndex()==0)
    {
        QString tempTreeLine;
    }

    //update plot data
    processPlotY->remove(0,1);
    processPlotY->push_back(_procsInfo.getProcAmount());
    threadPlotY->remove(0,1);
    threadPlotY->push_back(_procsInfo.getThreadAmount());
    procPlotY->remove(0,1);
    procPlotY->push_back(QTime::currentTime().second());
    memPlotY->remove(0,1);
    memPlotY->push_back(getRamBuisiness());
    greaterOfTwoRange = getMaxItem(graph1Y)>getMaxItem(graph2Y) ? getMaxItem(graph1Y) : getMaxItem(graph2Y);


    //update plot
    if(ui->tabWidget->currentIndex()==1)
    {
        ui->resPlot->graph(0)->setData(*graphX, *graph1Y);
        ui->resPlot->graph(1)->setData(*graphX, *graph2Y);
        ui->resPlot->yAxis->setRange(0, *plotRange);
        ui->resPlot->replot();
    }

    //update status bar
    procStat->setText("Processes: " + QString::number(_procsInfo.getProcAmount()));
    threadStat->setText("Threads: " + QString::number(_procsInfo.getThreadAmount()));
    memoryStat->setText("RAM: "+QString::number(floor(getRamBuisiness()))+"%");

    //update form
    this->update();
}

void MainWindow::on_tabWidget_currentChanged(int index)
{
    if(index==1)
    {
        ui->resPlot->graph(0)->setData(*graphX, *graph1Y);
        ui->resPlot->graph(1)->setData(*graphX, *graph2Y);
        ui->resPlot->yAxis->setRange(0, *plotRange);
        ui->resPlot->replot();
    }
}

void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    switch (index)
    {
    case 0:
        graph1Y = processPlotY;
        graph2Y = threadPlotY;
        ui->resPlot->graph(1)->setVisible(true);
        plotRange = &greaterOfTwoRange;
        break;
    case 1:
        graph1Y = procPlotY;
        graph2Y = procPlotY;
        ui->resPlot->graph(1)->setVisible(false);
        plotRange = &percentageRange;
        break;
    case 2:
        graph1Y = memPlotY;
        graph2Y = memPlotY;
        ui->resPlot->graph(1)->setVisible(false);
        plotRange = &percentageRange;
        break;
    default:
        break;
    }

    {
        ui->resPlot->graph(0)->setData(*graphX, *graph1Y);
        ui->resPlot->graph(1)->setData(*graphX, *graph2Y);
        ui->resPlot->yAxis->setRange(0, *plotRange);
        ui->resPlot->replot();
    }
}

void MainWindow::on_actionExit_triggered()
{
    this->close();
}
