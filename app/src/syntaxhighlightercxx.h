#ifndef SYNTAXHIGHLIGHTER_H
#define SYNTAXHIGHLIGHTER_H

#include "stylesyntaxhighlighter.h"
#include "highlightrule.h"
#include <QRegularExpression>
#include <QVector>

class SyntaxStyle;

class SyntaxHiglighterCXX : public StyleSyntaxHighlighter
{
Q_OBJECT
public:
    explicit SyntaxHiglighterCXX(QTextDocument* document=nullptr);
protected:
    void highlightBlock(const QString& text) override;
private:
    QVector<QHighlightRule> m_highlightRules;
    QRegularExpression m_includePattern;
    QRegularExpression m_functionPattern;
    QRegularExpression m_defTypePattern;
    QRegularExpression m_commentStartPattern;
    QRegularExpression m_commentEndPattern;
};

#endif // SYNTAXHIGHLIGHTER_H
