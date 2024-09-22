#ifndef MERGE_SORT_CPP_INCLUDED
#define MERGE_SORT_CPP_INCLUDED

template <typename T> void merge_sort(T* arr, int l, int r, bool (*cmp)(const T &a, const T &b))
{
	if (l >= r)
		return;
	int mid = (l + r) / 2;
	merge_sort(arr, l, mid, cmp);
	merge_sort(arr, mid + 1, r, cmp);

	T* temp = new T[r - l + 1];
	int i = l, j = mid + 1, total = 0;
	while (i <= mid && j <= r)
	{
		if (cmp(arr[i], arr[j]))
			temp[total++] = arr[i++];
		else
			temp[total++] = arr[j++];
	}

	if (i <= mid)
		memcpy(temp + total, arr + i, (mid - i + 1) * sizeof(T));
	if (j <= r)
		memcpy(temp + total, arr + j, (r - j + 1) * sizeof(T));
	memcpy(arr + l, temp, (r - l + 1) * sizeof(T));
	delete[] temp;
}

#endif
