#include <QFileDialog>
#include <algorithm>
#include <iostream>
#include <QLabel>
#include <QPlainTextEdit>
#include <QMessageBox>
#include "mainwindow.h"
#include "ui_mainwindow.h"


using std::cout;
using std::endl;

#define NAME(x) #x

//auto *test = new QPlainTextEdit();


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow), m_tabmg(new TabMenager()) {
    ui->setupUi(this);

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
}


void MainWindow::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this);
    if (!fileName.isEmpty()) {
        loadFile(fileName);
    }
}

void MainWindow::setCurrentFile(QString file_name) {
    curFile = file_name;
}

void MainWindow::loadFile(const QString &fileName) {
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, "Application",
                            QString("Cannot read file %1:\n%2.").arg(QDir::toNativeSeparators(fileName), file.errorString()));
        return;
    }

    QTextStream in(&file);
#ifndef QT_NO_CURSOR
    QGuiApplication::setOverrideCursor(Qt::WaitCursor);
#endif
    auto *new_file = new QPlainTextEdit();
    new_file->setPlainText(in.readAll());
//    ui->tabWidget->addTab(new_file, NAME());
    ui->tabWidget->addTab(new_file, fileName);

#ifndef QT_NO_CURSOR
    QGuiApplication::restoreOverrideCursor();
#endif

    setCurrentFile(fileName);
    statusBar()->showMessage(fileName + " loaded", 2000);
}
