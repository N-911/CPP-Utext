
//    auto *tmp = qobject_cast<QPlainTextEdit>(m_parent->tabWidget->currentWidget());

#include "file_manager.h"

#include <QDir>
#include <QFile>
#include <QSaveFile>
#include <QFileInfo>
#include <QMessageBox>
#include <QTextStream>
#include <QPlainTextEdit>
#include "ui_mainwindow.h"


FileManager::FileManager(Ui::MainWindow *parent) : m_parent(parent) {
}

void FileManager::loadFile(const QString &fileName) {
    // если файл уже открыт
    if (m_load_files.count(fileName) != 0) {
        m_parent->tabWidget->setCurrentWidget(m_load_files[fileName]);  // делаем окно текущим
        setCurrentFile(m_load_files[fileName]);
        return;
    }

    QFile file(fileName);
    QFileInfo info_file(fileName);

    if (!file.open(QFile::ReadOnly | QFile::Text)) {
//        QMessageBox::warning (this, "Application",
//                             QString("Cannot read file %1:\n%2.").arg(QDir::toNativeSeparators(fileName), file.errorString()));
        m_parent->statusbar->showMessage(QString("Cannot read file %1:\n%2.").arg(QDir::toNativeSeparators(fileName),
                                                                                  file.errorString()), 2000);
        return;
    }

    QTextStream in(&file);
#ifndef QT_NO_CURSOR
    QGuiApplication::setOverrideCursor(Qt::WaitCursor);
#endif
    auto *text_edit_file = new QPlainTextEdit();

    text_edit_file->setPlainText(in.readAll());

    auto index = m_parent->tabWidget->addTab(text_edit_file, info_file.fileName());

    m_parent->tabWidget->setCurrentIndex(index);  // делаем новое окно текущим
    m_load_files[fileName] = m_parent->tabWidget->widget(index);

#ifndef QT_NO_CURSOR
    QGuiApplication::restoreOverrideCursor();
#endif
    setCurrentFile(m_parent->tabWidget->currentWidget());

    m_parent->statusbar->showMessage(fileName + " loaded", 2000);

}

void FileManager::setCurrentFile(QWidget *current_file) {
    m_current_file = current_file;
}

//void MainWindow::setCurrentFile(QString file_name) {
//    curFile = file_name;
//}

/*
bool FileManager::saveFile(const QString &fileName) {
    QString errorMessage;

    QGuiApplication::setOverrideCursor(Qt::WaitCursor);

    QSaveFile file(fileName);

    if (file.open(QFile::WriteOnly | QFile::Text)) {
        QTextStream out(&file);

        auto text_to_save = qobject_cast<QPlainTextEdit>(m_parent->tabWidget->currentWidget());

        out << text_to_save.toPlainText();

//        textEdit->toPlainText();
        if (!file.commit()) {
            errorMessage = (QString("Cannot write file %1:\n%2.").arg(QDir::toNativeSeparators(fileName), file.errorString()));
        }
    } else {
        errorMessage = (QString("Cannot open file %1 for writing:\n%2.").arg(QDir::toNativeSeparators(fileName), file.errorString()));
    }
    QGuiApplication::restoreOverrideCursor();

    if (!errorMessage.isEmpty()) {
        const QMessageBox::StandardButton ret = QMessageBox::warning(this, "Application", errorMessage);
        return false;
    }

//    setCurrentFile(fileName);
    m_parent->statusbar->showMessage("File saved", 2000);
    return true;
}
*/

void FileManager::close_file() {

}
