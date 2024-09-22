#ifndef QUICK_SORT_CPP_INCLUDED
#define QUICK_SORT_CPP_INCLUDED

template <typename Elem> void quick_sort(Elem* arr, int l, int r, bool (*cmp)(const Elem &a, const Elem &b))
{
	Elem pivot = arr[(l + r) / 2];	
	int i = l, j = r;
	do
	{
		while (cmp(arr[i], pivot))
			i++;
		while (cmp(pivot, arr[j]))
			j--;
		if (i <= j)
		{
			my_swap(arr[i], arr[j]);
			i++;
			j--;
		}
	}
	while (i <= j);
	if (l < j)
		quick_sort(arr, l, j, cmp);
	if (i < r)
		quick_sort(arr, i, r, cmp);
}

#endif
