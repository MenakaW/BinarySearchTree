#include "TreeNode.h"
#include <iostream>
#include <cstring>

using namespace std;

TreeNode::TreeNode(int newValue){
  value = newValue;
  left = nullptr;
  right = nullptr;
}

int TreeNode::getValue(){
  return value;
}

TreeNode* TreeNode::getLeft(){
  return left;
}

TreeNode* TreeNode::getRight(){
  return right;
}

void TreeNode::setLeft(TreeNode* newLeft){
  left = newLeft;
}

void TreeNode::setRight(TreeNode* newRight){
  right = newRight;
}

void TreeNode::setValue(int newValue){
  value = newValue;
}
