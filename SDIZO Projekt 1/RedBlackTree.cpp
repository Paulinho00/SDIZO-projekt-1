#include "DataStructures.h"
#include <fstream>
using namespace std;

RBTreeNode::RBTreeNode(int value, NodeColor color) {
	parent = nullptr;
	left = nullptr;
	right = nullptr;
	key = value;
	this->color = color;
}

RBTreeNode::RBTreeNode(int value, RBTreeNode* parent, NodeColor color) {
	this->parent = parent;
	left = nullptr;
	right = nullptr;
	key = value;
	this->color = color;
}

RBTreeNode::~RBTreeNode() {
	left = nullptr;
	right = nullptr;
	parent = nullptr;
}

RedBlackTree::RedBlackTree() {
	root = nullptr;
}

RedBlackTree::~RedBlackTree() {
	//Usuniecie struktury
	if (root != nullptr) {
		dropTree(root);
		root = nullptr;
	}
}

//Usuwa cale drzewo
void RedBlackTree::dropTree(RBTreeNode* element) {
	if (element != nullptr) {
		dropTree(element->left);
		dropTree(element->right);
		delete element;
	}
}