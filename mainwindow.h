#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include "chart.h"
#include <fstream>
#include <QFile>
#include <QTime>
#include <QTimer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_lineEdit_textChanged(const QString &arg1);

    void on_lineEdit_2_textChanged(const QString &arg1);

    void on_pushButton_clicked();

    void test_slot(QModelIndex,QModelIndex,QVector<int>);

    void fout();

    void fin();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void progresscheck(int state);

private:
    int N;
    double T;
    void enable_button1();
    //лучше пусть будут фолс
    bool check_N = true;
    bool check_T = true;
    Ui::MainWindow *ui;
    QStandardItemModel *model1;
    QModelIndex ind;
    Chart ch;
    QTimer *timer;

};

#endif // MAINWINDOW_H
