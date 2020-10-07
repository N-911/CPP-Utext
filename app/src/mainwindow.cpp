#include <QFileDialog>
#include <algorithm>
#include <iostream>
#include <QLabel>
#include <QPlainTextEdit>
#include <QMessageBox>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "file_manager.h"


using std::cout;
using std::endl;

#define NAME(x) #x

//auto *test = new QPlainTextEdit();

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow), m_tabmg(new TabMenager()) {
    ui->setupUi(this);

    auto start_tab = new QWidget();

    m_open_files = new FileManager(ui);

    ui->tabWidget->setTabsClosable(true);

    ui->tabWidget->addTab(start_tab, NAME(start page));

    ui->tabWidget->removeTab(0);
    ui->tabWidget->removeTab(1);

//    setCentralWidget(ui->start_tab);


    ui->tabWidget->setStyleSheet("QTabBar {\n"
                                 "background-color: transparent;\n"
                                 "qproperty-drawBase:0;\n"
                                 "}");
//    QPlainTextEdit *textEdit = new QPlainTextEdit();;
//    auto *test = new QPlainTextEdit();
//    ui->tabWidget->addTab(test, NAME(test));

//    QAction *openAct = new QAction( this);
//    openAct->setShortcuts(QKeySequence::Open);
//    openAct->setStatusTip(tr("Open an existing file"));
//    connect(openAct, &QAction::triggered, this, &MainWindow::open);

//    test->setTabStopDistance(4 * ' ');
//    test->setPlainText(QString::number(test->tabStopDistance()));
//    ui->tabWidget->currentWidget()
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

    ui->tabWidget->removeTab(index);
}

void MainWindow::on_actionNew_file_triggered()
{
    auto untitled = new QWidget();
    auto index = ui->tabWidget->addTab(untitled, NAME(untitled));
    ui->tabWidget->setCurrentIndex(index);
}
