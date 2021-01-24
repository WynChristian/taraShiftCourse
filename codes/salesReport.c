
void initialize(Report (*)[], int *);
void salesReport(Report (*)[], int *);
int readDest(FILE *, Report (*)[], int, int *);
void updateReport(Report (*)[], int *);

void salesReport(Report (*report)[], int *total)
{
  // time_t t = time(NULL);
  // struct tm tm = *localtime(&t);
  // char filename[64];
  // sprintf(filename,
  //         "transaction-%d-%02d-%02d-%02d-%02d-%02d.txt",
  //         tm.tm_year + 1900, tm.tm_mon + 1,
  //         tm.tm_mday, tm.tm_hour,
  //         tm.tm_min, tm.tm_sec);

  // // INITIALIZES TICKET VARIABLES
  // int i = 0;
  // int finalqty = 0;
  // float finalAmt = 0;
  // float finalttx = 0;

  // // INITIALIZES THE TICKET
  // FILE *ticket;
  // ticket = fopen(filename, "w+");

  // fprintf(ticket, "\n   FLIGHT    QUANTITY\t AMOUNT\t\tTRAVEL TAX\n");
  // for (i = 0; i < dest_lines; i++)
  // {
  //   finalqty += dest_qty[i];
  //   finalAmt += dest_totalamt[i];
  //   finalttx += dest_totalttx[i];
  //   //FIX WEIRD BUG
  //   if (strlen(dest_name[i]) <= 8)
  //     fprintf(ticket, "  %s\t\t%i\t%.2f\t %.2f\n",
  //             dest_name[i], dest_qty[i], dest_totalamt[i], dest_totalttx[i]);
  //   else
  //     fprintf(ticket, "  %s\t%i\t%.2f\t %.2f\n", dest_name[i], dest_qty[i], dest_totalamt[i], dest_totalttx[i]);
  // }
  // fprintf(ticket, "  TOTAL\t\t%i\t%.2f\t %.2f\n", finalqty, finalAmt, finalttx);
  // fclose(ticket);

  // //READS THE TICKET
  // int c;
  // FILE *file;
  // file = fopen(filename, "r");
  // if (file)
  // {
  //   while ((c = getc(file)) != EOF)
  //     putchar(c);

  //   time_t rawTime;
  //   struct tm *timeInfo;
  //   printf("\n  Prepared by: ");
  //   time(&rawTime);
  //   timeInfo = localtime(&rawTime);
  //   printf("\n  Date Prepared: %s\n", asctime(timeInfo));
  //   fclose(file);
  // }
  // getch();
  printf("\n%-15s %-10s %-10s %s\n\n", "Flight", "Quantity", "Amount", "Travel Tax");
  int totalNum = *total;

  Report totalReport = {
      .quantity = 0,
      .amount = 0,
      .tax = 0,
  };
  strcpy(totalReport.destination, "TOTAL");

  for (int i = 0; i < totalNum; i++)
  {
    printf("\n%-14s %-10d %-10.2f %.2f", (*report)[i].destination, (*report)[i].quantity, (*report)[i].amount, (*report)[i].tax);
    totalReport.quantity += (*report)[i].quantity;
    totalReport.amount += (*report)[i].amount;
    totalReport.tax += (*report)[i].tax;
  }
  printf("\n%-14s %-10d %-10.2f %.2f", totalReport.destination, totalReport.quantity, totalReport.amount, totalReport.tax);
  printf("\nPress any KEY to return to the MAIN");
  getch();
  return;
}

void initialize(Report (*report)[], int *total)
{

  FILE *destinationFile = fopen("destcat.txt", "r");
  int index = 0;

  while (readDest(destinationFile, report, index, total))
  {
    index += 1;
  }
  updateReport(report, total);
}

int readDest(FILE *file, Report (*report)[], int i, int *total)
{
  int result;
  // temp var
  char tempDestination[100];
  float tempPrice, tempTax;
  while ((result = fscanf(file, "%s %f %f", tempDestination, &tempPrice, &tempTax)) == 1)
  {
    readDest(file, report, i, total);
  }

  if (result == EOF)
  {
    printf("\n TESTING EOF success!");
    return 0;
  }
  else if (result != 3)
  {
    printf("\nERROR READING DEST FILE");
    return 0;
  }
  else
  {
    strcpy((*report)[i].destination, tempDestination);
    (*report)[i].quantity = 0;
    (*report)[i].amount = 0;
    (*report)[i].tax = 0;
    *total += 1;
    // testing
    // printf("\nTESTING (*report)[%d]", i);
    // printf("\nTESTING \t dest = %s", (*report)[i].destination);
    return 1;
  }
}

void updateReport(Report (*shakeAndBake)[], int *total)
{
  FILE *reportFile = fopen("salesReport.txt", "w");
  fprintf(reportFile, "%-10s %-10s %-10s\n", "FLIGHT", "QUANTITY", "AMOUNT");
  for (int i = 0; i < *total; i++)
  {
    fprintf(reportFile, "\n%-15s %-10d %-10.2f",
            (*shakeAndBake)[i].destination,
            (*shakeAndBake)[i].quantity,
            (*shakeAndBake)[i].amount);
  }
  fclose(reportFile);
}