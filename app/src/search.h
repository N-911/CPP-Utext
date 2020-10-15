#ifndef SEARCH_H
#define SEARCH_H

#include <QSyntaxHighlighter>
#include <QRegularExpression>

class Search : public QSyntaxHighlighter
{
    Q_OBJECT
    using HLClass = QSyntaxHighlighter;
public:
    explicit Search(QTextDocument* parent = nullptr);
    void searchText(const QString& text);
    void setTextDocument(QTextDocument *parent);

protected:
    virtual void highlightBlock(const QString &text) override;

private:
    QRegularExpression m_pattern;
    QTextCharFormat m_format;
};

#endif // SEARCH_H
