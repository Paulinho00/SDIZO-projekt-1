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
};

//Element w tablicy
struct Node {
	//Wskaünik na poprzedni element
	Node* previous;
	//Wskaünik na nastepny element
	Node* next;
	//Przechowywana wartoúÊ
	int value;

	Node(int value);
	Node(int value, Node* next, Node* previous);
	~Node();

};

//Klasa reprezentujaca liste dwukierunkowa
class DoubleLinkedList {
private:
	//Wskaünik na pierwszy element listy
	Node* head;
	//Wskaünik na ostatni element listy
	Node* tail;
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

	//Wyszukiwanie indeksow na ktorym znajduje sie podana wartosc
	void findElement(int value);

	//Generowanie okreslonej liczby wartosci w strukturze
	void fillList(int amount);

private:
	//Umieszcza element w odpowiednim miejscu
	void fixUp();

	//Naprawia kopiec algorytmem Floyda
	void fixDown();
};
