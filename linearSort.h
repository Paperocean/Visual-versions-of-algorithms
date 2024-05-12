#ifndef LINEARSORT_H
#define LINEARSORT_H

#include <iostream>
using namespace std;

// how it works:
// 1. We start from the second element of the array, and we compare it with the first element.
// 2. If the second element is smaller than the first element, we swap them.
// 3. We continue this process until the second element is greater than the first element.
// 4. We then move to the third element and compare it with the second element and so on.
// okay what is the diffetence between bubble sort and insertion sort?
// bubble sort compares the current element with the next element, and if the current element is greater than the next element, it swaps them.
// it is very similar to insertion sort, but the difference is that bubble sort compares the current element with the next element, and if the current element is greater than the next element, it swaps them.
// insertion sort compares the current element with the previous element, and if the current element is smaller than the previous element, it swaps them.

class LinearSort {
public:
	// bubble sort is about bubbling
	// because we bubble the largest element to the end of the array.
	void bubbleSort(int arr[], int n) {
		for (int i = 0; i < n - 1; i++) {
			for (int j = 0; j < n - i - 1; j++) {
				if (arr[j] > arr[j + 1])
					swap(arr[j], arr[j + 1]);
			}
		}
	}

	// why insertion sort is about insertion?
	// because we insert the current element into the correct position in the sorted part of the array.
	void insertionSort(int arr[], int n) {
		for (int i = 1; i < n; i++) {
			int key = arr[i];
			int j = i - 1;
			while (j >= 0 && arr[j] > key) {
				arr[j + 1] = arr[j];
				j = j - 1;
			}
		}
	}

	// selection sort is about selection
	// because we select the minimum element from the unsorted part of the array and swap it with the first element of the unsorted part of the array.
	// it can be also named as swap sort?
	// because we swap the minimum element with the first element of the unsorted part of the array.
	void selectionSort(int arr[], int n) {
		for (int i = 0; i < n - 1; i++) {
			int minIndex = i;
			for (int j = i + 1; j < n; j++) {
				if (arr[j] < arr[minIndex])
					minIndex = j;
			}
			swap(arr[minIndex], arr[i]);
		}
	}

	void printArray(int arr[], int n) {
		for (int i = 0; i < n; i++) {
			cout << arr[i] << " ";
		}
		cout << endl;
	}
};

#endif // LINEARSORT_H