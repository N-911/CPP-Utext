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
//    QApplication app(argc, argv);
//    MainWindow window;
//    window.show();
//    system("leaks -q utag");


    TestRunner tr;
    RUN_TEST(tr, TestConstruct_from_two_nodes);
    RUN_TEST(tr, TestRopeAt);

    return 0;
}


/*
{
    LOG_DURATION("Set");
    std::set<std::string> s;
    for (int i =0; i < 10'000'000; ++i)
        s.insert("a");
}
{
    LOG_DURATION("unord Set");
    std::unordered_set<std::string> s;
    for (int i =0; i < 10'000'000; ++i)
        s.insert("a");
}


{
    LOG_DURATION("String");
    std::string s;
    for (int i =0; i < 10'000'000; ++i) {
        s.insert(s.size() - 1, "f");
    }
}

 */
