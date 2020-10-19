#ifndef SEARCH_H
#define SEARCH_H

#include <QSyntaxHighlighter>
#include <QRegularExpression>
#include <QPlainTextEdit>


class Search : public QSyntaxHighlighter
{
    Q_OBJECT
    using HLClass = QSyntaxHighlighter;
public:
    explicit Search(QPlainTextEdit *parent = nullptr);
    virtual ~Search() = default;
    bool searchText(const QString& text, bool reverse = false, bool casesens = false, bool words = false);
    void setTextDocument(QPlainTextEdit *new_parent);
    void replaceAll(const QString &text, const QString &find);
    void replace(const QString &text);

protected:
    void highlightBlock(const QString &text) override;

private:
    QString m_current_key{""};
    QTextCursor m_currentCursor;
    QPlainTextEdit *m_parent = nullptr;
    QRegularExpression m_pattern;
    QTextCharFormat m_format;
};

#endif // SEARCH_H
