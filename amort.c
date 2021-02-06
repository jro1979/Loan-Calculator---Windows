//----------------------------------------------------------------------------
// File:			d:\amort.c     Jeremiah Robinson
//
// Description      Amort library. Functions for working with money & loans
//
// Functions:	    void safeReadInt(int* number_ptr, const char* prompt)
//					void safeReadDouble(double* number_ptr, const char* prompt)
//					void PrintCommas(double amount)
//					void cleanBuffer()
//					void DisplayTable(const double loanSize, double paymentSize,
//						const double interestRate, int months)
//					void SaveTable(const double loanSize, double paymentSize,
//						const double interestRate, int months)
//					void PrintResults(const double loanSize, const double
//					   paymentSize, const double interestRate, const int months)
//					double getPaymentAmount(const int months, const double 
//						principal, const double interestRate)
//					double getLoanAmount(const double payment, const int months,
//						const double interestRate)
//					int getNumberOfMonths(const double payment, const double 
//					    principal, const double interestRate)
//					double roundInterest(double interest, const int fraction)
//					double getInterestRate(const int months, const double 
//						principal, const double payment)
//					double ReadInterestRate()
//					double ReadLoanSize()
//					double ReadPaymentSize()
//					int ReadMonths()
//----------------------------------------------------------------------------

#include "amort.h"

