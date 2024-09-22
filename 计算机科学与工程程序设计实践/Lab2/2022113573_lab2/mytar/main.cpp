#include "mytar.h"

int main(int argc, char** argv)
{ 
	cout << "Usage: " << argv[0] << " -c [dir_name] [package_name]\n";
	cout << "Usage: " << argv[0] << " -x [package_name] [dir_name]\n";
	cout << "-c for tar, -x for untar\n";

	raise(EINVAL, 4 != argc);
	
	if (0 == strcmp(argv[1], "-c"))
		tar(argv[2], argv[3]);
	else if (0 == strcmp(argv[1], "-x"))
		untar(argv[2], argv[3]);
	else
		raise(EINVAL, true);

	return 0;
}
