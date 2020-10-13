#include <QFileDialog>
#include <algorithm>
#include <iostream>
#include <QLabel>
#include <QPlainTextEdit>
#include <QMessageBox>
#include <QCoreApplication>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "file_manager.h"
#include "tabwelcome.h"
#include "loggingcategories.h"
#include <iostream>

#include "app.h"


using std::cout;
using std::endl;

#define NAME(x) #x

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    qInfo(logInfo()) << QString("    start Utext\n");

    m_file_manager = new FileManager(ui);
//    m_tabmg = new TabManager(ui->tabWidget);
    ui->tabWidget->removeTab(0);
    ui->tabWidget->removeTab(0);

    readSettings();


    ui->tabWidget->setStyleSheet("QTabBar {\n"
                                 "background-color: transparent;\n"
                                 "qproperty-drawBase:0;\n"
                                 "}");

    ui->toolBar->setHidden(true);
//    ui->treeView->setSelectionModel(QAbstractItemView::ExtendedSelection);
    ui->treeView->setDragEnabled(true);
    ui->treeView->setAcceptDrops(true);

    m_dirmodel = new QFileSystemModel(this);
//    m_dirmodel->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs);
    m_dirmodel->setRootPath("~/");

    ui->treeView->setModel(m_dirmodel);
//    ui->treeWidget->scrollTo(m_dirmodel->index(current_project));

    for (int i = 1; i < m_dirmodel->columnCount(); ++i)
    {
        ui->treeView->hideColumn(i);
    }

}

MainWindow::~MainWindow() {
    qInfo(logInfo()) << "~MainWindow";
    delete ui;
    delete m_file_manager;

    system("leaks -q utext");
}

void MainWindow::readSettings() {
    QSettings *settings = App::utext_app()->utext_settings();

    const QByteArray geometry = settings->value("geometry", QByteArray()).toByteArray();
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
    QSettings *settings = App::utext_app()->utext_settings();
    settings->setValue("geometry", saveGeometry());
}

void MainWindow::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this);
    if (!fileName.isEmpty()) {
        m_file_manager->loadFile(fileName);
    }
}

void MainWindow::on_tabWidget_tabCloseRequested(int index)
{
    // click on icon close tab file
    // set tab-file current
    ui->tabWidget->setCurrentIndex(index);  // !!!!
    m_file_manager->closeFile(index);
    ui->tabWidget->removeTab(index);
    qDebug(log_text_window()) <<  "MainWindow::on_tabWidget_tabCloseRequested close tab " << index << "\n";
}

void MainWindow::on_actionNew_file_triggered()
{
    m_file_manager->newFile();
}

void MainWindow::on_actionSave_triggered()
{
    if (ui->tabWidget->count() == 0) {
        return;
    }
    qDebug(log_text_window()) << "MainWindow::on_actionSave_triggered";
    m_file_manager->save();
}

void MainWindow::on_actionSave_as_triggered()
{
    qDebug(log_text_window()) << "MainWindow::on_actionSave_as_triggered";
    m_file_manager->saveAs();
}

void MainWindow::on_actionClose_Tab_triggered()
{
    //   cmd + W
    int index = ui->tabWidget->currentIndex();
    qDebug(log_text_window()) << "MainWindow::on_actionClose_Tab_triggered close tab " << index << "\n";
    if (index >= 0) {
        m_file_manager->closeFile(index);
        ui->tabWidget->removeTab(index);
    }
}

void MainWindow::on_actionQuit_Utext_triggered()
{
    // cmd + q
    writeSettings();
    qInfo(logInfo()) << QString("    end Utext\n");
}

void MainWindow::on_actionSave_All_triggered()
{
    m_file_manager->saveAll();
}

void MainWindow::on_actionNex_Tab_triggered()
{
    int index = (ui->tabWidget->currentIndex() + 1) < ui->tabWidget->count() ? ui->tabWidget->currentIndex() + 1 :
                ui->tabWidget->currentIndex() + 1 - ui->tabWidget->count();
    qDebug(logDebug()) << QString("set  %1 tab index").arg(index);
    ui->tabWidget->setCurrentIndex(index);
}

void MainWindow::on_actionSelect_Previous_tab_triggered()
{
    int index = ui->tabWidget->currentIndex() > 0 ? ui->tabWidget->currentIndex() - 1:
                ui->tabWidget->currentIndex() + ui->tabWidget->count() - 1;
    qDebug(logDebug()) << QString("set  %1 tab index").arg(index);
    ui->tabWidget->setCurrentIndex(index);
}



//////////////////

//    on_fileBrowser_clicked(m_dirmodel->index(m_path));
//    test->setTabStopDistance(4 * ' ');
//    test->setPlainText(QString::number(test->tabStopDistance()));


//    const QIcon newIcon = QIcon::fromTheme("New", QIcon(":/filenew.png"));
//    QAction *newAct = new QAction(newIcon, tr("&New"), this);
//    ui->toolBar->addAction(newAct);