#include <QFileDialog>
#include <algorithm>
#include <iostream>
#include <QLabel>
#include <QPlainTextEdit>
#include <QMessageBox>
#include <QCoreApplication>
#include <QFileSystemModel>
#include <QTreeView>
#include <QInputDialog>
#include <QMenu>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "file_manager.h"
#include "tabwelcome.h"
#include "loggingcategories.h"
#include <iostream>

#include "search.h"
#include "app.h"
#include "syntaxstyle.h"
#include "syntaxhighlightercxx.h"

using std::cout;
using std::endl;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    qInfo(logInfo()) << QString("Start Utext\n");

    ui->setupUi(this);
    m_file_manager = new FileManager(ui);
//    m_project_manager = new ProjectManager(ui);

    ui->tabWidget->removeTab(0);
    ui->tabWidget->removeTab(0);
    readSettings();
//    m_searcher = new Search(qobject_cast<QPlainTextEdit *>(ui->tabWidget->currentWidget()));
    ui->tabWidget->setStyleSheet("QTabBar {\n"
                                 "background-color: transparent;\n"
                                 "qproperty-drawBase:0;\n"
                                 "}");
    ui->toolBar->setHidden(true);
    ui->findWidget->setHidden(true);
    ui->replace_Widget->setHidden(true);
    ui->treeView->setHidden(true);

    m_dirmodel = new QFileSystemModel(this);
    m_dirmodel->setRootPath("/");

    ui->treeView->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->treeView, SIGNAL(customContextMenuRequested(const QPoint &)), this, SLOT(onCustomContextMenu(const QPoint &)));

    m_file_manager->getTabManager()->setSyntaxStyle(SyntaxStyle::darkStyle());          // Dark Style;
//    m_file_manager->getTabManager()->setSyntaxStyle(SyntaxStyle::defaultStyle());     // Default Style;
}

void MainWindow::onCustomContextMenu(const QPoint &point)
{

    QMenu contextMenu(tr("Context menu"), this);

    auto fullFileName = dynamic_cast<QFileSystemModel *>(ui->treeView->model())->filePath(ui->treeView->indexAt(point));

    QAction action_new("New ", this);
    connect(&action_new, SIGNAL(triggered()), this, SLOT(on_actionNew_file_triggered()));
    contextMenu.addAction(&action_new);

    QAction action_rename("Rename ", this);
    connect(&action_rename, &QAction::triggered, this, [=] () { on_action_context_file_rename(fullFileName); });
    contextMenu.addAction(&action_rename);

    QAction action_delete("Delete ", this);
    connect(&action_delete, &QAction::triggered, this, [=] { on_action_context_file_delete(fullFileName) ;});
    contextMenu.addAction(&action_delete);

    QAction action_new_folder("New folder ", this);
    connect(&action_new_folder, &QAction::triggered, this, [=] () {on_action_context_new_folder(fullFileName); });
    contextMenu.addAction(&action_new_folder);

    contextMenu.exec(mapToGlobal(point));
}

void MainWindow::on_action_context_file_rename(QString fullFileName) {
    if (QFileInfo info(fullFileName); info.isDir()) {
        QMessageBox::warning(0, "Warning ", "You cannot rename the folder");  // show warning
    }
    else {
        m_file_manager->fileRename(fullFileName);
    }
}

void MainWindow::on_action_context_file_delete(QString fullFileName) {


    const QMessageBox::StandardButton ret = QMessageBox::warning(0, QString("Application"),
                                        QString("Are you sure you want to delete the selected item?"),
                                             QMessageBox::Cancel | QMessageBox:: Ok);
    if (ret == QMessageBox::Ok) {
        if (QFileInfo(fullFileName).isFile()) {
            m_file_manager->deleteFile(fullFileName );
        } else {
            QMessageBox::warning(0, "Warning ", "You cannot delete the folder");  // show warning
            qInfo(logInfo()) << "Warning You cannot delete the folder " << fullFileName;
        }
    }
}

void MainWindow::on_action_context_new_folder(QString fullFileName) {
    qDebug(logDebug()) << "fullFileName = " << fullFileName;
    bool ok;
    QString new_folder_name = QInputDialog::getText(this,"New folder",
                                                    tr("Enter the new path for the new folder"),
                                                    QLineEdit::Normal,
                                                    "",
                                                     &ok);
    if (ok) {
        if (QFileInfo(fullFileName).isDir()) {
            fullFileName.append("/");
        }
        else {
            fullFileName.remove(fullFileName.lastIndexOf("/"),fullFileName.size());
        }
        QDir dir;
        if (!dir.mkpath(fullFileName + new_folder_name)) {
            qWarning(logWarning()) << "Folder is alrady exists";
            QMessageBox::warning (0, "new folder", "Folder is alrady exists");  // show warning
        }
        qInfo(logInfo()) << "New folder " << fullFileName + new_folder_name;
    }
}

