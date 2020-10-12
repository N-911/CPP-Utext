#include "tabmenager.h"
#include "tabwelcome.h"
#include <iostream>
#include <QPlainTextEdit>
#include <memory>

TabManager::TabManager(QTabWidget *parent) : m_parent(parent) {
//    m_parent->addTab(new TabWelcome(m_parent), "Welcome!");
}

TabManager::~TabManager() {
    for (auto &w : m_tablist) {
        delete w;
        w = nullptr;
    }
    m_tablist.clear();
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
    }
    else {
        auto *tmpPlainText = new QPlainTextEdit();
        tmpPlainText->setPlainText(content);
        index = m_parent->addTab(tmpPlainText, nameTab);
        m_tablist.push_back(tmpPlainText);
    }
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
