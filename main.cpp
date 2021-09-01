#include <iostream>
#include <cstdlib>
#include <vector>
#include <set>
#include "red_black_tree.h"

using namespace std;

int main() {
    vector<int> inserted;
    red_black_tree rb_tree;
    for (int i=0;i<100;++i){
        int key=rand()%(100-1+1)+1;
        rb_tree.insert(key);
        inserted.push_back(key);
    }
    rb_tree.check_black_height();
    cout<<endl<<"Check Red Black:"<<rb_tree.check_red_black()<<endl;
    rb_tree.print();
    for (int i=0;i<inserted.size()/2;++i){
        rb_tree.remove(inserted[i]);
    }
    cout<<endl<<"Check Tree:"<<rb_tree.check_red_black()<<endl;
    rb_tree.check_black_height();
    rb_tree.print();
    return 0;
}