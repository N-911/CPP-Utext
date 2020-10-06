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
#include "tabmenager.h"

QT_BEGIN_NAMESPACE
namespace Ui {
    class MainWindow;
}
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);


    ~MainWindow() override;

    void loadFile(const QString &fileName);
    void setCurrentFile(QString file_name);

private slots:

        void newFile(){};
        void open(){};
        bool save(){};


        void on_actionOpen_triggered();

private:
    Ui::MainWindow *ui;
    TabMenager *m_tabmg;
//    QPlainTextEdit *textEdit;
    QString curFile;
};


#endif // MAINWINDOW_H
