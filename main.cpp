#include <iostream>
#include <cstdlib>
#include "red_black_tree.h"

int main() {
    red_black_tree rb_tree;
    for (int i=0;i<10;++i){
        int key=rand()%(100-1+1)+1;
        std::cout<<key<< std::endl;
        rb_tree.insert(key);
    }
    rb_tree.print();
    return 0;
}
