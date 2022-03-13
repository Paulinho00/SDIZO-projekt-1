#include "DataStructures.h"
#include <fstream>
using namespace std;

BinaryHeap::BinaryHeap() {
	dynArray = new DynamicArray();
}

BinaryHeap::~BinaryHeap() {
	dynArray->~DynamicArray();
}

//Odczytuje do kopca, dane z pliku
void BinaryHeap::readFromFile(std::string filename) {
	//Usuniecie struktury
	while(dynArray->getSize() != 0) {
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

//Dodaje element do kopca
void BinaryHeap::addElement(int value) {
	//Dopisanie elementu do tablicy
	dynArray->addElement(value);

	//Odczyt indeksu nowego elementu
	int indexOfNewElement = dynArray->getSize() - 1;
	int* array = dynArray->getArray();

	//Sprawdzamy czy dodany element to korzen drzewa
	if (indexOfNewElement == 0) return;
	else {
		bool shouldContinueFixing = true;
		while (shouldContinueFixing) {
			int indexOfParent = (indexOfNewElement - 1) / 2;
			if (array[indexOfNewElement] > array[indexOfParent]) {
				//Zamiana miejsc z rodzicem nowego elementu
				int temp = array[indexOfParent];
				array[indexOfParent] = array[indexOfNewElement];
				array[indexOfNewElement] = temp;
				indexOfNewElement = indexOfParent;
				//Sprawdzenie czy algorytm doszedl do korzenia
				if (indexOfNewElement == 0) {
					shouldContinueFixing = false;
				}
			}
			else{
				//Zatrzymanie algorytmu
				shouldContinueFixing = false;
			}
		}
	}
}

//Usuwa element ze szczytu
void BinaryHeap::deleteElement() {
	//Pobranie tablicy w ktorej przechowywane sa elementy
	int* arr = dynArray->getArray();

	//Zmiana miejsca szczytu drzewa i ostatniego elementu w drzewie
	int root = arr[0];
	arr[0] = arr[(dynArray->getSize()) - 1];
	arr[(dynArray->getSize()) - 1] = root;

	//Usuniecie ostatniego elementu
	dynArray->deleteElement();
	arr = dynArray->getArray();
	
	bool shouldContinueFixing = true;
	int currentIndex = 0;
	while (shouldContinueFixing) {
		//Indeks lewego dziecka
		int leftChild = (2 * currentIndex) + 1;
		//Indeks prawego dziecka
		int rightChild = (2 * currentIndex) + 2;

		//Sprawdzenie czy lewe dziecko jest wiêksze
		if ( (leftChild < dynArray->getSize() && (arr[leftChild] > arr[currentIndex])) || (rightChild < dynArray->getSize() && (arr[rightChild] > arr[currentIndex]))) {

			//Sprawdzenie ktory potomek jest wiekszy
			if (arr[leftChild] > arr[rightChild]) {
				//Zamiana miejsc z dzieckiem
				int temp = arr[leftChild];
				arr[leftChild] = arr[currentIndex];
				arr[currentIndex] = temp;
				currentIndex = leftChild;
			}
			else
			{
				//Zamiana miejsc z dzieckiem
				int temp = arr[rightChild];
				arr[rightChild] = arr[currentIndex];
				arr[currentIndex] = temp;
				currentIndex = rightChild;
			}
		}
		else {
			shouldContinueFixing = false;
		}
	}


}

//Wyswietla zawartosc kopca
void BinaryHeap::showElements() {

	cout << "\n";
	//Wywolanie funkcji wypisujacej
	print("", false, 0);
}

//Funkcja wypisujaca dzieci danego elementu
void BinaryHeap::print(string prefix, bool isLeft, int index) {
	if (index < dynArray->getSize()) {
		cout << prefix + (isLeft ? "|--" : "\\--") << (dynArray->getArray())[index] << "\n";
		print((prefix + (isLeft ? "|  " : "   ")), true, (index * 2 + 1));
		print((prefix + (isLeft ? "|  " : "   ")), false, (index * 2 + 2));
	}
}

