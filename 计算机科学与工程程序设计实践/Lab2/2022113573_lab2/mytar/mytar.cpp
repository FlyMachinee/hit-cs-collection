#include "mytar.h"

void raise(int err_no, bool is_err)
{
	// if is_err, show err info, terminate program
	if (is_err)
        {
                cout << "ERROR " << err_no << ": " << strerror(err_no) << endl;
                exit(-1);
        }
}

void tar(const char* dir_name, const char* out_file_name)
{
	FILE* pf_out = fopen(out_file_name, "w");
	
	// open the directory "dir_name"
	DIR* pdir = opendir(dir_name);
	raise(ENOENT, NULL == pdir);

	struct dirent* pd;
	while (NULL != (pd = readdir(pdir)))
	// traverses all files in the specified directory path "dir_name"
	{
		// if the file is a regular file
		if (DT_REG == pd->d_type)
		{
			// tar the file
			tar_file(dir_name, pd->d_name, pf_out);
		}
	}
	
	closedir(pdir);
	fclose(pf_out);
}

void tar_file(const char* file_dir, const char* file_name, FILE* pf_out)
{
	// get the path of the file
	char file_path[512];
	sprintf(file_path, "%s/%s", file_dir, file_name);
	
	// get the stat of the file
	struct stat stat_buf;
	stat(file_path, &stat_buf);
	
	// output str "file", file name, and file size
	fprintf(pf_out, "file\n%s\n%d\n", file_name, (int)stat_buf.st_size);

	FILE* pf_in = fopen(file_path, "r");
	
	char buf[4096];
	while (1)
	{
		// read the file block by block, 4096 byte for one block
		int res = fread(buf, 1, sizeof(buf), pf_in);
		
		if (res <= 0)
		// the whole file is already output
			break;
		else
		// write the block to the tar file
			fwrite(buf, res, 1, pf_out);
	}
	fclose(pf_in);
}

void untar(const char* file_name, const char* out_dir_name)
{
	if (NULL == opendir(out_dir_name))
	// if the output dir is not exist, make new dir
		mkdir(out_dir_name, 0777);
	
	FILE* pf_in = fopen(file_name, "r");
	
	char buf[1024];
	while (1)
	{
		if (NULL == fgets(buf, sizeof(buf), pf_in))
		// the file is empty			
			break;

		if (0 == strcmp("file\n", buf))
		// try to read the string "file"
		{
			// get file name
			fgets(buf, sizeof(buf), pf_in);
			
			// change '\n' to '\0'
			buf[strlen(buf) - 1] = '\0';
			
			// get file path
			char file_path[512];
			sprintf(file_path, "%s/%s", out_dir_name, buf);
			
			// get file size
			fgets(buf, sizeof(buf), pf_in);
			int len = atol(buf);
			
			// read from tar file, and output
			FILE* pf_out = fopen(file_path, "w");
			while (len > 0)
			{
				int read_len = MIN(len, sizeof(buf));
				int res = fread(buf, 1, read_len, pf_in);
				fwrite(buf, 1, res, pf_out);
				len -= res;
			}
			fclose(pf_out);
		}
		else
		// tar file format error
			break;
	}
	fclose(pf_in);
}