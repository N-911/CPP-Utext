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
#include "loggingcategories.h"
#include <iostream>


using std::cout;
using std::endl;

#define NAME(x) #x

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    m_open_files = new FileManager(ui);
    m_tabmg = new TabMenager(ui->tabWidget);
    ui->tabWidget->removeTab(0);
    ui->tabWidget->removeTab(0);

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
    // set tab-file current
    ui->tabWidget->setCurrentIndex(index);  // !!!!
    m_open_files->closeFile(index);
    ui->tabWidget->removeTab(index);
}

void MainWindow::on_actionNew_file_triggered()
{
    m_open_files->newFile();
}

void MainWindow::on_actionSave_triggered()
{
    qInfo(logInfo()) << "action save";
    m_open_files->save();
}

void MainWindow::on_actionSave_as_triggered()
{
    qInfo(logInfo()) << "action saveAs";
    m_open_files->saveAs();
}

void MainWindow::on_actionClose_Tab_triggered()
{
    qInfo(logInfo()) << "action on_actionClose_Tab_triggered";
    int index = ui->tabWidget->currentIndex();
    m_open_files->closeFile(index);
    ui->tabWidget->removeTab(index);
}