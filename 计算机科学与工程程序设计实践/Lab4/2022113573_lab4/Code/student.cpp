#ifndef STUDENT_CPP_INCLUDED
#define STUDENT_CPP_INCLUDED

#include "main.hpp"

bool descend_by_ics(const STUDENT& a, const STUDENT& b)
{
    return a.score[0] > b.score[0];
}

bool descend_by_pdp(const STUDENT& a, const STUDENT& b)
{
    return a.score[1] > b.score[1];
}

bool descend_by_ds(const STUDENT& a, const STUDENT& b)
{
    return a.score[2] > b.score[2];
}

bool descend_by_dl(const STUDENT& a, const STUDENT& b)
{
    return a.score[3] > b.score[3];
}

STUDENT string_to_STUDENT(const char* str)
{
    STUDENT temp;
	sscanf(str, "%lu %s %f %f %f %f", &temp.stu_id, temp.stu_name, &temp.score[0], &temp.score[1], &temp.score[2], &temp.score[3]);
	return temp;
}

char* STUDENT_to_string(const STUDENT& stu, char str[128])
{
    char buf[128];
    sprintf(buf, "%lu %s\t%.1f\t%.1f\t%.1f\t%.1f", stu.stu_id, stu.stu_name, stu.score[0], stu.score[1], stu.score[2], stu.score[3]);
    strcpy(str, buf);
    return str;
}

void show_title()
{
    cout << "ID         name\tics\tpdp\tds\tdl" << endl;
}

void show_menu()
{
    cout << "1.  Append record" << endl;
    cout << "2.  Search by name" << endl;
    cout << "3.  Search by ID" << endl;
    cout << "4.  Modify by ID" << endl;
    cout << "5.  Delete by ID" << endl;
    cout << "6.  Caculate total and average score of every student" << endl;
    cout << "7.  Caculate average score of every course" << endl;
    cout << "8.  Sort in descending order by course score" << endl;
    cout << "9.  Statistic analysis for every course" << endl;
    cout << "10. Save record" << endl;
    cout << "11. Load record" << endl;
    cout << "12. Show all record" << endl;
    cout << "0.  Exit" << endl;
    cout << "-1. Show menu" << endl;
}

unsigned long get_ID(const char* memo)
{
	unsigned long temp;
	cout << memo;
	cin >> temp;
	while (cin.fail())
	{
		cin.clear();
		cin.ignore();
		cout << "Input error, try again" << endl;
		cout << memo;
		cin >> temp;
	}
	return temp;
}

#endif
