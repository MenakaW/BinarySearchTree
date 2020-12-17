#include <iostream>
#include <fstream>
#include <cstring>
#include "TreeNode.h"

using namespace std;

//function prototypes
void sortTree(TreeNode* &toSort, TreeNode* &root, TreeNode* &current);
void removeNode(int value, TreeNode* &current);
TreeNode* removeNode(TreeNode* &toRemove, TreeNode* &previous, TreeNode* current);
void printTree(TreeNode* root, int space);
void searchTree(int value, bool &found, TreeNode* current);
void returnNode(TreeNode* &current, TreeNode* &found, TreeNode* &previous, int value);

int main(){

  //define main variables
  TreeNode* root = nullptr;
  int inputNums[101];
  char input[20];
  int numnums = 0;
  cout << "input from file or console, type file/console" << endl;
  cin >> input;
  cin.get();
  //if user decides to input from file
  if(input[0]=='f'||input[0]=='F'){
    //open a input file stream
    ifstream file;
    char filename[20];
    cout << "enter file name correctly" << endl;
    cin >> filename;
    cin.get();
    file.open(filename);
    //cycle through for a max of 100 times or until the text is over
    for(int a = 1; a < 101; a++){
      if(file.eof()){
	break;
      }
      int in;
      file >> in;
      cout << in << endl;
      inputNums[a] = in;
      numnums++;
    }
    //get rid of the extra number at the end of the array and close the program
    inputNums[numnums]=0;
    numnums--;
    file.close();
  }
  //if the user chooses to enter input through console
  else{
    //ask for the size and set it
    cout << "enter the number of numbers you are inputting" << endl;
    cin >> numnums;
    cin.get();
    cout << "enter your numbers, pressing the ENTER key between each one." << endl;
    //cycle through the array and add numbers for size number of times
    for(int a = 1; a <= numnums; a++){
      int input;
      cin >> input;
      cin.get();
      inputNums[a] = input;
    }
  }
  //go through the input array and send to the sorting algorithm so it can be added it correctly
  for(int a = 1; a <= numnums; a++){
    TreeNode* tn = new TreeNode(inputNums[a]);
    sortTree(tn, root, root);
  }
  //do the initial print of the tree
  printTree(root, -10);
  bool isRunning = true;
  //user loop
  while(isRunning){
    cout << "would you like to add, remove, search, print, or quit?" << endl;
    cin >> input;
    //if the user wants to add
    if(input[0]=='a'||input[0]=='A'){
      //have them enter the number and then send it through to the sorting algorithm so it can be added correctly
      int number;
      cout << "enter your number" << endl;
      cin >> number;
      cin.get();
      TreeNode* tn = new TreeNode(number);
      sortTree(tn, root, root);
    }
    //if the user wants to remove a node
    else if(input[0]=='r' || input[0]=='R'){
      int number;
      cout << "enter the number you wish to remove" << endl;
      cin >> number;
      cin.get();
      TreeNode* found = nullptr;
      TreeNode* previous = nullptr;
      //first retrieve the node from the tree, making sure to get the node and the previous node
      returnNode(root, found, previous, number);
      //if the node isn't found, notify the user
      if(found==nullptr){
	cout << "sorry this node does not exist" << endl;
      }
      //call the remove node and delete the node, and make sure the root is fixed
      else{
	TreeNode* tn = removeNode(found, previous, found);
	if(previous==nullptr){
	  if(tn==nullptr){
	    root = nullptr;
	  }
	  else{
	    root = tn;
	  }
	}
      }
    }
    //if the user wants to search the tree for a number
    else if(input[0]=='s' || input[0]=='S'){
      int number;
      cout << "enter the number you want to search for" << endl;
      cin >> number;
      cin.get();
      bool found = false;
      //call the search method and print out the correct print statement
      searchTree(number, found, root);
      if(found){
	cout << "yes! the number is in the tree" << endl;
      }
      else{
	cout << "this number is not in the tree" << endl;
      }
    }
    //if the user wants to print, then print the tree
    else if(input[0]=='p'||input[0]=='P'){
      printTree(root, -10);
    }
    //if the user wants to quit, break from the tree
    else if(input[0]=='q'|| input[0]=='Q'){
      break;
    }
    else{
      cout << "this operation is not included in the program..."<< endl;
    }
  }
  return 0;

}

void searchTree(int value, bool &found, TreeNode* current){
  //if the value entered is larger than the current node recursively go right, else go left
  if(current==nullptr){
    return;
  }
  //if you find a match, change the booelan by reference
  if(current->getValue()==value){
    found = true;
    return;
  }
  else if(value > current->getValue()){
    searchTree(value, found, current->getRight());
  }
  else if (value < current->getValue()){
    searchTree(value, found, current->getLeft());
  }
}

