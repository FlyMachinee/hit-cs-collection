#ifndef SELECTION_SORT_CPP_INCLUDED
#define SELECTION_SORT_CPP_INCLUDED

template <typename T> void selection_sort(T* arr, int len, bool (*cmp)(const T &a, const T &b))
{
	for (int i = 0; i < len; i++)
	{
		int l_index = i;
		for (int j = i + 1; j < len; j++)
			if (cmp(arr[j], arr[l_index]))
				l_index = j;
		swap(arr[i], arr[l_index]);
	}
}

#endif
