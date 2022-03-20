#include <iostream>
#include <random>
using namespace std;

//Losowanie losowej liczby int
inline int randomValue() {
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> dist(-250, 250);
	return dist(gen);
}
//Klasa reprezentujaca tablice dynamiczna
class DynamicArray {
private:
	//Wskaznik na dynamiczna tablice
	int* array;
	//Wielkosc tablicy
	long long size;
public:
	DynamicArray();

	~DynamicArray();

	//Odczytuje do tablicy, dane z pliku
	void readFromFile(std::string filename);

	//Dodaje element na koncu tablicy
	void addElement(int value);

	//Dodaje element do tablicy w okreslonym indeksie
	void addElementAtIndex(int index, int value);

	//Usuwa ostatni element w tablicy
	void deleteElement();

	//Usuwa element na podanym indeksie
	void deleteElementAtIndex(int index);

	//Wyswietla zawartosc tablicy
	void showElements();

	//Wyszukiwanie indeksow na ktorym znajduje sie podana wartosc
	void findElement(int value);

	//Generowanie okreslonej liczby wartosci w strukturze
	void fillArray(int amount);

	//Getter do tablicy dynamicznej
	int* getArray();

	//Getter do rozmiaru tablicy
	long long getSize();
};

//Element w tablicy
struct ListNode {
	//Wskaünik na poprzedni element
	ListNode* previous;
	//Wskaünik na nastepny element
	ListNode* next;
	//Przechowywana wartoúÊ
	int value;

	ListNode(int value);
	ListNode(int value, ListNode* next, ListNode* previous);
	~ListNode();

};

//Klasa reprezentujaca liste dwukierunkowa
class DoubleLinkedList {
private:
	//Wskaünik na pierwszy element listy
	ListNode* head;
	//Wskaünik na ostatni element listy
	ListNode* tail;
	//Rozmiar listy
	int size;
public:
	DoubleLinkedList();
	~DoubleLinkedList();

	//Odczytuje do listy, dane z pliku
	void readFromFile(std::string filename);

	//Dodaje element na koncu tablicy
	void addElement(int value);

	//Dodaje element do tablicy w okreslonym indeksie
	void addElementAtPosition(int position, int value);

	//Usuwa ostatni element w tablicy
	void deleteElement();

	//Usuwa element na podanym indeksie
	void deleteElementAtPosition(int position);

	//Wyswietla zawartosc tablicy
	void showElements();

	//Wyszukiwanie indeksow na ktorym znajduje sie podana wartosc
	void findElement(int value);

	//Generowanie okreslonej liczby wartosci w strukturze
	void fillList(int amount);
};

//Klasa reprezentujaca kopiec
class BinaryHeap {
private:
	DynamicArray* dynArray;

public:
	BinaryHeap();
	~BinaryHeap();

	//Odczytuje do kopca, dane z pliku
	void readFromFile(std::string filename);

	//Dodaje element do kopca
	void addElement(int value);

	//Usuwa element ze szczytu
	void deleteElement();

	//Wyswietla zawartosc kopca
	void showElements();

	//Wyszukiwanie pozycji na ktorym znajduje sie podana wartosc
	void findElement(int value);

	//Generowanie okreslonej liczby wartosci w strukturze
	void fillHeap(int amount);

private:
	//Naprawia kopiec algorytmem Floyda
	void heapCreateUp();

	//Naprawia kopiec zaczynajac od danej pozycji
	void fixDown(int index);

	//Funkcja wypisujaca dzieci danego elementu
	void print(string prefix, bool isLeft, int index);
};

//Element w BST
struct BstNode {
	//Wartosc wierzcholka
	int key;
	//Wskaznik na lewego potomka
	BstNode* left;
	//Wskaznik na prawego potomka
	BstNode* right;
	//Wskaznik na rodzica
	BstNode* parent;

	BstNode(int value);
	BstNode(int value, BstNode* parent);
	~BstNode();
};

//Drzewo poszukiwan binarnych
class Bst {
private:
	//Korzen drzewa
	BstNode* root;

	//Liczba wezlow
	int count;
public:
	Bst();
	~Bst();

	//Odczytuje do drzewa, dane z pliku
	void readFromFile(std::string filename);

	//Dodaje element do drzewa
	void addElement(int value);

	//Usuwa wybrany element
	void deleteElement(int value);

	//Wyswietla zawartosc BST
	void showElements();

	//Wyszukiwanie pozycji na ktorym znajduje sie podana wartosc
	void findElement(int value);

	//Generowanie okreslonej liczby wartosci w strukturze
	void fillBst(int amount);

	//Rownowazenie drzewa metoda DSW
	void dswBalance();
	
	//Rotacja w lewo na wybranym elemencie
	void rotateLeft(int value);

	//Rotacja w lewo na wybranym elemencie
	int rotateNodeLeft(BstNode* node);

	//Rotacja w prawo na wybranym elemencie
	void rotateRight(int value);

	//Rotacja w prawo na wybranym elemencie
	int rotateNodeRight(BstNode* node);

private:
	//Funkcja wypisujaca potomkow danego elementu
	void print(string prefix, string childrenPrefix, BstNode* node);

	//Znajduje nastepnik elementu
	BstNode* findSuccessor(BstNode* element);

	//Znajduje wskaznik na dany element
	BstNode* findPointerToElement(int value);

	//Zwraca najmniejszy klucz zaczynajac od danego elementu
	BstNode* findMinKey(BstNode* element);

	//Usuwa cale drzewo
	void dropTree(BstNode* element);

};

//Enum do elementu drzewa czerwono czarnego
enum class NodeColor {Red, Black};

//Element drzewa czerwono czarnego
struct RBTreeNode {
	//Wskaznik na rodzica
	RBTreeNode* parent;
	//Wskaznik na lewego potomka
	RBTreeNode* left;
	//Wskaznik na prawego potomka
	RBTreeNode* right;
	//Klucz/wartosc przechowywana
	int key;
	//Kolor elementu
	NodeColor color;
	
	RBTreeNode();
	~RBTreeNode();
};

//Drzewo czerwono czarne
class RedBlackTree {
private:
	//Korzen drzewa
	RBTreeNode* root;

public:
	RedBlackTree();
	~RedBlackTree();

	//Odczytuje do kopca, dane z pliku
	void readFromFile(std::string filename);

	//Dodaje element do kopca
	void addElement(int value);

	//Usuwa wybrany element
	void deleteElement(int value);

	//Wyswietla zawartosc BST
	void showElements();

	//Wyszukiwanie pozycji na ktorym znajduje sie podana wartosc
	void findElement(int value);

	//Generowanie okreslonej liczby wartosci w strukturze
	void fillBst(int amount);
};
