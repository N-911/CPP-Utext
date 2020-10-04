#include "rope_node.h"

Rope_node::Rope_node() : Rope_node("") {
}

Rope_node::Rope_node(const string &_str) : weight(_str.size()),
                                           str(_str),
                                           left(nullptr) ,
                                           right(nullptr) {
}

bool Rope_node::isLeaf(void) const {
    if (left == nullptr && right == nullptr) {
        return true;
    }
    return false;
}

size_t Rope_node::getLength(void) const {
        return weight;
}
