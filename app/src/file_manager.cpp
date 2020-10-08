#include "file_manager.h"

#include <QDir>
#include <QFile>
#include <QSaveFile>
#include <QFileInfo>
#include <QMessageBox>
#include <QTextStream>
#include <QPlainTextEdit>
#include <iostream>
#include <QFileDialog>

#include "ui_mainwindow.h"


FileManager::FileManager(Ui::MainWindow *parent) : m_file_widget(parent) {
}

void FileManager::loadFile(const QString &fullFileName) {
    // если файл уже открыт
    if (m_load_files.count(fullFileName) != 0) {
        m_file_widget->tabWidget->setCurrentWidget(m_load_files[fullFileName]);  // делаем окно текущим
//        setCurrentFile(m_load_files[fullFileName]);
        return;
    }

    QFile file(fullFileName);

    if (!file.open(QFile::ReadOnly | QFile::Text)) {
      QMessageBox::warning (0, "Application",
                       QString("Cannot read file %1:\n%2.").arg(QDir::toNativeSeparators(fullFileName),
                            file.errorString()));

      m_file_widget->statusbar->showMessage(QString("Cannot read file %1:\n%2.").arg(QDir::toNativeSeparators(fullFileName),
                                                                                     file.errorString()), 2000);
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
    m_load_files[fullFileName] = m_file_widget->tabWidget->widget(index);

#ifndef QT_NO_CURSOR
    QGuiApplication::restoreOverrideCursor();
#endif
//    setCurrentFile(m_file_widget->tabWidget->currentWidget());
    m_file_widget->statusbar->showMessage(fullFileName + " loaded", 2000);
    file.close();
}

bool FileManager::saveFile(const QString &fileName) {
    QString errorMessage;
    QGuiApplication::setOverrideCursor(Qt::WaitCursor);
    QSaveFile file(fileName);

    if (file.open(QFile::WriteOnly | QFile::Text)) {
        QTextStream out(&file);
        auto * text_to_save =  qobject_cast<QPlainTextEdit *>(m_file_widget->tabWidget->currentWidget());
        out << text_to_save->toPlainText();
        if (!file.commit()) {
            errorMessage = (QString("Cannot write file %1:\n%2.").arg(QDir::toNativeSeparators(fileName), file.errorString()));
        }
    } else {
        errorMessage = (QString("Cannot open file %1 for writing:\n%2.").arg(QDir::toNativeSeparators(fileName), file.errorString()));
    }
    QGuiApplication::restoreOverrideCursor();

    if (!errorMessage.isEmpty()) {
        const QMessageBox::StandardButton ret = QMessageBox::warning(0, "Application", errorMessage);
        return false;
    }
    m_load_files[fileName] = m_file_widget->tabWidget->currentWidget();
    // set tabName to new fileName
    m_file_widget->tabWidget->setTabText(m_file_widget->tabWidget->currentIndex(),
                                         strippedName(fileName));
    // associated new filepath with widget
    m_file_widget->tabWidget->currentWidget()->setWindowFilePath(fileName);  // associated path with widget
    m_file_widget->statusbar->showMessage("File " + fileName + " saved", 2000);
    //    setCurrentFile(fileName);
    return true;
}


void FileManager::closeFile(int index) {
    isChanged();

    auto key = m_file_widget->tabWidget->widget(index)->windowFilePath();
    m_load_files.erase(key);

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
//            return saveFile(m_file_widget->tabWidget->tabText(m_file_widget->tabWidget->currentIndex()));
            return save();
        case QMessageBox::Cancel:
            return false;
        default:
            break;
    }
    return true;
}

void FileManager::newFile() {
    m_file_widget->statusbar->showMessage("newFile", 2000);
    auto *new_file = new QPlainTextEdit();

    // делаем новое окно текущим
    auto index = m_file_widget->tabWidget->addTab(new_file, "untitled");
    m_file_widget->tabWidget->setCurrentIndex(index);
}

bool FileManager::save() {
    m_file_widget->statusbar->showMessage("save", 2000);
    // проверяєм привязан ли Widget to Path
    QString fullFileName = m_file_widget->tabWidget->currentWidget()->windowFilePath();

    if (fullFileName.isEmpty()) {
        return saveAs();
    } else {
        return saveFile(fullFileName);
    }
}

bool FileManager::saveAs() {
    QFileDialog dialog(0);
    m_file_widget->statusbar->showMessage("saveAs", 2000);

    dialog.setWindowModality(Qt::WindowModal);
    dialog.setAcceptMode(QFileDialog::AcceptSave);

    if (dialog.exec() != QDialog::Accepted)
        return false;
//    std::cout << "file name to save =" << dialog.selectedFiles().first().toStdString() << std::endl;
    return saveFile(dialog.selectedFiles().first());

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