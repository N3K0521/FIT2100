#include <stdio.h>
#include <string.h>

int main()
{
	char string[40];
	printf("Enter a non-NULL string: ");
	scanf("%s", &string);
	
	//head is the first string letter, tail is the last
	int head = 0;
	int tail = strlen(string)-1;

	//string[1]=string[-1]; head = tail -> go to the next digit (head++, tail--)
	while (tail > head) {
		if (string[head++] != string[tail--]) {
			printf("The string entered is not palindrome.\n");
		}
		else {
			printf("The string entered is palindrome.\n");
		}
	}

	return 0;
}
