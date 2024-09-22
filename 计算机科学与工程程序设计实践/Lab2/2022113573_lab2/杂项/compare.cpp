#include <iostream>
#include <cstring>

using namespace std;

int main()
{
	FILE* p1 = fopen("float_binary.dat", "wb");
	FILE* p2 = fopen("float_txt.txt", "w");
	FILE* p3 = fopen("char_binary.dat", "wb");
	FILE* p4 = fopen("char_txt.txt", "w");
	
	float num[100];
	char ch[100];
	for (int i = 1; i <= 100; i++)
	{
		num[i] = i;
		ch[i] = 'a' + i % 26;

		fprintf(p2, "%f\n", num[i]);
		fprintf(p4, "%c\n", ch[i]);
	}
	
	fwrite(num, sizeof(float), 100, p1);
	fwrite(ch, sizeof(char), 100, p3);

	fclose(p1);
	fclose(p2);
	fclose(p3);
	fclose(p4);

	return 0;
}

