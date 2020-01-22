#include <stdio.h>
#include <time.h>
#include <stdlib.h>


/*
Parameters, int divisor, int quotient
This function asks the user a division question
Uses scanf to recieve an input
If input is equal to the quotient, return 1
else return 2
*/
int division(int divisor, int quotient)
{
	int dividend;
	int a;
	dividend = divisor * quotient;
	printf("What is the Answer to: %d / %d = __\n", dividend, divisor);
	scanf("%d", &a);
	if(a == quotient)
	{
		
		printf("Correct!\n");
		return 1;

	}	
	else
	{
		
		printf("Wrong! The correct answer is %d\n", quotient);
		return 2;
	}
}

/*
This is the main function for division
It creates 2 random numbers
Then, using a while loop, it calls the division function 10 times
Keeps track of the users score
Prints out the users score at the end
*/
int main(void)
{
	int divisor;
	int quotient;
	int dividend;
	int count;
	int a;
	int score;

	srand((int)time(NULL));
	while(count != 10)
	{
		divisor = rand () % 12 + 1;
		quotient = rand () % 13;

		if((division(divisor, quotient)) == 1)
		{
			score = score + 1;
		}
		else
		{
			score = score + 0;
		}
		count++;
	}
	printf("Your Score is: %d out of 10\n", score);
	return 0;
}