void returnNode(TreeNode* &current, TreeNode* &found, TreeNode* &previous, int value){
  //same algorithm as searchtree except update teh parameters passed by reference so you can acces them later
  if(current==nullptr){
    return;
  }
  if(current->getValue()==value){
    found = current;
  }
  else if(value > current->getValue()){
    previous = current;
    TreeNode* next = current->getRight();
    returnNode(next, found, previous, value);
  }
  else if (value < current->getValue()){
    previous = current;
    TreeNode* next = current->getLeft();
    returnNode(next, found, previous, value);
  }
}

TreeNode* removeNode(TreeNode* &toRemove, TreeNode* &previous, TreeNode* current){
  //if the treenode has two children(left and right)
  if(toRemove->getRight()!=nullptr && toRemove->getLeft()!=nullptr){
    //first go left and use prevcurrent to track the parent of the current node
    current = toRemove->getLeft();
    TreeNode* prevCurrent = toRemove;
    //while you haven't reached the end of the tree, keep going right
    while(current->getRight()!=nullptr){
      prevCurrent = current;
      current = current->getRight();
    }
    //swap the values of the original node you wanted to delete and the current then delete current and fix up any holes in the tree
    toRemove->setValue(current->getValue());
    if(prevCurrent==toRemove){
      prevCurrent->setLeft(current->getLeft());
    }
    else{
      prevCurrent->setRight(current->getLeft());
    }
    //if the node you wanted to delete was the root, return it and reset the root to toRemove
    delete current;
    return toRemove;
  }
  //if the parent node only has one leaf node
  else if(toRemove->getRight()!=nullptr || toRemove->getLeft()!=nullptr){
    //if it is not the head
    if(previous!=nullptr){
      //if the toremove is the left ndoe
      if(previous->getLeft()==toRemove){
	//if the leaf node is a right node then set previous left to current right
	if(toRemove->getRight()!=nullptr){
	  TreeNode* temp = toRemove;
	  previous->setLeft(temp->getRight());
	  delete temp;
	}
	//if the leaf node is a left node then set previous left to current left
	else if(toRemove->getLeft()!=nullptr){
	  TreeNode* temp = toRemove;
	  previous->setLeft(temp->getLeft());
	  delete temp;
	}
      }
      //if the toremove is the right node
      else if(previous->getRight()==toRemove){
	//if the leaf node is a right node then se previous right to current right
	if(toRemove->getRight()!=nullptr){
	  TreeNode* temp = toRemove;
	  previous->setRight(temp->getRight());
	  delete temp;
	}
	//if the leaf node is a left node then set previous right to current left
	else if(toRemove->getLeft()!=nullptr){
	  TreeNode* temp = toRemove;
	  previous->setRight(temp->getLeft());
	  delete temp;
	}
      }
    }
    //if the node you want to delete is the root
    else{
      //return the next root to set it up later
      if(toRemove->getRight()!=nullptr){
	return toRemove->getRight();
      }
      //return the next root to set it up later
      else if(toRemove->getLeft()!=nullptr){
        return toRemove->getLeft();
      }
    }
  }
  //if the node you want to delete has no leaf nodes
  else{
    //if it's not the head
    if(previous!=nullptr){
      //just delete the node and set the previous left/right to null
      if(previous->getLeft()==toRemove){
	delete toRemove;
	previous->setLeft(nullptr);
      }
      else if(previous->getRight()==toRemove){
	delete toRemove;
	previous->setRight(nullptr);
      }
    }
    //if it's the root, return null ptr to initialize the root to null later
    else{
      return nullptr;
    }
  }
  return previous;
}

//infix post algorithm from GeeksForGeeks https://www.geeksforgeeks.org/print-binary-tree-2-dimensions/
void printTree(TreeNode* root, int space){

  //if the current root isn't null
  if(root!=nullptr){
    //every layer down you go in the tree, add 10 spaces
    space+=10;
    //print out the right subtree through recursion
    printTree(root->getRight(), space);
    //new line before every print
    cout << "\n";
    //print out the number of spaces
    for(int a = 0; a < space; a++){
      cout << " ";
    }
    //print out the current node
    cout << root->getValue() << "\n";
    //after, print out the left subtree through recursion
    printTree(root->getLeft(), space);
  }
  
}

void sortTree(TreeNode* &toSort, TreeNode* &root, TreeNode* &current){

  //if root is a null, set the root to toSort
  if(root==nullptr){
    root = toSort;
    return;
  }
  else{
    //if to sort has a less value than the current node then go left
    if(toSort->getValue()<=current->getValue()){
      if(current->getLeft()==nullptr){
	current->setLeft(toSort);
	return;
      }
      else{
	TreeNode* next = current->getLeft();
	sortTree(toSort, root, next);
      }
    }
  //if to sort has a greater value than the current node go right
    else if(toSort->getValue()>current->getValue()){
      if(current->getRight()==nullptr){
	current->setRight(toSort);
	return;
      }
      else{
	TreeNode* next = current->getRight();
	sortTree(toSort, root, next);
      }
    }
  }

  
}
