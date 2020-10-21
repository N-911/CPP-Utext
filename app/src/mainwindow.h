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
#include "settings.h"

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
        void on_findLine_returnPressed();
        void on_buttonFind_clicked();
        void on_actionFind_All_triggered(bool checked);

        void on_actionReplace_Next_triggered(bool checked);  // cmd + R
        void on_actionActivity_Log_triggered();

        // context menu
        void onCustomContextMenu(const QPoint &point);

        // find replace
        void on_replaceLine_editingFinished();
        void on_buttonReplaceAll_clicked();

        // About
        void on_actionAbout_Utext_triggered();

        // dialog settings
        void on_actionPreferences_triggered();

//        void applySettings(QMap<QString, QString> _settings);

private:

    void readSettings();
    void writeSettings();
    void loadStyle(const QString &path);

    void on_action_context_file_new(QString fullFileName);
    void on_action_context_file_rename(QString fullFileName);
    void on_action_context_file_delete(QString fullFileName);
    void on_action_context_new_folder(QString fullFileName);

    Ui::MainWindow *ui;
    FileManager *m_file_manager = nullptr;
    QFileSystemModel *m_dirmodel = nullptr;
    Search *m_searcher = nullptr;
    Settings *m_settings = nullptr;
};

#endif // MAINWINDOW_H
