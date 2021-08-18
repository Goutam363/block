#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sha256.h"

std::string int_to_string(int num){
    std::string res="";
    while (num>0) {
        res+=char(num%10+48);
        num/=10;
    }
    for(int i=0,j=res.length()-1;i<j;i++,j--)
    {
        char temp=res[i];
        res[i]=res[j];
        res[j]=temp;
    }
    return res;
}

void MainWindow::calculateHashOfBlock()
{
    QString qstr=ui->lineEdit->text();
    qstr+=ui->lineEdit_2->text();
    qstr+=ui->textEdit->toPlainText();
    std::string str=qstr.toStdString();
    ui->label_5->setText(QString::fromStdString(sha256::hash256_hex_string(str)));
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Block");
    ui->lineEdit->setText("1");
    calculateHashOfBlock();
    for(int i=0;ui->label_5->text().at(0)!='0' || ui->label_5->text().at(1)!='0' || ui->label_5->text().at(2)!='0';i++){
        ui->lineEdit_2->setText(QString::fromStdString(int_to_string(i)));
        calculateHashOfBlock();
    }
    connect(ui->lineEdit,&QLineEdit::textChanged,[=](){
        calculateHashOfBlock();
    });
    connect(ui->lineEdit_2,&QLineEdit::textChanged,[=](){
        calculateHashOfBlock();
    });
    connect(ui->textEdit,&QTextEdit::textChanged,[=](){
        calculateHashOfBlock();
    });
    connect(ui->pushButton,&QPushButton::pressed,[=](){
        for(int i=0;ui->label_5->text().at(0)!='0' || ui->label_5->text().at(1)!='0' || ui->label_5->text().at(2)!='0';i++){
            ui->lineEdit_2->setText(QString::fromStdString(int_to_string(i)));
            calculateHashOfBlock();
        }
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

