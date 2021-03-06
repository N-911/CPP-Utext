#include "tabmenager.h"
#include "tabwelcome.h"
#include <iostream>
#include <QPlainTextEdit>
#include <memory>
#include "loggingcategories.h"
#include "codeeditor.h"
#include "ui_mainwindow.h"

TabManager::TabManager(QTabWidget *parent, Ui::MainWindow *ui_parent) :
                                        m_parent(parent), m_main_widget(ui_parent) {
//    m_parent->addTab(new TabWelcome(m_parent), "Welcome!");
}

TabManager::~TabManager() {
    for (auto &w : m_tablist) {
        delete w;
        w = nullptr;
    }
    m_tablist.clear();
    qInfo(logInfo()) << "~TabManager";
}

void TabManager::closeTab(int index) {
    auto wd = m_parent->widget(index);
    auto id = this->getTabListIndex(wd);
    if (id != -1) {
        delete m_tablist[id];
        m_tablist.remove(id);
    }
    m_parent->removeTab(index);
}

int TabManager::addNewTab(QWidget *wd, const QString &nameTab, const QString &content) {
    int index;
    if (wd) {
        index = m_parent->addTab(wd, nameTab);
//        setHighlighter(m_highlighter);
        qobject_cast<CodeEditor *>(wd)->setSyntaxStyle(m_style);
    }
    else {
//        auto *tmpPlainText = new QPlainTextEdit(); //// CodeEditor
        auto *tmpPlainText = new CodeEditor(m_main_widget, wd, m_style); //// CodeEditor

        tmpPlainText->setPlainText(content);
        tmpPlainText->setHighlighter(m_highlighter);
        tmpPlainText->setSyntaxStyle(m_style);
        index = m_parent->addTab(tmpPlainText, nameTab);
        m_tablist.push_back(tmpPlainText);
    }
    updateTabs();
    return index;
}

int TabManager::getTabListIndex(QWidget *wd) {
    int id = -1;
    for (int i = 0; i < m_tablist.size(); ++i) {
        if (wd == m_tablist[i]) {
            id = i;
            break;
        }
        id = -1;
    }
    return id;
}

QWidget *TabManager::getWidget(int index)  const{
    return m_parent->widget(index);
}

QWidget *TabManager::getCurrentWidget()  const{
    return m_parent->currentWidget();
}

int TabManager::getCurrentIndex()  const{
    return m_parent->currentIndex();
}

void TabManager::setCurrentIndex(int index) {
    m_parent->setCurrentIndex(index);
}

void TabManager::setTabTitle(int index, const QString &title) {
    m_parent->setTabText(index, title);
}

int TabManager::getCountTab() const {
    return m_parent->count();
}

void TabManager::setSyntaxStyle(SyntaxStyle *style) {
    m_style = style;
    for (int i = 0; i < m_parent->count(); ++i) {
        qobject_cast<CodeEditor *>(m_parent->widget(i))->setSyntaxStyle(m_style);
    }
}

void TabManager::setHighlighter(StyleSyntaxHighlighter *highlighter) {
    m_highlighter = highlighter;
    for (int i = 0; i < m_parent->count(); ++i) {
        qobject_cast<CodeEditor *>(m_parent->widget(i))->setHighlighter(m_highlighter);
    }
}

void TabManager::updateTabs() {
    for (int i = 0; i < m_parent->count(); ++i) {
        std::cout << i << std::endl;
        qobject_cast<CodeEditor *>(m_parent->widget(i))->setSyntaxStyle(SyntaxStyle::darkStyle());
        qobject_cast<CodeEditor *>(m_parent->widget(i))->setHighlighter(new SyntaxHiglighterCXX);
    }
}


