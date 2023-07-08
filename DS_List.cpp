#include "DS_List.h"

int DS_List::empty() const {
    return (int) List.empty();
}

void DS_List::ins_end(int x, int y) {
    List.push_back(Node(x, y));
}

void DS_List::del_head() {
    if (!List.empty())
        List.pop_front();
}

Node DS_List::peek_head() {
    if (!List.empty())
        return List.front();
    return {-1, -1};
}

void DS_List::test_print() {
    std::cout << "List elements:" << std::endl;
    for (auto i: List) {
        std::cout << i.x << " " << i.y << std::endl;
    }
}

DS_List DS_List::operator+(const DS_List &oth) {
    DS_List ret;

    for (auto i: List) {
        ret.ins_end(i.x, i.y);
    }
    for (auto i: oth.List) {
        ret.ins_end(i.x, i.y);
    }

    return ret;
}