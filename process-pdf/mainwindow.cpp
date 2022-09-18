#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QProcess>
#include <QDialog>
#include <QDir>
#include <QFileDialog>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(this,SIGNAL(filePath(QString)),this,SLOT(process_python(QString)));
    QPixmap pic("./select.png");
    ui->label->setPixmap(pic);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::process_python(QString p)
{
    // Setup a process to run the Python script   https://stackoverflow.com/questions/47276571/qprocess-passing-arguments-to-a-python-script
    //qDebug()<<p;
    process1=new QProcess(this);
    QDir dir("/home/yj/qtl/process-pdf");
    QFileInfo info(dir,"py-pdf.py");
    process1->start("/usr/bin/python3.10",QStringList()<<info.absoluteFilePath()<<p);
    connect(process1,SIGNAL(readyReadStandardOutput()),this,SLOT(OnReadData()));

}

void MainWindow::on_selectButton_clicked()
{
    QString filename=QFileDialog::getOpenFileName(this,"Load PDF file",QDir::homePath(),"PDF file (*.pdf)");
    //qDebug()<<filename;
    emit filePath(filename);
}
void MainWindow::OnReadData(){
    QString strResult=QString::fromLocal8Bit(process1->readAllStandardOutput().data());
    QString stdOut=strResult.mid(0,strResult.length()-1);
    //qDebug()<<stdOut;
    if(stdOut=="Process completed!"){
        QPixmap pic("./done.jpeg");
        ui->label->setPixmap(pic);
    }
}
