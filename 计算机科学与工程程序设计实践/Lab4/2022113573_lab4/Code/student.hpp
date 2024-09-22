#ifndef STUDENT_HPP_INCLUDED
#define STUDENT_HPP_INCLUDED

typedef struct student
{
	unsigned long stu_id;
	char stu_name[32];
	float score[4];
	//ics pdp ds dl
}STUDENT;

bool descend_by_ics(const STUDENT& a, const STUDENT& b);
bool descend_by_pdp(const STUDENT& a, const STUDENT& b);
bool descend_by_ds(const STUDENT& a, const STUDENT& b);
bool descend_by_dl(const STUDENT& a, const STUDENT& b);

STUDENT string_to_STUDENT(const char* str);
char* STUDENT_to_string(const STUDENT& stu, char str[128]);

void show_title();
void show_menu();

unsigned long get_ID(const char* memo);

#endif