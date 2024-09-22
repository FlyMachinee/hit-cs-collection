#ifndef _SORTS_HPP_
#define _SORTS_HPP_

#include <iostream>
#include <functional>
#include <random>
#include <limits>
#include <ctime>
#include <string>
#include <fstream>

namespace My {

	/**
	 * @brief generate random integer
	 * @param dest output stream destination
	 * @param length generated number count
	 * @note separated with space (aka char ' ')
	*/
	void make_int(::std::ostream& dest, int length, ::std::default_random_engine& e) {
		::std::uniform_int_distribution<int> u(INT32_MIN, INT32_MAX);
		for (int i = 0; i < length; ++i) {
			dest << u(e) << ' ';
		}
	}

	/**
	 * @brief generate random integer to file
	 * @param path file path
	 * @param length generated number count
	 * @note output: first line the <length>, second line numbers
	*/
	void make_int_to_file(const ::std::string& path, int length, ::std::default_random_engine& e) {
		::std::ofstream file(path);
		file << length << '\n';
		make_int(file, length, e);
		file.close();
	}

	template <typename Elem, class CmpFunc>
	void selection_sort(Elem* arr, int len, CmpFunc cmp) {
		for (int i = 0; i < len; i++) {
			int l_index = i;
			for (int j = i + 1; j < len; j++)
				if (cmp(arr[j], arr[l_index]))
					l_index = j;
			::std::swap(arr[i], arr[l_index]);
		}
	}

	template <typename Elem>
	void selection_sort(Elem* arr, int len) {
		selection_sort(arr, len, ::std::less<Elem>());
	}

	template <typename Elem, class CmpFunc>
	void insertion_sort(Elem* arr, int len, CmpFunc cmp) {
		for (int i = 1; i < len; i++) {
			Elem temp = arr[i];
			int j = i - 1;
			while (cmp(temp, arr[j]) && j >= 0) {
				arr[j + 1] = arr[j];
				--j;
			}
			arr[j + 1] = temp;
		}
	}

	template <typename Elem>
	void insertion_sort(Elem* arr, int len) {
		insertion_sort(arr, len, ::std::less<Elem>());
	}

	template <typename Elem, class CmpFunc>
	void merge_sort(Elem* arr, int l, int r, CmpFunc cmp) {
		if (l >= r)
			return;
		int mid = l + (r - l) / 2;

		merge_sort(arr, l, mid, cmp);
		merge_sort(arr, mid + 1, r, cmp);

		Elem* temp = new Elem[r - l + 1];
		int i = l, j = mid + 1, total = 0;
		while (i <= mid && j <= r) {
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

	template <typename Elem>
	void merge_sort(Elem* arr, int l, int r) {
		merge_sort(arr, l, r, ::std::less<Elem>());
	}

	template <typename Elem>
	void merge_sort(Elem* arr, int len) {
		merge_sort(arr, 0, len - 1);
	}

	template <typename Elem, class CmpFunc>
	void quick_sort(Elem* arr, int l, int r, CmpFunc cmp) {
		Elem pivot = arr[l + (r - l) / 2];	
		int i = l, j = r;

		do {
			while (cmp(arr[i], pivot))
				++i;
			while (cmp(pivot, arr[j]))
				--j;
			if (i <= j)
				::std::swap(arr[i++], arr[j--]);
		} while (i <= j);

		if (l < j)
			quick_sort(arr, l, j, cmp);
		if (i < r)
			quick_sort(arr, i, r, cmp);
	}

	template <typename Elem>
	void quick_sort(Elem* arr, int l, int r) {
		quick_sort(arr, l, r, ::std::less<Elem>());
	}

	template <typename Elem>
	void quick_sort(Elem* arr, int len) {
		quick_sort(arr, 0, len - 1);
	}

	template <typename Elem, class CmpFunc>
	static void heapify (Elem* arr, int len, int father, CmpFunc cmp) {
		int child = father * 2 + 1;
		// sink down process
		while (child < len) {
			// get the "maximum" child (depend on the cmp func)
			if (child + 1 < len && cmp(arr[child], arr[child + 1]))
				child++;

			// if father is "bigger" than child (depend on the cmp func)
			if (cmp(arr[child], arr[father]))
				// sink down over
				return;
			else {
				// swap father with the "bigger" child (depend on the cmp func)
				::std::swap(arr[child], arr[father]);
				// child become father
				father = child;
				child = father * 2 + 1;
			}
		}
	}

	template <typename Elem, class CmpFunc>
	void heap_sort(Elem* arr, int len, CmpFunc cmp) {
		for (int i = (len - 1) / 2; i >= 0; i--)
			heapify(arr, len, i, cmp);

		for (int i = len - 1; i >= 0; i--) {
			::std::swap(arr[0], arr[i]);
			heapify(arr, i, 0, cmp);
		}
	}

	template <typename Elem>
	void heap_sort(Elem* arr, int len) {
		heap_sort(arr, len, ::std::less<Elem>());
	}

} // namespace My

#endif // _SORTS_HPP_