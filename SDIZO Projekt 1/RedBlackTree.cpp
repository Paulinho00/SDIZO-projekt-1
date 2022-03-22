#include "DataStructures.h"
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

//Odczytuje do kopca, dane z pliku
void RedBlackTree::readFromFile(std::string filename) {
	//Usuniecie struktury
	if (root != nullptr) {
		dropTree(root);
		root = nullptr;
	}
	//Otwarcie pliku
	fstream file;
	file.open(filename, ios::in);
	//Sprawdzenie poprawnosci otwarcia
	if (file.is_open()) {

		//Odczyt rozmiaru danych zawartych w pliku
		int sizeOfData;
		file >> sizeOfData;

		//Sprawdzenie poprawnosci odczytu rozmiaru danych
		if (file.fail()) {
			cout << "Blad odczytu dlugosci pliku";
		}
		else {

			//Odczyt wszystkich danych z pliku
			for (int i = 0; i < sizeOfData; i++) {
				int value;
				file >> value;
				//Sprawdzanie czy ka¿dy element zostal poprawnie odczytany
				if (file.fail()) {
					cout << "Blad odczytu danych";
				}
				else {
					//Dodanie danej do listy
					addElement(value);
				}
				//Zamkniêcie pliku

			}
			file.close();
		}

	}
	else {
		cout << "Blad otwarcia pliku\n";
	}
}

