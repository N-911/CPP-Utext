#include <iomanip>
#include <iostream>
#include <string>

#include "src/mainwindow.h"
#include "src/test_runner.h"
#include "src/rope_tests.h"



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
#include <set>
#include <unordered_set>

#include "profile.h"


using std::cout;
using std::endl;


int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    MainWindow window;
    window.show();

//    TestRunner tr;
//    RUN_TEST(tr, Test_Node_Construct_from_two_nodes);
//    RUN_TEST(tr, Test_Rope_At);
//    RUN_TEST(tr, Test_Node_getLenght);

//    system("leaks -q utext");
//    return 0;
    return app.exec();
}

