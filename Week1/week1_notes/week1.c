#define MAX_LENGTH 9

//variables in c
int main(){
	MAX_LENGTH
	return 0;
}

//converting data type
int i = 5;
float f = i;
int j;
j = (int) f; //casting float to int

//arrays in c
int a[10]; /* one-dimensional array of size 10 */
a[2] = 3; /*initialise the third element */

//enumerated types in c
enum boolean {NO, YES}; /* NO is 0. YES is 1 */
enum months {JAN = 1, FEB, MAR, APR, MAY, JUN, JUL, AUG, SEP, OCT, NOV, DEC}; /* FEB is 2, MAR is 3 */

//scanf funciton -> scanning.c : receiving input from stdin
#include <stdio.h>

int main(void)
{
	int day, month, year;
	
	printf("Enter the date: ");
	scanf("%d %d %d", &day, &month, &year);
	
	printf("%d-%d-%d\n", day, month, year);
	return 0;
}
