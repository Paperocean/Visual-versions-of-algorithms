#ifndef BASICTRAVERSAL_H
#define BASICTRAVERSAL_H

#include <iostream>
using namespace std;

class BasicTraversal {
public:
	void linearTraversal(int arr[], int size, int key) {
		for (int i = 0; i < size; i++) {
			if (arr[i] == key) {
				cout << "Key found at index " << i << endl;
				return;
			}
		}
		cout << "Key not found" << endl;
	}

	void reverseTraversal(int arr[], int size, int key) {
		for (int i = size - 1; i >= 0; i--) {
			if (arr[i] == key) {
				cout << "Key found at index " << i << endl;
				return;
			}
		}
		cout << "Key not found" << endl;
	}

	void binaryTraversal(int arr[], int size, int key) {
		int left = 0, right = size - 1;
		int mid = (left + right) / 2;

		while (left <= right) {
			if (arr[mid] == key) {
				cout<< "Key found at index " << mid << endl;
				return;
			}
			else if (key < arr[mid]) {
				right = mid - 1;
			}
			else {
				left = mid + 1;
			}
			mid = (left + right) / 2;
		}
		cout << "Key not found" << endl;
	}
};

#endif // !BASICTRAVERSAL_H