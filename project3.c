//----------------------------------------------------------------------------
// File:            d:\project3.c   Jeremiah Robinson
// Functions:       main()
//					PrintMenu()
//					PrintSubMenu()
//----------------------------------------------------------------------------

#include "amort.h"

#define SUMMARY_PROMPT "Press enter to display loan summary:"
#define DISPLAY_PAYMENTSIZE "The monthly payment amount is: "
#define MIN_PAYMENT "The minimum required number of monthly payments is: %d\n"
#define DISPLAY_LOANSIZE "The total amount of loan is: "
#define MAXIMUM_MONTHS "The maximum allowed number of monthly payments is: %d\n"
#define EIGHTY_PERCENT .8

void PrintMenu(void);
void PrintSubMenu(void);
//----------------------------------------------------------------------------
// Function:        int main(void)
//
// Title:           Loan Calculator
// Version:			1.0
//
// Description:		A program for loan calculations.  User has 4 options to
//					calculate a loan's size, the monthly payment size, the 
//					number of months or the	interest rate.  The results are 
//					displayed to the screen and the	user may print an 
//				    amortization table to screen or save to file. 
//											
//
// Parameters:	    none
// Input:		    User selects from the 4 loan calculation options, or to 
//					quit. Then user is prompted to enter amounts used in the 
//				    calculations. Interest rate, loan amount, months, and/or 
//					payment size. When results are displayed, user has option 
//					to restart, print or save table from sub-menu. If saving
//					table, user enters a filename.
//
// Output:          Printed to console: Main menu, prompts for amounts, amounts
//					when entered, final loan results, sub-menu, and amortization
//				    table. 
//					Output to text file: amortization table with a 
//					running loan balance and a breakdown of each monthly payment
//				    put towards the principal and the interest.  			
//			
// Returns:		    EXIT_SUCCESS or EXIT_FAILURE
// Programmer:	    Jeremiah Robinson               
// Date:            11/04/2016  
//
// Environment:     Hardware: Intel Xeon PC 
//                  Software: MS Windows 10. Compiles under Microsoft Visual 
//							  C++.Net 2015 
//
// Calls:			Local functions: PrintMenu(), PrintSubMenu()
//
//					Amort library functions:  ReadInterestRate(), ReadLoanSize()
//					ReadPaymentSize(), ReadMonths(), CleanBuffer(), 
//					PrintResults(), GetNumberOfMonths(), GetPaymentAmount(),
//					GetLoanAmount(), GetInterestRate(), PrintTable(),
//					SaveTable()
//  
// History Log:    11/04/2016  JR completed version 1.0
//----------------------------------------------------------------------------

