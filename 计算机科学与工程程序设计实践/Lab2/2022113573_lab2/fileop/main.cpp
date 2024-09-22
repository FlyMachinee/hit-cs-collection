#include "fileop.h"

int main(int argc, char** argv)
{
	int type;
	if (1 != sscanf(argv[1], "%d", &type))
		raise(EINVAL);
	
	struct my_record records[MAX_RECORDS];
	int record_cnt = 0;

	if (3 == argc)
	// only 2 paras
	{
		FILE* pf;
		switch (type)
		{
		case 1:
			// read from txt
			pf = fopen(argv[2], "r");
			raise(ENOENT, pf == NULL);

			read_from_txt(pf, records, &record_cnt);	
			break;
		case 2:
			// read from binary
			pf = fopen(argv[2], "rb");
			raise(ENOENT, pf == NULL);

			read_from_binary(pf, records, &record_cnt);
			break;
		default:
			raise(ENOENT);
			break;
		}
		fclose(pf);
	}
	else
	// 3 paras
	{
		FILE* pf_from, * pf_to;
		switch (type)
		{
		case 1:
			// read from txt, and write to binary
			pf_from = fopen(argv[2], "r");
			pf_to = fopen(argv[3], "wb");
			raise(ENOENT, pf_from == NULL || pf_to == NULL);

			txt_to_binary(pf_from, pf_to, records, &record_cnt);	
			break;
		case 2:
			// read from binary, and write to txt
			pf_from = fopen(argv[2], "rb");
			pf_to = fopen(argv[3], "w");
			raise(ENOENT, pf_from == NULL || pf_to == NULL);

			binary_to_txt(pf_from, pf_to, records, &record_cnt);
			break;
		default:
			raise(EINVAL);
			break;
		}
		fclose(pf_from);
		fclose(pf_to);
	}
	
	// show records in terminal
	records_to_screen(records, record_cnt);
	return 0;
}


