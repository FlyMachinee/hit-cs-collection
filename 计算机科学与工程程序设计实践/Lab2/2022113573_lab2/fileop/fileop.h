#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <cstring>

#define MAX_RECORDS 20

using namespace std;

struct my_record
{
	unsigned long id;
	char name[32];
	float score[4];
};

void raise(int err_no);
void raise(int err_no, bool is_err);
struct my_record str_to_record(char* str);
void records_to_screen(struct my_record* rec, int cnt);

void read_from_txt(FILE* pf, struct my_record* rec, int* pcnt);
void read_from_binary(FILE* pf, struct my_record* rec, int* pcnt);
void txt_to_binary(FILE* pf_from, FILE* pf_to, struct my_record* rec, int* pcnt);
void binary_to_txt(FILE* pf_from, FILE* pf_to, struct my_record* rec, int* pcnt);

