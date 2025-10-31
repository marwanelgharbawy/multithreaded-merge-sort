#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX 10000 

// Struct for thread arguments
// It consists of left and right indices and the array pointer
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
    // Arguments type casting
    ThreadArgs* args = (ThreadArgs*)arg;

    // Base case
    if (args->left >= args->right) {
        return NULL;
    }

    int mid = args->left + (args->right - args->left) / 2;

    // Sort left half, right half, then merge
    // First, create thread arguments for left and right halves
    ThreadArgs leftArgs = {args->left, mid, args->arr};
    ThreadArgs rightArgs = {mid + 1, args->right, args->arr};

    // Create threads for left and right halves
    pthread_t leftThread, rightThread;

    // Recursively sort both halves in separate threads
    pthread_create(&leftThread, NULL, threaded_merge_sort, &leftArgs);
    pthread_create(&rightThread, NULL, threaded_merge_sort, &rightArgs);

    // Wait for both threads to finish
    pthread_join(leftThread, NULL);
    pthread_join(rightThread, NULL);

    // Merge the sorted halves
    merge(args->arr, args->left, mid, args->right);

    return NULL;
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

    ThreadArgs args = {0, n - 1, arr};
    threaded_merge_sort(&args);

    printf("Sorted array:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}
