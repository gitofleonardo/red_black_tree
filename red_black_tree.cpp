//
// Created by huangchengxi on 2021/8/30.
//

#include "red_black_tree.h"
#include <queue>
#include <iostream>

red_black_tree::red_black_tree() {
    sentinel_node=new TreeNode{-1, nullptr, nullptr, nullptr,BLACK};
    root=sentinel_node;
}
red_black_tree::~red_black_tree() {
    destroy(root);
    delete sentinel_node;
}
void red_black_tree::print() {
    print(root);
}
void red_black_tree::print(TreeNode *root_node) {
    if (root_node==sentinel_node) return;
    std::queue<TreeNode*> nodes;
    nodes.push(root_node);
    while (!nodes.empty()){
        int cur_size=nodes.size();
        while(cur_size-->0){
            auto node=nodes.front();
            nodes.pop();
            if (node==sentinel_node){
                std::cout<<"SENTINEL"<<"\t";
                continue;
            }
            nodes.push(node->left);
            nodes.push(node->right);
            std::string color;
            if (node->color==BLACK) color="BLACK";
            else color="RED";
            std::cout<<color<<":"<<node->key<<"\t";
        }
        std::cout<<std::endl;
    }
}
void red_black_tree::remove(int key) {
    auto cur_node=root;
    while (cur_node!=sentinel_node){
        if (cur_node->key==key){
            break;
        }else if (cur_node->key>key){
            cur_node=cur_node->left;
        }else{
            cur_node=cur_node->right;
        }
    }
    if (cur_node!=sentinel_node){
        remove(cur_node);
    }
}
void red_black_tree::remove(TreeNode *node) {
    if (node== nullptr || node==sentinel_node) return;
    TreeNode *to_delete;
    TreeNode *child;
    if (node->left==sentinel_node || node->right==sentinel_node){
        to_delete=node;
    }else{
        to_delete= findMinNode(node->right);
    }
    if (to_delete->left!=sentinel_node){
        child=to_delete->left;
    }else{
        child=to_delete->right;
    }
    child->parent=to_delete->parent;
    if (to_delete->parent==sentinel_node){
        root=child;
    }else if (to_delete->parent->left==to_delete){
        to_delete->parent->left=child;
    }else{
        to_delete->parent->right=child;
    }
    if (to_delete!=node){
        copy(to_delete,node);
    }
    if (to_delete->color==BLACK){
        tree_remove_fix(child);
    }
}
void red_black_tree::tree_remove_fix(TreeNode *node) {

}
void red_black_tree::copy(TreeNode *src, TreeNode *dst) {
    dst->key=src->key;
    dst->color=src->color;
}
TreeNode* red_black_tree::findMinNode(TreeNode *node) {
    while (node->left!=sentinel_node){
        node=node->left;
    }
    return node;
}
void red_black_tree::insert(int key) {
    auto *new_node=new TreeNode{key,sentinel_node,sentinel_node, nullptr,RED};
    auto parent=sentinel_node;
    auto cur=root;
    while (cur!=sentinel_node){
        parent=cur;
        if (cur->key==key){
            return;
        }else if (cur->key>key){
            cur=cur->left;
        }else{
            cur=cur->right;
        }
    }
    new_node->parent=parent;
    if (parent==sentinel_node){
        root=new_node;
        root->color=BLACK;
        return;
    }
    if (new_node->key>parent->key){
        parent->right=new_node;
    }else{
        parent->left=new_node;
    }
    tree_fix(new_node);
}
void red_black_tree::tree_fix(TreeNode *inserted) {
    auto cur_node= inserted;
    while (cur_node->parent->color==RED){
        if (cur_node->parent==cur_node->parent->parent->left){
            auto uncle_node=cur_node->parent->parent->right;
            if (uncle_node->color==RED){
                uncle_node->color=BLACK;
                cur_node->parent->color=BLACK;
                cur_node->parent->parent->color=RED;
                cur_node=cur_node->parent->parent;
            }else{
                if (cur_node==cur_node->parent->right){
                    rotate_left(cur_node->parent);
                    rotate_right(cur_node->parent);
                    cur_node->left->color=RED;
                    cur_node->right->color=RED;
                    cur_node->color=BLACK;
                    cur_node=cur_node->left;
                }else{
                    rotate_right(cur_node->parent->parent);
                    cur_node->color=RED;
                    cur_node->parent->right->color=RED;
                    cur_node->parent->color=BLACK;
                }
            }
        }else{
            auto uncle_node=cur_node->parent->parent->left;
            if (uncle_node->color==RED){
                uncle_node->color=BLACK;
                cur_node->parent->color=BLACK;
                cur_node->parent->parent->color=RED;
                cur_node=cur_node->parent->parent;
            }else{
                if (cur_node==cur_node->parent->left){
                    cur_node=cur_node->parent;
                    rotate_right(cur_node);
                }
                rotate_left(cur_node->parent->parent);
                cur_node->parent->color=BLACK;
                cur_node->parent->left->color=RED;
                cur_node->color=RED;
            }
        }
    }
    root->color=BLACK;
}
void red_black_tree::destroy(TreeNode *root_node) {
    if (root_node== sentinel_node) return;
    destroy(root_node->left);
    destroy(root_node->right);
    delete root_node;
}
void red_black_tree::rotate_left(TreeNode *child) {
    if (child->right!= sentinel_node){
        auto parent=child->parent;
        bool left_node= is_left_child(child);
        auto right=child->right;
        child->right=right->left;
        if (child->right!= sentinel_node)
            child->right->parent=child;
        child->parent=right;
        right->left=child;
        right->parent=parent;
        if (parent==sentinel_node){
            root=right;
        }else if (left_node){
            parent->left=right;
        }else{
            parent->right=right;
        }
    }
}
void red_black_tree::rotate_right(TreeNode *child) {
    if (child->left!= sentinel_node){
        auto parent=child->parent;
        bool left_child= is_left_child(child);
        auto left=child->left;
        child->left=left->right;
        if (child->left!=sentinel_node)
            child->left->parent=child;
        left->right=child;
        child->parent=left;
        left->parent=parent;
        if (parent==sentinel_node){
            root=left;
        }else if (left_child){
            parent->left=left;
        }else{
            parent->right=left;
        }
    }
}
bool red_black_tree::is_left_child(TreeNode *child) {
    if (child->parent->left==child) return true;
    return false;
}