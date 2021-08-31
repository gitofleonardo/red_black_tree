#include <iostream>
#include <cstdlib>
#include <vector>
#include "red_black_tree.h"

using namespace std;

int main() {
    vector<int> inserted;
    red_black_tree rb_tree;
    for (int i=0;i<10;++i){
        int key=rand()%(100-1+1)+1;
        std::cout<<key<< std::endl;
        rb_tree.insert(key);
        inserted.push_back(key);
    }
    rb_tree.print();
    for (auto &i:inserted){
        rb_tree.remove(i);
        rb_tree.print();
    }
    return 0;
}
