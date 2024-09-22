#ifndef SELECTION_SORT_CPP_INCLUDED
#define SELECTION_SORT_CPP_INCLUDED

template <typename Elem> void selection_sort(Elem* arr, int len, bool (*cmp)(const Elem &a, const Elem &b))
{
	for (int i = 0; i < len; i++)
	{
		int l_index = i;
		for (int j = i + 1; j < len; j++)
			if (cmp(arr[j], arr[l_index]))
				l_index = j;
		my_swap(arr[i], arr[l_index]);
	}
}

#endif
