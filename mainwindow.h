#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include <QtGui>
#include <QGraphicsView>
#include <QPushButton>
#include "nNet.h"
namespace Ui {
class MainWindow;
}
using namespace std;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    vector<QGraphicsRectItem *> points;
    QGraphicsRectItem *rect;
    QPushButton *butt;
    vector<Trainer*> train;
    vector<Trainer *> test;
    Perception * per;
    QGraphicsLineItem *line;
    int height,width;
    bool Training;
};

#endif // MAINWINDOW_H
