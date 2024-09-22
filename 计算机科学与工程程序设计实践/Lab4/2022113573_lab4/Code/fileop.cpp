#ifndef FILEOP_CPP_INCLUDED
#define FILEOP_CPP_INCLUDED

#include "fileop.hpp"

void read_from_txt(FILE* pf, STUDENT* rec, int& len)
{
	char buf[128];
	while (fgets(buf, 128, pf))
	// read str, line by line, convert it into struct, store in array
		rec[len++] = string_to_STUDENT(buf);
}

void write_to_binary(FILE* pf, STUDENT* rec, const int& len)
{
	fwrite(rec, sizeof(STUDENT), len, pf);
}

void read_from_binary(FILE* pf, STUDENT* rec, int& len)
{
	while (1 == fread(rec + len, sizeof(STUDENT), 1, pf))
	// read struct, one by one
		len++;
}

void write_to_txt(FILE* pf, STUDENT* rec, const int& len)
{
	char buf[128];
	for (int i = 0; i < len; i++)
		fputs(STUDENT_to_string(rec[i], buf), pf);
}

#endif
