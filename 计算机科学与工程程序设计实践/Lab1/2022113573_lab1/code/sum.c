#include <stdio.h>

int main()
{
	int n;
	printf("Please input an integer: ");
	scanf("%d", &n);

	int ans = 0;
	for (int i = 1; i <= n; i++)
		ans += i;

	printf("The sum is: %d\n", ans);
	return 0;
}

