#include "DataStructures.h"
using namespace std;

BstNode::BstNode(int value) {
	key = value;
	left = nullptr;
	right = nullptr;
	parent = nullptr;
}

BstNode::BstNode(int value, BstNode* parent) {
	key = value;
	left = nullptr;
	right = nullptr;
	this->parent = parent;
}

BstNode::~BstNode() {
	delete left;
	delete right;
}

Bst::Bst() {
	root = nullptr;
}

Bst::~Bst() {
	delete root;
}

//Wyswietla zawartosc BST
void Bst::showElements() {
	cout << "\n";

	//Wywolanie funkcji wypisujacej
	print("", false, root);
}

//Funkcja wypisujaca potomkow danego elementu
void Bst::print(string prefix, bool isLeft, BstNode* node) {
	if (node != nullptr) {
		cout << prefix + (isLeft ? "|--" : "\\--") << "[" << node->key << "]\n";
		print((prefix + (isLeft ? "|  " : "   ")), true, node->left);
		print((prefix + (isLeft ? "|  " : "   ")), false, node->right);
	}
}

//Dodaje element do kopca
void Bst::addElement(int value) {
	BstNode* parent = nullptr;
	BstNode* currentNode = root;
	//Wyszukanie rodzica dla nowego elementu
	while (currentNode != nullptr) {
		parent = currentNode;
		if (value > currentNode->key) currentNode = currentNode->right;
		else currentNode = currentNode->left;
	}

	//Tworzenie nowego elementu
	BstNode* newElement = new BstNode(value, parent);
	
	//Sprawdzenie czy drzewo jest puste
	if (parent == nullptr) {
		root = newElement;
	}
	else {
		if (value > parent->key) parent->right = newElement;
		else parent->left = newElement;
	}
}