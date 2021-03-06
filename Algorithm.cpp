// Algorithm.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdlib.h>
#include <random>
#include <iostream>
#include <time.h>

using namespace std;

// Struct Of Linked List
struct Node
{
	int item;
	Node *next;
};

// Linked List Display Printer
void LinkedListPrint(Node *pr) {
	while (pr != NULL) {
		printf("%d", pr->item);
		printf("  ");
		pr = pr->next;
	}
}

// Random Integer Generator
template<class Temp>
void Random(Temp ar[], int size) {
	for (int i = 0; i<size; i++) {
		ar[i] = rand() % 1000 + 1;
	}
}

// Swap Part
template<class Temp>
void swap(Temp *first, Temp *second) {
	Temp tmp = *first;
	*first = *second;
	*second = tmp;
}

// Two Way Quick Sort Part
template<class Temp>
void TwoWayQuickSort(Temp ar[], int lft, int rght) {
	int i = lft, j = rght;
	Temp piv = ar[(lft + rght) / 2];

	while (i <= j) {
		while (ar[i] < piv) {
			i++;
		}
		while (ar[j] > piv) {
			j--;
		}
		if (i <= j) {
			swap(ar[i], ar[j]);
			i++;
			j--;
		}
	}

	if (lft < i - 1) {
		TwoWayQuickSort(ar, lft, i - 1);
	}
	if (i < rght) {
		TwoWayQuickSort(ar, i, rght);
	}
}

// Insertion Sort Part
template<class Temp>
void InsertionSort(Temp ar[], int size)
{
	int hold;
	int j;
	for (int i = 1; i < size; i++)
	{
		hold = ar[i];
		j = i - 1;
		while (j >= 0 && ar[j] > hold)
		{
			ar[j + 1] = ar[j];
			j = j - 1;
		}
		ar[j + 1] = hold;
	}
}

// Three Way Quick Sort Part
template<class Temp>
void ThreeWayQuickSortPartition(Temp a[], int low, int size, int &i, int &j)
{
	if (size - low <= 1)
	{
		if (a[size] < a[low])
			swap(&a[size], &a[low]);
		i = low;
		j = size;
		return;
	}
	int mid = low;
	int piv = a[size];
	while (mid <= size)
	{
		if (a[mid]<piv)
			swap(&a[low++], &a[mid++]);
		else if (a[mid] == piv)
			mid++;
		else if (a[mid]>piv)
			swap(&a[mid], &a[size--]);
	}
	i = low - 1;
	j = mid;
}

template<class Temp>
void ThreeWayQuickSort(Temp ar[], int low, int size)
{
	if (low >= size) {
		return;
	}
	int i, j;
	ThreeWayQuickSortPartition(ar, low, size, i, j);
	ThreeWayQuickSort(ar, low, i);
	ThreeWayQuickSort(ar, j, size);
}

// Radix Sort Part
template<class Temp>
int MaxValue(Temp ar[], int n)
{
	int max = ar[0];
	for (int i = 1; i < n; i++)
		if (ar[i] > max)
			max = ar[i];
	return max;
}

template<class Temp>
void RSort(Temp ar[], int n, int exp)
{
	int* out = new int[n];
	int i, count[10] = { 0 };
	for (i = 0; i < n; i++)
	{
		count[(ar[i] / exp) % 10]++;
	}
	for (i = 1; i < 10; i++)
	{
		count[i] += count[i - 1];
	}
	for (i = n - 1; i >= 0; i--)
	{
		out[count[(ar[i] / exp) % 10] - 1] = ar[i];
		count[(ar[i] / exp) % 10]--;
	}
	for (i = 0; i < n; i++)
		ar[i] = out[i];
}

template<class Temp>
void RadixSort(Temp ar[], int size)
{
	int max = MaxValue(ar, size);
	for (int i = 1; max / i > 0; i *= 10)
		RSort(ar, size, i);
}

// Main Of The program
int main(int argc, char** argv) {
	int size;
	cout << "Write a size of array:", cin >> size;
	int* ar = new int[size];
	Random(ar, size); //Random
	cout << "1- Insertion Sort \n2- 2-Way Quick Sort \n3- 3-Way Quick Sort \n4- Radix Sort \nSelect one of them: ";
	int choice;
	cin >> choice;// Switch Choice
	clock_t begin_time; // Timer Defination
	int time; // Result Time Picker.
	switch (choice) {
	case 1: cout << "Insertion Sort starting!" << endl;
		begin_time = clock();
		InsertionSort(ar, size); // Insertoin Sort
		time = clock() - begin_time;
		break;
	case 2: cout << "2-Way Quick Sort starting!" << endl;
		begin_time = clock();
		TwoWayQuickSort(ar, 0, size); // Two Way Quick Sort
		time = clock() - begin_time;
		break;
	case 3: cout << "3-Way Quick Sort starting!" << endl;
		begin_time = clock();
		ThreeWayQuickSort(ar, 0, size); // Three Way Quick Sort
		time = clock() - begin_time;
		break;
	case 4: cout << "Radix Sort starting!" << endl;
		begin_time = clock();
		RadixSort(ar, size); // Radix Sort
		time = clock() - begin_time;
		break;
	}
	cout << "Sort Time :" << time << endl; // Spended Time Shower 
	printf("Do you want to print sorted list? (Write 1 (Yes) or 0 (No)) : ");
	int chc;
	cin >> chc;
	if (chc == 1) {
		// LinkedList part
		Node *root;
		Node *ptr;
		root = (Node *)malloc(sizeof(Node));
		ptr = root;
		root->item = ar[0];
		for (int i = 1; i < size; i++)
		{
			ptr->next = (Node *)malloc(sizeof(Node));
			ptr = ptr->next;
			ptr->item = ar[i];
			ptr->next = NULL;
		}
		LinkedListPrint(root);
	}
	else if (chc == 0) {
		cout << endl << "Press any key and close the program";
		cin.get();// After click to any key program colse.
	}

	cout << endl << "Press any key and close the program";
	cin.get();// After click to any key program colse.

	return 0;
}

