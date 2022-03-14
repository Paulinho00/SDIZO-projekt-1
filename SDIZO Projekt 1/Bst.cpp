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
	left = nullptr;
	right = nullptr;
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

//Usuwa wybrany element
void Bst::deleteElement(int value) {
	//Wyszukanie wskaznikan usuwany element
	BstNode* deleteNode = findPointerToElement(value);
	if (deleteNode != nullptr) {
		BstNode* next;
		BstNode* child;
		//Sprawdzenie czy element ma potomka
		if (deleteNode->left == nullptr || deleteNode->right == nullptr) {
			next = deleteNode;
		}
		else {
			//Znalezienie nastepnika
			next = findSuccessor(deleteNode);
		}

		//Odczyt jedynego potomka nastepnika
		if (next->left != nullptr) child = next->left;
		else child = next->right;

		//Sprawdzenie czy nastepnik ma jakiegos potomka
		if (child != nullptr) {
			//Dodanie do dziecka rodzica nastepnika, 
			child->parent = next->parent;
		}

		//Sprawdzenie czy nastepnik ma rodzica
		if (next->parent == nullptr) {
			//Zmiana korzenia
			root = child;
		}
		else {
			//Sprawdzenie ktorym potomkiem jest nastepnik i podmiana u potomka nastepnika
			if (next == next->parent->left)  next->parent->left = child;
			else next->parent->right = child;
		}

		//Sprawdzenie czy trzeba zamieniac pozycje nastepnika i usuwanego elementu
		if (deleteNode != next) {
			deleteNode->key = next->key;
			//Zwolnienie pamieci
			delete next;
		}
		
	}
	else {
		cout << "Nie ma takiego elementu\n";
	}
}

//Znajduje wskaznik na dany element
BstNode* Bst::findPointerToElement(int value) {
	BstNode* currentElement = root;
	//Pêtla przeszukuj¹ca drzewo
	while (currentElement != nullptr && currentElement->key != value) {
		if (value < currentElement->key) currentElement = currentElement->left;
		else currentElement = currentElement->right;
	}
	return currentElement;
}

//Znajduje nastepnik elementu
BstNode* Bst::findSuccessor(BstNode* element) {
	//Sprawdzenie czy element ma prawego potomka
	if (element->right != nullptr) {
		//Zwrocenie nastepnika
		return findMinKey(element);
	}
	//Odczyt rodzica danego elementu
	BstNode* elementParent = element->parent;
	//Pêtla szukajaca nastepnika
	while (elementParent != nullptr && elementParent->left != element) {
		element = elementParent;
		elementParent = element->parent;
	}
	return elementParent;
}

BstNode* Bst::findMinKey(BstNode* element) {
	//Pêtla przechodz¹ca po lewych potomkach danego elementu
	while (element->left != nullptr) {
		element = element->left;
	}
	return element;
}