#include <iostream>
#include <fstream>
#include <time.h>
#include <random>
#include "DataStructures.h"
using namespace std;

ListNode::ListNode(int value) {
	this->value = value;
	previous = nullptr;
	next = nullptr;
}

ListNode::ListNode(int value, ListNode* next, ListNode* previous) {
	this->value = value;
	this->previous = previous;
	this->next = next;
}

ListNode::~ListNode() {
	previous = nullptr;
	next = nullptr;
}

DoubleLinkedList::DoubleLinkedList() {
	head = nullptr;
	tail = nullptr;
	size = 0;
}

DoubleLinkedList::~DoubleLinkedList() {
	if (head != nullptr) {
		size = 0;
		bool shouldContinue = true;
		ListNode* currentNode;
		ListNode* nextNode = head;
		//Usuniecie wszystkich elementow
		while (shouldContinue) {
			currentNode = nextNode;
			if (currentNode->next == nullptr) {
				shouldContinue = false;
			}
			else {
				nextNode = currentNode->next;
			}
			delete currentNode;
			tail = nullptr;
			head = nullptr;
			tail = nullptr;
		}
	}
}

//Odczytuje do tablicy, dane z pliku
void DoubleLinkedList::readFromFile(std::string filename) {
	//Usuniecie struktury
	while (head != nullptr) {
		deleteElement();
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

//Dodaje element na koncu tablicy
void DoubleLinkedList::addElement(int value) {
	//Sprawdzenie czy lista jest zainicjalizowana
	if (head == nullptr) {
		//Inicjalizacja listy
		ListNode* newNode = new ListNode(value);
		head = newNode;
		tail = newNode;
		size++;
		return;
	}

	//Odczyt ostatniego elementu
	ListNode* lastElement = tail;

	//Zainicjowanie nowego elementu
	ListNode* newElement = new ListNode(value);
	lastElement->next = newElement;
	newElement->previous = lastElement;
	size++;

	//Zmiana ogona listy
	tail = newElement;

}

//Dodaje element do tablicy w okreslonym indeksie
void DoubleLinkedList::addElementAtPosition(int position, int value) {
	//Sprawdzenie czy tablica jest zainicjalizowana lub czy element ma zostac dodany na koncu
	if ((head == nullptr && position == 0) || position == size) {
		addElement(value);
	}

	//Sprawdzenie czy dodanie elementu na tej pozycji jest mozliwe
	if (position > size || position < 0) {
		cout << "Dodanie elementu na tej pozycji nie jest mozliwe\n";
		return;
	}

	//Sprawdzenie czy element ma zostac dodany na poczatku
	if (position == 0) {
		//Inicjalizacja nowego elementu
		ListNode* newElement = new ListNode(value);
		newElement->next = head;
		size++;

		//Zmiana glowy listy
		head->previous = newElement;
		head = newElement;
		return;
	}

	ListNode* currentNode = head;
	//Odczyt elementu, ktory ma byc przed nowym elementem
	for (int i = 0; i < position - 1; i++) {
		currentNode = currentNode->next;
	}

	//Utworzenie i inicjalizacja nowego elementu
	ListNode* newElement = new ListNode(value, currentNode->next, currentNode);
	//Zmiana wskaznikow w poprzedzajacym i nastepujacym elemencie
	ListNode* elementAfterNewElement = currentNode->next;
	elementAfterNewElement->previous = newElement;
	currentNode->next = newElement;
	size++;
}

//Usuwa ostatni element w tablicy
void DoubleLinkedList::deleteElement() {
	//Sprawdzenie czy lista nie jest pusta
	if (head == nullptr) {
		cout << "Lista jest pusta\n";
		return;
	}

	//Sprawdzenie czy jest to jedyny element na liscie
	if (size == 1) {
		//Usuniecie jedynego elementu
		tail = nullptr;
		delete head;
		head = nullptr;
		size--;
		return;
	}

	//Usuniecie elementu
	ListNode* elementToDelete = tail;
	tail = elementToDelete->previous;
	ListNode* penultimateElement = elementToDelete->previous;
	penultimateElement->next = nullptr;
	delete elementToDelete;
	size--;
}

//Usuwa element na podanym indeksie
void DoubleLinkedList::deleteElementAtPosition(int position) {
	//Sprawdzenie czy dodanie elementu na tej pozycji jest mozliwe
	if (position >= size || position < 0) {
		cout << "Nie ma takiej pozycji w liscie\n";
		return;
	}

	//Sprawdzenie czy lista nie jest pusta
	if (head == nullptr) {
		cout << "Lista jest pusta\n";
		return;
	}

	//Sprawdzenie czy usuwany element jest ostatnim w liscie
	if (position == size - 1) {
		deleteElement();
		return;
	}

	//Sprawdzenie czy usuwany element jest na poczatku listy
	if (position == 0) {
		//Odczyt pierwszego i drugiego elementu z listy
		ListNode* elementToDelete = head;
		ListNode* secondElement = elementToDelete->next;

		//Usuniecie wskaznika na poprzedni element w drugim elemencie listy
		secondElement->previous = nullptr;
		//Ustawienie glowy listy
		head = secondElement;
		//Usuniecie elementu
		delete elementToDelete;
		size--;
		return;
	}

	//Wyszukanie elementu do usuniêca
	ListNode* currentNode = head;
	for (int i = 0; i < position; i++) {
		currentNode = currentNode->next;
	}

	//Usuniecie elementu
	ListNode* previousElement = currentNode->previous;
	previousElement->next = currentNode->next;
	currentNode->next->previous = previousElement;
	delete currentNode;
	size--;
}

//Wyswietla zawartosc tablicy
void DoubleLinkedList::showElements() {
	//Sprawdzenie czy lista nie jest pusta
	if (head == nullptr) {
		cout << "Lista jest pusta\n";
		return;
	}

	//Wypisywanie listy
	cout << "Wartosci: ";
	bool hasNextElement = true;
	ListNode* currentNode = head;
	while (hasNextElement) {
		cout << currentNode->value << ", ";

		//Sprawdzenie czy istnieje nastepny element na liscie
		if (currentNode->next == nullptr) {
			hasNextElement = false;
		}
		else {
			//Odczyt nastepnego elementu
			currentNode = currentNode->next;
		}
	}

	//Wypisywanie listy w odwrotnej kolejnosci
	cout << "\nWartosc w odwrotnej kolejnosc: ";
	hasNextElement = true;
	currentNode = tail;
	while (hasNextElement) {
		cout << currentNode->value << ", ";

		//Sprawdzenie czy doszlismy do pierwszego elementu listy
		if (currentNode->previous == nullptr) {
			hasNextElement = false;
		}
		else {
			//Odczyt kolejnego elementu
			currentNode = currentNode->previous;
		}
	}
	cout << "\n";
}

//Wyszukiwanie indeksow na ktorym znajduje sie podana wartosc
void DoubleLinkedList::findElement(int value) {
	//Sprawdzenie czy lista jest pusta
	if (head == nullptr) {
		cout << "Tablica jest pusta\n";
		return;
	}

	cout << "\nLiczby o zadanej wartosci znajduja sie na indeksach: ";
	int position = 0;
	ListNode* element = head;
	while (element != nullptr) {
		if (element->value == value) {
			cout << position << ", ";
		}
		element = element->next;
		position++;
	}
}


//Generowanie okreslonej liczby wartosci w strukturze
void DoubleLinkedList::fillList(int amount) {
	//Usuniecie struktury
	while (head != nullptr) {
		deleteElement();
	}

	//Wypelnienie listy
	for (int i = 0; i < amount; i++) {
		int newValue = randomValue();
		addElement(newValue);
	}
}