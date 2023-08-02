/*
*****************************************************************************
                        Assignment 1 - Milestone 3
Full Name  :
Student ID#:
Email      :
Section    :

Authenticity Declaration:
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider. This submitted
piece of work is entirely of my own creation.
*****************************************************************************
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#include "core.h"

//////////////////////////////////////
// USER INTERFACE FUNCTIONS
//////////////////////////////////////

// Clear the standard input buffer
void clearInputBuffer(void)
{
    // Discard all remaining char's from the standard input buffer:
    while (getchar() != '\n')
    {
        ; // do nothing!
    }
}

// Wait for user to input the "enter" key to continue
void suspend(void)
{
    printf("<ENTER> to continue...");
    clearInputBuffer();
    putchar('\n');
}


//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

//
// Copy your work done from Milestone #2 (core.c) into this file
// - Organize your functions in the same order as they are listed in the core.h file
//

//1 inputInt
int inputInt(void)
{
	char newLine;
	int value = 0;


	do
	{
		scanf("%d%c", &value, &newLine);


		if (!(newLine == '\n'))
		{
			clearInputBuffer();

			printf("Error! Input a whole number: ");
		}

	} while (!(newLine == '\n'));

	return value;
}

//2  inputIntPositive

int inputIntPositive(void)
{
	int valueintpositive = 0;

	while (!(valueintpositive > 0))
	{
		scanf("%d", &valueintpositive);


		if (!(valueintpositive > 0))
		{
			clearInputBuffer();

			printf("ERROR! Value must be > 0: ");
		}

	}
	return valueintpositive;
}

//3 inputIntRange
int inputIntRange(int lower_bound, int upper_bound)
{
	char alive = 'b';

	int lower_highervalue;

	do
	{
		scanf("%d%c", &lower_highervalue, &alive);

		if (alive != '\n')
		{
			
			printf("Error! Input a whole number: ");
			scanf("%d%c", &lower_highervalue, &alive);
		}

		if (lower_highervalue < lower_bound || lower_highervalue > upper_bound)
		{
			
			printf("ERROR! Value must be between %d and %d inclusive: ", lower_bound, upper_bound);
			
			scanf("%d%c", &lower_highervalue, &alive);
		}
	} while ((lower_highervalue < lower_bound && lower_highervalue > upper_bound) && (alive != '\n'));

	return lower_highervalue;
}

//4 inputChrOption
char inputCharOption(const char cstringarray[])
{

	
		char a, b;
		int counter = 0; int i = 0;
		scanf(" %c%c", &a, &b);
		while (b != '\n') {
			clearInputBuffer();
			printf("ERROR: Character must be one of [%s]: ", cstringarray);
			scanf(" %c%c", &a, &b);

		}
		do {
			for (i = 0; cstringarray[i] != '\0' && counter == 0; i++)
			{
				if (cstringarray[i] == a) {
					counter = 1;
					//j = str[i];

				}
			}

			if (counter != 1 || b != '\n') {

				printf("ERROR: Character must be one of [%s]: ", cstringarray);
				scanf(" %c%c", &a, &b);
			}
		} while (counter == 0 || b != '\n');

		return a;



}

//5 inputCString

void inputCString(char* cstringargument, int minimum, int maximum)
{

	char csentence[99];
	int i, x = 0;
	int words = 0;


	do
	{

		scanf(" %[^\n]", csentence);

		for (i = 0; csentence[i] != '\0'; i++)
		{


			words++;

		}

		if (words >= minimum && words <= maximum)
		{


			x = 1;

		}

		else
		{

			if (words > maximum)
			{
				if (minimum == maximum)
				{
					clearInputBuffer();
					printf("ERROR: String length must be exactly %d chars: ", maximum);
					words = 0;
				}
				else
				{
					clearInputBuffer();
					printf("ERROR: String length must be no more than %d chars: ", maximum);
					words = 0;
				}
			}
			else if (words < minimum)
			{
				if (minimum == maximum)
				{
					clearInputBuffer();
					printf("ERROR: String length must be exactly %d chars: ", maximum);
					words = 0;
				}
				else
				{
					clearInputBuffer();
					printf("ERROR: String length must be between %d and %d chars: ", minimum, maximum);
					words = 0;
				}
			}
		}




	} while (x != 1);

	for (i = 0; i < words; i++)
	{
		cstringargument[i] = csentence[i];
	}cstringargument = csentence;

	//*cstringargument = csentence;



}
//6 displayFormattedPhone
void displayFormattedPhone(const char* pointerdisplay)
{



	int i, words = 0;

	if (pointerdisplay != NULL)
	{


		for (i = 0; pointerdisplay[i] != '\0'; i++)
		{

			words++;
			if (pointerdisplay[i] == 'z')
			{
				words--;
			}

		}


		if (words == 10)
		{
			printf("(");
			for (i = 0; i < 3; i++)
			{
				printf("%c", pointerdisplay[i]);
			}
			printf(")");
			for (i = 0; i < 3; i++)
			{
				printf("%c", pointerdisplay[i + 3]);
			}
			printf("-");
			for (i = 0; i < 4; i++)
			{
				printf("%c", pointerdisplay[i + 6]);
			}
		}
		else
		{
			printf("(___)___-____");


		}
	}
	else
	{
		printf("(___)___-____");
	}

}




//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////
