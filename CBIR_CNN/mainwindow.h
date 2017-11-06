#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include<fstream>
#include<cassert>
#include<string>
#include <iostream>
#include <QMainWindow>
#include <QImage>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QFileDialog>
#include <QtGui>
#include <QGridLayout>
#include <QLabel>
#include <QDir>
#include <QAbstractScrollArea>
#include "extracthash.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

private:
    Ui::MainWindow *ui;
    QImage *image;
    QWidget *ImageView;
    QScrollBar *m_vscrollBar;
    NetTy* query_code;
};

#endif // MAINWINDOW_H
