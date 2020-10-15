#ifndef UTEXT_CODEEDITOR_H
#define UTEXT_CODEEDITOR_H


#include <QPlainTextEdit>
#include <QObject>

QT_BEGIN_NAMESPACE
namespace Ui {
    class MainWindow;
}
QT_END_NAMESPACE


class CodeEditor : public QPlainTextEdit
{
    Q_OBJECT

public:
    CodeEditor(Ui::MainWindow *ui_parent, QWidget *parent);

    void lineNumberAreaPaintEvent(QPaintEvent *event);
    int lineNumberAreaWidth();

protected:
    void resizeEvent(QResizeEvent *event) override;

private slots:
    void updateLineNumberAreaWidth(int newBlockCount);
    void highlightCurrentLine();
    void updateLineNumberArea(const QRect &rect, int dy);

private:
    QWidget *lineNumberArea;
    Ui::MainWindow *m_main_widget;
};

#endif //UTEXT_CODEEDITOR_H
