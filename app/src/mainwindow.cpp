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

    readSettings();

//    const QIcon newIcon = QIcon::fromTheme("New", QIcon(":/filenew.png"));
//    QAction *newAct = new QAction(newIcon, tr("&New"), this);
//    ui->toolBar->addAction(newAct);

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
    qDebug(log_text_window()) << "action on_actionClose_Tab_triggered";
}

void MainWindow::on_actionNew_file_triggered()
{
    m_open_files->newFile();
}

void MainWindow::on_actionSave_triggered()
{
    qDebug(log_text_window()) << "cmd + S";
    m_open_files->save();
}

void MainWindow::on_actionSave_as_triggered()
{
    qDebug(log_text_window()) << "shft + cmd + S";
    m_open_files->saveAs();
}

void MainWindow::on_actionClose_Tab_triggered()
{
    qDebug(log_text_window()) << "cmd + W";
    int index = ui->tabWidget->currentIndex();
    m_open_files->closeFile(index);
    ui->tabWidget->removeTab(index);
}

void MainWindow::readSettings() {

    QSettings settings(QCoreApplication::organizationName(), QCoreApplication::applicationName());
    const QByteArray geometry = settings.value("geometry", QByteArray()).toByteArray();
    if (geometry.isEmpty()) {
        const QRect availableGeometry = screen()->availableGeometry();
        resize(availableGeometry.width() / 3, availableGeometry.height() / 2);
        move((availableGeometry.width() - width()) / 2,
             (availableGeometry.height() - height()) / 2);
    } else {
        restoreGeometry(geometry);
    }
}

void MainWindow::writeSettings() {
    QSettings settings(QCoreApplication::organizationName(), QCoreApplication::applicationName());
    settings.setValue("geometry", saveGeometry());
}

void MainWindow::on_actionQuit_Utext_triggered()
{
    writeSettings();
}
