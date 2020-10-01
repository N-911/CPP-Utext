#include <iomanip>
#include <iostream>
#include <string>

#include "src/mainwindow.h"

#include <sys/stat.h>
#include <dirent.h>
#include <QApplication>
#include <QPushButton>
#include <QGridLayout>
#include <QLineEdit>
#include <QDateTimeEdit>
#include <QSpinBox>
#include <QComboBox>
#include <QLabel>
#include <QStringList>
#include <QDir>
#include <QToolBar>
#include "src/mainwindow.h"


using std::cout;
using std::endl;


int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    MainWindow window;
    window.show();
//    system("leaks -q utag");

    return app.exec();
}
