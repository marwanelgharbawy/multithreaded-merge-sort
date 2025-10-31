# Multithreaded Merge Sort

- This is a university assignment. Given a merge sort implementation, it's required to apply it using multithreading in C.
- The given material is on a branch called [`original-template`](https://github.com/marwanelgharbawy/multithreaded-merge-sort/tree/original-template)

## Code Logic

The idea of merge sort is a divide and conquer algorithm. It divides the array into two halves, sorts each half recursively, and then merges the sorted halves.

In the traditional implementation, the recursive calls are made in the same thread, where each call waits for the previous one to finish before proceeding. They are normal function calls.

In the multithreaded implementation, a new thread is created for each half, then each thread runs the same function to sort its half. The main thread waits for both threads to finish so that it can merge the sorted halves. This implementation makes the merge sort work concurrently instead of sequentially, which can lead to performance improvements for parallelizable tasks.

## Code Implementation

The threaded implementation exists in one function called `threaded_merge_sort`. It takes a single argument, which is a void pointer. This function will be recursively called in multiple threads.

Each thread starts executing the `threaded_merge_sort` function. First, it needs to cast the void pointer argument to the required type (which in this case is `ThreadArgs` struct pointer).

Then, it executes the normal merge sort logic, but instead of making normal recursive calls, it creates new threads for each half using `pthread_create`. This function has the following format:

```c
pthread_t leftThread, rightThread;

pthread_create(&leftThread, NULL, threaded_merge_sort, &leftArgs);
pthread_create(&rightThread, NULL, threaded_merge_sort, &rightArgs);
```

- The **first** argument is the thread pointer that was just created.
- The **second** is for thread attributes (NULL for default).
- The **third** is the function to execute.
- The **fourth** is the pointer to the arguments to pass to that function.

The arguments are `&leftArgs` and `&rightArgs` are pointers to the arguments for each thread. 

After creating both threads, the main thread waits for both of them to finish using `pthread_join`:

```c
pthread_join(leftThread, NULL);
pthread_join(rightThread, NULL);
```

- The **first** argument is the thread to wait for.
- The **second** is for the return value of the thread (NULL if not needed).

Finally, the merge function is called to merge the two sorted halves.

## Compilation and Execution

A Makefile is used to compile and run the program. Since threads are used, the `-pthread` flag is necessary during compilation.

To compile the program, run:
```make
make
```

To run the program, execute:
```make
make run
``` 