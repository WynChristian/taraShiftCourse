// typedef struct info Info;
typedef struct info
{
  char destination[100];
  int age;
  float price;
  float tax;
} Info;

// main function
void buyTicket(void);

// reserve

void reserved(void);
int scanData(FILE *, Info *);

// no reserve
void noReservation(void);
void getTotalPrice(int, int);

//SUBPROGS NA PART NG BUY TICKET
void buyTicket(void)
{
  // system("cls");
  // printUnderscore();
  printf("\n\t\t\t\t\t  BUY TICKET ");
  // printUnderscore();
  printf("\n\t\t\t       1  Reserved");
  printf("\n\t\t\t       2  No Reservation");
  printf("\n\t\t\t       3  Return to MAIN\n");
  int buyNum;
  printf("\n\t\t\t    Enter choice: ");
  scanf("%d", &buyNum);

  switch (buyNum)
  {
  case 1:
    // system("cls");
    reserved();
    break;
  case 2:
    system("cls");
    noReservation();
    break;
  case 3:
    system("cls");
    choiceMain();
    break;

  default: //choice of destination is not within case 1 to case 5
    printf("\n\t\t\t    Your choice is not available!\n");
    break;
  }
  buyTicket();
  return;
}

void reserved(void)
{
  int resCode;
  char filePathCode[100];

  printf("\n\t\t\t Enter reservation code: ");
  scanf("%d", &resCode);
  sprintf(filePathCode, "database/%d.txt", resCode);
  FILE *fileCode = fopen(filePathCode, "r");
  if (!fileCode)
  {
    printf("\nCode doesn't exist");
    return;
  }

  char proceedToBuyTicket;
  printf("\n\t\t\t Proceed to buy ticket? [y/n]: ");
  scanf("%s", &proceedToBuyTicket);

  if (proceedToBuyTicket == 'Y' || proceedToBuyTicket == 'y')
  {
    Info currentLine;
    FILE *transactionFile = fopen("transaction.txt", "a");

    while (scanData(fileCode, &currentLine))
    {
      fprintf(transactionFile, "\n%-15s %-10d %-10.2f %.2f",
              currentLine.destination, currentLine.age,
              currentLine.price, currentLine.tax);
    }
    fclose(transactionFile);
    // printf("\n\t\t\t\t Press any key to RETURN.");
    printf("\nTESTING sucess");
    buyTicket();
  }

  else if (proceedToBuyTicket == 'N' || proceedToBuyTicket == 'n')
  {

    printf("\n\t\t\t\t Press any key to RETURN.");
    _getch();
    buyTicket();
  }
  else
  {
    printf("\n\t\t\t\t Invalid keyword");
  }
  return;
}

int scanData(FILE *file, Info *data)
{
  //(*data).age
  // data->age
  int result;
  while ((result = fscanf(file, "%s %d %f %f",
                          &data->destination, &data->age,
                          &data->price, &data->tax)) == 1)
  {
    scanData(file, data);
  };

  if (result == EOF)
  {
    return 0;
  }
  else if (result != 4)
  {
    printf("Error reading data");
    return 0;
  }
  else
  {
    return 1;
  }
}

