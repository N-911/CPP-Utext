#include <QFileDialog>
#include <algorithm>
#include <iostream>
#include <QLabel>
#include <QPlainTextEdit>
#include <QMessageBox>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "file_manager.h"
#include "tabwelcome.h"


using std::cout;
using std::endl;

#define NAME(x) #x

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

        m_open_files = new FileManager(ui);

    m_tabmg = new TabMenager(ui->tabWidget);

    ui->tabWidget->removeTab(0);
    ui->tabWidget->removeTab(0);

//    ui->tabWidget->addTab(new TabWelcome(ui->tabWidget), "Hello");

    ui->tabWidget->setStyleSheet("QTabBar {\n"
                                 "background-color: transparent;\n"
                                 "qproperty-drawBase:0;\n"
                                 "}");
//    test->setTabStopDistance(4 * ' ');
//    test->setPlainText(QString::number(test->tabStopDistance()));
}

MainWindow::~MainWindow() {
    delete ui;
    system("leaks -q utext");
}


void MainWindow::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this);
    if (!fileName.isEmpty()) {
        m_open_files->loadFile(fileName);
    }
}



void MainWindow::on_tabWidget_tabCloseRequested(int index)
{
    // click on icon close tab file

    m_open_files->close_file();
    ui->tabWidget->removeTab(index);
}

void MainWindow::on_actionNew_file_triggered()
{
    auto untitled = new QWidget();
    auto index = ui->tabWidget->addTab(untitled, NAME(untitled));
    ui->tabWidget->setCurrentIndex(index);
}

void MainWindow::on_actionSave_triggered()
{
//    QString fileName =

}
