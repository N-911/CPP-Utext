#ifndef STYLESYNTAXHIGHLIGHTER_H
#define STYLESYNTAXHIGHLIGHTER_H

#include <QSyntaxHighlighter>
#include "syntaxstyle.h"

class StyleSyntaxHighlighter : public QSyntaxHighlighter
{
public:
    explicit StyleSyntaxHighlighter(QTextDocument* document = nullptr);
//    StyleSyntaxHighlighter(const StyleSyntaxHighlighter&) = delete;
//    StyleSyntaxHighlighter& operator=(const StyleSyntaxHighlighter&) = delete;
    void setSyntaxStyle(SyntaxStyle* style);
    SyntaxStyle* syntaxStyle() const;

private:
    SyntaxStyle* m_syntaxStyle;
};

#endif // STYLESYNTAXHIGHLIGHTER_H