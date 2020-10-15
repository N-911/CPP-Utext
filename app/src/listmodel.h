#ifndef UTEXT_LISTMODEL_H
#define UTEXT_LISTMODEL_H

#include <QAbstractListModel>
#include <QFileSystemModel>


class Listmodel : public QAbstractListModel {
    Q_OBJECT

public:
    Listmodel(const QString &header, QObject *parent = nullptr) : QAbstractListModel(parent), m_header(header) { }

//    ~Listmodel();

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;

    void add_project_folder(const QString &dirName);

private:
    QString m_header;
//    QList<QFileSystemModel> m_projects_list;
    QVector<QString> m_name_projects;
};


#endif //UTEXT_LISTMODEL_H
