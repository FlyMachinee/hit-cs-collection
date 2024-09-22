#include <iostream>

using namespace std;

int main()
{
	FILE* fp = fopen("./float_binary.dat", "rb");

	float num[100];
	fread(num, sizeof(float), 100, fp);

	for (int i = 0; i < 100; i++)
		cout << num[i] << ' ';

	return 0;
}
