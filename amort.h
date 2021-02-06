//----------------------------------------------------------------------------
// File:			d:\amort.h     
//
// Description:     Header file used with Amort library (amort.c)
//
// Programmer:      Jeremiah Robinson
// Date:            11/04/2016
//
//
// History Log:    11/04/2016  JR completed version 1.0
//----------------------------------------------------------------------------

#ifndef AMORT_H
#define AMORT_H
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#pragma warning(disable: 4996)

#define LINE "__________________________________________________________________"
#define HEAD "|  Month     | Payments | Principal Paid |"
#define HEAD2 " Interest Paid | Loan Balance |"
#define FORMAT "\n%5d       $%12.2lf   $%12.2lf   $%12.2lf   $%12.2lf"
#define DISPLAY_INTEREST "Interest Rate: %.3lf%c "
#define ROUNDED_INTEREST "(%d %d/%d)%% rounded to nearest 1/8th\n\n"
#define DISPLAY_MONTHS "Number of payments: %d or (%d years, %d months)\n"
#define INTEREST_PROMPT "Please enter the annual interest rate. (>= 0) Ex: 5.4\n"
#define LOAN_PROMPT "Please enter the amount of loan (positive number only): \n"
#define MONTHS_PROMPT "Enter number of payments (between 1 and 6000): \n"
#define PAYMENT_PROMPT "\nEnter amount of monthly payment (greater than 0):\n "
#define PERCENT '%'
#define ONE_CENT .01
#define MONTHLY_DIVISOR 1200
#define TOTAL_ROWS 40
#define TOTAL_COLUMNS 73
#define TAB_CENTER "                     "
#define MONTHS_PER_YEAR 12
#define HUNDRED 100
#define ONE 1
#define HALF .5
#define INDENT = "		"
#define FIVE_HUNDRED_YEARS 6000
#define THOUSAND_YEARS 12000
#define MILLION 1000000
#define BILLION 1000000000
#define TRILLION 1000000000000
#define THOUSAND 1000


void cleanBuffer();
void safeReadInt(int* number_ptr, const char* prompt);
void safeReadDouble(double* number_ptr, const char* prompt);

void DisplayTable(const double loanSize, double paymentSize, 
	const double interestRate, int months);
void SaveTable(const double loanSize, double paymentSize, 
	const double interestRate, int months);
void PrintResults(const double loanSize, const double paymentSize,
	const double interestRate, const int months);
void PrintCommas(const double amount);

double ReadInterestRate();
double ReadLoanSize();
double ReadPaymentSize();
double roundInterest(double interest, const int fraction);
double getPaymentAmount(const int numberOfPayments, const double principal,
	const double interestRate);
double getLoanAmount(const double payment, const int numberOfPayments, 
	const double interestRate);
double getInterestRate(const int months, const double principal, 
	const double payment);
int ReadMonths();
int getNumberOfMonths(const double payment, const double principal, 
	const double interestRate);

#endif
