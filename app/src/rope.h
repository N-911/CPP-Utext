#ifndef UTEXT_ROPE_H
#define UTEXT_ROPE_H

#include "rope_node.h"

#include <string>
using std::string;



class Rope {
public:

    Rope(); // default constructor
    Rope(const string& _str); // constructor from string
    Rope(const Rope& _rope);  // copy constructor

    char at(size_t index) const;
    string substring(size_t start_pos, size_t lenght) const;


    // modify
//    insert
//    append
//    delete


    //// operators

    Rope& operator = (const Rope& rhs);

    bool operator == (const Rope& rhs);
    bool operator != (const Rope& rhs);


private:
    std::unique_ptr<Node> root_node;
};


#endif //UTEXT_ROPE_H
