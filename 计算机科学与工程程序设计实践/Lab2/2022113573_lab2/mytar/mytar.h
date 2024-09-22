#include <dirent.h>
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <cstring> 

#define MAX_FILE_NUM 20
#define MAX_FILE_NAME_LEN 64
#define MIN(x,y) (((x)<(y))?(x):(y))

using namespace std;

void raise(int err_no, bool is_err);

void tar(const char* dir_name, const char* out_file_name);
void tar_file(const char* file_dir, const char* file_name, FILE* pf_out);
void untar(const char* file_name, const char* out_dir_name);
