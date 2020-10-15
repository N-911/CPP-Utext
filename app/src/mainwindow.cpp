#include <QFileDialog>
#include <algorithm>
#include <iostream>
#include <QLabel>
#include <QPlainTextEdit>
#include <QMessageBox>
#include <QCoreApplication>
#include <QFileSystemModel>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "file_manager.h"
#include "tabwelcome.h"
#include "loggingcategories.h"
#include <iostream>
#include "search.h"

#include "app.h"
#include "treemodel.h"
#include "listmodel.h"


using std::cout;
using std::endl;

#define NAME(x) #x

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    qInfo(logInfo()) << QString("    start Utext\n");
    m_file_manager = new FileManager(ui);
    m_project_manager = new ProjectManager(ui);
//    m_tabmg = new TabManager(ui->tabWidget);
    ui->tabWidget->removeTab(0);
    ui->tabWidget->removeTab(0);
    readSettings();
    m_searcher = ui->tabWidget->count() > 0 ? new Search(qobject_cast<QPlainTextEdit *>(ui->tabWidget->currentWidget())->document())
            : new Search(nullptr);

    ui->tabWidget->setStyleSheet("QTabBar {\n"
                                 "background-color: transparent;\n"
                                 "qproperty-drawBase:0;\n"
                                 "}");

    ui->toolBar->setHidden(true);
//    ui->listView->setSelectionModel(QAbstractItemView::ExtendedSelection);
//    ui->listView->setDragEnabled(true);
//    ui->listView->setAcceptDrops(true);
    const QString headers{"Title"};
    m_project_model = new Listmodel(headers, this, ui);
//    ui->listView->setModel(m_project_model);


//    m_dirmodel = new QFileSystemModel(this);
//    m_dirmodel->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs);
//    m_dirmodel->setRootPath("~/");
//    ui->treeWidget->scrollTo(m_dirmodel->index(current_project));
//    for (int i = 1; i < m_dirmodel->columnCount(); ++i)
//    {
//        ui->listView->hideColumn(i);
//    }

}

MainWindow::~MainWindow() {
    delete ui;
    delete m_file_manager;
    delete m_searcher;

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
    // click on icon close tab file  set tab-file current
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

void MainWindow::on_actionSave_All_triggered()  // shift + cmd + s
{
    m_file_manager->saveAll();
}

void MainWindow::on_actionNex_Tab_triggered()  // cmd + ]
{
    int index = (ui->tabWidget->currentIndex() + 1) < ui->tabWidget->count() ? ui->tabWidget->currentIndex() + 1 :
                ui->tabWidget->currentIndex() + 1 - ui->tabWidget->count();
    qDebug(logDebug()) << QString("set  %1 tab index").arg(index);
    ui->tabWidget->setCurrentIndex(index);
}

void MainWindow::on_actionSelect_Previous_tab_triggered()  // cmd + [
{
    int index = ui->tabWidget->currentIndex() > 0 ? ui->tabWidget->currentIndex() - 1:
                ui->tabWidget->currentIndex() + ui->tabWidget->count() - 1;
    qDebug(logDebug()) << QString("set  %1 tab index").arg(index);
    ui->tabWidget->setCurrentIndex(index);
}


void MainWindow::on_treeView_doubleClicked(const QModelIndex &index)
{
//    QString fullFilePath = m_dirmodel->filePath(index);
//    if (!(QDir(fullFilePath).exists())) {
//        m_file_manager->loadFile(fullFilePath);
//    }
}

void MainWindow::on_actionAdd_Project_Folder_triggered() {
//    readDir(index);
    QString dirName = QFileDialog::getExistingDirectory(this, "Open Directory", "/",
                                                        QFileDialog::ShowDirsOnly
                                                        | QFileDialog::DontResolveSymlinks);

    if (!m_project_model)
        delete m_project_model;


//    m_project_manager->add_project_folder(dirName);
    m_project_model->add_data(dirName);

    m_project_model = new Listmodel("", this, ui);
    ui->treeView->setModel(m_project_model);

    ui->treeView->viewport()->update();
}
















//////////////////////////


//    if (QDir(dirName).exists()) {
//        m_project_manager->add_project_folder(dirName);
        // redraw tre view !!!!!
//        m_project_model


//        m_dirmodel->setRootPath(dirName);
//        ui->listView->setRootIndex()
//        ui->listView->setModel(m_dirmodel);
//        for (int i = 1; i < m_dirmodel->columnCount(); ++i)
//        {
//            ui->listView->hideColumn(i);
//        }
//    }
//}



/*
 *     const QModelIndex index = ui->listView->selectionModel()->currentIndex();
    QAbstractItemModel *model = ui->listView->model();

    if (model->columnCount(index) == 0) {
        if (!model->insertColumn(0, index))
            return;
    }

    if (!model->insertRow(0, index))
        return;

    for (int column = 0; column < model->columnCount(index); ++column) {
        const QModelIndex child = model->index(0, column, index);
        model->setData(child, QVariant(tr("[No data]")), Qt::EditRole);
        if (!model->headerData(column, Qt::Horizontal).isValid())
            model->setHeaderData(column, Qt::Horizontal, QVariant(tr("[No header]")), Qt::EditRole);
    }

    ui->listView->selectionModel()->setCurrentIndex(model->index(0, 0, index),
                                            QItemSelectionModel::ClearAndSelect);
//    updateActions();
 */


//////////////////

//    on_fileBrowser_clicked(m_dirmodel->index(m_path));
//    test->setTabStopDistance(4 * ' ');
//    test->setPlainText(QString::number(test->tabStopDistance()));

//    const QIcon newIcon = QIcon::fromTheme("New", QIcon(":/filenew.png"));
//    QAction *newAct = new QAction(newIcon, tr("&New"), this);
//    ui->toolBar->addAction(newAct);


void MainWindow::on_buttonFind_clicked()
{
    QString text = ui->findLine->text();
    m_searcher->setTextDocument(qobject_cast<QPlainTextEdit *>(ui->tabWidget->currentWidget())->document());
    m_searcher->searchText(text);
}
