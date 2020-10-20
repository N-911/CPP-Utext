#include "codeeditor.h"
#include "linenumberarea.h"
#include <QPainter>
#include <QTextBlock>
#include "ui_mainwindow.h"

static QVector<QPair<QString, QString>> parentheses = {
        {"(", ")"},
        {"{", "}"},
        {"[", "]"},
        {"\"", "\""},
        {"'", "'"}
};

CodeEditor::CodeEditor(Ui::MainWindow *ui_parent, QWidget *parent, SyntaxStyle* syntaxStyle)
                    : QPlainTextEdit(parent),
                    m_highlighter(new SyntaxHiglighterCXX),
                    m_syntaxStyle(syntaxStyle),
                    lineNumberArea(nullptr),
                    m_main_widget(ui_parent) {
    lineNumberArea = new LineNumberArea(this);

//    CodeEditor->setStyleSheet("color: white; background-color: blue;");

    connect(this, &CodeEditor::blockCountChanged, this, &CodeEditor::updateLineNumberAreaWidth);
    connect(this, &CodeEditor::updateRequest, this, &CodeEditor::updateLineNumberArea);
    connect(this, &CodeEditor::cursorPositionChanged, this, &CodeEditor::highlightCurrentLine);

    connect(this, SIGNAL(m_main_widget->actionCopy), this, SLOT(CodeEditor::copy_new));
    connect(this, SIGNAL(m_main_widget->actionPaste), this, SLOT(CodeEditor::paste_new));
    connect(this, SIGNAL(m_main_widget->actionCut), this, SLOT(CodeEditor::cut_new));

    updateLineNumberAreaWidth(0);
    highlightCurrentLine();
    ui_parent->tabWidget->setFocus();
    initFont();
    this->setTabStopDistance(this->fontMetrics().horizontalAdvance(' ') * 4);
}

int CodeEditor::lineNumberAreaWidth()
{
    int digits = 1;
    int max = qMax(1, blockCount());
    while (max >= 10) {
        max /= 10;
        ++digits;
    }
    int space = 3 + fontMetrics().horizontalAdvance(QLatin1Char('9')) * digits;

    return space;
}

void CodeEditor::updateLineNumberAreaWidth(int /* newBlockCount */)
{
    setViewportMargins(lineNumberAreaWidth(), 0, 0, 0);
}

void CodeEditor::updateLineNumberArea(const QRect &rect, int dy)
{
    if (dy)
        lineNumberArea->scroll(0, dy);
    else
        lineNumberArea->update(0, rect.y(), lineNumberArea->width(), rect.height());

    if (rect.contains(viewport()->rect()))
        updateLineNumberAreaWidth(0);
}

void CodeEditor::resizeEvent(QResizeEvent *e)
{
    QPlainTextEdit::resizeEvent(e);

    QRect cr = contentsRect();
    lineNumberArea->setGeometry(QRect(cr.left(), cr.top(), lineNumberAreaWidth(), cr.height()));
}

void CodeEditor::highlightCurrentLine()
{
    QList<QTextEdit::ExtraSelection> extraSelections;

    if (!isReadOnly()) {
        QTextEdit::ExtraSelection selection{};

        selection.format = m_syntaxStyle->getFormat("CurrentLine");
        selection.format.setForeground(QBrush());
        selection.format.setProperty(QTextFormat::FullWidthSelection, true);
        selection.cursor = textCursor();
        selection.cursor.clearSelection();
//        QColor lineColor = QColor( 72, 108, 241).lighter(150);

//        selection.format.setBackground(lineColor);
//        selection.format.setProperty(QTextFormat::FullWidthSelection, true);
//        selection.cursor = textCursor();
//        selection.cursor.clearSelection();

        extraSelections.append(selection);
    }

    setExtraSelections(extraSelections);
}

void CodeEditor::lineNumberAreaPaintEvent(QPaintEvent *event)
{
    QPainter painter(lineNumberArea);
    painter.fillRect(event->rect(), Qt::lightGray);

    QTextBlock block = firstVisibleBlock();
    int blockNumber = block.blockNumber();
    int top = qRound(blockBoundingGeometry(block).translated(contentOffset()).top());
    int bottom = top + qRound(blockBoundingRect(block).height());

    while (block.isValid() && top <= event->rect().bottom()) {
        if (block.isVisible() && bottom >= event->rect().top()) {
            QString number = QString::number(blockNumber + 1);
            painter.setPen(Qt::black);
            painter.drawText(0, top, lineNumberArea->width(), fontMetrics().height(),
                             Qt::AlignRight, number);
        }

        block = block.next();
        top = bottom;
        bottom = top + qRound(blockBoundingRect(block).height());
        ++blockNumber;
    }
}

void CodeEditor::insertFromMimeData(const QMimeData *source) {
    insertPlainText(source->text());
}

void CodeEditor::setHighlighter(StyleSyntaxHighlighter* highlighter)
{
    if (m_highlighter)
    {
        m_highlighter->setDocument(nullptr);
    }

    m_highlighter = highlighter;

    if (m_highlighter)
    {
        m_highlighter->setSyntaxStyle(m_syntaxStyle);
        m_highlighter->setDocument(document());
    }
}

void CodeEditor::setSyntaxStyle(SyntaxStyle* style)
{
    m_syntaxStyle = style;

    if (m_highlighter)
    {
        m_highlighter->setSyntaxStyle(m_syntaxStyle);
    }

    updateStyle();
}

