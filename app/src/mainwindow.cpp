#include <QFileDialog>
#include <algorithm>
#include <iostream>
#include "mainwindow.h"
#include "ui_mainwindow.h"


using std::cout;
using std::endl;


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
//    m_text = new Q

}

MainWindow::~MainWindow() {
    delete ui;

}
