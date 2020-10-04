#include "rope.h"

Rope::Rope() : Rope("") {
}

Rope::Rope(const string & _str) {
    this->root_node = std::make_unique<Rope_node>(_str);
}

Rope::Rope(const Rope& _rope) {
    if (this->root_node != _rope.root_node) {
        this->root_node = move(_rope.root_node);
    }

}


