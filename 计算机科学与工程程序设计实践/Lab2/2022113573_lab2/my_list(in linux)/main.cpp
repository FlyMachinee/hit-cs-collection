#include <dirent.h>
#include <iostream>
#include <sys/types.h>
#include <stdlib.h>
#include <cstring> 

using namespace std;

int main(int argc, char** argv)
{ 
	if (2 != argc)
	{
		cout << "ERROR " << EINVAL << ": " << strerror(EINVAL) << endl;
		exit(-1);
	}
	
	struct dirent* pd;

	// open given directory
	DIR* pdir = opendir(argv[1]);
	
	if (NULL == pdir)
	{
		cout << "ERROR " << ENOENT << ": " << strerror(ENOENT) << endl;
		exit(-1);
	}

	while (NULL != (pd = readdir(pdir))) 
	{
		if (DT_REG == pd->d_type)
		// if it is a regular file (e.g. not a directory)
			cout << pd->d_name << endl;
	}      

	// close given directory
	closedir(pdir);
	return 0;
}
