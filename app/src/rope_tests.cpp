#include "test_runner.h"
#include "rope.h"
#include "rope_node.h"
#include <memory>

#include "rope_tests.h"

using std::string;

void TestConstruct_from_two_nodes() {
    string str_1("Hello     ");
    string str_2("world");

    Node _left(str_1);
    Node _right(str_2);

    Node node_3(make_unique<Node>(_left), make_unique<Node>(_right));
    ASSERT_EQUAL(_left.getLength(), 10u);
//    Rope new_rope(node_3);
//    ASSERT_EQUAL(node_3.at_node(14), 'd');


}
void TestRopeAt() {
    auto text = new Rope("qwerty");
    ASSERT_EQUAL(text->at(3), 'r');

    auto text2 = new Rope("create mode 100644 app/src/rope.h");
//    text2.

}
