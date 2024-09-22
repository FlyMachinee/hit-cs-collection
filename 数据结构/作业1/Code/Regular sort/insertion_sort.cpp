#ifndef INSERTION_SORT_CPP_INCLUDED
#define INSERTION_SORT_CPP_INCLUDED

template <typename T> void insertion_sort(T* arr, int len, bool (*cmp)(const T &a, const T &b))
{
	for (int i = 1; i < len; i++)
	{
		T temp = arr[i];
		int j = i - 1;
		while (cmp(temp, arr[j]) && j >= 0)
		{
			arr[j + 1] = arr[j];
			j--;
		}
		arr[j + 1] = temp;
	}
}

#endif
