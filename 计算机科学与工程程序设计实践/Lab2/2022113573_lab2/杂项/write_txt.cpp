#include <iostream>
using namespace std;

int main()
{
	FILE* pf = fopen("./outtxt.txt", "w");
	fputs("Hello!\nLinux\nUbuntu\nCpp\n", pf);
	fclose(pf);
	return 0;
}
