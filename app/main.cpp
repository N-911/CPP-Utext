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
#include "loggingcategories.h"

QScopedPointer<QFile>   m_logFile;

using std::cout;
using std::endl;

void messageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg);

int main(int argc, char **argv)
{
//    / Устанавливаем файл логирования,
    // внимательно сверьтесь с тем, какой используете путь для файла
    m_logFile.reset(new QFile("/Users/snikolayen/CPP-Utext/logFile.txt"));
    // Открываем файл логирования
    m_logFile.data()->open(QFile::Append | QFile::Text);
    // Устанавливаем обработчик
    qInstallMessageHandler(messageHandler);

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

void messageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    // Открываем поток записи в файл
    QTextStream out(m_logFile.data());
    // Записываем дату записи
    out << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz ");
    // По типу определяем, к какому уровню относится сообщение
    switch (type)
    {
        case QtInfoMsg:     out << "INF "; break;
        case QtDebugMsg:    out << "DBG "; break;
        case QtWarningMsg:  out << "WRN "; break;
        case QtCriticalMsg: out << "CRT "; break;
        case QtFatalMsg:    out << "FTL "; break;
    }
    // Записываем в вывод категорию сообщения и само сообщение
    out << context.category << ": "
        << msg << endl;
    out.flush();    // Очищаем буферизированные данные
}