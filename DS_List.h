#include <list>
#include <iostream>

class Node {
public:
    int x;
    int y;

    Node(int x, int y) : x(x), y(y) {}
    
};

class DS_List {
public:
    std::list<Node> List;

    int empty() const;

    void ins_end(int x, int y);

    void del_head();

    Node peek_head();

    void test_print();

    DS_List operator+(const DS_List &oth);
};