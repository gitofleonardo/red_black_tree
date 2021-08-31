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
    int key=-1;
    TreeNode *left= nullptr;
    TreeNode *right= nullptr;
    TreeNode *parent= nullptr;
    COLOR color=BLACK;
};

class red_black_tree {
private:
    TreeNode *sentinel_node= nullptr;
    TreeNode *root= nullptr;
    void rotate_left(TreeNode *child);
    void rotate_right(TreeNode *child);
    bool is_left_child(TreeNode *child);
    void tree_fix(TreeNode *inserted);
    void destroy(TreeNode *root);
    void print(TreeNode *root);
    void remove(TreeNode *node);
    TreeNode* findMinNode(TreeNode *node);
    void tree_remove_fix(TreeNode *node);
    void copy(TreeNode *src,TreeNode *dst);
public:
    red_black_tree();
    ~red_black_tree();
    void insert(int key);
    void remove(int key);
    void print();
};


#endif //RED_BLACK_TREE_RED_BLACK_TREE_H
