#ifndef FILEOP_HPP_INCLUDED
#define FILEOP_HPP_INCLUDED

#include "main.hpp"
#include "student.hpp"

void read_from_txt(FILE* pf, STUDENT* rec, int& len);
void write_to_binary(FILE* pf, STUDENT* rec, const int& len);
void read_from_binary(FILE* pf, STUDENT* rec, int& len);
void write_to_txt(FILE* pf, STUDENT* rec, const int& len);

#endif
