#include "tabmenager.h"
#include "tabwelcome.h"
#include <iostream>
#include <QPlainTextEdit>
#include <memory>

TabManager::TabManager(QTabWidget *parent) : m_parent(parent) {
    m_parent->addTab(new TabWelcome(m_parent), "Welcome!");
}

TabManager::~TabManager() {
    m_tablist.clear();
}

void TabManager::closeTab(int index) {
    auto wd = m_parent->widget(index);
    auto id = this->getTabListIndex(wd);
    if (id != -1)
        m_tablist.remove(id);
    m_parent->removeTab(index);
}

int TabManager::addNewTab(std::unique_ptr<QWidget> wd, const QString &nameTab) {
    int index;
    if (wd) {
        index = m_parent->addTab(wd.get(), nameTab);
    }
    else {
        std::unique_ptr<QPlainTextEdit> tmpPlainText = std::make_unique<QPlainTextEdit>();
        index = m_parent->addTab(tmpPlainText.get(), nameTab);
        m_tablist.push_back(move(tmpPlainText));
    }
    return index;
}

int TabManager::addNewTab(QWidget *wd, const QString &nameTab) {
    int index;
    if (wd) {
        index = m_parent->addTab(wd, nameTab);
    }
    else {
        std::unique_ptr<QPlainTextEdit> tmpPlainText = std::make_unique<QPlainTextEdit>();
        index = m_parent->addTab(tmpPlainText.get(), nameTab);
        m_tablist.push_back(move(tmpPlainText));
    }
    return index;
}

int TabManager::getTabListIndex(QWidget *wd) {
    int id = -1;
    for (int i = 0; i < m_tablist.size(); ++i) {
        if (wd == m_tablist[i].get()) {
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