void CodeEditor::updateStyle()
{
    if (m_highlighter)
    {
        m_highlighter->rehighlight();
    }

    if (m_syntaxStyle)
    {
        auto currentPalette = palette();

        currentPalette.setColor(
                QPalette::ColorRole::Text,
                m_syntaxStyle->getFormat("Text").foreground().color()
        );

        // Setting common background
        currentPalette.setColor(
                QPalette::Base,
                m_syntaxStyle->getFormat("Text").background().color()
        );

        // Setting selection color
        currentPalette.setColor(
                QPalette::Highlight,
                m_syntaxStyle->getFormat("Selection").background().color()
        );

        setPalette(currentPalette);
    }
    updateExtraSelection();
}

void CodeEditor::updateExtraSelection()
{
    QList<QTextEdit::ExtraSelection> extra;

    highlightCurrentLine();
//    highlightParenthesis(extra);

    setExtraSelections(extra);
}

CodeEditor::~CodeEditor() {
    delete m_highlighter;
//    m_syntaxStyle;
}

void CodeEditor::initFont()
{
    auto fnt = QFontDatabase::systemFont(QFontDatabase::FixedFont);
    fnt.setFixedPitch(true);
    fnt.setPointSize(10);

    setFont(fnt);
}
#include "iostream"
void CodeEditor::keyPressEvent(QKeyEvent* e) {
    const int defaultIndent = tabStopDistance() / fontMetrics().averageCharWidth();
//    auto completerSkip = proceedCompleterBegin(e);

//    if (!completerSkip) {
        if (e->key() == Qt::Key_Tab &&
            e->modifiers() == Qt::NoModifier) {
            insertPlainText(m_tabReplace);
            return;
        }

    // Auto indentation
    int indentationLevel = getIndentationSpaces();

    int tabCounts = indentationLevel * fontMetrics().averageCharWidth() / tabStopDistance();

    if (e->key() == Qt::Key_C && e->modifiers() == Qt::ControlModifier) {
        std::cerr << "Cmd + C" << std::endl;

//        auto cursor = this->textCursor();
//        cursor.movePosition(QTextCursor::Start);
//        cursor.movePosition(QTextCursor::Down, QTextCursor::MoveAnchor);
//        cursor.select(QTextCursor::LineUnderCursor);
//        this->copy();
    }

    if ((e->key() == Qt::Key_Return || e->key() == Qt::Key_Enter) &&
        charUnderCursor() == '}' && charUnderCursor(-1) == '{') {
        int charsBack = 0;
        insertPlainText("\n");

        if (/*m_replaceTab*/true)
            insertPlainText(QString(indentationLevel + defaultIndent, ' '));
        else
            insertPlainText(QString(tabCounts + 1, '\t'));

        insertPlainText("\n");
        charsBack++;

        if (/*m_replaceTab*/true) {
            insertPlainText(QString(indentationLevel, ' '));
            charsBack += indentationLevel;
        } else {
            insertPlainText(QString(tabCounts, '\t'));
            charsBack += tabCounts;
        }

        while (charsBack--) {
            moveCursor(QTextCursor::MoveOperation::Left);
        }
        return;
    }
    if (e->key() == Qt::Key_Backtab) {
        indentationLevel = std::min(indentationLevel, m_tabReplace.size());
        auto cursor = textCursor();

        cursor.movePosition(QTextCursor::MoveOperation::StartOfLine);
        cursor.movePosition(QTextCursor::MoveOperation::Right,
                            QTextCursor::MoveMode::KeepAnchor, indentationLevel);

        cursor.removeSelectedText();
        return;
    }

    QPlainTextEdit::keyPressEvent(e);

    if ((e->key() == Qt::Key_Return || e->key() == Qt::Key_Enter)) {
        if (true) // ************
            insertPlainText(QString(indentationLevel, ' '));
        else
            insertPlainText(QString(tabCounts, '\t'));
    }

    if (/*m_autoParentheses*/true) {
        for (auto &&el : parentheses) {
            // Inserting closed brace
            if (el.first == e->text()) {
                insertPlainText(el.second);
                moveCursor(QTextCursor::MoveOperation::Left);
                break;
            }

            // If it's close brace - check parentheses
            if (el.second == e->text()) {
                auto symbol = charUnderCursor();

                if (symbol == el.second) {
                    textCursor().deletePreviousChar();
                    moveCursor(QTextCursor::MoveOperation::Right);
                }
                break;
            }
        }
    }
//}
//    proceedCompleterEnd(e);
}

QChar CodeEditor::charUnderCursor(int offset) const
{
    auto block = textCursor().blockNumber();
    auto index = textCursor().positionInBlock();
    auto text = document()->findBlockByNumber(block).text();

    index += offset;

    if (index < 0 || index >= text.size())
    {
        return {};
    }

    return text[index];
}
int CodeEditor::getIndentationSpaces()
{
    auto blockText = textCursor().block().text();

    int indentationLevel = 0;

    for (auto i = 0; i < blockText.size() && QString("\t ").contains(blockText[i]); ++i)
    {
        if (blockText[i] == ' ')
        {
            indentationLevel++;
        }
        else
        {
            indentationLevel += tabStopDistance() / fontMetrics().averageCharWidth();
        }
    }

    return indentationLevel;
}

void CodeEditor::setTabSize(int size) {
    this->setTabStopDistance(this->fontMetrics().horizontalAdvance(' ') * size);
}

void CodeEditor::copy_new() {
    if (hasFocus())
        QPlainTextEdit::copy();
}

void CodeEditor::paste_new() {
    if (hasFocus())
        QPlainTextEdit::paste();
}

void CodeEditor::cut_new() {
    if (hasFocus())
        QPlainTextEdit::cut();
}
