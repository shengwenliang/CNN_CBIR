#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "extracthash.h"
#include "compute_distance.h"
#include "qt_kgraph.h"
using namespace std;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->image = new QImage();
    initial();
    ui->label->setStyleSheet("color:red;");
}

MainWindow::~MainWindow()
{
    delete image;
    delete ui;
    delete[] query_code;
}


void MainWindow::on_pushButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,"open image file",".","Image files (*.bmp *.jpg *.JPEG;;All files (*.*)");
    if(fileName !="" && ((ui->deploy_textBrowser->toPlainText()).toStdString())!=""&&((ui->model_textBrowser->toPlainText()).toStdString())!="")
    {
        if(image->load(fileName))
        {
            qDebug()<<fileName;
            QGraphicsScene *scene = new QGraphicsScene;
            QImage query = image->scaled(150,150,Qt::KeepAspectRatio,Qt::FastTransformation).scaled(150,150,Qt::KeepAspectRatio,Qt::SmoothTransformation);
            scene->addPixmap(QPixmap::fromImage(query));
            ui->image->setScene(scene);
            //ui->image->resize(image->width()+10,image->height()+10);
            ui->image->show();
            query_code = Extract_Hash(fileName.toStdString(),(ui->deploy_textBrowser->toPlainText()).toStdString(),(ui->model_textBrowser->toPlainText()).toStdString(),1);
        }
    }
    else
        ui->label->setText("error! chech input image and select deploy and model file");
}


QFileInfoList GetFileList(QString path)
{
    QDir dir(path);
    QFileInfoList file_list = dir.entryInfoList(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    QFileInfoList folder_list = dir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot);

    for(int i = 0; i != folder_list.size(); i++)
    {
         QString name = folder_list.at(i).absoluteFilePath();
         QFileInfoList child_file_list = GetFileList(name);
         file_list.append(child_file_list);
    }

    return file_list;
}
void MainWindow::on_pushButton_2_clicked()
{
    qDeleteAll(ui->ScrollView->children());
    QGridLayout *layout = new QGridLayout;
    QString pathname = QFileDialog::getExistingDirectory(this,tr("Open Directory"),".",QFileDialog::ShowDirsOnly|QFileDialog::DontResolveSymlinks);
    if(pathname !="")
    {
        qDebug()<<pathname;
        QFileInfoList list = GetFileList(pathname);
        for(int i=0;i<list.size();i++)
        {
            if(i>100)
            {
                break;
            }
            qDebug()<<list.at(i).fileName();
            qDebug()<<i;
            if(image->load(pathname+"/"+list.at(i).fileName()))
            {

                QLabel *label = new QLabel();
                QImage query = image->scaled(100,100);
                label->setPixmap(QPixmap::fromImage(query));
                layout->addWidget(label,i/4,i%4);
            }
        }

    }
    ui->ScrollView->setLayout(layout);
}



void MainWindow::on_pushButton_3_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,"open deploy file",".","deploy files (All files (*.*)");
    if(fileName !="")
    {
        ui->deploy_textBrowser->setText(fileName);
    }
    else
        ui->label->setText("please select depoly file");

}

void MainWindow::on_pushButton_4_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,"open model file",".","model files (All files (*.*)");
    if(fileName !="")
    {
        ui->model_textBrowser->setText(fileName);
    }
    else
        ui->label->setText("please select model file");

}

void MainWindow::on_pushButton_5_clicked() //retrieval
{
    string query;
    qDeleteAll(ui->ScrollView->children());
    vector<float> encode_query;
    vector<float> hash_float_query;
    QGridLayout *layout = new QGridLayout;
    for (int i = 0; i < 48; i++)
    {
        encode_query.push_back(query_code[i]);
        //std::cout << *pstart << endl;
        if(query_code[i] > 0.5)
        {
           query.append("1");
           hash_float_query.push_back(1);
           std::cout << "1-" << query_code[i]<<endl;
        }
        else
        {
            query.append("0");
            hash_float_query.push_back(0);
            std::cout << "0- " << query_code[i]<<endl;
        }
    }
    vector<string> receiver_res;
    QButtonGroup button;
    button.addButton(ui->radioButton,0);// hamming
    button.addButton(ui->radioButton_2,1);//eculidean
    int a = button.checkedId();
    receiver_res = Computing_Distance(query,hash_float_query,encode_query,a);
    int i=0;
    for(auto iter=receiver_res.begin();iter!=receiver_res.end();++iter)
    {
        if(image->load((QString::fromStdString(*iter))))
        {

            QLabel *label = new QLabel();
            QImage query = image->scaled(100,100);
            label->setPixmap(QPixmap::fromImage(query));
            layout->addWidget(label,i/4,i%4);
        }
        i++;
        //cout<<*iter<<endl;
    }

    ui->ScrollView->setLayout(layout);
    //std::cout<<query<<endl;

}
void MainWindow::on_pushButton_6_clicked()
{
    qDeleteAll(ui->ScrollView->children());
    QGridLayout *layout = new QGridLayout;
    vector<string> receiver_res;
    receiver_res =  mains(query_code);
    int i=0;
    for(auto iter=receiver_res.begin();iter!=receiver_res.end();++iter)
    {
        if(image->load((QString::fromStdString(*iter))))
        {

            QLabel *label = new QLabel();
            QImage query = image->scaled(100,100);
            label->setPixmap(QPixmap::fromImage(query));
            layout->addWidget(label,i/4,i%4);
        }
        i++;
        //cout<<*iter<<endl;
    }

    ui->ScrollView->setLayout(layout);
    //std::cout<<query<<endl;

}
