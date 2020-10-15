#ifndef UTEXT_LISTMODEL_H
#define UTEXT_LISTMODEL_H

#include <QAbstractListModel>
#include <QFileSystemModel>
#include <QTreeView>
#include <QVector>

class ProjectManager;

namespace Ui {
    class MainWindow;
}

class Listmodel : public QAbstractListModel {
    Q_OBJECT

public:
    Listmodel(const QString &header, QWidget *parent = nullptr, Ui::MainWindow *ui = nullptr, const ProjectManager *manager = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;

    void add_project_folder(const QString &dirName);

private:
    QString m_header;
    const ProjectManager *m_manager;
    QList<QFileSystemModel> m_projects_list;
    QVector<QTreeView *> m_project_treeView;
    QVector<QString> m_name_projects;
};


#endif //UTEXT_LISTMODEL_H