void getTotalPrice(int ppd, int userDesti)
{
  //int userDesti;
  int i = 0, j = 0, k = 0;
  int adultAge[MAX];
  int childAge[MAX];
  int childCount, adultCount;
  int age[MAXSUM];
  /*ADULTS*/
  printf("\n\t\t\t  How many adult?: ");
  scanf("%d", &adultCount);

  if (adultCount > 1 && adultCount < 11)
  {
    int count = 1, i = 0;
    while (count <= adultCount)
    {

      printf("\t\t\t  Enter age of adult %d: ", count);
      scanf("%d", &adultAge[i]);
      i++;
      count++;
    }

    //for(int i = 0; i < adultCount; ++i) {//temporary print kung nastore ba sa array
    //printf("array:%d\n", adultAge[i]);}
  }
  else if (adultCount == 1)
  {
    i = 0;
    {
      printf("\t\t\t  Enter age: ");
      scanf("%d", &adultAge[i]);
    }

    //for(int i = 0; i <adultCount; ++i){//print test kung nastore ba sa array,,,
    //printf("array: %d\n", adultAge[i]);}
  }
  else if (adultCount == 0)
  {
    printf("\n");
  }
  else
  {
    printf("\n\t\t    You have reached the maximum capacity per transaction.");
    printf("\n\t\t\t\t Press any key to return MAIN.");
    _getch();
    choiceMain();
  }

  /*CHILDREN*/
  printf("\n\t\t\t  How many children?: ");
  scanf("%d", &childCount);

  if (childCount > 1 && childCount < 11)
  {
    int count = 1, i = 0;
    while (count <= childCount)
    {

      printf("\t\t\t  Enter age of child %d: ", count);
      scanf("%d", &childAge[i]);
      i++;
      count++;
    }

    //for(int i = 0; i < childCount; ++i) {//print test kung nastore ba sa array,,,
    //printf("array: %d\n", childAge[i]);}
  }
  else if (childCount == 1)
  {
    i = 0;
    {
      printf("\t\t\t  Enter age: ");
      scanf("%d", &childAge[i]);
    }

    //for(int i = 0; i < childCount; ++i) {//print test kung nastore ba sa array,,,
    //printf("array: %d\n", childAge[i]);}
  }
  else if (childCount == 0)
  {
    printf("\n");
  }
  else
  {
    printf("\n\t\t    You have reached the maximum capacity per transaction.");
    printf("\n\t\t\t\t Press any key to return MAIN.");
    _getch();
    choiceMain();
  }
  // MERGE TWO ARRAYS
  /* adultAge */
  while (i < adultCount)
  {
    age[k] = adultAge[i];
    k++;
    i++;
  }
  /* childAge */
  while (j < childCount)
  {
    age[k] = childAge[j];
    k++;
    j++;
  }
  //Displaying elements of array 'age'
  int count = adultCount + childCount;
  //printf("\nMerged array is :");
  //for (i = 0; i < count; i++){
  //printf("%d ", age[i]);}

  //=================================================
  float discount[count];
  //Process Discounts
  i = 0;
  int n = 0;
  while (i < count)
  {
    if (age[i] <= 1 || age[i] >= 100)
    {
      discount[n] = 1;
    }
    else if (age[i] > 5 && age[i] < 60)
    {
      discount[n] = 0;
    }
    else if (age[i] > 1 && age[i] < 6)
    {
      discount[n] = .1;
    }
    else if (age[i] >= 60)
    {
      discount[n] = .2;
    }
    else
      printf("\n");
    n++;
    i++;
  }
  //printf("\nDiscount per age:\n");
  //for (i = 0; i < count; i++){
  //printf("%.1f\n", discount[i]);}

  float ticketAmt[count];
  //Process Ticket Amount
  int a;
  a = 0;
  i = 0;
  while (i < count && a < count)
  {
    ticketAmt[a] = ppd - (ppd * discount[i]);
    a++;
    i++;
  }
  //printf("prices for each age:\n");
  //for (i = 0; i < count; i++){
  //printf("%.2f\n", ticketAmt[i]);
  //fprintf(sales, "\t%.2f", ticketAmt[i]);
  //fprintf(reserve, "%.2f", ticketAmt[i]);}

  float totalPrice;
  //Process Total Price
  for (i = 0; i < count; i++)
  {
    totalPrice += ticketAmt[i];
  }
  printf("\n\t\t\t\tTotal ticket price:%.2f\n", totalPrice);

  float travelTax[count];
  //Process Travel Tax
  a = 0;
  i = 0;
  while (i < count && a < count)
  {
    travelTax[a] = ticketAmt[i] * atof(dest_ttx[userDesti]);
    a++;
    i++;
  }
  //   fprintf(sales, "\t%.2f", travelTax[i]);
  // fprintf(reserve, "\t\t%.2f", travelTax[i]);}

  FILE *sales = fopen("transaction.txt", "a");
  //FILE *reserve=fopen("reservation.txt", "a");

  if (sales == NULL)
  {
    printf("\t\t\t\t  transaction.txt not found! Exiting!\n");
    exit(1);
  }

  for (i = 0; i < count; i++)
  {
    fprintf(sales, "\n%s\t\t%d\t%.2f\t\t%.2f", dest_name[userDesti], age[i], ticketAmt[i], travelTax[i]);
    //fprintf(reserve, "\n%s\t%d\t%.2f\t\t%.2f", dest_name[userDesti],age[i],ticketAmt[i],travelTax[i]);
  }
  fclose(sales);

  return;
}

void noReservation(void)
{
  int userDesti;
  printUnderscore();
  printf("\n\t\t\t\t      FLIGHT DESTINATION\n");

  FILE *destcat;
  destcat = fopen("destcat.txt", "r");

  if (destcat == NULL)
  {
    printf("destcat.txt not found! Exiting!\n");
    exit(1);
  }

  int i = 0;

  for (i = 0; i < MAXDESTINATIONS; i++)
  {
    fscanf(destcat, "%64s\t%64s\t\t%64s", dest_name[i], dest_ppd[i], dest_ttx[i]);

    if (feof(destcat))
    {
      dest_lines = i + 1;
      break;
    }
  }
  fclose(destcat);

  for (i = 0; i < dest_lines; i++)
  {
    printf("\n\t\t\t\t%d   %s\t\t%s", i + 1, dest_name[i], dest_ppd[i]);
  }
  printf("\n\t\t\t\t%d   Return to MAIN\n", dest_lines + 1);

  printUnderscore();
  printf("\n\t\t\t  Select destination: ");
  scanf("%d", &userDesti);

  //printf("%.2f\n", ticketAmt[i]);
  //fprintf(sales, "\n%s", dest_name[userDesti]);

  dest_lines = dest_lines + 1;

  if (userDesti > dest_lines)
  {
    printf("\n\t\t\t    Your flight destination is not available.");
    printf("\n\t\t\t\t press any key to RETURN");
    _getch();
    buyTicket();
  }
  else if (userDesti == dest_lines)
  {
    choiceMain();
  }
  else
  {
    userDesti = userDesti - 1;
    int ppd = atoi(dest_ppd[userDesti]);

    getTotalPrice(ppd, userDesti);

    // calculateTravelTax(totalPrice,resDesti);
    printf("\n\t\t\t\t press any key to RETURN");
    _getch();
    buyTicket();
  }
  return;
}
