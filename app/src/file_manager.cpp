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


FileManager::FileManager(Ui::MainWindow *parent) : m_file_widget(parent) {
}

void FileManager::loadFile(const QString &fullFileName) {
    // если файл уже открыт
    if (m_open_files.count(fullFileName) != 0) {
        qInfo(logInfo()) << QString("file %1 was already been open ").arg(QFileInfo(fullFileName).fileName());
        m_file_widget->tabWidget->setCurrentIndex(m_open_files[fullFileName]);  // делаем окно текущим
        return;
    }

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
    auto *text_edit_file = new QPlainTextEdit();
    text_edit_file->setPlainText(in.readAll());
    auto index = m_file_widget->tabWidget->addTab(text_edit_file, strippedName(fullFileName));
    m_file_widget->tabWidget->setCurrentIndex(index);  // делаем новое окно текущим
    m_file_widget->tabWidget->widget(index)->setWindowFilePath(fullFileName);  // associated path with widget
    m_open_files[fullFileName] = index;
    m_files.insert(fullFileName);
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
        auto *text_to_save =  qobject_cast<QPlainTextEdit *>(m_file_widget->tabWidget->currentWidget());
        out << text_to_save->toPlainText();
        if (!file.commit()) {
            errorMessage = (QString("Cannot write file %1:\n%2.").arg(QDir::toNativeSeparators(fileName),
                                                                      file.errorString()));
        }
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
    m_file_widget->tabWidget->setTabText(m_file_widget->tabWidget->currentIndex(),
                                         strippedName(fileName)); // set tabName to new fileName
    m_file_widget->tabWidget->currentWidget()->setWindowFilePath(fileName);  // associated path with widget
    qInfo(logInfo()) << QString("File %1 saved").arg(fileName);
    m_file_widget->statusbar->showMessage("File " + fileName + " saved", 2000);
    return true;
}


void FileManager::closeFile(int index) {
    isChanged();

    auto key = m_file_widget->tabWidget->widget(index)->windowFilePath();
    m_open_files.erase(key);
    m_files.erase(key);
    qDebug(logDebug()) << QString("close file + key");
}

QString FileManager::strippedName(const QString &fullFileName) {
    return QFileInfo(fullFileName).fileName();
}

bool FileManager::isChanged() {
    auto *text_edit_file = qobject_cast<QPlainTextEdit *>(m_file_widget->tabWidget->currentWidget());
    if (!text_edit_file->document()->isModified()) {
        return true;
    }
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

    auto *new_file = new QPlainTextEdit();
    // делаем новое окно текущим
    auto index = m_file_widget->tabWidget->addTab(new_file, "untitled");
    m_file_widget->tabWidget->setCurrentIndex(index);
    qDebug(logDebug()) << QString("newFile add %1 tab idex").arg(index);
}

bool FileManager::save() {
    m_file_widget->statusbar->showMessage("save", 2000);
    // проверяєм привязан ли Widget to Path
    QString fullFileName = m_file_widget->tabWidget->currentWidget()->windowFilePath();
    qInfo(logInfo()) << QString("save file " + fullFileName);

    if (fullFileName.isEmpty()) {
        return saveAs();
    } else {
        return saveFile(fullFileName);
    }
}

bool FileManager::saveAs() {
    if (m_file_widget->tabWidget->count() == 0) {
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
    int temp = m_file_widget->tabWidget->currentIndex();

    for (int i = 1; i < m_file_widget->tabWidget->count(); ++i) {
        m_file_widget->tabWidget->setCurrentIndex(i);
        qDebug(logDebug()) << QString("save All %1 tab index").arg(i);
        isChanged();
    }
    m_file_widget->tabWidget->setCurrentIndex(temp);
    return true;
}












////////////============================================================================

//void FileManager::setCurrentFile(QWidget *current_file) {
//    m_current_file = current_file;
//}




//void MainWindow::on_actionClose_Tab_triggered()
//{
////    std::cout <<
//    auto *curr_tab = m_file_widget->tabWidget->currentWidget();
//    std::cout << "cuttenr tab =" <<
//              m_file_widget->tabWidget->tabText(m_file_widget->tabWidget->currentIndex()).toStdString() << std::endl;
//    closeFile(m_file_widget->tabWidget->currentIndex());
//}