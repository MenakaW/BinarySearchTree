#pragma once
#include <iostream>
#include <cstring>

using namespace std;

class TreeNode{
 public:
  TreeNode(int);
  int getValue();
  TreeNode* getLeft();
  TreeNode* getRight();
  void setLeft(TreeNode*);
  void setRight(TreeNode*);
  void setValue(int);
 private:
  int value;
  TreeNode* left;
  TreeNode* right;
};
