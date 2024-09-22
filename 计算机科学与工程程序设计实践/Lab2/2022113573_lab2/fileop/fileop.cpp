#include "fileop.h"

void raise(int err_no)
{
	// raise err with the errno of (err_no)
	cout << "*** ERROR " << err_no << ": " << strerror(err_no) << " ***" << endl;
	exit(-1);
}

void raise(int err_no, bool is_err)
{
	// raise err, if is_err
	if (is_err)
		raise(err_no);
}

struct my_record str_to_record(char* str)
{
	// convert str to struct my_record
	struct my_record res = {0};
	if (6 != sscanf(str, "%lu%s%f%f%f%f", &res.id, res.name, &res.score[0], &res.score[1], &res.score[2], &res.score[3]))
		raise(ENODATA);
	return res;
}

void records_to_screen(struct my_record* rec, int cnt)
{
	// show records in terminal
	for (int i = 0; i < cnt; i++)
		printf("%lu, %s, %f, %f, %f, %f\n", rec[i].id, rec[i].name, rec[i].score[0], rec[i].score[1], rec[i].score[2], rec[i].score[3]);
}

void read_from_txt(FILE* pf, struct my_record* rec, int* pcnt)
{
	// read records from txt file
	char buf[256];

	rewind(pf);

	while (fgets(buf, 256, pf))
	// read str, line by line, convert it into struct, store in array
		rec[(*pcnt)++] = str_to_record(buf);
}

void txt_to_binary(FILE* pf_from, FILE* pf_to, struct my_record* rec, int* pcnt)
{
	// read structs from (pf_from) txt, and write structs to (pf_to) binary
	read_from_txt(pf_from, rec, pcnt);

	fwrite(rec, sizeof(my_record), *pcnt, pf_to);
}

void read_from_binary(FILE* pf, struct my_record* rec, int* pcnt)
{
	// read records from binary file
	rewind(pf);

	while (1 == fread(rec + *pcnt, sizeof(my_record), 1, pf))
	// read struct, one by one
		(*pcnt)++;
}

void binary_to_txt(FILE* pf_from, FILE* pf_to, struct my_record* rec, int* pcnt)
{
	// read structs from (pf_from) binary, and write structs to (pf_to) txt
	read_from_binary(pf_from, rec, pcnt);

	for (int i = 0; i < *pcnt; i++)
		fprintf(pf_to, "%lu %s %f %f %f %f\n", rec[i].id, rec[i].name, rec[i].score[0], rec[i].score[1], rec[i].score[2], rec[i].score[3]);
}




