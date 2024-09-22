#ifndef SORT_HPP_INCLUDED
#define SORT_HPP_INCLUDED

#include <iostream>
#include <cstring>
#include <type_traits>
#include <time.h>
#include <iomanip>

using namespace std;

typedef struct STU
{
    char  id[20];
    char  name[20];
    float score[5];
    float total;
}STU;

bool operator>(STU const& a, STU const& b)
{
	return a.total > b.total;
}

ostream & operator<<(ostream &out, STU &a)
{
	out << a.id << " " << a.name << "\t";
	out << fixed << setprecision(1);
	out << a.score[0] << " ";
	out << a.score[1] << " ";
	out << a.score[2] << " ";
	out << a.score[3] << " ";
	out << a.score[4] << " ";
	out << fixed << setprecision(1);
	out << a.total << endl;
	out.unsetf(ios_base::fixed);
	out << setprecision(6);
	return out;
}

#include "swap.cpp"
#include "bubble_sort.cpp"
#include "selection_sort.cpp"
#include "insertion_sort.cpp"
#include "merge_sort.cpp"
#include "quick_sort.cpp"
#include "heap_sort.cpp"

#endif
