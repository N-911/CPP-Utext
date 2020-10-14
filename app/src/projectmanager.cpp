#include "projectmanager.h"
#include "loggingcategories.h"
#include <QDir>

ProjectManager::ProjectManager(Ui::MainWindow *parent) : m_project_widget(parent) { }

void ProjectManager::add_project_folder(const QString &dirName) {
    qDebug(logDebug()) << "add new project " << dirName;

    if (auto it = find(m_projects.begin(), m_projects.end(), dirName);  it != m_projects.end()) {
        qInfo(logInfo()) << QString("project %1 was already been open ").arg(QDir(dirName).dirName());
        return;
    }
    m_projects.insert(m_projects.begin() + m_projects.size(), dirName);
    qInfo(logInfo()) << "m_projects size = " << m_projects.size();
}

void ProjectManager::close_project_folder(QModelIndex &index) {
    // get dirname from index
    QString dirName("find_dir");
    auto it = find(m_projects.begin(), m_projects.end(), dirName);
    m_projects.erase(it);
}
