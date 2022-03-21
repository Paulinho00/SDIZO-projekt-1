#include "DataStructures.h"
#include "Colors.h"
#include <fstream>
#include <string>
using namespace std;
const string red("\033[0;31;107m");
const string black("\033[0;30;107m");


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

//Dodaje element do kopca
void RedBlackTree::addElement(int value) {
	//Sprawdzenie czy nie probujemy dodac duplikatu
	if (findPointerToElement(value) != nullptr) {
		cout << "Istnieje element o takim kluczu, dodawanie duplikatow jest zabronione\n";
		return;
	}

	RBTreeNode* parent = nullptr;
	RBTreeNode* currentNode = root;
	//Wyszukanie rodzica dla nowego elementu
	while (currentNode != nullptr) {
		parent = currentNode;
		if (value > currentNode->key) currentNode = currentNode->right;
		else currentNode = currentNode->left;
	}

	//Tworzenie nowego elementu
	RBTreeNode* newElement = new RBTreeNode(value, parent, NodeColor::RED);

	//Sprawdzenie czy drzewo jest puste
	if (parent == nullptr) {
		root = newElement;
		newElement->color = NodeColor::BLACK;
	}
	else {
		if (value > parent->key) parent->right = newElement;
		else parent->left = newElement;
		fixColor(newElement);
	}
}

//Wyswietla zawartosc BST
void RedBlackTree::showElements() {
	cout << "\n";
	//Wywolanie funkcji wypisujacej
	print("", "", root);
}

//Usuwa cale drzewo
void RedBlackTree::dropTree(RBTreeNode* element) {
	if (element != nullptr) {
		dropTree(element->left);
		dropTree(element->right);
		delete element;
	}
}

//Znajduje wskaznik na dany element
RBTreeNode* RedBlackTree::findPointerToElement(int value) {
	RBTreeNode* currentElement = root;
	//Pêtla przeszukuj¹ca drzewo
	while (currentElement != nullptr && currentElement->key != value) {
		if (value < currentElement->key) currentElement = currentElement->left;
		else currentElement = currentElement->right;
	}
	return currentElement;
}


//Rotacja w prawo na wybranym elemencie
int RedBlackTree::rotateNodeRight(RBTreeNode* node) {
	//Sprawdzenie czy dany element istnieje
	if (node != nullptr) {
		//Sprawdzenie czy jest spelniony warunek konieczny do rotacji
		if (node->left == nullptr) {
			return -2;
		}
		else {
			//Rotacja poprzez zmiane wskaznikow na dzieci i rodzicow
			RBTreeNode* leftChild = node->left;
			node->left = leftChild->right;
			if (leftChild->right != nullptr) leftChild->right->parent = node;
			leftChild->parent = node->parent;

			//Sprawdzenie czy element jest korzeniem
			if (node->parent != nullptr) {
				if (node->parent->left == node) node->parent->left = leftChild;
				else node->parent->right = leftChild;
			}
			else {
				//Zmiana korzenia
				root = leftChild;
			}
			leftChild->right = node;
			node->parent = leftChild;
		}
	}
	else {
		return -1;
	}
}

//Rotacja w lewo na wybranym elemencie
int RedBlackTree::rotateNodeLeft(RBTreeNode* node) {
	//Sprawdzenie czy dany element istnieje
	if (node != nullptr) {
		//Sprawdzenie czy jest spelniony warunek konieczny do rotacji
		if (node->right == nullptr) {
			return -2;
		}
		else {

			//Rotacja poprzez zmiane wskaznikow na dzieci i rodzicow
			RBTreeNode* rightChild = node->right;
			node->right = rightChild->left;
			if (rightChild->left != nullptr) rightChild->left->parent = node;
			rightChild->parent = node->parent;
			//Sprawdzenie czy element jest korzeniem
			if (node->parent != nullptr) {
				if (node->parent->left == node) node->parent->left = rightChild;
				else node->parent->right = rightChild;
			}
			else {
				//Zmiana korzenia
				root = rightChild;
			}
			rightChild->left = node;
			node->parent = rightChild;
		}
	}
	else {
		return -1;
	}
}

