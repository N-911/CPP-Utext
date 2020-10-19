#ifndef SYNTAXSTYLE_H
#define SYNTAXSTYLE_H

#include <QObject>
#include <QMap>
#include <QString>
#include <QTextCharFormat>

class SyntaxStyle : public QObject
{
    Q_OBJECT
public:
    explicit SyntaxStyle(QObject* parent = nullptr);
    static SyntaxStyle* defaultStyle();
    static SyntaxStyle* darkStyle();
    bool load(const QString &fl);
    QString name() const;
    bool isLoaded() const;
    QTextCharFormat getFormat(const QString &name) const;

private:

    QString m_name;
    QMap<QString, QTextCharFormat> m_data;
    bool m_loaded;
};

#endif // SYNTAXSTYLE_H