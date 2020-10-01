#include <QFileDialog>
#include <algorithm>
#include <iostream>
#include "mainwindow.h"
#include "ui_mainwindow.h"


using std::cout;
using std::endl;


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {

}

MainWindow::~MainWindow() {
    delete ui;

}
