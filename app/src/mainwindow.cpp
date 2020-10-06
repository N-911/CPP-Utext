#include <QFileDialog>
#include <algorithm>
#include <iostream>
#include <QLabel>
#include <QPlainTextEdit>
#include "mainwindow.h"
#include "ui_mainwindow.h"


using std::cout;
using std::endl;

#define NAME(x) #x

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow), m_tabmg(new TabMenager()) {
    ui->setupUi(this);
    auto *test = new QPlainTextEdit();
    ui->tabWidget->setStyleSheet("QTabBar {\n"
                                 "background-color: transparent;\n"
                                 "qproperty-drawBase:0;\n"
                                 "}");
    ui->tabWidget->addTab(test, NAME(test));
//    QFont() font;
//    font.
//    test->setTabStopDistance(4 * ' ');
    test->setPlainText(QString::number(test->tabStopDistance()));
//    ui->tabWidget->currentWidget()
}

MainWindow::~MainWindow() {
    delete ui;
}
