#include <iostream>

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
	//Wska�nik na poprzedni element
	Node* previous;
	//Wska�nik na nastepny element
	Node* next;
	//Przechowywana warto��
	int value;

	Node(int value);
	~Node();

};

//Klasa reprezentujaca liste dwukierunkowa
class DoubleLinkedList {
private:
	//Wska�nik na pierwszy element listy
	Node* head;
	//Wska�nik na ostatni element listy
	Node* tail;
public:
	DoubleLinkedList();
	~DoubleLinkedList();

	//Odczytuje do tablicy, dane z pliku
	void readFromFile(std::string filename);

	//Dodaje element na koncu tablicy
	void addElement(int value);

	//Dodaje element do tablicy w okreslonym indeksie
	void addElementAtPosition(int position, int value);

	//Usuwa ostatni element w tablicy
	void deleteElement();

	//Usuwa element na podanym indeksie
	void deleteElementAtPosition(int Position);

	//Wyswietla zawartosc tablicy
	void showElements();

	//Wyszukiwanie indeksow na ktorym znajduje sie podana wartosc
	void findElement(int value);

	//Generowanie okreslonej liczby wartosci w strukturze
	void fillList(int amount);
};
