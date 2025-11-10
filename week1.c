#include <stdio.h>

void bubble_sort_ascending(int arr[], int n) {
    int i, j, temp;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void selection_sort_descending(int arr[], int n) {
    int i, j, max_idx, temp;
    for (i = 0; i < n - 1; i++) {
        max_idx = i;
        for (j = i + 1; j < n; j++) {
            if (arr[j] > arr[max_idx]) {
                max_idx = j;
            }
        }
        temp = arr[max_idx];
        arr[max_idx] = arr[i];
        arr[i] = temp;
    }
}

void print_array(int arr[], int size) {
    int i;
    for (i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int list_bubble[] = {64, 34, 25, 12, 22, 11, 90};
    int n_bubble = sizeof(list_bubble) / sizeof(list_bubble[0]);
    
    printf("Bubble Sort (Ascending):\n");
    printf("Original list: ");
    print_array(list_bubble, n_bubble);
    
    bubble_sort_ascending(list_bubble, n_bubble);
    printf("Sorted list: ");
    print_array(list_bubble, n_bubble);
    printf("--------------------\n");
    
    int list_selection[] = {64, 25, 12, 22, 11, 90, 34};
    int n_selection = sizeof(list_selection) / sizeof(list_selection[0]);
    
    printf("Selection Sort (Descending):\n");
    printf("Original list: ");
    print_array(list_selection, n_selection);
    
    selection_sort_descending(list_selection, n_selection);
    printf("Sorted list: ");
    print_array(list_selection, n_selection);
    
    return 0;
}