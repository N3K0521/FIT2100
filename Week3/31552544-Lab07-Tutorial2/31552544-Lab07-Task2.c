#include <stdio.h>
#include <math.h>

int main()
{
	int n;
	int sum = 0;
	
	printf("Please enter number of elements (positve integer): \n");
	scanf("%d", &n);
	//since array starts from 0, the actual lenghth will be number of elements - 1
	int array[n-1];
	
	int i;
	printf("Please enter your array: \n");
	//store all input elements in an array using for loops
	for (i = 0; i < n; i++)
	{
		scanf("%d", &array[i]);
	}
	//sum each element to the 'sum' variable
	for (int j = 0; j < n; j++)
	{
		sum += array[j];
	}
	
	printf("The sum of your array is: %d \n", sum);
	
	return 0;
	
}

