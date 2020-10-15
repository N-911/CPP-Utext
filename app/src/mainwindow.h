#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <stdexcept>
#include <QMainWindow>
#include <QtCore>
#include <QtGui>
#include <QFileSystemModel>
#include <QDir>
#include <QTreeView>
#include <QString>
#include <QStringList>
#include <QGraphicsPixmapItem>
#include <QMediaPlayer>
#include <QtMultimedia>
#include <QMediaMetaData>
#include <QMetaDataReaderControl>
#include <QToolBar>
#include <iostream>
#include <deque>
#include "tabmenager.h"
#include "file_manager.h"
#include "treemodel.h"
#include "listmodel.h"
#include <projectmanager.h>

QT_BEGIN_NAMESPACE
namespace Ui {
    class MainWindow;
}
QT_END_NAMESPACE

class Search;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow() override;

private slots:
        void on_actionOpen_triggered();
        void on_tabWidget_tabCloseRequested(int index);
        void on_actionNew_file_triggered();
        void on_actionSave_triggered();
        void on_actionSave_as_triggered();

        void on_actionClose_Tab_triggered();
        void on_actionQuit_Utext_triggered();
        void on_actionSave_All_triggered();

        void on_actionNex_Tab_triggered();
        void on_actionSelect_Previous_tab_triggered();
        void on_treeView_doubleClicked(const QModelIndex &index);

        void on_actionAdd_Project_Folder_triggered();

        void on_buttonFind_clicked();

private:

    void readSettings();
    void writeSettings();

    Ui::MainWindow *ui;
    FileManager *m_file_manager;
    TabManager *m_tabmg = nullptr;
//    QFileSystemModel *m_dirmodel;
    ProjectManager *m_project_manager;
    Listmodel *m_project_model;
    Search *m_searcher = nullptr;
};


#endif // MAINWINDOW_H
