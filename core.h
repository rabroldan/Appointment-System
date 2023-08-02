/*
*****************************************************************************
                       
Full Name  : Ronald Roldan

Authenticity Declaration:
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider. This submitted
piece of work is entirely of my own creation.
*****************************************************************************
*/

//////////////////////////////////////
// USER INTERFACE FUNCTIONS
//////////////////////////////////////

// Clear the standard input buffer
void clearInputBuffer(void);

// Wait for user to input the "enter" key to continue
void suspend(void);


//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////
//1
int inputInt(void);
//2
int inputIntPositive(void);
//3
int inputIntRange(int lower_bound, int upper_bound);
//4
char inputCharOption(const char cstringarray[]);
//5
void inputCString(char* cstringargument, int minimum, int maximum);

//6
void displayFormattedPhone(const char* pointerdisplay);


// !!! DO NOT DELETE THE BELOW LINE !!!
#endif // !CORE_H
