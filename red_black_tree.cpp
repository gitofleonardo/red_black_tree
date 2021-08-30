//
// Created by huangchengxi on 2021/8/30.
//

#include "red_black_tree.h"

red_black_tree::red_black_tree() {
    sentinel_node=new TreeNode{0,0, nullptr, nullptr, nullptr,BLACK};
}
red_black_tree::~red_black_tree() {
    delete sentinel_node;
}
void red_black_tree::rotate_left(TreeNode *root, TreeNode *target) {
    if (root== nullptr || target== nullptr) return;
    if (root->value>target->value){

    }
}