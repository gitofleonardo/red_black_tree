//
// Created by huangchengxi on 2021/8/30.
//

#ifndef RED_BLACK_TREE_RED_BLACK_TREE_H
#define RED_BLACK_TREE_RED_BLACK_TREE_H

enum COLOR{
    RED,
    BLACK
};

struct TreeNode{
    int key;
    int value;
    TreeNode *left= nullptr;
    TreeNode *right= nullptr;
    TreeNode *parent= nullptr;
    COLOR color=BLACK;
};

class red_black_tree {
private:
    TreeNode *sentinel_node= nullptr;
    void rotate_left(TreeNode *root,TreeNode *target);
    void rotate_right(TreeNode *root,TreeNode *target);
    TreeNode* rotate_left(TreeNode *child);
    TreeNode* rotate_right(TreeNode *child);
public:
    red_black_tree();
    ~red_black_tree();
};


#endif //RED_BLACK_TREE_RED_BLACK_TREE_H
