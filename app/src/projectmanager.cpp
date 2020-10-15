#include "projectmanager.h"
#include "loggingcategories.h"
#include <QDir>
#include <QFileSystemModel>
#include "listmodel.h"

ProjectManager::ProjectManager(Ui::MainWindow *parent) : m_project_widget(parent) { }

void ProjectManager::add_project_folder(const QString &dirName) {
    qDebug(logDebug()) << "add new project " << dirName;

    if (m_projects.count(dirName) != 0) {
        qInfo(logInfo()) << QString("project %1 was already been open ").arg(QDir(dirName).dirName());
        return;
    }
    QFileSystemModel *tmp = new QFileSystemModel();
    tmp->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs);
    tmp->setRootPath(dirName);
    m_projects[dirName] = tmp;
    qInfo(logInfo()) << "m_projects size = " << m_projects.size();
}

void ProjectManager::close_project_folder(QModelIndex &index) {
    // get dirname from index
    QString dirName("find_dir");
//    auto it = m_projects.indexOf(dirName, 0);
//    m_projects.remove(it);
}

QMap<QString, QFileSystemModel *> ProjectManager::getProjects() const {
    return m_projects;
}
