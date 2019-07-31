#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>

#define TRAINING 5000
#define TESTING 25
float f(float x)
{
    return x-10;
}
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    QRect viewRect(-100, -100, 200, 200);
    ui->setupUi(this);
    scene = new QGraphicsScene(this);
    ui->graph->setScene(scene);
    ui->graph->setSceneRect(viewRect);


    //get height and widths for the graph
    width = ui->graph->geometry().width(),
    height = ui->graph->geometry().height();

    //Draw f(x)
   line = scene->addLine(0-width/2,0- f(0-width/2), width/2,0-f(width/2));
   for(int i =0- width/2 ; i < width/2 - 1 ; i++)
   {
       line = scene->addLine(i,0- f(i), i+1,0-f(i+1));
   }

   // rect = scene->addRect(0,width/2,200,200);

    //Draw x and y axis
    line = scene->addLine(0-width/2,0,width/2,0);
    line = scene->addLine(0,height/2, 0, 0 - height/2 );

    per = new Perception(3);

}


MainWindow::~MainWindow()
{
    delete ui;
    delete scene;
    delete per;
    for(int i = 0 ; i < train.size() ; i++)
    {
        delete train[i];
    }
    for(int i= 0 ; i < test.size() ; i++)
    {
        delete test[i];
    }
}

void MainWindow::on_pushButton_clicked()
{
    QBrush whiteBrush(Qt::white);
    QBrush redBrush(Qt::red);
    QPen blackPen(Qt::black);
    blackPen.setWidth(1);

    for(int i = 0 ; i < TRAINING; i++)
     {
        float x = (float)( rand() % (width /2/2)),
            y =(float)( rand() % (height / 2));

        int answer;
        if( y < f(x) )
          answer =  -1;
        else
          answer = 1;

        Trainer *temp = new Trainer(x,y,answer);

        train.push_back(temp);
        per->train(train[i]->input(), train[i]->getAnswer());
        qDebug() << '(' << train[i]->input()[0] << " , " << train[i]->input()[1] << ')' << train[i]->getAnswer() <<  endl;
    }

    for(int i = 0 ; i < TESTING  ; i++)
    {
        float x = (float)( rand() % (width /2)),
            y = (float)( rand() % (height / 2));
        int answer =  ( y < f(x) ) ? -1 : 1;


        Trainer* temp = new Trainer(x,y ,answer );
        test.push_back(temp);

    }

    qDebug() << "-------------Test------------\n";
    for(int i = 0 ; i < test.size(); i++)
    {
        int guess = per->feedForward(test[i]->input());
        qDebug() << '(' << test[i]->input()[0] << " , " << test[i]->input()[1] << ')' << test[i]->getAnswer() << guess << endl;

        if(guess > 0)
            points.push_back( scene->addRect(test[i]->getX(),0-test[i]->getY(),3,3,blackPen,redBrush));
        else
            points.push_back(scene->addRect(test[i]->getX(),0-test[i]->getY(),3,3));
    }
    for(int i = 0 ; i < test.size() ; i++)
        delete test[i];
    test.clear();

}

void MainWindow::on_pushButton_2_clicked()
{
    //clear the screen
    scene->clear();
    ui->graph->resetCachedContent();
    ui->graph->items().clear();

    //Draw line
    line = scene->addLine(0-width/2,0- f(0-width/2), width/2,0-f(width/2));

   // rect = scene->addRect(0,width/2,200,200);

    //Draw x and y axis
    line = scene->addLine(0-width/2,0,width/2,0);
    line = scene->addLine(0,f(-width/2), 0,f(width/2) );

   //Retrain the network with new points and create new test
   for(int i = 0 ; i < train.size() ; i++)
   {
       delete[] train[i];
   }
   for(int i = 0 ; i < test.size() ; i++)
   {
       delete[] test[i];
   }
   train.clear();
   test.clear();
   per->reTrain();
}
