#ifndef UTEXT_CODEEDITOR_H
#define UTEXT_CODEEDITOR_H


#include <QPlainTextEdit>
#include <QObject>
#include <QMimeData>
#include "syntaxstyle.h"
#include "syntaxhighlightercxx.h"

QT_BEGIN_NAMESPACE
namespace Ui {
    class MainWindow;
}
QT_END_NAMESPACE


class CodeEditor : public QPlainTextEdit
{
    Q_OBJECT

public:
    CodeEditor(Ui::MainWindow *ui_parent, QWidget *parent, SyntaxStyle* syntaxStyle);
    ~CodeEditor();

    void lineNumberAreaPaintEvent(QPaintEvent *event);
    int lineNumberAreaWidth();
    void setSyntaxStyle(SyntaxStyle* style);
    void setHighlighter(StyleSyntaxHighlighter* highlighter);

protected:
    void resizeEvent(QResizeEvent *event) override;
    void insertFromMimeData(const QMimeData* source) override;
    void keyPressEvent(QKeyEvent* e) override;
private slots:
    void updateLineNumberAreaWidth(int newBlockCount);
    void highlightCurrentLine();
    void updateLineNumberArea(const QRect &rect, int dy);
    void updateStyle();
    void updateExtraSelection();
    void initFont();
    QChar charUnderCursor(int offset = 0) const;
    int getIndentationSpaces();
    void setTabSize(int size);

private:
    StyleSyntaxHighlighter* m_highlighter = nullptr;
    SyntaxStyle* m_syntaxStyle = nullptr;
    QWidget *lineNumberArea;
    Ui::MainWindow *m_main_widget;
    QString m_tabReplace{4, ' '};
};

#endif //UTEXT_CODEEDITOR_H
