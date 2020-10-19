#pragma once
#include <QObject>
#include <QString>
#include <QMap>

class QIODevice;

class Language : public QObject
{
    Q_OBJECT

public:
    explicit Language(QIODevice* device=nullptr, QObject* parent=nullptr);
    bool load(QIODevice* device);
    QStringList keys();
    QStringList names(const QString& key);
    bool isLoaded() const;

private:

    bool m_loaded;

    QMap<QString, QStringList> m_list;

};

