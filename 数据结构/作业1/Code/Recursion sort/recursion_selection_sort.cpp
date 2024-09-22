#ifndef SELECTION_SORT_CPP_INCLUDED
#define SELECTION_SORT_CPP_INCLUDED

template <typename T> void selection_sort(T* arr, int len, bool (*cmp)(const T &a, const T &b))
{
	if (len <= 1)
		return;

	int l_index = 0;
	
	for (int i = 1; i < len; i++)
	{
		if (cmp(arr[i], arr[l_index]))

			l_index = i;
	}
	swap(arr[0], arr[l_index]);

	selection_sort(arr + 1, len - 1, cmp);
}

#endif
