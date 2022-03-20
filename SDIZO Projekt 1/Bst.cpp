#include "DataStructures.h"
#include <fstream>
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
	count = 0;
}

Bst::~Bst() {
	delete root;
	count = 0;
}

//Odczytuje do kopca, dane z pliku
void Bst::readFromFile(std::string filename) {
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

//Wyswietla zawartosc BST
void Bst::showElements() {
	cout << "\n";

	//Wywolanie funkcji wypisujacej
	print("", "", root);
}

//Funkcja wypisujaca potomkow danego elementu
void Bst::print(string prefix, string childrenPrefix, BstNode* node) {
	if (node != nullptr) {
		cout << " " << prefix <<"[" << node->key <<"]" << endl;
		BstNode* next;
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
			print(childrenPrefix + "  \\--", childrenPrefix + "      ",node->right);
		}
	}
}

//Dodaje element do kopca
void Bst::addElement(int value) {
	//Sprawdzenie czy nie probujemy dodac duplikatu
	if (findPointerToElement(value) != nullptr) {
		cout << "Istnieje element o takim kluczu, dodawanie duplikatow jest zabronione\n";
		return;
	}

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
	count++;
	
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
		else {
			//Zwolnienie pamieci
			delete deleteNode;
		}
		count--;
	}
	else {
		cout << "Nie ma takiego elementu\n";
	}
}

//Wyszukiwanie pozycji na ktorym znajduje sie podana wartosc
void Bst::findElement(int value) {
	//Wyszukanie wskaznika na element
	BstNode* element = findPointerToElement(value);
	if (element != nullptr) {
		//Wyswietlenie odpowiedniego komunikatu
		cout << " Element o wartosci: " << value << endl;
		//Wyswietlenie informacji o rodzicu
		cout << "   Rodzic: ";
		if (element != root) cout << element->parent->key << endl;
		else cout << "Brak\n";
		//Wyswietlenie informacji o lewym nastepniku
		cout << "   Lewy nastepnik: ";
		if (element->left != nullptr) cout << element->left->key << endl;
		else cout << "Brak\n";
		//Wyswietleie informacji o prawym nastepniku
		cout << "   Prawy nastepnik: ";
		if (element->right != nullptr) cout << element->right->key << endl;
		else cout << "Brak\n";
		cout << endl;
	}
	else {
		cout << "Nie ma takiego elementu\n";
	}
}

//Generowanie okreslonej liczby wartosci w strukturze
void Bst::fillBst(int amount) {
	//Usuniecie struktury
	if (root != nullptr) {
		dropTree(root);
		root = nullptr;
	}

	//Uzupelnienie listy
	for (int i = 0; i < amount; i++) {
		int newValue;
		//Losowanie unikatowej wartosci
		do {
			newValue = randomValue();
		} while (findPointerToElement(newValue) != nullptr);
		addElement(newValue);
	}

}

//Rotacja w lewo na wybranym elemencie
void Bst::rotateLeft(int value) {
	BstNode* node = findPointerToElement(value);
	//Wykonanie rotacji
	int output = rotateNodeLeft(node);
	if (output == -1) cout << "Nie ma takiego elementu\n";
	else if (output == -2) cout << "Niemozliwe jest wykonanie takiej rotacji dla tego elementu\n";
}

//Rotacja w prawo na wybranym elemencie
void Bst::rotateRight(int value) {
	BstNode* node = findPointerToElement(value);
	//Wykonanie rotacji
	int output = rotateNodeRight(node);
	if (output == -1) cout << "Nie ma takiego elementu\n";
	else if(output == -2) cout << "Niemozliwe jest wykonanie takiej rotacji dla tego elementu\n";
	
}

//Rotacja w lewo na wybranym elemencie
int Bst::rotateNodeLeft(BstNode* node) {
	//Sprawdzenie czy dany element istnieje
	if (node != nullptr) {
		//Sprawdzenie czy jest spelniony warunek konieczny do rotacji
		if (node->right == nullptr) {
			return -2;
		}
		else {

			//Rotacja poprzez zmiane wskaznikow na dzieci i rodzicow
			BstNode* rightChild = node->right;
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

//Rotacja w prawo na wybranym elemencie
int Bst::rotateNodeRight(BstNode* node) {
	//Sprawdzenie czy dany element istnieje
	if (node != nullptr) {
		//Sprawdzenie czy jest spelniony warunek konieczny do rotacji
		if (node->left == nullptr) {
			return -2;
		}
		else {
			//Rotacja poprzez zmiane wskaznikow na dzieci i rodzicow
			BstNode* leftChild = node->left;
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
		return findMinKey(element->right);
	}
	//Odczyt rodzica danego elementu
	BstNode* elementParent = element->parent;
	//Pêtla szukajaca nastepnika
	while (elementParent != nullptr && elementParent->left != element) {
		element = elementParent;
		elementParent = elementParent->parent;
	}
	return elementParent;
}

//Rownowazenie drzewa metoda DSW
void Bst::dswBalance() {
	BstNode* node = root;
	while(node != nullptr){
		if (node->left != nullptr) {
			//Rotacja w prawo
			rotateNodeRight(node);
			node = node->parent;
		}
		else {
			node = node->right;
		}
	}
	
	//Obliczanie ilosci wierzcholkow na poziomach calkowicie zapelnionych
	int h = log2(count + 1);
	int m = pow(2, h) - 1;
	node = root;
	//Petla wstepnie rownowazaca drzewo
	for (int i = 0; i < count - m; i++) {
		rotateNodeLeft(node);
		if (node->parent != nullptr && node->parent->right != nullptr) node = node->parent->right;
	}

	//Petla rownowazaca drzewo
	while (m > 1) {
		m = m / 2;
		node = root;
		for (int i = 0; i < m; i++) {
			rotateNodeLeft(node);
			if(node->parent != nullptr && node->parent->right != nullptr) node = node->parent->right;
		}
	}
}



//Wyszukiwanie najmniejszej wartosci w drzewie od danego elementu
BstNode* Bst::findMinKey(BstNode* element) {
	//Pêtla przechodz¹ca po lewych potomkach danego elementu
	while (element->left != nullptr) {
		element = element->left;
	}
	return element;
}

//Usuwa cale drzewo
void Bst::dropTree(BstNode* element) {
	if (element != nullptr) {
		dropTree(element->left);
		dropTree(element->right);
		delete element;
	}
}

