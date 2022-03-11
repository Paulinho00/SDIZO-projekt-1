#include <iostream>
#include <fstream>
#include <time.h>
#include "DataStructures.h"
using namespace std;

//Losowanie losowej liczby int
int randomValue() {
	//Zakres losowania
	int range = 500 - 0 + 1;
	//Losowanie liczby
	int randonNumber = rand() % range - 250;
	return randonNumber;
}


DynamicArray::DynamicArray() {
	array = nullptr;
	size = 0;
}
DynamicArray::~DynamicArray() {
	delete[] array;
}

//Odczytuje do tablicy, dane z pliku
void DynamicArray::readFromFile(string filename) {
	//Usuniecie struktury
	if (array != nullptr) {
		delete[] array;
		size = 0;
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
					//Dodanie danej do tablicy
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
void DynamicArray::addElement(int value) {
	//Sprawdzenie czy tablica jest zainicjalizowana
	if (array == nullptr) {
		//Inicjalizacja tablicy i zwiekszenie rozmiaru
		size++;
		array = new int[size];
		array[0] = value;
		return;
	}

	//Zwiekszenie rozmiaru
	size++;
	//Stworzenie i wypelnienie buforu
	int* buff = new int[size];
	for (int i = 0; i < size - 1; i++) {
		buff[i] = array[i];
	}
	buff[size - 1] = value;

	//Zastapienie starej tablicy nowa
	delete[] array;
	array = buff;
}

//Dodaje element do tablicy w okreslonym indeksie
void DynamicArray::addElementAtIndex(int index, int value) {
	//Sprawdzenie czy tablica jest zainicjalizowana
	if (array == nullptr && index == 0) {
		//Inicjalizacja tablicy i zwiekszenie rozmiaru
		size++;
		array = new int[size];
		array[0] = value;
		return;
	}
	//Sprawdzenie czy wybrany indeks jest poprawny
	if (index > size || index < 0) {
		cout << "Nie ma takiego indeksu w tablicy\n\n";
		return;
	}

	//Sprawdzenie czy element ma zostac dodany na koncu
	if (index == size) {
		addElement(value);
		return;
	}

	//Zwiêkszenie rozmiaru tablicy i utworzenie buforu
	size++;
	int* buff = new int[size];

	//Przepisanie tablicy do buforu z uwzglednieniem nowego elementu
	for (int i = 0; i < index; i++) {
		buff[i] = array[i];
	}
	buff[index] = value;
	for (int i = index + 1; i < size; i++) {
		buff[i] = array[i - 1];
	}

	//Zastapienie starej tablicy nowa
	delete[] array;
	array = buff;
}

//Usuwa ostatni element w tablicy
void DynamicArray::deleteElement() {
	//Sprawdzenie czy tablica jest pusta
	if (array == nullptr) {
		cout << "Tablica jest pusta\n";
		return;
	}
	//Sprawdzenie czy tablica ma tylko jeden element
	if (size == 1) {
		//Usuniecie tablicy
		size--;
		delete[] array;
		array = nullptr;
		return;
	}

	//Zmniejszenie rozmiaru i utworzenie buforu
	size--;
	int* buff = new int[size];

	//Przepisanie tablicy bez ostatniego elementu
	for (int i = 0; i < size; i++) {
		buff[i] = array[i];
	}

	//Zastapienie starej tablicy nowa
	delete[] array;
	array = buff;

}

//Usuwa element na podanym indeksie
void DynamicArray::deleteElementAtIndex(int index) {
	//Sprawdzenie czy wybrany indeks jest poprawny
	if (index >= size || index < 0) {
		cout << "Nie ma takiego indeksu w tablicy\n\n";
		return;
	}

	//Sprawdzenie czy tablica jest pusta
	if (array == nullptr) {
		cout << "Tablica jest pusta\n";
		return;
	}

	//Zmniejszenie rozmiaru i utworzenie buforu
	size--;
	int* buff = new int[size];

	//Przepisanie tablicy bez usuwanego elementu
	for (int i = 0; i < index; i++) {
		buff[i] = array[i];
	}
	for (int i = index; i < size; i++) {
		buff[i] = array[i + 1];
	}

	//Zastapienie starej tablicy nowa
	delete[] array;
	array = buff;

}

//Wyswietla zawartosc tablicy
void DynamicArray::showElements() {

	//Wypisywanie tablicy
	cout << "Wartosci: ";
	for (int i = 0; i < size; i++) {
		cout << array[i] << ", ";
	}
	cout << "\n";
	
	//Wypisywanie w odwrotnej kolejnosci
	cout << "Odwrocona kolejnosc: ";
	for (int i = size - 1; i >= 0; i--) {
		cout << array[i] << ", ";
	}
	cout << "\n";

}

//Wyszukiwanie indeksow na ktorym znajduje sie podana wartosc
void DynamicArray::findElement(int value) {
	//Zmienna przechowujaca informacje czy znaleziono taka wartosc
	bool foundValues = false;

	cout << "\nLiczby o zadanej wartosci znajduja sie na indeksach: ";

	//Petla przeszukujaca
	for (int i = 0; i < size; i++) {
		if (array[i] == value) {
			//Wyswietlenie odpowiedniego indeksu
			cout << i << " ";
			//Zapisanie informacji o znalezieniu wartosci
			foundValues = true;
		}
	}
	//Komunikat o braku takiej wartosci
	if (!foundValues) cout << "Nie ma takiej wartosci ";
	cout << "\n";
}

//Generowanie okreslonej liczby wartosci w strukturze
void DynamicArray::fillArray(int amount) {
	//Usuniecie istniejacej tablicy
	if (array != nullptr) {
		delete[] array;
		size = 0;
	}

	//Wygenerowanie seeda do losowania
	srand(time(NULL));
	//Alokacja nowej tablicy
	array = new int[amount];

	//Wypelnienie tablicy losowymi elementami
	for (int i = 0; i < amount; i++) {
		int value = randomValue();
		array[i] = value;
		size++;
	}
}




Node::Node(int value) {
	this->value = value;
	previous = nullptr;
	next = nullptr;
}

Node::Node(int value, Node* next, Node* previous) {
	this->value = value;
	this->previous = previous;
	this->next = next;
}

Node::~Node() {
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
		Node* currentNode;
		Node* nextNode = head;
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
	if (head != nullptr) {
		size = 0;
		bool shouldContinue = true;
		Node* currentNode;
		Node* nextNode = head;
		//Usuniecie wszystkich elementow
		while (shouldContinue) {
			currentNode = nextNode;
			if (currentNode->next == nullptr) {
				shouldContinue = false;
			}
			else {
				nextNode = currentNode->next;
			}
		}
		head = nullptr;
		tail = nullptr;
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
		Node* newNode = new Node(value);
		head = newNode;
		tail = newNode;
		size++;
		return;
	}
	
	//Odczyt ostatniego elementu
	Node* lastElement = tail;

	//Zainicjowanie nowego elementu
	Node* newElement = new Node(value);
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
		Node* newElement = new Node(value);
		newElement->next = head;
		size++;
		
		//Zmiana glowy listy
		head->previous = newElement;
		head = newElement;
		return;
	}
	
	Node* currentNode = head;
	//Odczyt elementu, ktory ma byc przed nowym elementem
	for (int i = 0; i < position-1; i++) {
		currentNode = currentNode->next;
	}

	//Utworzenie i inicjalizacja nowego elementu
	Node* newElement = new Node(value, currentNode->next, currentNode);
	//Zmiana wskaznikow w poprzedzajacym i nastepujacym elemencie
	Node* elementAfterNewElement = currentNode->next;
	elementAfterNewElement->previous = newElement;
	currentNode->next = newElement;
	size++;
}

//Usuwa ostatni element w tablicy
void DoubleLinkedList::deleteElement(){
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
	Node* elementToDelete = tail;
	tail = elementToDelete->previous;
	Node* penultimateElement = elementToDelete->previous;
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
		Node* elementToDelete = head;
		Node* secondElement = elementToDelete->next;

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
	Node* currentNode = head;
	for (int i = 0; i < position; i++) {
		currentNode = currentNode->next;
	}

	//Usuniecie elementu
	Node* previousElement = currentNode->previous;
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
	Node* currentNode = head;
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
	Node* element = head;
	while(element != nullptr) {
		if (element->value == value) {
			cout << position << ", ";
		}
		element = element->next;
		position++;
	}
}



