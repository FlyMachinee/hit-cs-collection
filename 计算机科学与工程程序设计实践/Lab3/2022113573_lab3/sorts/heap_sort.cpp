#ifndef HEAP_SORT_CPP_INCLUDED
#define HEAP_SORT_CPP_INCLUDED

template <typename Elem> void heapify (Elem* arr, int len, int father, bool (*cmp)(const Elem &a, const Elem &b))
{
	int child = father * 2 + 1;
	// percolate down process
	while (child < len)
	{
		// get the "maximum" child (depend on the cmp func)
		if (child + 1 < len && cmp(arr[child], arr[child + 1]))
			child++;

		// if father is "bigger" than child (depend on the cmp func)
		if (cmp(arr[child], arr[father]))
			// percolate down over
			return;
		else
		{
			// swap father with the "bigger" child (depend on the cmp func)
			my_swap(arr[child], arr[father]);
			// child become father
			father = child;
			child = father * 2 + 1;
		}
	}
}

template <typename Elem> void heap_sort(Elem* arr, int len, bool (*cmp)(const Elem &a, const Elem &b))
{
	for (int i = (len - 1) / 2; i >= 0; i--)
		heapify(arr, len, i, cmp);

	for (int i = len - 1; i >= 0; i--)
	{
		my_swap(arr[0], arr[i]);
		heapify(arr, i, 0, cmp);
	}
}

#endif

