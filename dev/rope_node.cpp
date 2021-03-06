#include "rope_node.h"

Node::Node(const string &_str) : weight(_str.length()),
                                 str(_str),
                                 left(nullptr) ,
                                 right(nullptr) {
}

Node::Node(std::unique_ptr<Node> _left, std::unique_ptr<Node> _right)
                                                                : str("") {
    this->left = move(_left);
    this->right = move(_right);
    this->weight = this->left->getLength();
}

Node::Node(const Node &node) {
    auto temp_left = node.left.get();
    auto temp_right = node.right.get();
    left = std::unique_ptr<Node>(temp_left);
    right = std::unique_ptr<Node>(temp_right);
    weight = left->getLength();
    str = "";
}


bool Node::isLeaf(void) const {
    if (this->left == nullptr && this->right == nullptr) {
        return true;
    }
    return false;
}

size_t Node::getLength(void) const {
    if (this->isLeaf()) {
        return this->weight;
    }
//    size_t tmp = (this->right == nullptr) ? 0 : this->right->getLength();
//    return this->weight + tmp;

    size_t temp_len = 0;
    if (this->left) {
        temp_len += this->left->getLength();
    }
    if (this->right) {
        temp_len += this->right->getLength();
    }
    return temp_len;
}

bool Node::isLeft() const {
    return left != nullptr;
}

bool Node::isRight() const {
    return right != nullptr;
}

char Node::at_node(size_t index) const {
    size_t curr_weight = this->weight;
    if (this->isLeaf()) {
        if (index > this->weight) {
            throw std::invalid_argument("invalid argument\n");
        }
        else {
            return str[index];
        }
    }
    else {
        if (index > this->weight && this->right) {
            return this->right->at_node(index - curr_weight);
        }
        else {
            return this->left->at_node(index);
        }
    }
}


