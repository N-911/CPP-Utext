#ifndef UTEXT_ROPE_NODE_H
#define UTEXT_ROPE_NODE_H


#include <memory>
#include <string>

using std::string;
class Node {
public:

    Node(std::unique_ptr<Node> _left, std::unique_ptr<Node> _right);
    Node(const string& _str);
    Node(const Node& node);  // copy constructor

    char at_node(size_t index) const;

    size_t getLength(void) const;

    void insert();

    bool isLeft() const;
    bool isRight() const;
    bool isLeaf(void) const;

private:
    std::unique_ptr<Node> left;   // pointer to a left child rope_node
    std::unique_ptr<Node> right;  // pointer to a right child rope_node
    size_t weight;                     // weight of node
    string str;                        // if node isLeast  str = part of text


};

#endif //UTEXT_ROPE_NODE_H
