void reserveTicket(int);
void getResTotalPrice(int, int, int);

void reserveTicket(int dest_lines)
{
  // printUnderscore();
  printf("\n\t\t\t\t\tRESERVE TICKET");
  // printUnderscore();
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

  int userDesti;
  printf("\n\t\t\t  Select reserve destination: ");
  scanf("%d", &userDesti);

  dest_lines = dest_lines + 1;
  if (userDesti > dest_lines)
  {
    printf("\n\t\t\t    Your flight destination is not available.");
    printf("\n\t\t\t\t press any key to RETURN");
    _getch();
    choiceMain();
  }

  else if (userDesti == dest_lines)
  {
    choiceMain();
  }

  else
  {
    userDesti = userDesti - 1;
    int ppd = atoi(dest_ppd[userDesti]);

    srand(time(NULL));
    int random = rand();

    getResTotalPrice(ppd, userDesti, random);
    char res_yesno;
    printf("\n\t\t\t\t   Proceed your reservation[y/n]?: ");
    scanf("%s", &res_yesno);

    if (res_yesno == 'Y' || res_yesno == 'y')
    {
      printf("\n\t\t\t\tYour reservation code: %d\n", random);
      printf("\n\t\t\t\tpress any key to RETURN");
      _getch();
      choiceMain();
    }
    else
    {
      printf("\n\t\t\t\tpress any key to RETURN");
      _getch();
      choiceMain();
    }
    return;
  }
}

//SUBPROGS NA PART NG RESERVATION TICKET

//=======================================RESERVATION
void getResTotalPrice(int ppd, int userDesti, int code)
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

  float totalPrice = 0;
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

  char filePath[100];
  sprintf(filePath, "database/%d.txt", code);

  FILE *backEnd = fopen(filePath, "a");
  FILE *reserve = fopen("reservation.txt", "a");

  if (reserve == NULL)
  {
    printf("\t\t\t\t  transaction.txt not found! Exiting!\n");
    exit(1);
  }

  for (i = 0; i < count; i++)
  {
    fprintf(backEnd, "%-15s %-8d %-10.2f %.2f\n",
            dest_name[userDesti], age[i], ticketAmt[i], travelTax[i]);
    fprintf(reserve, "\n%s\t%d\t%.2f\t\t%.2f", dest_name[userDesti], age[i], ticketAmt[i], travelTax[i]);
  }
  fclose(reserve);
  fclose(backEnd);

  return;
}
