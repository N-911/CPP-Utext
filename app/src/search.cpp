#include "search.h"

Search::Search(QTextDocument *parent) : HLClass(parent)
{
    m_format.setBackground(Qt::blue);
}

void Search::searchText(const QString &text)
{
    m_pattern = QRegularExpression(text);
    rehighlight();
}

void Search::highlightBlock(const QString &text)
{
    QRegularExpressionMatchIterator matchIterator = m_pattern.globalMatch(text);
    while (matchIterator.hasNext())
    {
        QRegularExpressionMatch match = matchIterator.next();
        setFormat(match.capturedStart(), match.capturedLength(), m_format);
    }
}

void Search::setTextDocument(QTextDocument *document) {
    setDocument(document);
}
