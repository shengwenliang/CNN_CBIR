#include "mainwindow.h"
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <cassert>
#include <string>
#include <QApplication>
#include "extracthash.h"
#include "compute_distance.h"
using namespace std;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
