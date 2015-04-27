#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "logics.h"
#include <algorithm>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    _procsInfo = getProcsInfo();
    auto procList = _procsInfo.getProcList();

    //tree model
    treeModel = new QStandardItemModel(_procsInfo.getProcAmount(), 5);
    treeModel->setHorizontalHeaderItem( 0, new QStandardItem( "Executable" ) );
    treeModel->setHorizontalHeaderItem( 1, new QStandardItem( "PID" ) );
    treeModel->setHorizontalHeaderItem( 2, new QStandardItem( "TID" ) );
    treeModel->setHorizontalHeaderItem( 3, new QStandardItem( "RAM" ) );
    treeModel->setHorizontalHeaderItem( 4, new QStandardItem( "CPU" ) );
    int procNum = 0;

    for(auto procIter = procList.begin(); procIter != procList.end(); procIter++, procNum++)
    {
       QStandardItem *item = new QStandardItem( QString::fromStdString(procIter->_execName) );
       for(auto threadIter = procIter->getThreadList().begin(); threadIter != procIter->getThreadList().end(); threadIter++)
       {
          QStandardItem *child_1 = new QStandardItem( "" );
          QStandardItem *child_2 = new QStandardItem( "" );
          QStandardItem *child_3 = new QStandardItem( QString::number(threadIter->_tid) );
          QStandardItem *child_4 = new QStandardItem( "     0" );
          QStandardItem *child_5 = new QStandardItem( "     0" );

          auto itemsList = new QList<QStandardItem*> {child_1, child_2, child_3, child_4,child_5};
          item->appendRow( *itemsList );
       }
       treeModel->setItem(procNum, 0, item);

       item = new QStandardItem( QString::number(procIter->_pid));
       treeModel->setItem(procNum, 1, item);
       item = new QStandardItem( "" );
       treeModel->setItem(procNum, 2, item);
       item = new QStandardItem( "0");
       treeModel->setItem(procNum, 3, item);
       item = new QStandardItem( "0");
       treeModel->setItem(procNum, 4, item);
    }

    ui->treeView->setModel( treeModel );
    ui->treeView->setColumnWidth(0, 280);
    ui->treeView->setColumnWidth(1, 70);
    ui->treeView->setColumnWidth(2, 70);
    ui->treeView->setColumnWidth(3, 70);
    ui->treeView->setColumnWidth(4, 70);

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
