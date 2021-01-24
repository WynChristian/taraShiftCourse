
void anotherRecord(Report (*)[], int *);
void manageDesti(Report (*)[], int *);
void deleteLine(FILE *, FILE *, const int);
//SUBPROGS NA PART NG MANAGE DESTI

void addNewDesti(Report (*report)[], int *total)
{
  char save_yesno, anotherRec;
  char addDesti[50];
  float addPrice;
  float addTax;

  FILE *readdestcat;
  readdestcat = fopen("destcat.txt", "r");
  if (readdestcat == NULL)
  {
    printf("destcat.txt not found! Exiting!\n");
    exit(1);
  }

  int i = 0;
  for (i = 0; i < MAXDESTINATIONS; i++)
  {
    fscanf(readdestcat, "%64s\t%64s\t\t%64s", dest_name[i], dest_ppd[i], dest_ttx[i]);
    if (feof(readdestcat))
    {
      dest_lines = i + 1;
      break;
    }
  }
  fclose(readdestcat);

  // <promptshit> olraayyt
  printf("\n\t\t\t Destination Code: %03d", dest_lines + 1);
  printf("\n\t\t\t Enter new destination: ");
  scanf("%s", addDesti);
  printf("\n\t\t\t Enter price ticket: ");
  scanf("%f", &addPrice);
  printf("\n\t\t\t Enter travel tax: ");
  scanf("%f", &addTax);

  addTax *= 0.01;

  printf("\n\t\t\t SAVE this RECORD[y/n]? ");
  scanf("%s", &save_yesno);
  if (save_yesno == 'Y' || save_yesno == 'y')
  {
    FILE *inFile;
    inFile = fopen("destcat.txt", "a");
    if (inFile == NULL)
    {
      printf("\nFailed to open file.\n");
      exit(1);
    }
    fprintf(inFile, "\n%-15s %-10.2f %.2f", addDesti, addPrice, addTax);
    fclose(inFile);

    // NEW: append in salesReport
    int index = *total;
    strcpy((*report)[index].destination, addDesti);
    (*report)[index].quantity = 0;
    (*report)[index].amount = 0;
    (*report)[index].tax = 0;
    *total += 1;
    printf("\nTESTING (*report)[%d]", index);
    printf("\nTESTING \t dest = %s", (*report)[index].destination);
  }

  anotherRecord(report, total);
  return;
}

void anotherRecord(Report (*report)[], int *total)
{
  char anotherRec;
  printf("\n\t\t\t Another Record [y/n]: ");
  scanf("%s", &anotherRec);

  if (anotherRec == 'Y' || anotherRec == 'y')
  {
    addNewDesti(report, total);
  }
  else if (anotherRec == 'N' || anotherRec == 'n')

  {
    printf("\n\t\t\t\t Press any key to RETURN.");
    _getch();
    manageDesti(report, total);
  }
  else
  {
    printf("\n\t\t\t\t Invalid keyword");
  }
  return;
}

void editDesti(void)
{
  char save_yesno, editAnotherRec;
  int editDesti;
  float newprice;
  FILE *readdestcat;
  readdestcat = fopen("destcat.txt", "r");
  if (readdestcat == NULL)
  {
    printf("destcat.txt not found! Exiting!\n");
    exit(1);
  }

  int i = 0;
  for (i = 0; i < MAXDESTINATIONS; i++)
  {
    fscanf(readdestcat, "%64s\t%64s\t\t%64s", dest_name[i], dest_ppd[i], dest_ttx[i]);
    if (feof(readdestcat))
    {
      dest_lines = i + 1;
      break;
    }
  }
  fclose(readdestcat);

  FILE *fPtr;
  FILE *fTemp;
  char path[100] = {"destcat.txt"};

  char buffer[BUFFER_SIZE];
  char newline[BUFFER_SIZE];
  int line, count;

  printf("\n\t\t\tEnter destination code: ");
  scanf("%d", &line);

  fflush(stdin);

  printf("\n\t\tEnter new destination and ticket price:", line);
  fgets(newline, BUFFER_SIZE, stdin);

  printf("\n\t\t\t SAVE Changes[y/n]? ");
  scanf("%s", &save_yesno);

  if (save_yesno == 'Y' || save_yesno == 'y')
  {
    fPtr = fopen(path, "r");
    fTemp = fopen("replace.tmp", "w");

    /* fopen() return NULL if unable to open file in given mode. */
    if (fPtr == NULL || fTemp == NULL)
    {
      printf("\nUnable to open file.\n");
      printf("Please check whether file exists and you have read/write privilege.\n");
      exit(EXIT_SUCCESS);
    }
    count = 0;

    while ((fgets(buffer, BUFFER_SIZE, fPtr)) != NULL)
    {
      count++;
      if (count == line)
        fputs(newline, fTemp);
      else
        fputs(buffer, fTemp);
    }

    fclose(fPtr);
    fclose(fTemp);

    remove(path);
    rename("replace.tmp", path);

    printf("\n\t\t\tSaving this record...");
  }

  return;
}

