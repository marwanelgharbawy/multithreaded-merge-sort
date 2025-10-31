#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX 10000 

// Struct for thread arguments
typedef struct {
    int left;
    int right;
    int *arr;
} ThreadArgs;

// Merge function
void merge(int arr[], int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int *L = malloc(n1 * sizeof(int));
    int *R = malloc(n2 * sizeof(int));

    for (i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    i = 0;
    j = 0;
    k = left;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j])
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }

    while (i < n1)
        arr[k++] = L[i++];

    while (j < n2)
        arr[k++] = R[j++];

    free(L);
    free(R);
}

void* threaded_merge_sort(void* arg) {

    // Implement the full function to be using the merge function
    // Then call it from main function
}

int main() {
    FILE* file = fopen("input", "r");
    if (!file) {
        printf("Error opening file.\n");
        return 1;
    }

    int n;
    fscanf(file, "%d", &n);
    int arr[MAX];
    for (int i = 0; i < n; i++) {
        fscanf(file, "%d", &arr[i]); 
    }
    fclose(file);

    // Make the required changes inorder to be able to call the Thread function

    printf("Sorted array:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}
