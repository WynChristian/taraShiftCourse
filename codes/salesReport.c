
void salesReport(void)
{
  time_t t = time(NULL);
  struct tm tm = *localtime(&t);
  char filename[64];
  sprintf(filename,
          "transaction-%d-%02d-%02d-%02d-%02d-%02d.txt",
          tm.tm_year + 1900, tm.tm_mon + 1,
          tm.tm_mday, tm.tm_hour,
          tm.tm_min, tm.tm_sec);

  // INITIALIZES TICKET VARIABLES
  int i = 0;
  int finalqty = 0;
  float finalAmt = 0;
  float finalttx = 0;

  // INITIALIZES THE TICKET
  FILE *ticket;
  ticket = fopen(filename, "w+");

  fprintf(ticket, "\n   FLIGHT    QUANTITY\t AMOUNT\t\tTRAVEL TAX\n");
  for (i = 0; i < dest_lines; i++)
  {
    finalqty += dest_qty[i];
    finalAmt += dest_totalamt[i];
    finalttx += dest_totalttx[i];
    //FIX WEIRD BUG
    if (strlen(dest_name[i]) <= 8)
      fprintf(ticket, "  %s\t\t%i\t%.2f\t %.2f\n", dest_name[i], dest_qty[i], dest_totalamt[i], dest_totalttx[i]);
    else
      fprintf(ticket, "  %s\t%i\t%.2f\t %.2f\n", dest_name[i], dest_qty[i], dest_totalamt[i], dest_totalttx[i]);
  }
  fprintf(ticket, "  TOTAL\t\t%i\t%.2f\t %.2f\n", finalqty, finalAmt, finalttx);
  fclose(ticket);

  //READS THE TICKET
  int c;
  FILE *file;
  file = fopen(filename, "r");
  if (file)
  {
    while ((c = getc(file)) != EOF)
      putchar(c);

    time_t rawTime;
    struct tm *timeInfo;
    printf("\n  Prepared by: ");
    time(&rawTime);
    timeInfo = localtime(&rawTime);
    printf("\n  Date Prepared: %s\n", asctime(timeInfo));
    fclose(file);
  }
  getch();
  return;
}