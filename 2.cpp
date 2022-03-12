#include <iostream>

int merge(int* arr, int begin, int end) {
    int* tmp_arr = new int[99];

    int middle = (begin + end) / 2; 
    int start = begin;
    int final = middle + 1; 
    for(int j = begin; j <= end; ++j) 
    if ((start <= middle) && ((final > end) || (arr[start] < arr[final]))) {
        tmp_arr[j] = arr[start];
        start++;
    }
    else {
        tmp_arr[j] = arr[final];
        final++;
    }

    for (int j = begin; j <= end; ++j) 
        arr[j] = tmp_arr[j];

    delete[] tmp_arr;

}

int mergeSort(int* arr, int begin, int end) {
    if (begin > end)
        return 1;

    int middle = (begin + end) / 2;

    mergeSort(arr, begin, middle);
    mergeSort(arr, middle + 1, end);
    merge(arr, begin, end);
}