//DELETEDESTI
void deleteDesti(void)
{
  char anotherRec;

  do
  {
    FILE *srcFile;
    FILE *tempFile;

    char delete_yesno;
    int line;
    char path[100] = {"destcat.txt"};

    printf("\n\n\t\t\tEnter destination code: ");
    scanf("%d", &line);

    printf("\n\t\t\tAre you sure you want to delete this record[y/n]? ");
    scanf("%s", &delete_yesno);

    if (delete_yesno == 'Y' || delete_yesno == 'y')
    {
      srcFile = fopen(path, "r");
      tempFile = fopen("delete-line.tmp", "w");

      if (srcFile == NULL || tempFile == NULL)
      {
        printf("Unable to open file.\n");
        exit(EXIT_FAILURE);
      }

      // Move src file pointer to beginning
      rewind(srcFile);

      // Delete given line from file.
      deleteLine(srcFile, tempFile, line);

      fclose(srcFile);
      fclose(tempFile);

      remove(path);
      rename("delete-line.tmp", path);

      srcFile = fopen(path, "r");

      printf("\n\t\t\t\t     Deleted successfully.");

      printf("\n\t\t\t    Another Record [y/n]: ");
      scanf("%s", &anotherRec);

      fclose(srcFile);
    }

    else if (delete_yesno == 'N' || delete_yesno == 'n')
    {
      printf("\n\n\t\t\t  press any key to RETURN");
      _getch();
      return;
    }

    else
    {
      printf("\n\t\t\t\t Invalid keyword");
      printf("\n\t\t\t\t Press any key to RETURN.");
      _getch();
      return;
    }

  } while (anotherRec == 'Y' || anotherRec == 'y');

  if (anotherRec == 'N' || anotherRec == 'n')
  {
    printf("\n\t\t\t\t Press any key to RETURN.");
    _getch();
    return;
  }
  else
  {
    printf("\n\t\t\t\t Invalid keyword");
    printf("\n\t\t\t\t Press any key to RETURN.");
    _getch();
    return;
  }
  return;
}

//DELETEFLINE
void deleteLine(FILE *srcFile, FILE *tempFile, const int line)
{
  char buffer[BUFFER_SIZE];
  int count = 1;

  while ((fgets(buffer, BUFFER_SIZE, srcFile)) != NULL)
  {
    /* If current line is not the line user wanted to remove */
    if (line != count)
      fputs(buffer, tempFile);
    count++;
  }
}

void displayAll(void)
{
  printUnderscore();
  printf("\n\t\t\t\t       List of Destinations\n");
  printf("\n\t\t\t\t  Destinations\t   Price\n\n");
  FILE *destcat;
  destcat = fopen("destcat.txt", "r");

  if (destcat == NULL)
  {
    printf("destcat.txt not found! Exiting!\n");
    exit(0);
  }

  int i = 0;

  for (i = 0; i < MAXDESTINATIONS; i++)
  {
    fscanf(destcat, "%64s\t\t%64s\t\t%64s", dest_name[i], dest_ppd[i], dest_ttx[i]);

    if (feof(destcat))
    {
      dest_lines = i + 1;
      break;
    }
  }
  fclose(destcat);

  for (i = 0; i < dest_lines; i++)
  {
    if (strlen(dest_name[i]) <= 8)
      printf("\t\t\t\t   %s\t   %s\n", dest_name[i], dest_ppd[i]);
    else
      printf("\t\t\t\t   %s\t   %s\n", dest_name[i], dest_ppd[i]);
  }

  printf("\n\t\t\t\t  press any key to RETURN");
  _getch();

  return;
}

void manageDesti(Report (*report)[], int *total)
{
  system("cls");
  printUnderscore();
  printf("\n\t\t\t\t      MANAGE DESTINATION ");
  printUnderscore();
  printf("\n\t\t\t\t   1  Add New Destination");
  printf("\n\t\t\t\t   2  Edit");
  printf("\n\t\t\t\t   3  Delete");
  printf("\n\t\t\t\t   4  Display All");
  printf("\n\t\t\t\t   5  Return to MAIN\n");

  int manage;

  printf("\n\t\t\t Enter your choice: ");
  scanf("%d", &manage);

  switch (manage)
  {
  case 1:
    system("cls");
    addNewDesti(report, total);
    break;
  case 2:
    system("cls");
    editDesti();
    break;
  case 3:
    system("cls");
    deleteDesti();
    break;
  case 4:
    system("cls");
    displayAll();
    break;
  case 5:
    system("cls");
    choiceMain();
    break;

  default:
    printf("\n\t\t\t  Your choice is not available!\n"); //choice of destination is not within case 1 to case 5
    break;
  }
  manageDesti(report, total);
  return;
}