MainWindow::~MainWindow() {
    if (m_searcher)
        delete m_searcher;
    delete m_file_manager;
    delete ui;

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

void MainWindow::on_actionClose_Tab_triggered()  //   cmd + W
{
    int index = ui->tabWidget->currentIndex();
    qDebug(log_text_window()) << "MainWindow::on_actionClose_Tab_triggered close tab " << index << "\n";
    if (index >= 0) {
        m_file_manager->closeFile(index);
        ui->tabWidget->removeTab(index);
    }
}

void MainWindow::on_actionQuit_Utext_triggered()  // cmd + q
{
    writeSettings();
    m_file_manager->saveAll();
    qInfo(logInfo()) << QString("Quit Utext\n");
    App::quit();
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
//    qDebug(logDebug()) << QString("set  %1 tab index").arg(index);
    ui->tabWidget->setCurrentIndex(index);
}


void MainWindow::on_treeView_doubleClicked(const QModelIndex &index)
{
    QString fullFilePath = m_dirmodel->filePath(index);
    qInfo(logInfo()) << "Opne file " << fullFilePath;
    if (!(QDir(fullFilePath).exists())) {
        m_file_manager->loadFile(fullFilePath);
    }
}

void MainWindow::on_actionAdd_Project_Folder_triggered() {
    QString dirName = QFileDialog::getExistingDirectory(this, "Open Directory", "/",
                                                        QFileDialog::ShowDirsOnly
                                                        | QFileDialog::DontResolveSymlinks);

    if (QDir cur_dir(dirName); !cur_dir.isReadable())
    {
        qWarning(logWarning()) << QString(QDir(dirName).dirName() + " directory not readable");
        ui->statusbar->showMessage(QString(QDir(dirName).dirName() + " directory not readable"), 3000);
    };


    m_dirmodel->setRootPath(dirName);
    ui->treeView->setHidden(false);
    ui->treeView->setModel(m_dirmodel);
    ui->treeView->setRootIndex(m_dirmodel->index(dirName));
    for (int i = 1; i < m_dirmodel->columnCount(); ++i)
    {
        ui->treeView->hideColumn(i);
    }
//    ui->treeView->viewport()->update();
}

void MainWindow::on_buttonFind_clicked()
{
    if (ui->tabWidget->count() <= 0)
        return;
    QString text = ui->findLine->text();
    m_searcher->setTextDocument(qobject_cast<QPlainTextEdit *>(ui->tabWidget->currentWidget()));
    m_searcher->searchText(text);
}

void MainWindow::on_actionFind_All_triggered(bool checked)
{
    if (m_searcher) {
        delete m_searcher;
        m_searcher = nullptr;
    }
    if (!checked && ui->tabWidget->currentWidget()) {
        m_searcher = new Search(qobject_cast<QPlainTextEdit *>(ui->tabWidget->currentWidget()));
        ui->findLine->setFocus();
    }
    if (!ui->replace_Widget->isHidden() && checked)
    {
        ui->replace_Widget->setHidden(checked);
    }

    ui->findWidget->setHidden(checked);
}

void MainWindow::on_actionReplace_Next_triggered(bool checked)
{
    if (!checked)
        on_actionFind_All_triggered(checked);
    ui->replace_Widget->setHidden(checked);
}


void MainWindow::on_findLine_returnPressed()
{
    on_buttonFind_clicked();
}

void MainWindow::on_actionActivity_Log_triggered()
{
    m_file_manager->loadFile(QCoreApplication::applicationDirPath() + "/logFile.txt");
}

void MainWindow::on_replaceLine_editingFinished()
{
    if (ui->replaceLine->text() == "")
        return;
    if (m_searcher) {
        m_searcher->searchText(ui->findLine->text());
        m_searcher->replace(ui->replaceLine->text());
    }
}

void MainWindow::on_buttonReplaceAll_clicked()
{
    if (ui->replaceLine->text() == "")
        return;
    if (m_searcher) {
        m_searcher->replaceAll(ui->replaceLine->text(), ui->findLine->text());
    }
}

void MainWindow::loadStyle(const QString &path)
{
    QFile fl(path);

    if (!fl.open(QIODevice::ReadOnly))
    {
        return;
    }

    auto style = new SyntaxStyle(this);

    if (!style->load(fl.readAll()))
    {
        delete style;
        return;
    }
}

//void MainWindow::on_actionToggle_Tree_View_triggered(bool checked)  // show or hide treeView
//{
//    ui->treeView->setHidden(checked);
//}


////////////////////////// delete before release

/*
void MainWindow::on_buttonFind_clicked()
{
    QString text = ui->findLine->text();
    m_searcher->setTextDocument(qobject_cast<QPlainTextEdit *>(ui->tabWidget->currentWidget())->document());
    m_searcher->searchText(text);
}

void MainWindow::on_findLine_returnPressed()
{
    on_buttonFind_clicked();
}

*/


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


//    auto index = dynamic_cast<QFileSystemModel *>(ui->treeView->model())->index(dirName);
//    if (m_dirmodel)
//        delete m_dirmodel;
//    m_dirmodel = new QFileSystemModel(this);
//    m_dirmodel->setNameFilters(QStringList()  << QString(QDir(dirName).dirName()));
//    QString(QDir(dirName).dirName())



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

//  QModelIndex index = ui->treeView->indexAt(point);
//  if (index.isValid() && index.row() % 2 == 0) {
//    ui->treeView->exec(ui->treeView->viewport()->mapToGlobal(point));
//    ui->contextMenu->exec(ui->treeView->viewport()->mapToGlobal(point));
//  }


//         QInputDialog* dialog = new QInputDialog(this);
//         dialog->setInputMode(QInputDialog::TextInput);
//         dialog->setStyleSheet("QLineEdit { background-color: blue }");
//         dialog->setOptions(QInputDialog::NoButtons);