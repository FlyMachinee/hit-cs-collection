#ifndef MERGE_SORT_CPP_INCLUDED
#define MERGE_SORT_CPP_INCLUDED

template <typename Elem> void merge_sort(Elem* arr, int l, int r, bool (*cmp)(const Elem &a, const Elem &b))
{
	if (l >= r)
		return;
	int mid = (l + r) / 2;
	merge_sort(arr, l, mid, cmp);
	merge_sort(arr, mid + 1, r, cmp);

	Elem* temp = new Elem[r - l + 1];
	int i = l, j = mid + 1, total = 0;
	while (i <= mid && j <= r)
	{
		if (cmp(arr[i], arr[j]))
			temp[total++] = arr[i++];
		else
			temp[total++] = arr[j++];
	}

	if (i <= mid)
		memcpy(temp + total, arr + i, (mid - i + 1) * sizeof(Elem));
	if (j <= r)
		memcpy(temp + total, arr + j, (r - j + 1) * sizeof(Elem));
	memcpy(arr + l, temp, (r - l + 1) * sizeof(Elem));
	delete[] temp;
}

#endif
