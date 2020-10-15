#include "search.h"
#include <QTextDocument>
#include <algorithm>

Search::Search(QPlainTextEdit *parent) : HLClass(parent->document()), m_parent(parent)
{
    if (m_parent)
        setDocument(parent->document());
    m_format.setBackground(Qt::blue);
}



void Search::searchText(const QString &text)
{
    auto document = m_parent->document();
    QTextCursor newCursor(document);

    while (!newCursor.isNull() && !newCursor.atEnd()) {
        newCursor = document->find(text, newCursor);
        if (!newCursor.isNull()) {
//            newCursor;
            newCursor.mergeCharFormat(m_format);
        }
    }
    QTextDocument::FindFlags flag;

    bool reverse = false;
    bool casesens = false;
    bool words = false;
    if (reverse) flag |= QTextDocument::FindBackward;
    if (casesens) flag |= QTextDocument::FindCaseSensitively;
    if (words) flag |= QTextDocument::FindWholeWords;

    QTextCursor cursor = m_parent->textCursor();
    QTextCursor cursorSaved = cursor;

    if (!m_parent->find(text, flag))
    {
        cursor.movePosition(reverse ? QTextCursor::End:QTextCursor::Start);
        m_parent->setTextCursor(cursor);
    }
    m_pattern = QRegularExpression(text);
    QRegularExpression::PatternOption fl;
    fl = QRegularExpression::CaseInsensitiveOption;
    fl = QRegularExpression::DontCaptureOption;
    m_pattern.setPatternOptions(fl);

    rehighlight();
}

void Search::highlightBlock(const QString &text)
{
    QRegularExpressionMatchIterator matchIterator = m_pattern.globalMatch(text, 0, QRegularExpression::NoMatch);
    while (matchIterator.hasNext())
    {
        QRegularExpressionMatch match = matchIterator.next();
        setFormat(match.capturedStart(), match.capturedLength(), m_format);
    }
}

void Search::setTextDocument(QPlainTextEdit *new_parent) {
    m_parent = new_parent;
    setDocument(m_parent->document());
}
