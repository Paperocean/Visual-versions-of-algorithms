#ifndef ADVANCESORT_H
#define ADVANCESORT_H

#include <iostream>
using namespace std;

class AdvanceSort {
public:
	void merge(int arr[], int temp[], int start, int mid, int end) {
		int i = start, j = mid + 1, k = 0;

		while (i <= mid && j <= end) {
			if (arr[i] < arr[j]) {
				temp[k++] = arr[i++];
			}
			else {
				temp[k++] = arr[j++];
			}
		}

		while (i <= mid) {
			temp[k++] = arr[i++];
		}
		while (j <= end) {
			temp[k++] = arr[j++];
		}

		for (int i = start; i <= end; i++) {
			arr[i] = temp[i - start];
		}

		delete[] temp;
	}

	void mergeSort(int arr[], int start, int end) {
		int *temp = new int[end - start + 1];
		int mid = (start + end) / 2;
		mergeSort(arr, start, mid);
		mergeSort(arr, mid + 1, end);
		merge(arr, temp, start, mid, end);
	}

	void quickSort(int arr[], int start, int end) {
		if (start >= end) return;
		int mid = (end + start) / 2;
		int pivot = rand() % (end - start + 1) + start;
		swap(arr[pivot], arr[mid]);

		int i = start, j = end, pivotV = arr[mid];
		while (i <= j) {
			while (arr[i] < pivotV) i++;
			while (arr[j] > pivotV) j--;
			if (i <= j) {
				swap(arr[i], arr[j]);
				i++;
				j--;
			}
		}

		quickSort(arr, start, j);
		quickSort(arr, i, end);
	}

	void bucketSort(int arr[], int n) {
		int max = arr[0];

		for (int i = 1; i < n; i++) {
			if (arr[i] > max) {
				max = arr[i];
			}
		}

		int* bucket = new int[max + 1]();

		for (int i = 0; i < n; i++) {
			bucket[arr[i]]++;
		}

		for (int i = 0, j = 0; i <= max; i++) {
			while (bucket[i] > 0) {
				arr[i] = i;
				bucket[i]--;
			}
		}

		delete[] bucket;
	}
};

#endif // !ADVANCESORT_H
