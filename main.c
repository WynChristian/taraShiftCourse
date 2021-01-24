#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <conio.h>
#include <string.h>
#include <assert.h>

#define MAXDESTINATIONS 200
#define BUFFER_SIZE 1000
#define MAX 10
#define MAXSUM 20

// GLOBAL VARIABLE DECLARATION
char dest_name[MAXDESTINATIONS][18];
char dest_ppd[MAXDESTINATIONS][18];
char dest_ttx[MAXDESTINATIONS][18];
float dest_totalamt[MAXDESTINATIONS];
float dest_totalttx[MAXDESTINATIONS];
int dest_qty[MAXDESTINATIONS];

int dest_lines = 0;

#include "codes/structs.h"
#include "codes/salesReport.c"
#include "codes/UIdesigns.c"
#include "codes/manageDest.c"
#include "codes/reserveTicket.c"
#include "codes/buyTicket.c"
#include "codes/mainMenu.c"

//FUNCTIONS

//FUNCTIONS OUTSIDE main.c
// void destination(void);

//FUNCTIONS FOR
//void calculateTicketAmt(void);
//void calculateTravelTax (void);

int main(void)
{
	// system("COLOR 4E");
	// char given_name[20], last_name[20];

	// printf("\n\n\n   Input your Given Name: ");
	// scanf("%[^\n]", given_name);
	// printf("   Input your Last Name: ");
	// scanf("%s", last_name);
	// printf("\n   Passenger's Name: %s %s\n", given_name, last_name);

	// printf("\n\n\n\t\t\tWelcome to 'TaraShiftCourse' Airline %s %s\n", given_name, last_name);

	// printf("\n\n\n\t\t\t\tpress any key to continue");
	// _getch();
	Report salesReports[100];
	int totalCategory = 0;
	initialize(&salesReports, &totalCategory);

	choiceMain(&salesReports, &totalCategory);
	return 0;
}
