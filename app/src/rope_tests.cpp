#include "test_runner.h"
#include "rope.h"
#include "rope_node.h"
#include <memory>

#include "rope_tests.h"

using std::string;

void Test_Node_Construct_from_two_nodes() {
    string str_1("Hello ");
    string str_2("world");
    string str_3(" node");
    string str_4(" four");

    Node _left1(str_1);
    Node _right1(str_2);
    Node _left2(str_2);
    Node _right2(str_3);

    Node node_3(make_unique<Node>(_left1), make_unique<Node>(_right1));
//    Node node_4(make_unique<Node>(_left2), make_unique<Node>(_right2));
//    Node node_50(make_unique<Node>(node_3), make_unique<Node>(node_4));

//    ASSERT_EQUAL(node_50.getLength(), 10u);
//    Rope new_rope(node_3);
//    ASSERT_EQUAL(node_3.at_node(12), 'w');
}

void Test_Node_getLenght() {
    string str_1("Helllo ");
    string str_2("world");
    string str_3("right node ....");

    std::unique_ptr<Node> left1 = make_unique<Node>(str_1);
    std::unique_ptr<Node> right2 = make_unique<Node>(str_3);
    std::unique_ptr<Node> right1 = make_unique<Node>(str_2);
    std::unique_ptr two_node = make_unique<Node>(move(left1), move(right1));

    Node three_node(move(two_node), move(right2));

    ASSERT_EQUAL(three_node.getLength(), 27u);

}

void Test_Node_copy_constructor() {

    string str_1("New node");
    std::unique_ptr<Node> left1 = make_unique<Node>(str_1);

}


void Test_Rope_At() {
    auto text = new Rope("qwerty");
    ASSERT_EQUAL(text->at(3), 'r');

    auto text2 = new Rope("create mode 100644 app/src/rope.h");
//    text2.

}
