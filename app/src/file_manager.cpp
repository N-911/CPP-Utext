#include "ui_mainwindow.h"
#include "file_manager.h"
#include "loggingcategories.h"

#include <QDir>
#include <QFile>
#include <QSaveFile>
#include <QFileInfo>
#include <QMessageBox>
#include <QTextStream>
#include <QPlainTextEdit>
#include <iostream>
#include <QFileDialog>
#include "tabmenager.h"

FileManager::FileManager(Ui::MainWindow *parent) : m_file_widget(parent),
            m_tabManager(new TabManager(m_file_widget->tabWidget, parent)) {}

FileManager::~FileManager() {
//    qInfo(logInfo()) << "~FileManager";
    delete m_tabManager;
}

void FileManager::loadFile(const QString &fullFileName) {
    // если файл уже открыт
    if (m_open_files.count(fullFileName) != 0) {
        qInfo(logInfo()) << QString("file %1 was already been open ").arg(QFileInfo(fullFileName).fileName());
        m_tabManager->setCurrentIndex(m_open_files[fullFileName]);  // делаем окно текущим
        return;
    }
    // новий файл
    QFile file(fullFileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QString warning = QString("Cannot read file %1:\n%2.").arg(QDir::toNativeSeparators(fullFileName),
                                                 file.errorString());
      QMessageBox::warning (0, "Application", warning);  // show warning
      qWarning(logWarning()) << warning;  // log warning
      return;
    }

    QTextStream in(&file);
#ifndef QT_NO_CURSOR
    QGuiApplication::setOverrideCursor(Qt::WaitCursor);
#endif
    auto index = m_tabManager->addNewTab(nullptr, strippedName(fullFileName), in.readAll());
    m_tabManager->setCurrentIndex(index);  // делаем новое окно текущим
    m_tabManager->getWidget(index)->setWindowFilePath(fullFileName);  // associated path with widget
    m_open_files[fullFileName] = index;
//    m_files.insert(fullFileName);
//    auto file_in_hisfind(m_history_files.begin(), m_history_files.begin() + 10, fullFileName);
    qInfo(logInfo()) << QString("open file %1").arg(QFileInfo(fullFileName).fileName());

#ifndef QT_NO_CURSOR
    QGuiApplication::restoreOverrideCursor();
#endif
    m_file_widget->statusbar->showMessage(fullFileName + " loaded", 2000);
    file.close();
}

bool FileManager::saveFile(const QString &fileName) {
    QString errorMessage;
    QGuiApplication::setOverrideCursor(Qt::WaitCursor);
    QSaveFile file(fileName);

    if (file.open(QFile::WriteOnly | QFile::Text)) {
        QTextStream out(&file);
        auto *text_to_save =  qobject_cast<QPlainTextEdit *>(m_tabManager->getCurrentWidget());
        out << text_to_save->toPlainText();
        if (!file.commit()) {
            errorMessage = (QString("Cannot write file %1:\n%2.").arg(QDir::toNativeSeparators(fileName),
                                                                      file.errorString()));
        }
        text_to_save->document()->setModified(false);
    } else {
        errorMessage = (QString("Cannot open file %1 for writing:\n%2.").arg(QDir::toNativeSeparators(fileName),
                                                                             file.errorString()));
    }
    QGuiApplication::restoreOverrideCursor();

    if (!errorMessage.isEmpty()) {
        const QMessageBox::StandardButton ret = QMessageBox::warning(0, "Application", errorMessage);
        qWarning(logWarning()) << errorMessage;
        return false;
    }
    m_tabManager->setTabTitle(m_tabManager->getCurrentIndex(),
                                         strippedName(fileName)); // set tabName to new fileName
    m_tabManager->getCurrentWidget()->setWindowFilePath(fileName);  // associated path with widget
    qInfo(logInfo()) << QString("File %1 saved").arg(fileName);
    m_file_widget->statusbar->showMessage("File " + fileName + " saved", 2000);
    return true;
}


void FileManager::closeFile(int index) {
    isChanged();

    auto fuulfilename = m_file_widget->tabWidget->widget(index)->windowFilePath();
    m_open_files.erase(fuulfilename);
//    m_files.erase(fuulfilename);
    m_history_files.push_front(fuulfilename);
    qDebug(logDebug()) << QString("close file " + fuulfilename);
//=======
//    auto key = m_tabManager->getWidget(index)->windowFilePath();
//    m_open_files.erase(key);
//    m_files.erase(key);
//    qDebug(logDebug()) << QString("close file + key");
//>>>>>>> 20b67a4537ba49cde9f941fa2b64d6572e9e9da3
}

QString FileManager::strippedName(const QString &fullFileName) const {
    return QFileInfo(fullFileName).fileName();
}

bool FileManager::isChanged() {

    auto *text_edit_file = qobject_cast<QPlainTextEdit *>(m_tabManager->getCurrentWidget());
    if (!text_edit_file->document()->isModified()) {
        qDebug(logDebug()) << "isChanged - false";
        return true;
    }
    qDebug(logDebug()) << "isChanged - true";

    const QMessageBox::StandardButton ret
            = QMessageBox::warning(0, QString("Application"),
                                   QString("The document has been modified.\n"
                                      "Do you want to save your changes?"),
                                   QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    switch (ret) {
        case QMessageBox::Save:
            return save();
        case QMessageBox::Cancel:
            return false;
        default:
            break;
    }
    return true;
}

void FileManager::newFile() {
//    m_file_widget->statusbar->showMessage("newFile", 2000);
//    auto new_file = std::make_unique<QPlainTextEdit>();

    // делаем новое окно текущим
    auto index = m_tabManager->addNewTab();
    m_tabManager->setCurrentIndex(index);
    qDebug(logDebug()) << QString("newFile add %1 tab idex").arg(index);
}

bool FileManager::save() {
    m_file_widget->statusbar->showMessage("save", 2000);
    // проверяєм привязан ли Widget to Path
    QString fullFileName = m_tabManager->getCurrentWidget()->windowFilePath();
    qInfo(logInfo()) << QString("save file " + fullFileName);

    if (fullFileName.isEmpty()) {
        return saveAs();
    } else {
        return saveFile(fullFileName);
    }
}

bool FileManager::saveAs() {
    if (m_tabManager->getCountTab() == 0) {
        return true;
    }
    QFileDialog dialog(0);
//    m_file_widget->statusbar->showMessage("saveAs", 2000);
    dialog.setWindowModality(Qt::WindowModal);
    dialog.setAcceptMode(QFileDialog::AcceptSave);

    if (dialog.exec() != QDialog::Accepted)
        return false;
    return saveFile(dialog.selectedFiles().first());

}

bool FileManager::saveAll() {
    int temp = m_tabManager->getCurrentIndex();

    for (int i = 0; i < m_tabManager->getCountTab(); ++i) {
        m_tabManager->setCurrentIndex(i);
        qDebug(logDebug()) << QString("save All %1 tab index").arg(i);
        isChanged();
    }
    m_tabManager->setCurrentIndex(temp);
    return true;
}

void FileManager::update_history_files() {
//    if ()

}

