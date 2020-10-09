#include "src/mainwindow.h"
#include "src/test_runner.h"
#include "src/rope_tests.h"
#include "profile.h"
#include "loggingcategories.h"

#include <iomanip>
#include <iostream>
#include <string>
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

QScopedPointer<QFile>   m_logFile;

using std::cout;
using std::endl;

void messageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg);

int main(int argc, char **argv)
{
//    / Устанавливаем файл логирования,
    m_logFile.reset(new QFile("../../app/logFile.txt"));
    m_logFile.data()->open(QFile::Append | QFile::Text);
    // Устанавливаем обработчик. To restore the message handler, call qInstallMessageHandler(0).
    qInstallMessageHandler(messageHandler);

    QApplication app(argc, argv);
    // app settings
    QCoreApplication::setOrganizationName("Ucode");
    QCoreApplication::setApplicationName("Utext");
    QCoreApplication::setApplicationVersion(QT_VERSION_STR);
    MainWindow window;
    window.show();

//    system("leaks -q utext");
    return app.exec();
}

void messageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QTextStream out(m_logFile.data());

    // Записываем дату запис
    out << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz ");

    QByteArray localMsg = msg.toLocal8Bit();
    const char *file = context.file ? context.file : "";
    const char *function = context.function ? context.function : "";

    switch (type) {
        case QtDebugMsg:
            out << QString("Debug: %1 (%2:%3, %4)\n").arg(localMsg.constData()).arg(file).arg(context.line).arg(function);
            break;
        case QtInfoMsg:
            out << QString("Info: %1 (%2:%3, %4)\n").arg(localMsg.constData()).arg(file).arg(context.line).arg(function);
            break;
        case QtWarningMsg:
            out << QString("Warning: %1 (%2:%3, %4)\n").arg(localMsg.constData()).arg(file).arg(context.line).arg(function);
            break;
        case QtCriticalMsg:
            out << QString("Critical: %1 (%2:%3, %4)\n").arg(localMsg.constData()).arg(file).arg(context.line).arg(function);
            break;
        case QtFatalMsg:
            out << QString("Fatal: %1 (%2:%3, %4)\n").arg(localMsg.constData()).arg(file).arg(context.line).arg(function);
            break;
    }
    out.flush();    // Очищаем буферизированные данные
}


//////////=========

//    TestRunner tr;
//    RUN_TEST(tr, Test_Node_Construct_from_two_nodes);
//    RUN_TEST(tr, Test_Rope_At);
//    RUN_TEST(tr, Test_Node_getLenght);