int main(void)
{
	char ch;
	int months = 0;
	int minMonths = 0;
	int maxMonths = 0;
	int years = 0;
	int monthsRemaining = 0;
	double interestRate = 0;         // Annual interest rate
	double loanSize = 0;             // Total amount of loan
	double paymentSize= 0;           // Total amount of 1 monthly payment
	double minPaymentSize = 0;       // Min payment size for option 3
	const int HUNDRED_YEARS = 1200;  // Max length of loan in months for option 4
	
		
	PrintMenu();
	while(ch = getchar())
		switch (ch)
		{
		case '1':;  //Calculate monthly payment size
		case 'P':;
		case 'p': 
			interestRate = ReadInterestRate();
			loanSize = ReadLoanSize();
			months = ReadMonths();
			paymentSize = getPaymentAmount(months, loanSize, interestRate);
			puts("\n\n\n"LINE "\n\n");
			printf(DISPLAY_PAYMENTSIZE, paymentSize);
			PrintCommas(paymentSize);
			puts(LINE);
			puts(SUMMARY_PROMPT);
			while (getchar() == '\n')
			{
				system("cls");
				PrintResults(loanSize, paymentSize, interestRate, months);
				break;
			}
			PrintSubMenu();
			break;
		case '2':;   // Calculate loan size
		case 'L':;
		case 'l':  
			interestRate = ReadInterestRate();
			paymentSize = ReadPaymentSize();
			months = ReadMonths();
			loanSize = getLoanAmount(paymentSize, months, interestRate);	
			puts("\n\n\n"LINE "\n\n");
			printf(DISPLAY_LOANSIZE, loanSize);
			PrintCommas(loanSize);
			puts(LINE);
			puts(SUMMARY_PROMPT);
			while (getchar() == '\n')
			{
				system("cls");
				PrintResults(loanSize, paymentSize, interestRate, months);
				break;
			}
			PrintSubMenu();
			break;
		case '3':;   //Calculate number of monthly payments
		case 'N':;
		case 'n':   
			interestRate = ReadInterestRate();
			loanSize = ReadLoanSize();
			minPaymentSize = 
				(loanSize * (interestRate / MONTHLY_DIVISOR)) + ONE_CENT;
			printf("\n\nThe minimum payment size is: $%.2lf \n\n",
				minPaymentSize);
			while ((paymentSize = ReadPaymentSize()) < minPaymentSize)
			{
				puts("Please enter a larger payment size");
			}
			months = getNumberOfMonths(paymentSize, loanSize, interestRate);
			years = (int)floor(months / MONTHS_PER_YEAR);    
			monthsRemaining = months % MONTHS_PER_YEAR;
			puts("\n\n\n"LINE "\n\n");
			printf(DISPLAY_MONTHS, months, years, monthsRemaining);
			puts(LINE);
			puts(SUMMARY_PROMPT);
			while (getchar() == '\n')
			{
				system("cls");
				PrintResults(loanSize, paymentSize, interestRate, months);
				break;
			}
			PrintSubMenu();
			break;
		case '4':;    // Calculate interest rate
		case 'i':;   
		case 'I': 
			loanSize = ReadLoanSize();
			//Check if monthly payment is big enough to cover loan
			do         
			{  
				paymentSize = ReadPaymentSize();
				minMonths = (int)ceil(loanSize / paymentSize);
				if (minMonths > HUNDRED_YEARS)
					puts("Please enter a larger monthly payment\n");
			} while (minMonths > HUNDRED_YEARS);

			puts("Enter number of monthly payments");
			// Check if loan term is less than the max loan term(100 years)
			do		                      // and long enough to cover loan.
			{		 
				maxMonths = (paymentSize >= loanSize ) ? 
					(int)ceil(loanSize / paymentSize) * MONTHS_PER_YEAR : 
					(paymentSize >= loanSize * EIGHTY_PERCENT) ?
					HUNDRED_YEARS * HALF : HUNDRED_YEARS;
				safeReadInt(&months, "Enter number of monthly payments");
				printf(MIN_PAYMENT, minMonths);
				printf(MAXIMUM_MONTHS, maxMonths);
			} while ((months < minMonths) || (months > maxMonths));
			interestRate = getInterestRate(months, loanSize, paymentSize);
			PrintResults(loanSize, paymentSize, interestRate, months);
			PrintSubMenu();
			break;
		case 't':;    //Display table
		case 'T': 
			DisplayTable(loanSize, paymentSize, interestRate, months);
			PrintSubMenu();
			break;
		case 's' :;   //Save table to file
		case 'S' : 
			SaveTable(loanSize, paymentSize, interestRate, months);
			PrintSubMenu();
			break;
		case 'r':;    //Restart
		case 'R': 
			system("cls");
			PrintMenu();
			interestRate = 0;
			paymentSize = 0;
			loanSize = 0;
			months = 0;
			break;
		case 'q':;    //Quit
		case 'Q': return EXIT_SUCCESS;
		}
	return EXIT_SUCCESS;
}
//----------------------------------------------------------------------------
// Function: void PrintMenu(void)
//												  
// Description:  Prints the main menu to user's screen.  It displays 4 options
//				 to calculate loan, monthly payment, term or interest rate.  
//				 Also has option 'q' to quit program. 
//				 		 				  	     			
// Parameters:	  none
// Returns:       none
// Programmer:	  Jeremiah Robinson
//                  
// Date:          11/14/2016  
//  
// Environment:   Hardware: Intel Xeon PC 
//			      Software: MS Windows 10. Compiles under Microsoft Visual 
//						    C++.Net 2015    
//
// Input:          none
// Output:         Main menu is printed to user's screen.
// Called By:      ReadPaymentSize()
//				   PrintResults()
//				   ReadLoanSize()
// Calls:          
// History Log:    11/14/2016  JR completed version 1.0
//----------------------------------------------------------------------------
void PrintMenu(void)
{
	puts("\n\n");
	for (size_t col = 0; col < TOTAL_COLUMNS ; col++)  //Top border
		putchar(220);
	putchar('\n');
	for (size_t row = 0; row < 4; row++)			  //Top margin
	{
		putchar(221);
		for (size_t col = 0; col < TOTAL_COLUMNS -2; col++)
			putchar(32);
		putchar(222);
		putchar('\n');
	}
	putchar(221);
	printf(TAB_CENTER" Loan Calculator version 1.0" TAB_CENTER " ");
	putchar(222);
	putchar('\n');
	for (size_t row = 0; row < 3; row++)               //Skip 3 lines
	{
		putchar(221);
		for (size_t col = 0; col < TOTAL_COLUMNS - 2; col++)
			putchar(32);
		putchar(222);
		putchar('\n');
	}
	putchar(221);
	printf(TAB_CENTER"1. Calculate [P]ayment size");
	printf(TAB_CENTER "  ");
	putchar(222);
	putchar('\n');
	putchar(221);
	printf(TAB_CENTER"2. Calculate [L]oan size");
	printf(TAB_CENTER "\t");
	putchar(222);
	putchar('\n');
	putchar(221);
	printf(TAB_CENTER"3. Calculate [N]umber of payments");
	printf("\t\t\t");
	putchar(222);
	putchar('\n');
	putchar(221);
	printf(TAB_CENTER"4. Calculate [I]nterest");
	printf(TAB_CENTER "\t");
	putchar(222);
	putchar('\n');
	for (size_t row = 0; row < 2; row++)                  // Skip lines
	{
		putchar(221);
		for (size_t col = 0; col < TOTAL_COLUMNS - 2; col++)
			putchar(32);
		putchar(222);
		putchar('\n');
	}
	putchar(221);
	printf(TAB_CENTER"   Press [Q] to quit");
	printf(TAB_CENTER"\t\t");
	putchar(222);
	putchar('\n');
	for (size_t row = 0; row < 4; row++)                  //Bottom margin
	{
		putchar(221);
		for (size_t col = 0; col < TOTAL_COLUMNS - 2; col++)
			putchar(32);
		putchar(222);
		putchar('\n');
	}
	for (size_t col = 0; col < TOTAL_COLUMNS; col++)      //Bottom row
		putchar(223);
	putchar('\n');
}
//----------------------------------------------------------------------------
// Function: void PrintSubMenu(void)
//												  
// Description:  Prints the sub menu to user's screen with 2 options to either 
//			     display amortization table to screen or save to txt file. 
//				 Also shows option 'r' to restart and 'q' to quit program. 		
//				 		 				  	     			
// Parameters:	  none
// Returns:       none
// Programmer:	  Jeremiah Robinson
//                  
// Date:          11/14/2016  
//  
// Environment:   Hardware: Intel Xeon PC 
//			      Software: MS Windows 10. Compiles under Microsoft Visual 
//						    C++.Net 2015    
//
// Input:          none
// Output:         Sub Menu is printed to user's screen.
// Called By:      ReadPaymentSize()
//				   PrintResults()
//				   ReadLoanSize()
// Calls:          
// History Log:    11/14/2016  JR completed version 1.0
//----------------------------------------------------------------------------
void PrintSubMenu(void)
{
	puts("\n"LINE "\n");
	puts("Press 'T' to create and display table");
	puts("Press 'S' to Save table to file. \nPress 'R' when done to Restart \n");
	puts("Press 'Q' to quit");
	puts(LINE);
}


