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
        to_delete= find_min_node(node->right);
    }
    //origin color of node to be deleted
    auto color=to_delete->color;
    if (to_delete->left!=sentinel_node){
        child=to_delete->left;
    }else{
        child=to_delete->right;
    }
    child->parent = to_delete->parent;
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
    if (color==BLACK){
        tree_remove_fix(child);
    }
     delete to_delete;
    /*
    if (node==sentinel_node) return;
    if (node->left==sentinel_node && node->right==sentinel_node){
        if (node->parent==sentinel_node){
            root=sentinel_node;
        }else{
            sentinel_node->parent=node->parent;
            if (node->parent->left==node){
                node->parent->left=sentinel_node;
            }else{
                node->parent->right=sentinel_node;
            }
        }
        if (node->color==BLACK){
            tree_remove_fix(sentinel_node);
        }
        delete node;
        return;
    }
    if (node->left!= sentinel_node && node->right!= sentinel_node){
        auto to_delete= find_min_node(node->right);
        auto to_delete_right=to_delete->right;
        to_delete_right->parent=to_delete->parent;
        if (to_delete==to_delete->parent->left){
            to_delete->parent->left=to_delete_right;
        }else{
            to_delete->parent->right=to_delete_right;
        }
        copy(to_delete,node);
        if (to_delete->color==BLACK){
            tree_remove_fix(to_delete_right);
        }
        delete to_delete;
        return;
    }
    TreeNode *child;
    if (node->left!=sentinel_node){
        child=node->left;
    }else{
        child=node->right;
    }
    auto to_delete=node;
    child->parent=to_delete->parent;
    if (to_delete->parent==sentinel_node){
        root=child;
    }else if (to_delete->parent->left==to_delete){
        to_delete->parent->left=child;
    }else{
        to_delete->parent->right=child;
    }
    if (to_delete->color==BLACK){
        tree_remove_fix(child);
    }
    delete to_delete;
     */
}
void red_black_tree::tree_remove_fix(TreeNode *node) {
    auto cur_node=node;
    while (cur_node!=root && cur_node->color==BLACK){
        if (cur_node==cur_node->parent->left){
            auto sibling=cur_node->parent->right;
            if (sibling->color==RED){
                sibling->color=BLACK;
                sibling->parent->color=RED;
                rotate_left(cur_node->parent);
                sibling=cur_node->parent->right;
            }
            if (sibling->left->color==BLACK && sibling->right->color==BLACK){
                sibling->color=RED;
                cur_node->parent->color=RED;
                cur_node=cur_node->parent;
            }else if (sibling->left->color==RED){
                sibling->color=RED;
                sibling->left->color=BLACK;
                sibling=sibling->left;
                rotate_right(sibling->parent);
            }else{
                sibling->right->color=BLACK;
                sibling->color=RED;
                sibling->parent->color=BLACK;
                rotate_left(sibling->parent);
                cur_node=root;
            }
        }else{
            auto sibling=cur_node->parent->left;
            if (sibling->color==RED){
                sibling->color=BLACK;
                cur_node->parent->color=RED;
                rotate_right(cur_node->parent);
                sibling=cur_node->parent->left;
            }
            if (sibling->left->color==BLACK && sibling->right->color==BLACK){
                sibling->color=RED;
                cur_node->parent->color=RED;
                cur_node=cur_node->parent;
            }else if (sibling->right->color==RED){
                sibling->right->color=BLACK;
                sibling->color=RED;
                sibling=sibling->right;
                rotate_left(sibling->parent);
            }else{
                sibling->left->color=BLACK;
                sibling->color=RED;
                sibling->parent->color=BLACK;
                rotate_right(sibling->parent);
                cur_node=root;
            }
        }
    }
    cur_node->color=BLACK;
}
void red_black_tree::copy(TreeNode *src, TreeNode *dst) {
    dst->key=src->key;
}
TreeNode* red_black_tree::find_min_node(TreeNode *node) {
    auto cur=node;
    while (cur->left!=sentinel_node){
        cur=cur->left;
    }
    return cur;
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
void red_black_tree::check_black_height() {
    std::cout<<"Printing RBTree Black Height:"<<std::endl;
    check_black_height(root,0);
}
void red_black_tree::check_black_height(TreeNode *root_node, int height) {
    if (root_node== nullptr || root_node==sentinel_node){
        std::cout<<height<<"\t\t";
        return;
    }
    int cur_height=0;
    if (root_node->color==BLACK) cur_height=1;
    if (root_node->left==sentinel_node && root_node->right==sentinel_node){
        std::cout<<height+cur_height<<"\t\t";
    }
    if (root_node->left!=sentinel_node){
        check_black_height(root_node->left,height+cur_height);
    }
    if (root_node->right!=sentinel_node){
        check_black_height(root_node->right,height+cur_height);
    }
}
bool red_black_tree::check_red_black() {
    return check_red_black(root);
}
bool red_black_tree::check_red_black(TreeNode *root_node) {
    if (root_node==sentinel_node) return true;
    if (root_node->color==RED && (root_node->left->color==RED || root_node->right->color==RED)){
        return false;
    }
    return check_red_black(root_node->left) && check_red_black(root_node->right);
}