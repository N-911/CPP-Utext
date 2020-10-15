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
    void searchText(const QString& text);
    void setTextDocument(QPlainTextEdit *new_parent);
    void searchAllMatch(const QString& text);

protected:
    void highlightBlock(const QString &text) override;

private:
    QPlainTextEdit *m_parent = nullptr;
    QRegularExpression m_pattern;
    QTextCharFormat m_format;
};

#endif // SEARCH_H
