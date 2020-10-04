#ifndef UTEXT_ROPE_H
#define UTEXT_ROPE_H

#include "rope_node.h"

#include <string>
using std::string;



class Rope {
public:

    Rope();
    Rope(const string& _str);
    Rope(const Rope& _rope);



    ~Rope();

    string toString(void) const;

    // operators

    Rope& operator = (const Rope& rhs);
    bool operator == (const Rope& rhs);
    bool operator != (const Rope& rhs);


private:
    std::unique_ptr<Rope_node> root_node;
};


#endif //UTEXT_ROPE_H
