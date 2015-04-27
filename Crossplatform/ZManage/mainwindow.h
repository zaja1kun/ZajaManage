#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QStandardItemModel>
#include "procsinfo.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    double getMaxItem(QVector<double>* vector);

private slots:
    void timer_overflow();
    void on_tabWidget_currentChanged(int index);
    void on_comboBox_currentIndexChanged(int index);
    void on_actionExit_triggered();

private:
    Ui::MainWindow *ui;
    QLabel *memoryStat
        , *processorStat
        , *procStat
        , *threadStat;
    QTimer *timer;
    ProcsInfo _procsInfo;
    QVector<double> *graphX
        , *graph1Y
        , *graph2Y
        , *procPlotY
        , *memPlotY
        , *processPlotY
        , *threadPlotY;
    QStandardItemModel* treeModel;
    double *plotRange
        , percentageRange = 100.0
        , greaterOfTwoRange;
};

#endif // MAINWINDOW_H
