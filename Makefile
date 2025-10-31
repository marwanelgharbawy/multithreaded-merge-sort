all: merge_sort

run: merge_sort
	@./merge_sort

merge_sort: merge_sort_multithreaded.c
	@gcc -o merge_sort merge_sort_multithreaded.c -pthread

clean:
	@rm -f merge_sort