#include <stdio.h>
#include <math.h>
#include <stdlib.h>

//function
int *find_largest(int the_array[], int num_elements)
{
	int i;
	int max = the_array[0];
	
	//compare each element with the current max
	for (i = 1; i < num_elements; i++)
	{
		if(the_array[i] > max)
		{
			max = the_array[i];
		}
	}
	//dynamic memory allocation (the malloc function from the <stdlib.h> library)
	int *iptr = (int*)malloc (sizeof(int)*1);
	iptr = &max; //iptr now store the add of max
	//the address of the max is stored into the pointer
	return iptr;
}

int main()
{
	int array[] = {1, 2, 3, 4, 5, 200};
	int length = 6;
	int *largest = find_largest(array, length);
	printf("The largest element in the given array is: %d. \n", *largest);
}

