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

auto *test = new QPlainTextEdit();


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow), m_tabmg(new TabMenager()) {
    ui->setupUi(this);
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

void MainWindow::on_actionOpen_triggered()
{

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
    test->setPlainText(in.readAll());
#ifndef QT_NO_CURSOR
    QGuiApplication::restoreOverrideCursor();
#endif

    setCurrentFile(fileName);
    statusBar()->showMessage(tr("File loaded"), 2000);
}
