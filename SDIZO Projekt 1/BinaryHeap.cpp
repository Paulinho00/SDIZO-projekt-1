#include "DataStructures.h"

BinaryHeap::BinaryHeap() {
	dynArray = new DynamicArray();
}

BinaryHeap::~BinaryHeap() {
	dynArray->~DynamicArray();
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
