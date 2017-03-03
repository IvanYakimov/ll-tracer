#ifndef __QUICK_SORT_H__
#define __QUICK_SORT_H__

void swap(int intArray[], int num1, int num2);
int partition(int intArray[], int left, int right, int pivot);
int* quickSort(int intArray[], int left, int right);
int* sort(int array[], int n);

#endif
