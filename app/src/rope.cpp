#include "rope.h"
#include <exception>

Rope::Rope() : Rope("") {
}

Rope::Rope(const string & _str) {
    this->root_node = std::make_unique<Node>(_str);
}

Rope::Rope(const Rope& _rope) {
    if (this->root_node != _rope.root_node) {
        Node temp = Node(*_rope.root_node);
        this->root_node = std::make_unique<Node>(temp);
    }
}

char Rope::at(size_t index) const {
    if (root_node == nullptr) {
        throw std::invalid_argument ("rope is empty\n");
    }
    return this->root_node->at_node(index);
}

string Rope::substring(size_t start_pos, size_t lenght) const {
    if (root_node->isLeaf()) {
        if (root_node->getLength() < lenght) {

        }
    }
    return std::string();
}