//Wyszukiwanie pozycji na ktorym znajduje sie podana wartosc
void RedBlackTree::findElement(int value) {
	//Wyszukanie wskaznika na element
	RBTreeNode* element = findPointerToElement(value);
	if (element != nullptr) {
		//Wyswietlenie odpowiedniego komunikatu
		cout << "Element o wartosci: " << value << endl;
		//Wyswietlenie koloru
		if (element->color == NodeColor::RED) cout <<  "Kolor: " << red << "Czerwony" << black << endl;
		else cout << "Kolor: Czarny" << endl;
		//Wyswietlenie informacji o rodzicu
		cout << "Rodzic: ";
		if (element != root) cout << element->parent->key << endl;
		else cout << "Brak\n";
		//Wyswietlenie informacji o lewym nastepniku
		cout << "Lewy nastepnik: ";
		if (element->left != nullptr) cout << element->left->key << endl;
		else cout << "Brak\n";
		//Wyswietleie informacji o prawym nastepniku
		cout << "Prawy nastepnik : ";
		if (element->right != nullptr) cout << element->right->key << endl;
		else cout << "Brak\n";
		cout << endl;
	}
	else {
		cout << "Nie ma takiego elementu\n";
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
		fixColorAfterInsertion(newElement);
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
void RedBlackTree::fixColorAfterInsertion(RBTreeNode* node) {
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
				fixColorAfterInsertion(grandParent);
			}
			//Sprawdzenie czy wujek jest czarny i nowy element jest lewym potomkiem
			else if ((uncle == nullptr || uncle->color == NodeColor::BLACK) && grandParent->left == parent) {
				if (parent->left == node) leftLeftFix(grandParent, parent);
				else leftRightFix(grandParent, parent);
				
			}
			//Sprawdzenie czy wujek jest czarny i nowy element jest prawym potomkiem
			else if ((uncle == nullptr || uncle->color == NodeColor::BLACK) && grandParent->right == parent) {
				if (parent->right == node) rightRightFix(grandParent, parent);
				else rightLeftFix(grandParent, parent);
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

//Usuwa wybrany element
void RedBlackTree::deleteElement(int value) {
	//Wyszukanie wskaznikan usuwany element, nastepnik i rodzic usuwanego elementu
	RBTreeNode* deleteNode = findPointerToElement(value);
	if (deleteNode != nullptr) {
		deleteElementByPointer(deleteNode);
	}
	else {
		cout << "Nie ma takiego elementu\n";
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

//Naprawianie koloru gdy element jest prawym potomkiem, prawego potomka dziadka
void RedBlackTree::rightRightFix(RBTreeNode* grandParent, RBTreeNode* parent) {
	rotateNodeLeft(grandParent);
	//Zmiana koloru rodzica na przeciwny
	if (parent->color == NodeColor::BLACK) parent->color = NodeColor::RED;
	else parent->color = NodeColor::BLACK;

	//Zmiana koloru dziadka na przeciwny
	if (grandParent != nullptr) {
		if (grandParent->color == NodeColor::BLACK) grandParent->color = NodeColor::RED;
		else grandParent->color = NodeColor::BLACK;
	}

}

//Naprawianie koloru gdy element jest lewym potomkiem, prawego potomka dziadka
void RedBlackTree::rightLeftFix(RBTreeNode* grandParent, RBTreeNode* parent) {
	rotateNodeRight(parent);
	rightRightFix(grandParent, parent->parent);

}

//Naprawianie koloru gdy element jest lewym potomkiem, lewego potomka dziadka
void RedBlackTree::leftLeftFix(RBTreeNode* grandParent, RBTreeNode* parent) {
	rotateNodeRight(grandParent);

	//Zmiana koloru rodzica na przeciwny
	if (parent->color == NodeColor::BLACK) parent->color = NodeColor::RED;
	else parent->color = NodeColor::BLACK;

	//Zmiana koloru dziadka na przeciwny
	if (grandParent != nullptr) {
		if (grandParent->color == NodeColor::BLACK) grandParent->color = NodeColor::RED;
		else grandParent->color = NodeColor::BLACK;
	}
}

//Naprawianie koloru gdy element jest prawym potomkiem, lewego potomka dziadka
void RedBlackTree::leftRightFix(RBTreeNode* grandParent, RBTreeNode* parent) {
	rotateNodeLeft(parent);
	leftLeftFix(grandParent, parent->parent);
}

//Zwraca najmniejszy klucz zaczynajac od danego elementu
RBTreeNode*  RedBlackTree::findMinKey(RBTreeNode* element) {
	//Pêtla przechodz¹ca po lewych potomkach danego elementu
	while (element->left != nullptr) {
		element = element->left;
	}
	return element;
}

//Znajduje nastepnik elementu
RBTreeNode* RedBlackTree::findSuccessor(RBTreeNode* element) {
	RBTreeNode* temp = element;
	while (temp->left != nullptr) {
		temp = temp->left;
	}
	return temp;
}

//Znajduje element zastepujacy usuwany
RBTreeNode* RedBlackTree::findReplacement(RBTreeNode* element) {
	//Znajduje nastepnik gdy element ma dwoje dzieci
	if (element->left != nullptr && element->right != nullptr)
		return findSuccessor(element->right);

	//Zwraca null kiedy element jest lisciem
	if (element->left == nullptr && element->right == nullptr)
		return nullptr;

	//Zwraca dziecko kiedy element ma jedno dziecko
	if (element->left != nullptr)
		return element->left;
	else
		return element->right;
}

//Naprawa koloru po usunieciu czarnego liscia
void RedBlackTree::fixDoubleBlack(RBTreeNode* element) {
	//Sprawdzenie czy element jest korzeniem
	if (element == root)
		return;

	RBTreeNode* sibling;
	RBTreeNode* parent = element->parent;
	//Zmiena przechowujaca informacje czy rodzenstwo jest lewym dzieckiem
	bool isOnLeft;

	//Odczyt rodzenstwa elementu
	if (parent == nullptr) {
		sibling = nullptr;
	}
	else {
		if (parent->left == element) {
			sibling = parent->right;
			isOnLeft = false;
		}
		else {
			sibling = parent->left; 
			isOnLeft = true;
		}
	}

	//Sprawdzenie czy element ma rodzenstwo
	if (sibling == nullptr) {
		//Jesli nie ma to naprawa idzie w gore drzewa
		fixDoubleBlack(parent);
	}
	else {
		if (sibling->color == NodeColor::RED) {
			parent->color = NodeColor::RED;
			sibling->color = NodeColor::BLACK;
			if (isOnLeft) {
				rotateNodeRight(parent);
			}
			else {
				rotateNodeLeft(parent);
			}
			fixDoubleBlack(element);
		}
		else {
			//Sprawdzenie czy rodzenstwo ma czerwone dziecko
			bool hasSiblingRedChild = (sibling->left != nullptr && sibling->left->color == NodeColor::RED) || (sibling->right != nullptr && sibling->right->color == NodeColor::RED);
			if (hasSiblingRedChild) {
				//Sprawdzenie czy czerwone dziecko jest z lewej strony
				if (sibling->left != nullptr && sibling->left->color == NodeColor::RED) {
					//Sprawdzenie czy rodzenstwo elementu jest z lewej strony
					if (isOnLeft) {
						//Czerwone dziecko po lewej, rodzenstwo po lewej
						sibling->left->color = sibling->color;
						sibling->color = parent->color;
						rotateNodeRight(parent);
					}
					else {
						//Czerwone dziecko po lewej, rodzenstwo po prawej
						sibling->left->color = parent->color;
						rotateNodeRight(sibling);
						rotateNodeLeft(parent);
					}
				}
				else {
					//Sprawdzenie czy rodzenstwo elementu jest z lewej strony
					if (isOnLeft) {
						//Czerwone dziecko po prawej, rodzenstwo po lewej
						sibling->right->color = parent->color;
						rotateNodeLeft(sibling);
						rotateNodeRight(parent);
					}
					else {
						//Czerwone dziecko po prawej, rodzenstwo po prawej
						sibling->right->color = sibling->color;
						sibling->color = parent->color;
						rotateNodeLeft(parent);
					}
				}
				parent->color = NodeColor::BLACK;
			}
			else {
				//Przypadek gdy rodzenstwo ma dwoje czarnych dzieci
				sibling->color = NodeColor::RED;
				if (parent->color == NodeColor::BLACK)
					fixDoubleBlack(parent);
				else {
					parent->color = NodeColor::BLACK;
				}
			}
		}
	} 
}

//Usuwanie elementu wskazanego przez wskaznik
void RedBlackTree::deleteElementByPointer(RBTreeNode* deleteNode) {
	RBTreeNode* next = findReplacement(deleteNode);
	RBTreeNode* parent = deleteNode->parent;

	//Sprawdzenie czy nastepnik istnieje
	if (next == nullptr) {
		//Sprawdzenie czy usuwany element to korzen
		if (deleteNode == root) {
			//Usuniecie korzenia
			root = nullptr;
		}
		else {
			//sprawdzenie czy usuwany element i lisc sa czarni
			if ((next == nullptr || next->color == NodeColor::BLACK) && (deleteNode->color == NodeColor::BLACK)) {
				//Nastepnik i usuwany element sa czarni
				fixDoubleBlack(deleteNode);
			}
			else {
				RBTreeNode* siblingOfDeleteNode;
				//Odczyt rodzenstwa
				if (deleteNode->parent == nullptr) {
					siblingOfDeleteNode = nullptr;
				}
				else {
					if (deleteNode->parent->left == deleteNode) siblingOfDeleteNode = deleteNode->parent->right;
					else siblingOfDeleteNode = deleteNode->parent->left;
				}

				//Nastepnik lub usuwany element jest czerwony
				if (siblingOfDeleteNode != nullptr) {
					siblingOfDeleteNode->color = NodeColor::RED;
				}
			}

			if (deleteNode->parent->left == deleteNode) parent->left = nullptr;
			else parent->right = nullptr;
		}

		delete deleteNode;
		return;
	}

	if (deleteNode->left == nullptr || deleteNode->right == nullptr) {
		//Usuwany element ma tylko jednego potomka
		if (deleteNode == root) {
			//Usuwany element jest korzeniem
			deleteNode->key = next->key;
			deleteNode->left = deleteNode->right = nullptr;
			delete next;
		}
		else {
			//Usuniecie elementu z drzewa i przesuniecie nastepnika w gore
			if (parent->left == deleteNode) parent->left = next;
			else parent->right = next;

			delete deleteNode;
			next->parent = parent;

			if ((next == nullptr || next->color == NodeColor::BLACK) && (deleteNode->color == NodeColor::BLACK)) {
				//Nastepnik i usuwany element sa czarni
				fixDoubleBlack(deleteNode);
			}
			else {
				//Nastepnik lub usuwany element jest czerwony
				next->color = NodeColor::BLACK;
			}
		}
		return;
	}

	//Usuwany element ma dwoje dzieci
	//Zamiana wartosci
	int temp;
	temp = next->key;
	next->key = deleteNode->key;
	deleteNode->key = temp;
	deleteElementByPointer(next);
}