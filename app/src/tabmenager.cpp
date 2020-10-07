#include "tabmenager.h"
#include "tabwelcome.h"
#include <iostream>
#include <QPlainTextEdit>

TabMenager::TabMenager(QTabWidget *parent) : m_parent(parent) {
    m_parent->addTab(new TabWelcome(m_parent), "Welcome!");
}

TabMenager::~TabMenager() {

}