//Naprawa koloru po wstawieniu elementu
void RedBlackTree::fixColor(RBTreeNode* node) {
	RBTreeNode* parent = nullptr;
	RBTreeNode* grandParent = nullptr;
	RBTreeNode* uncle = nullptr;

	//Odczyt rodzica

if (node->parent != nullptr) {
		parent = node->parent;
		//Odczyt dziadka
		if (parent->parent != nullptr) {
			grandParent = parent->parent;
			//Odczyt stryja
			if (grandParent->left != nullptr && grandParent->left != parent) uncle = grandParent->left;
			else if (grandParent->right != nullptr && grandParent->right != parent) uncle = grandParent->right;
		}

		//Sprawdzenie czy dziadek jest czerwony
		if (parent->color == NodeColor::RED) {
			//Sprawdzenie czy wujek jest czerwony
			if (uncle != nullptr && uncle->color == NodeColor::RED) {
				//Odpowiednia zmiana kolorow
				parent->color = NodeColor::BLACK;
				uncle->color = NodeColor::BLACK;
				if(root ==grandParent) grandParent->color = NodeColor::BLACK;
				else grandParent->color = NodeColor::RED;
				//Wywolanie funkcji naprawiajacej kolory z dziadkiem
				fixColor(grandParent);
			}
			//Sprawdzenie czy wujek jest czarny i nowy element jest lewym potomkiem
			else if ((uncle == nullptr || uncle->color == NodeColor::BLACK) && parent->left == node) {
				rotateNodeRight(grandParent);
				//Zmiana koloru rodzica na przeciwny
				if (parent->color == NodeColor::BLACK) parent->color = NodeColor::RED;
				else parent->color = NodeColor::BLACK;

				//Zmiana koloru dziadka na przeciwny
				if (grandParent->color == NodeColor::BLACK) grandParent->color = NodeColor::RED;
				else grandParent->color = NodeColor::BLACK;
			}
			//Sprawdzenie czy wujek jest czarny i nowy element jest prawym potomkiem
			else if ((uncle == nullptr || uncle->color == NodeColor::BLACK) && parent->right == node) {
				//TODO tu jest gdzies blad
				rotateNodeLeft(parent);
				rotateNodeRight(grandParent);

				//Zmiana koloru rodzica na przeciwny
				if (parent->color == NodeColor::BLACK) parent->color = NodeColor::RED;
				else parent->color = NodeColor::BLACK;

				//Zmiana koloru dziadka na przeciwny
				if (grandParent->color == NodeColor::BLACK) grandParent->color = NodeColor::RED;
				else grandParent->color = NodeColor::BLACK;
			}
		}
		else {
			return;
		}
	}
	else {
		return;
	}
}

//Funkcja wypisujaca potomkow danego elementu
void RedBlackTree::print(string prefix, string childrenPrefix, RBTreeNode* node) {
	if (node != nullptr) {
		//Wyswietlenie elementu w odpowiednim kolorze
		if (node->color == NodeColor::RED) {
			string value = to_string(node->key);
			cout << " " << prefix << red << "[" << node->key << "]" << black << endl;
		}
		else {
			cout << " " << prefix << black <<"[" << node->key << "]" << endl;
		}

		RBTreeNode* next;
		if (node->left != nullptr) {
			next = node->left;
			if (node->right != nullptr) {
				print(childrenPrefix + "  |--", childrenPrefix + "  |   ", node->left);
			}
			else {
				print(childrenPrefix + "  |--", childrenPrefix + "      ", node->left);
			}
		}
		if (node->right != nullptr) {
			print(childrenPrefix + "  \\--", childrenPrefix + "      ", node->right);
		}
	}
}