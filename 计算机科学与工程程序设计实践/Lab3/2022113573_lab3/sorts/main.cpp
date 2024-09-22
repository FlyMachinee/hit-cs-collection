#include "sort.hpp"

//#define DEBUG_1

const char* file_name = "";
const char* d_type;
bool is_display_item;

template <typename T> double sort_test(int len, const char* sort_method, double repeat_rate);
void raise(int err_no, bool is_err, const char* memo = "");
template <typename T> bool ascend(const T &a, const T &b);
template <typename T> void show(T *arr, int len);
template <typename T> void generate_data(T *arr, int len, double repeat_rate);
void generate_data(STU* arr, int len, double repeat_rate);
void rand_name(char* name);
void rand_id(char* id);
STU rand_STU();
double rand_01();

void input_info()
{
    cout << "//======================================================" << endl;
    cout << "|| Usage: " << file_name << " <type> <len> [sort_method = \"quick\"] [display_element = false] [repeat_rate = 0.]" << endl;
	cout << "|| <type> a string, indicate the data type to be sort" << endl;
    cout << "||     possible inputs: \"int\" \"float\" \"double\" \"STU\"" << endl;
    cout << "|| <len> an positive integer, indicate the data amount" << endl;
	cout << "|| [sort_method] a string, indicate the sort method, default: \"quick\"" << endl;
    cout << "||     possible inputs: \"bubble\" \"selection\"";
    cout << " \"insertion\" \"merge\" \"quick\" \"heap\"" << endl;
	cout << "|| [display_element] a boolean, determine whether or not to display array elements" << endl;
	cout << "||     p.s. any input differs than \"true\" will be considered as \"false\"" << endl;
	cout << "|| [repeat_rate] a double from 0 to 1" << endl;
	cout << "||     p.s. any input below 0 will be equivalant as 0" << endl;
	cout << "||          any input above 1 will be equivalant as 1" << endl;
	cout << "\\\\======================================================" << endl;
}

int main(int argc, char** argv)
{
	file_name = argv[0];
	if (argc < 3)
	{
		input_info();
		raise(EINVAL, true, "Too few arguments");
	}
	
	d_type = argv[1];
	int len = atoi(argv[2]);
	raise(EINVAL, len <= 0, "Len must be positive");
	
	const char* sort_method = ((argc < 4) ? "quick" : argv[3]);
	is_display_item = (argc >= 5) ? (strcmp("true", argv[4]) == 0) : false;
	double repeat_rate = (argc >= 6) ? atof(argv[5]) : 0.0;
	
#ifndef DEBUG_1
	srand(time(0));
#endif

	double run_time;
	if (strcmp(d_type, "int") == 0)
	{
		run_time = sort_test<int>(len, sort_method, repeat_rate);
	}
	else if (strcmp(d_type, "float") == 0)
	{
        run_time = sort_test<float>(len, sort_method, repeat_rate);
	}
	else if (strcmp(d_type, "double") == 0)     
	{
        run_time = sort_test<double>(len, sort_method, repeat_rate);
	}
	else if (strcmp(d_type, "STU") == 0)     
	{
		run_time = sort_test<STU>(len, sort_method, repeat_rate);
	}
	else
	{
		input_info();
		raise(EINVAL, true, "Unknown data type");
	}
	cout << sort_method << "_sort runs " << run_time << " seconds for " << len << ' '  << d_type << " elements" << endl;
	return 0;
}

template <typename T> double sort_test(int len, const char* sort_method, double repeat_rate)
{
	T* original = new T[len];
	T* sorted = new T[len];

	generate_data(original, len, repeat_rate);
	memcpy(sorted, original, sizeof(T) * len);

	if (is_display_item)
	{
		cout << "Before " << sort_method << "_sort:\n";
		show(original, len);
	}
	
	size_t t_begin = clock();
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
	size_t t_end = clock();

	if (is_display_item)
	{
		cout << "After " << sort_method << "_sort:\n";
        show(sorted, len);
	}
	
	delete[] original;
	delete[] sorted;
	return (t_end - t_begin) / (double)CLOCKS_PER_SEC;
}

void raise(int err_no, bool is_err, const char* memo)
{
	if (is_err)
	{
		cout << "ERROR " << err_no << " :" << strerror(err_no) << endl;
		if (0 != strcmp("", memo))
		cout << memo << endl;
		exit(-1);
	}
}

template <typename T> bool ascend(const T &a, const T &b)
{
	return a > b;
}

template <typename T> void show(T *arr, int len)
{
	for (int i = 0; i < len && i < 100; i++)
		cout << arr[i] << ((typeid(T) == typeid(STU)) ? "" : " ");
	if (len > 100)
		cout << "......(total " << len << " elements)";
	cout << endl;
}

template <typename T> void generate_data(T *arr, int len, double repeat_rate)
{
	T specimen = rand() % (10 * len) + rand_01();
	for (int i = 0; i < len; i++)
	{
		arr[i] = (rand_01() <= repeat_rate) ? specimen : (rand() % (10 * len) + rand_01());
	}
}

void generate_data(STU* arr, int len, double repeat_rate)
{
	STU specimen = rand_STU();
	for (int i = 0; i < len; i++)
	{
		arr[i] = (rand_01() <= repeat_rate) ? specimen : rand_STU();	
	}
}

void rand_name(char* name)
{
	// len between 5 and 10
	int len = 5 + rand() % 6;

	// letter between 'A' and 'Z'
	name[0] = 'A' + rand() % 26;

	for (int i = 1; i < len; i++)
		// letter between 'a' and 'z'
		name[i] = 'a' + rand() % 26;
	name[len] = '\0';
}

void rand_id(char* id)
{
	strcpy(id, "202211");
	char buf[5];

	// string between "0000" and "9999"
	sprintf(buf, "%04d", rand() % 10000);
	buf[4] = '\0';
	strcat(id, buf);
}

STU rand_STU()
{
	STU temp;
	rand_name(temp.name);
	rand_id(temp.id);
	temp.total = 0;
	for (int j = 0; j < 5; j++)
		// score between 60.0 and 99.9
		temp.total += (temp.score[j] = ((600 + rand() % 400) / (float)10));
	return temp;
}

double rand_01()
{
	// double between 0 and 1
	return (double)rand() / RAND_MAX;
}
