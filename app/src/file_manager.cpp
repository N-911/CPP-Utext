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
#include <QInputDialog>
#include "tabmenager.h"

FileManager::FileManager(Ui::MainWindow *parent) : m_file_widget(parent),
            m_tabManager(new TabManager(m_file_widget->tabWidget, parent)) {}

FileManager::~FileManager() {
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
//        const QMessageBox::StandardButton ret = QMessageBox::warning(0, "Application", errorMessage);
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

    auto fullFileName = m_file_widget->tabWidget->widget(index)->windowFilePath();
    m_open_files.erase(fullFileName);
    m_history_files.push_front(fullFileName);
    qInfo(logInfo()) << QString("close file " + fullFileName);
}



void FileManager::closeFile(const QString &fullFileName) {
    auto index = m_open_files[fullFileName];
    m_tabManager->closeTab(index);
    m_open_files.erase(fullFileName);
    qInfo(logInfo()) << QString("close file " + fullFileName);
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
    // делаем новое окно текущим
    auto index = m_tabManager->addNewTab();
    m_tabManager->setCurrentIndex(index);
    qDebug(logDebug()) << QString("newFile add %1 tab idex").arg(index);
}

bool FileManager::deleteFile(const QString &fullFileName) {
    if (this->isOpen(fullFileName)) {
        this->closeFile(fullFileName);
        qDebug(logDebug()) << fullFileName << " is open";
    }
    QFile file;
    file.moveToTrash(fullFileName);
    return true;
}

bool FileManager::save() {
    // проверяєм привязан ли Widget to Path
    QString fullFileName = m_tabManager->getCurrentWidget()->windowFilePath();
    qInfo(logInfo()) << QString("save file " + fullFileName);

    if (fullFileName.isEmpty()) {
        return saveAs();
    } else {
        return saveFile(fullFileName);
    }
    m_file_widget->statusbar->showMessage("save", 2000);
}

bool FileManager::saveAs() {
    if (m_tabManager->getCountTab() == 0) {
        return true;
    }
    QFileDialog dialog(0);
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

}

bool FileManager::isOpen(const QString &fullFileName) {
    if (m_open_files.count(fullFileName) == 0) {
        return false;
    }
    return true;
}

bool FileManager::fileRename(const QString &fullFileName) {
    bool ok;
    QFile current_file(fullFileName);

    QString new_name = QInputDialog::getText(0,"Rename file",
                                             ("Enter the new path for the file."),
                                             QLineEdit::Normal,
                                             QFileInfo(fullFileName).fileName(),
                                             &ok);
    if (ok) {
        QString new_file_path = QString(QFileInfo(fullFileName).absolutePath() + "/" + new_name);
        current_file.rename(fullFileName, new_file_path);
        if (m_open_files.count(fullFileName) != 0) {
            auto index = m_open_files[fullFileName];
            m_open_files.erase(fullFileName);
            m_tabManager->setTabTitle(index, new_name);
            m_tabManager->getWidget(index)->setWindowFilePath(new_file_path);  // associated path with widget
            qDebug(logDebug()) << QString("rename file %1 to %2").arg(fullFileName).arg(new_file_path);
        }

    }
    return false;
}

TabManager *FileManager::getTabManager() const {
    return m_tabManager;
}


