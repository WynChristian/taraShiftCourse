//----------------MAIN Screen----------------
void choiceMain(void)
{
  system("cls");
  // printEquals();
  printf("\n\t\t\t\t   FLIGHT RESERVATION SYSTEM\n ");
  printf("\n\t\t\t\t   1  Manage Destination");
  printf("\n\t\t\t\t   2  Reserve Ticket");
  printf("\n\t\t\t\t   3  Buy Ticket");
  printf("\n\t\t\t\t   4  Sales Report");
  printf("\n\t\t\t\t   5  Exit\n");
  // printEquals();

  int num;
  printf("\n\t\t\t    Input your choice: ");
  scanf("%d", &num);

  switch (num)
  {
  case 1:
    system("cls");
    manageDesti();
    break;
  case 2:
    system("cls");
    reserveTicket(dest_lines);
    break;
  case 3:
    system("cls");
    buyTicket();
    break;
  case 4:
    system("cls");
    salesReport();
    break;
  case 5:
    break;

  default:
    //choice of destination is not within case 1 to case 5
    printf("\n\t\t\tYour choice is not available!\n");
    break;
  }

  return;
}