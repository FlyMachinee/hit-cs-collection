#include "sort.hpp"

//#define DEBUG_1
#define DEBUG_2

const char* file_name = "";

template <typename T> double sort_test(T data_example, int len, const char* sort_method);
void raise(int err_no, bool is_err, const char* memo = "");
template <typename T> bool ascend(const T &a, const T &b);
template <typename T> void show(T *arr, int len);
template <typename T> void generate_data(T *arr, int len);
void generate_data(STU* arr, int len);
void rand_name(char* name);
void rand_id(char* id);

void input_info()
{
        cout << "========================================================" << endl;
        cout << "// Usage: " << file_name << " <len> <type> [sort_method = \"quick\"]" << endl;
        cout << "// <len> an integer, indicate the data amount" << endl;
        cout << "// <type> a string, indicate the data type to be sort" << endl;
        cout << "//     possible input: \"int\" \"float\" \"double\" \"STU\"" << endl;
        cout << "// [sort_method] a string, indicate the sort method, default: \"quick\"" << endl;
        cout << "//     possible input: \"bubble\" \"selection\"";
        cout << " \"insertion\" \"merge\" \"quick\" \"heap\"" << endl;
	cout << "========================================================" << endl;
}

int main(int argc, char** argv)
{
	file_name = argv[0];
	if (argc < 3)
	{
		input_info();
		raise(EINVAL, true, "not enough paras");
	}
	
	int len = atoi(argv[1]);
	const char* d_type = argv[2];
	const char* sort_method = ((argc < 4) ? "quick" : argv[3]);
	
	raise(EINVAL, len <= 0, "len must be positive");

#ifndef DEBUG_1
	srand(time(0));
#endif

	double run_time;
	if (strcmp(d_type, "int") == 0)
	{
		run_time = sort_test((int)0, len, sort_method);
	}
	else if (strcmp(d_type, "float") == 0)
	{
                run_time = sort_test((float)0, len, sort_method);
	}
	else if (strcmp(d_type, "double") == 0)     
	{
                run_time = sort_test((double)0, len, sort_method);
	}
	else if (strcmp(d_type, "STU") == 0)     
	{
                STU temp = {0};
		run_time = sort_test(temp, len, sort_method);
	}
	else
	{
		input_info();
		raise(EINVAL, true, "unexpected data type");
	}

	cout << sort_method << "_sort runs " << run_time << " seconds for " << len << " elements" << endl;
	
	return 0;
}

template <typename T> double sort_test(T data_example, int len, const char* sort_method)
{
	T* original = new T[len];
	T* sorted = new T[len];

	generate_data(original, len);
	memcpy(sorted, original, sizeof(T) * len);

#ifdef DEBUG_2
	cout << "Before " << sort_method << "_sort:\n";
	show(original, len);
#endif
	
	clock_t t_begin = clock();
	if (strcmp(sort_method, "bubble") == 0)
		bubble_sort(sorted, len, ascend);	
	else if (strcmp(sort_method, "selection") == 0)
		selection_sort(sorted, len, ascend);	
	else if (strcmp(sort_method, "insertion") == 0)
		insertion_sort(sorted, len, ascend);	
	else if (strcmp(sort_method, "merge") == 0)
		merge_sort(sorted, 0, len - 1, ascend);	
	else if (strcmp(sort_method, "quick") == 0)
		quick_sort(sorted, 0, len - 1, ascend);	
	else if (strcmp(sort_method, "heap") == 0)
		heap_sort(sorted, len, ascend);
	else
	{
		input_info();
		delete[] original;
	        delete[] sorted;
		raise(EINVAL, true, "unexpected sort method string");
	}
	clock_t t_end = clock();

#ifdef DEBUG_2
	cout << "After " << sort_method << "_sort:\n";
        show(sorted, len);
#endif
	
	delete[] original;
	delete[] sorted;
	return ((double)(t_end - t_begin)) / CLOCKS_PER_SEC;
}

void raise(int err_no, bool is_err, const char* memo)
{
	if (is_err)
	{
		cout << "ERROR " << err_no << " :" << strerror(err_no) << endl;
		if (0 != strcmp("", memo))
		{
			cout << memo << endl;
		}
		exit(-1);
	}
}

template <typename T> bool ascend(const T &a, const T &b)
{
	return a < b;
}

template <typename T> void show(T *arr, int len)
{
	for (int i = 0; i < len; i++)
	{
		cout << arr[i] << ((typeid(T) == typeid(STU)) ? "" : " ");
	}
	cout << endl;
}

template <typename T> void generate_data(T *arr, int len)
{
	for (int i = 0; i < len; i++)
	{
		arr[i] = rand() % (10 * len) + (double)rand() / RAND_MAX;
	}
}

void generate_data(STU* arr, int len)
{
	for (int i = 0; i < len; i++)
	{
		rand_name(arr[i].name);
		rand_id(arr[i].id);
		arr[i].total = 0;
		for (int j = 0; j < 5; j++)
		{
			arr[i].total += (arr[i].score[j] = ((600 + rand() % 401) / 10));
		}
	}
}

void rand_name(char* name)
{
	int len = 5 + rand() % 6;
	name[0] = 'A' + rand() % 26;
	for (int i = 1; i < len; i++)
	{
		name[i] = 'a' + rand() % 26;
	}
	name[len] = '\0';
}

void rand_id(char* id)
{
	strcpy(id, "2022");
	char buf[7];
	sprintf(buf, "%06d", rand() % 1000000);
	buf[6] = '\0';
	strcat(id, buf);
}