void safeReadInt(int* number_ptr, const char* prompt)
{
	while((scanf("%d", number_ptr)) != 1)
	{
		puts(prompt);
		cleanBuffer();
	}
	cleanBuffer();
}
void safeReadDouble(double* number_ptr, const char* prompt)
{
	while((scanf("%lf", number_ptr)) != 1)
	{
		puts(prompt);
		cleanBuffer();
	}
	cleanBuffer();
}
void cleanBuffer()
{	
	while(getchar() != '\n')
		;
}
//----------------------------------------------------------------------------
//Function: double getPaymentAmount(const int months, const double principal, 
//					                const double interestRate)
//
// Description:		Calculates and returns the amount of each monthly payment
//					(rounded up to the nearest cent).
//
// Parameters:	    const (int)    months		  Number of monthly payments
//				    const (double) principal      Total amount of loan
//				    const (double) interestRate   Annual interest rate
//
// Returns:		    (double) payment  Amount of monthly payment. Rounded to 
//									  nearest cent 
// Programmer:	    Jeremiah Robinson
//                  
// Date:            11/04/2016  
//  
// Environment:     Hardware: Intel Xeon PC 
//                  Software: MS Windows 10. Compiles under Microsoft Visual
//							  C++.Net 2015 
//        
// Called By:      main() 
// History Log:    11/04/2016  JR completed version 1.0
//----------------------------------------------------------------------------
double getPaymentAmount(const int months, const double principal, 
	const double interestRate)
{
	double payment = 0;
	double interestExp = 0;
	double monthlyInterest = interestRate / MONTHLY_DIVISOR;
	if (interestRate == 0)
	{
		payment = principal / months;
	}
	else
	{
		interestExp = pow(monthlyInterest + ONE, (double)months);
		payment = 
			(interestExp / (interestExp - ONE)) * principal * monthlyInterest;
	}
	payment = ceil(payment * HUNDRED) / HUNDRED;
	return payment;
}
//----------------------------------------------------------------------------
// Function:	    double getLoanAmount(const double payment, const int months, 
//										 const double interestRate)
//
// Description:		Calculates the amount of the entire loan
//					(rounded off to the nearest cent).
//
// Parameters:	   const (double) payment		 Amount of monthly payment
//				   const (int)    months		 Number of months 
//				   const (double) interestRate   Annual interest rate
//
// Returns:		   (double) principal   Amount of loan, rounded to nearest cent.
// Programmer:	   Jeremiah Robinson
//                  
// Date:           11/04/2016  
//  
// Environment:    Hardware: Intel Xeon PC 
//                 Software: MS Windows 10. Compiles under Microsoft Visual 
//							 C++.Net 2015 
//        
// Called By:      main() 
// History Log:    11/04/2016  JR completed version 1.0
//----------------------------------------------------------------------------
double getLoanAmount(const double payment, const int months, 
	const double interestRate)
{
	double principal = 0;
	double monthlyInterest = interestRate / MONTHLY_DIVISOR;
	double interestExp = pow(monthlyInterest + ONE, (double)months);
	if (interestRate == 0)
	{
		principal = payment * months;
	}
	else
	{
		principal = 
			((interestExp - 1) / (monthlyInterest * interestExp)) * payment;
	}
	principal = round(principal * HUNDRED) / HUNDRED;
	return principal;
}
//----------------------------------------------------------------------------
// Function: int getNumberOfMonths(const double payment, const double principal,
//								   const double interestRate)
//
// Description:	   Calculates the number of months needed to repay loan
//				
// Parameters:	   const (double) payment		  Amount of monthly payment
//				   const (double) principal       Amount of loan
//				   const (double) interestRate    Annual interest rate
//
// Returns:		   (double) monthsRounded   Number of months or payments
// Programmer:	   Jeremiah Robinson
//                  
// Date:           11/04/2016  
//  
// Environment:    Hardware: Intel Xeon PC 
//                 Software: MS Windows 10. Compiles under Microsoft Visual 
//						     C++.Net 2015 
//        
// Called By:      main() 
// History Log:    11/04/2016  JR completed version 1.0
//----------------------------------------------------------------------------
int getNumberOfMonths(const double payment, const double principal, 
	const double interestRate)
{
	double monthlyInterest = interestRate / MONTHLY_DIVISOR;
	double numberOfMonths = 0;
	int monthsRounded = 0;

	numberOfMonths = (interestRate == 0) ? principal / payment 
		: (log(payment) - log(payment - (principal * monthlyInterest)))
		/ log(1 + monthlyInterest);
	monthsRounded = (int)ceil(numberOfMonths);
	return monthsRounded;
}
//----------------------------------------------------------------------------
// Function:	    double roundInterest(double interest, const int fraction)
//
// Description:		Rounds number to a nearest fraction. 
//				  
//				
// Parameters:	   (double)   interestRate        Annual interest rate	
//				   const (int)    fraction        The fraction to round to
//
// Returns:		   (double) interest	    Annual interest rate, rounded.
// Programmer:	   Jeremiah Robinson
//                  
// Date:           11/04/2016  
//  
// Environment:    Hardware: Intel Xeon PC 
//                 Software: MS Windows 10. Compiles under Microsoft Visual
//					         C++.Net 2015 
//        
// Called By:      ReadInterestRate()
//				   PrintResults()
//			       SaveTable(), Print Table()
//     
// History Log:    11/04/2016  JR completed version 1.0
//----------------------------------------------------------------------------
double roundInterest(double interest, const int fraction)
{
	interest = round(interest * fraction) / fraction;
	return interest;
}
//----------------------------------------------------------------------------
// Function:	  double getInterestRate(const int months, const double 
//						                principal, const double payment)
//
// Description:	  Calculates and returns the interest rate rounded to 1/8th 
//				  percent. Loop increments a test number & checks for a match
//				  of monthly payment size in the getPaymentAmount() formula.
//
// Parameters:	    const (int) months:		    Number of months or payments
//					const (double) principal:   Amount of loan 				   
//					const (double) payment:	    Amound of monthly payment
//				   
// Returns:		   (double) interestRate  Annual interest rate 
// Programmer:	   Jeremiah Robinson
//                  
// Date:           11/04/2016  
//  
// Environment:    Hardware: Intel Xeon PC 
//                 Software: MS Windows 10. Compiles under Microsoft Visual 
//							 C++.Net 2015 
//       
// Called By:      main()
// History Log:    11/04/2016  JR completed version 1.0
//----------------------------------------------------------------------------
double getInterestRate(const int months, const double principal, 
	const double payment)
{
	double interestRate = 0;
	long double testNumber = 0;
	double range = .01; 
	long long depth = 100;
	int counter = 0;
	const double MAX_PAYMENT = 1.01;   // Set break point for payment loop > 1.
	double rangeInterval = 0;          // 
	const int DEPTH_INTERVAL = 10;     // Expand test numbers.

	rangeInterval = (principal > BILLION) ? HUNDRED :
		(principal > MILLION) ? 10 : .001;
	while (interestRate == 0)
	{
		for (long long j = 1; j <= LONG_MAX; j++)
		{
			long double monthlyInterest = 0;
			long double interestExp = 0;

			//Use formula in getPaymentAmount() to setup test number 
			monthlyInterest = (long double)j / depth;
			interestExp = (long double)pow(monthlyInterest + ONE, months);
			testNumber = (long double)(interestExp / (interestExp - ONE)) 
				* principal * monthlyInterest;
			//Check matching of test number & monthly payment
			if ((testNumber <= (payment + range)) && 
				(testNumber >= (payment - range)))
			{   
				interestRate = monthlyInterest * MONTHLY_DIVISOR;
				break;
			}
			//Check if test number was skipped over, and restart
			if (testNumber > (payment * MAX_PAYMENT)) 
				break;
		}
		counter++;						     //Number was skipped over
		printf("Scan number: %d \n", counter);
		range += rangeInterval;		         //Increase matching range 
		depth *= DEPTH_INTERVAL;	         // and shift decimal 
										
	} 
	return interestRate;
}
//----------------------------------------------------------------------------
// Function: double ReadInterestRate()
//
// Description:  Prompts user to enter in annual interest rate and checks that
//				 it is greater than 0 then rounds it to nearest 1/8th percent.   
//				
// Parameters:	 none
//
// Returns:     (double) interestRate   Annual interest rate rounded to 1/8th 
//										percent
// Programmer:	 Jeremiah Robinson
//                  
// Date:         11/04/2016  
//  
// Environment:  Hardware: Intel Xeon PC 
//               Software: MS Windows 10. Compiles under Microsoft Visual 
//						   C++.Net 2015 
//        
// Input: User enters annual interest rate on keyboard
// Output: interestRate is returned and printed to screen.
// Called By:      main()
// Calls:		   roundInterest(), safeReadDouble()
// History Log:    11/04/2016  JR completed version 1.0
//----------------------------------------------------------------------------
double ReadInterestRate()
{
	double interestRate = 0;
	int floorInterest = 0;
	int topEighth = 0;
	const int EIGHT = 8;
	
	do
	{
		puts(INTEREST_PROMPT);
		safeReadDouble(&interestRate, INTEREST_PROMPT);
	} while (interestRate < 0);
	
	interestRate = roundInterest(interestRate, EIGHT);
	floorInterest = (int)floor(interestRate);
	topEighth = (int)((interestRate - floorInterest) * EIGHT);
	printf(DISPLAY_INTEREST ROUNDED_INTEREST,
		interestRate, PERCENT, floorInterest, topEighth, EIGHT);

	return interestRate;
}
//----------------------------------------------------------------------------
// Function: double ReadLoanSize()
//
// Description:  Prompts user to enter in amount of loan and checks that it is
//				 greater than 0 then rounds to nearest cent.   
//				
// Parameters:	 none
//
// Returns:     (double) loanSize    Amount of loan.
// Programmer:	 Jeremiah Robinson
//                  
// Date:         11/04/2016  
//  
// Environment:   Hardware: Intel Xeon PC 
//                Software: MS Windows 10. Compiles under Microsoft Visual 
//							C++.Net 2015 
//        
// Input:          User enters total amount of loan on keyboard
// Output:         loanSize is returned and printed to screen.
// Called By:      main()
// Calls:		   safeReadDouble()
// History Log:    11/04/2016  JR completed version 1.0
//----------------------------------------------------------------------------
double ReadLoanSize()
{
	double loanSize = 0;

	do
	{
		puts(LOAN_PROMPT);
		safeReadDouble(&loanSize, LOAN_PROMPT);
	} while (loanSize <= 0);
	
	loanSize = floor(loanSize * HUNDRED + HALF) / HUNDRED;
	PrintCommas(loanSize);

	return loanSize;
}
//----------------------------------------------------------------------------
// Function: double ReadPaymentSize()
//
// Description:  Prompts user to enter in amount of monthly payment and checks 
//				 that it is greater than 0 then rounds to nearest cent.   
//				
// Parameters:	 none
//
// Returns:     (double) paymentSize     Amount of monthly payment.
// Programmer:	 Jeremiah Robinson
//                  
// Date:         11/04/2016  
//  
// Environment:   Hardware: Intel Xeon PC 
//                Software: MS Windows 10. Compiles under Microsoft Visual 
//							C++.Net 2015 
//       
// Input:          User enters amount of monthly payment on keyboard
// Output:         paymentSize is returned and printed to screen.
// Called By:      main()
// Calls:		   safeReadDouble()
// History Log:    11/04/2016  JR completed version 1.0
//----------------------------------------------------------------------------
double ReadPaymentSize()
{
	double paymentSize = 0;
		
	do
	{
		puts(PAYMENT_PROMPT);
		safeReadDouble(&paymentSize, PAYMENT_PROMPT);
	} while (paymentSize <= 0);
	
	paymentSize =  floor(paymentSize * HUNDRED + HALF) / HUNDRED;
	PrintCommas(paymentSize);
	
	return paymentSize;
}
//----------------------------------------------------------------------------
// Function: int ReadMonths()
//
// Description:  Prompts user to enter in number of monthly payments. Checks 
//				 that the number is > 0.    
//				
// Parameters:	 none
//
// Returns:      (int) months		Number of monthly payments.
// Programmer:	 Jeremiah Robinson
//                  
// Date:         11/04/2016  
//  
// Environment:    Hardware: Intel Xeon PC 
//                 Software: MS Windows 10. Compiles under Microsoft Visual 
//						     C++.Net 2015 
//        
// Input:          User enters number of months on keyboard
// Output:         months is returned and printed to screen.
// Called By:      main()
// Calls:		   safeReadInt()
// History Log:    11/04/2016  JR completed version 1.0
//----------------------------------------------------------------------------
int ReadMonths()
{
	int months = 0;
	int years = 0;
	int monthsRemaining = 0;

	do
	{
		puts(MONTHS_PROMPT);
		safeReadInt(&months, MONTHS_PROMPT);
	} while ((months <= 0) || (months > FIVE_HUNDRED_YEARS));
	
	years = (int)floor(months / MONTHS_PER_YEAR);
	monthsRemaining = months % MONTHS_PER_YEAR;
	printf(DISPLAY_MONTHS, months, years, monthsRemaining);

	return months;
}
//----------------------------------------------------------------------------
// Function: void DisplayTable(const double loanSize, double paymentSize, 
//							   const double interestRate, const int months)
//
// Description:  Displays amortization table to screen.  Monthly payment is 
//				 broken down into separate payments for interest and principal
//				 Each row represents one month of payments subtracted from the
//				 running loan balance.
//			     			
// Parameters:	 const double  loanSize			 Total size of loan
//				       double  paymentSize       Monthly payment amount
//				 const double  interestRate      Annual interest rate
//               const   int   months            Number of monthly payments
//
// Returns:      none
// Programmer:	 Jeremiah Robinson
//                  
// Date:         11/04/2016  
//  
// Environment:   Hardware: Intel Xeon PC 
//                Software: MS Windows 10. Compiles under Microsoft Visual 
//						    C++.Net 2015 
//       
// Input:          None
// Output:         Amortization table is displayed to screen
// Called By:      main()
// Calls:          RoundInterest()
// History Log:    11/04/2016  JR completed version 1.0
//----------------------------------------------------------------------------
void DisplayTable(const double loanSize, double paymentSize, 
	              const double interestRate, const int months)
{
	double interestPaid = 0;
	double principalPaid = 0;
	double loanBalance = loanSize;
	double roundedInterest = roundInterest(interestRate, 8);
	printf("Amortization Table for a: $%.2lf loan at: ", loanSize);
	printf("%.3lf%c interest for %d months\n\n", 
		roundedInterest, PERCENT, months);
	printf(HEAD HEAD2 "\n");
	for (size_t i = 1; i <= months; i++)
	{
		interestPaid = loanBalance * (roundedInterest / MONTHLY_DIVISOR);
		interestPaid = floor(interestPaid * HUNDRED + HALF) / HUNDRED;
		principalPaid = paymentSize - interestPaid;
		loanBalance -= principalPaid;
		if ((i == months) && (loanBalance != 0))
		{
			paymentSize += loanBalance;
			principalPaid += loanBalance;
			loanBalance -= loanBalance;
		}
		printf(FORMAT, i, paymentSize, principalPaid, interestPaid, loanBalance);
	}
}
//----------------------------------------------------------------------------
// Function: void SaveTable(const double loanSize, double paymentSize, 
//							const double interestRate, const int months)
//
// Description:  Saves amortization table to txt file.  Monthly payment is 
//				 broken down into separate payments for interest and principal.
//				 Each row represents one month of payments subtracted from the
//				 running loan balance.
//			     			
// Parameters:	 const double  loanSize			 Total size of loan
//				       double  paymentSize       Monthly payment amount
//				 const double  interestRate      Annual interest rate
//               const    int  months            Number of monthly payments
//
// Returns:      none
// Programmer:	 Jeremiah Robinson
//                  
// Date:         11/04/2016  
//  
// Environment:   Hardware: Intel Xeon PC 
//                Software: MS Windows 10. Compiles under Microsoft Visual 
//							C++.Net 2015  
//
// Input:          When prompted, user enters a filename for the table
// Output:         Amortization table is saved to program's root directory
// Called By:      main()
// Calls:		   RoundInterest()
// History Log:    11/04/2016  JR completed version 1.0
//----------------------------------------------------------------------------
void SaveTable(const double loanSize, double paymentSize, 
			   const double interestRate, const int months)
{
	FILE *fp = NULL;
	double interestPaid = 0;
	double principalPaid = 0;
	double loanBalance = loanSize;
	char filename[FILENAME_MAX] = "";
	double roundedInterest = roundInterest(interestRate, 8);

	printf("Please enter a filename (no spaces) : \n");
	scanf_s("%s", filename, FILENAME_MAX);
	system("cls");
	fp = fopen(filename, "w");
	fprintf(fp, "Amortization Table for a: $%.2lf loan at: ", loanSize);
	fprintf(fp, "%.3lf%c interest for %d months\n\n", 
		roundedInterest, PERCENT, months);
	fprintf(fp, HEAD HEAD2 "\n");
	for (size_t i = 1; i <= months; i++)
	{
		interestPaid = loanBalance * (roundedInterest / MONTHLY_DIVISOR);
		interestPaid = floor(interestPaid * HUNDRED + HALF) / HUNDRED;
		principalPaid = paymentSize - interestPaid;
		loanBalance -= principalPaid;
		if ((i == months) && (loanBalance != 0))   //adjust last months payment
		{
			paymentSize += loanBalance;
			principalPaid += loanBalance;
			loanBalance -= loanBalance;
		}
		fprintf(fp, FORMAT,
			i, paymentSize, principalPaid, interestPaid, loanBalance);
	}
	fclose(fp);
	printf("Table has been printed to file: %s \n", filename);
	printf("It is located in the root directory of the program\n");
}
//----------------------------------------------------------------------------
// Function: void PrintResults(const double loanSize, const double paymentSize,
//							   const double interestRate, const int months)
//							  
// Description:  Displays results of loan calculations to user's screen
//				 Shows amount of loan, monthly payment, number of months, 
//				 total, and interest rate.		  
//			     			
// Parameters:	 const double  loanSize			 Total size of loan
//				 const double  paymentSize       Monthly payment amount
//				 const double  interestRate      Annual interest rate
//                       int   months            Number of monthly payments
//
// Returns:      none
// Programmer:	 Jeremiah Robinson
//                  
// Date:         11/04/2016  
//  
// Environment:  Hardware: Intel Xeon PC 
//			     Software: MS Windows 10. Compiles under Microsoft Visual 
//						   C++.Net 2015 
//      
//
// Input:          When prompted, user enters a filename for the table
// Output:         Amortization table is saved to program's root directory
// Called By:      main()
// Calls:          RoundInterest()
// History Log:    11/04/2016  JR completed version 1.0
//----------------------------------------------------------------------------
void PrintResults(const double loanSize, const double paymentSize,
	const double interestRate, const int months)
{
	const int EIGHT = 8;
	int topEighth = 0;
	int floorInterest = 0;
	double roundedInterest = roundInterest(interestRate, EIGHT);
	double totalPayments = paymentSize * months;
	int years = (int)floor(months / MONTHS_PER_YEAR);
	int remainingMonths = months % MONTHS_PER_YEAR;

	floorInterest = (int)floor(roundedInterest);
	topEighth = (int)((roundedInterest - floorInterest) * EIGHT);
	
	system("cls");
	puts("\n\n\n");
	puts(LINE "\n");
	printf("Loan amount               : ");
	PrintCommas(loanSize);
	printf("Monthly payment size      : ");
	PrintCommas(paymentSize);
	printf("Number of monthly payments: %d (%d Years, %d Months)	\n",
		months, years, remainingMonths);
	puts(LINE);
	printf("Total payments            : ");
	PrintCommas(totalPayments);
	printf("\n\n\tThe interest rate is:       %.3lf%c \n",
		interestRate, PERCENT);
	printf("\n\t(%d %d/%d)%% rounded to nearest 1/8th%%\n"
		, floorInterest, topEighth, EIGHT);
}
//----------------------------------------------------------------------------
// Function:     void PrintCommas(const double amount)
//												  
// Description:  Prints larger numbers between 999 and 999 billion to screen 
//				 with added comma separators so people can read them easier.
//				 		 			 				  	     			
// Parameters:	  const (double) amount	  The number to print out
//		
// Returns:      none
// Programmer:	 Jeremiah Robinson
//                  
// Date:         11/14/2016  
//  
// Environment:   Hardware: Intel Xeon PC 
//			      Software: MS Windows 10. Compiles under Microsoft Visual 
//						    C++.Net 2015    
//
// Input:          none
// Output:         Number with comma separators is printed to user's screen.
// Called By:      ReadPaymentSize()
//				   PrintResults()
//				   ReadLoanSize()
// Calls:          
// History Log:    11/14/2016  JR completed version 1.0
//----------------------------------------------------------------------------
void PrintCommas(const double amount)
{
	int commas = 0;
	int hundreds = 0;					//the hundreds place
	int thousands = 0;                  //the thousands place
	int intRemainder = 0;
	long int millions = 0;              //the millions place
	long long int billions = 0;			//the billions place
	long long int balance = 0;
	long int divisor = 0;
	long long int intAmount = (long long int)floor(amount);
	
	double tempDouble = round((amount - intAmount) * HUNDRED) / HUNDRED;
	intRemainder = (int)(round(tempDouble * 100));
	
	if (amount < THOUSAND)              //For number with 0 commas
	{
		printf("$%lld.%02d\n", intAmount, intRemainder);
		return;
	}
	balance = intAmount;               //Figure out how many commas it needs
	commas = ((amount >= THOUSAND) && (amount < MILLION)) ? 1 :
		     ((amount >= MILLION) && (amount < BILLION)) ? 2 :
		     ((amount >= BILLION) && (amount < TRILLION)) ? 3 : 4;
	divisor = (commas == 1) ? THOUSAND :
		      (commas == 2) ? MILLION : 
		      (commas == 3) ? BILLION : TRILLION;
	if (commas == 1)                     //Number in the thousands
	{
		thousands = (int)floor(intAmount / divisor);
		printf("$%d,", thousands);
		balance -= (long long)thousands * divisor;
		printf("%03lld.%02d\n", balance, intRemainder);
	}
	if (commas == 2)                   // Number in the millions
	{
		millions = (long)balance / divisor;
		printf("$%ld,", millions);
		balance -= (long long)(millions * divisor);
		thousands = (int)(balance / THOUSAND);
		printf("%03d,", thousands);
		balance -= thousands * THOUSAND;
		printf("%03lld.%02d\n", balance, intRemainder);
	}
	if (commas == 3)                   // Number in the billions
	{
		billions = (long long)floor(intAmount / divisor);
		printf("$%lld,", billions);
		balance -= (long long)(billions * divisor);
		millions = (long)(balance / MILLION);
		printf("%03ld,", millions);
		balance -= (long long)(millions * MILLION);
		thousands = (int)balance / THOUSAND;
		printf("%03d,", thousands);
		balance -= thousands * THOUSAND;
		printf("%03lld.%02d\n", balance, intRemainder);
	}
	if (commas >= 4)                  // Number in trillions or more
		printf("$%.2lf\n", amount);
}


