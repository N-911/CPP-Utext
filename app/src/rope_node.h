#ifndef UTEXT_ROPE_NODE_H
#define UTEXT_ROPE_NODE_H


#include <memory>
#include <string>

using std::string;
class Rope_node {
public:
    Rope_node();
    Rope_node(const string& _str);
    Rope_node(const Rope_node& rhs);

    size_t getLength(void) const;


private:
    bool isLeaf(void) const;
    std::unique_ptr<Rope_node> left;
    std::unique_ptr<Rope_node> right;
    size_t weight;
    string str;


};

#endif //UTEXT_ROPE_NODE_H
