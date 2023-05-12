#include <stdio.h>

int main(void)
{
	float miles;
	float km;

	printf("Enter the number of miles: ");
	if(scanf("%f", &miles))
	{
		km = miles * 1.60934;
		printf("%f miles = %f km\n", miles, km);	
	}
	else
		puts("Invalid input");
	
	
	return 0;
}
