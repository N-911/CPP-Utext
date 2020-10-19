#include "search.h"
#include <QTextDocument>
#include <algorithm>

Search::Search(QPlainTextEdit *parent) : HLClass(parent->document()), m_parent(parent)
{
    if (m_parent)
        setDocument(parent->document());
    m_format.setBackground(Qt::blue);
}

bool Search::searchText(const QString &text, bool reverse, bool casesens, bool words)
{
    bool isDone;
    QTextDocument::FindFlags flag;
    if (reverse) flag |= QTextDocument::FindBackward;
    if (casesens) flag |= QTextDocument::FindCaseSensitively;
    if (words) flag |= QTextDocument::FindWholeWords;

    QTextCursor cursor = m_parent->textCursor();
    QTextCursor cursorSaved = cursor;

    m_currentCursor = m_parent->document()->find(text, cursor, flag);

    if (/*m_currentCursor.isNull() && */!m_parent->find(text, flag))
    {
//        m_currentCursor.movePosition(reverse ? QTextCursor::End : QTextCursor::Start);
        cursor.movePosition(reverse ? QTextCursor::End : QTextCursor::Start);
        m_parent->setTextCursor(cursor);
        m_currentCursor = m_parent->document()->find(text, cursor, flag);
        isDone = m_parent->find(text, flag);
    }
    else
        isDone = true;
    m_pattern = QRegularExpression(text);
    QRegularExpression::PatternOption fl{};
    if (casesens)  fl = QRegularExpression::CaseInsensitiveOption;
    m_pattern.setPatternOptions(fl);

    rehighlight();
    return isDone;
//
//    QTextDocument::FindFlags flag;
//    if (reverse) flag |= QTextDocument::FindBackward;
//    if (casesens) flag |= QTextDocument::FindCaseSensitively;
//    if (words) flag |= QTextDocument::FindWholeWords;
//
//    QTextCursor cursor = m_parent->textCursor();
//    QTextCursor cursorSaved = cursor;
//
//
//    if (!m_parent->find(text, flag))
//    {
//        cursor.movePosition(reverse ? QTextCursor::End : QTextCursor::Start);
//        m_parent->setTextCursor(cursor);
//        m_parent->find(text, flag);
//    }
//    m_pattern = QRegularExpression(text);
//    QRegularExpression::PatternOption fl;
//    if (casesens)  fl = QRegularExpression::CaseInsensitiveOption;
//    m_pattern.setPatternOptions(fl);
//
//    rehighlight();
}
void Search::highlightBlock(const QString &text)
{
    QRegularExpressionMatchIterator matchIterator = m_pattern.globalMatch(text, 0, QRegularExpression::NormalMatch);
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

void Search::replace(const QString &text) {
    m_currentCursor.beginEditBlock();
    if (m_currentCursor.isNull())
        return;
    m_currentCursor.insertText(text);
    m_currentCursor.endEditBlock();
}

void Search::replaceAll(const QString &text, const QString &find) {
    QTextCursor cursor = m_parent->textCursor();
    QTextCursor cursorSaved = cursor;
    for (; searchText(find);)
        replace(text);
}
