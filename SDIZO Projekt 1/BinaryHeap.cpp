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
				//Zamian miejsc z rodzicem nowego elementu
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
