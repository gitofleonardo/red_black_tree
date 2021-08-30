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
TreeNode* red_black_tree::rotate_left(TreeNode *child) {
    auto parent=child->parent;
    if (child->right!= nullptr){
        //set right node as current parent
        auto cur_parent=child->right;
        //move current parent's left node to child's right
        child->right=cur_parent->left;
        if (child->right!= nullptr){
            child->right->parent=child;
        }
        //set child's parent to current parent
        cur_parent->left=child;
        child->parent=cur_parent;
        //set current parent's parent to child's origin parent
        cur_parent->parent=parent;
        return cur_parent;
    }
    return child;
}
TreeNode* red_black_tree::rotate_right(TreeNode *child) {

}