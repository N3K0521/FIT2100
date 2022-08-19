#include <stdio.h>

int main(){
	//initializing the varaibles
	int num;
	int res;
	
	printf("Please enter zero or positive integer:");
	scanf("%d", &num);
	//if enter number is not a positive integer, the programm will stop and warn you
	if(num < 0)
	{
		printf("Invalid input.\n");
	}
	else
	{
		//new varaibles
		int i = num, res = 1;
		//n! = n*(n-1)*((n-1)-1)*...*1
		while (num / i != num)
		{
			res *= i;
			i--;
		}
		printf("The factorial of %d is: %d.\n", num, res);
	
	}
	return 0;
}
