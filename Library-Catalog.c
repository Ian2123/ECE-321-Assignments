/*
Author: Ian Isely
Date: 3/23/2019

Description:
  This program simulates a library database where the user can enter a book, remove a book,
  or print all available books. Once done the program will write the results to a file
  named "library.txt" from oldest to newest.

Contributors: Ian Isely
PS: The list is already a sorted linked list sorted by oldest->newest publication year so no
    print sorted option.
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 60

//Sorted Linked List Declaration
typedef struct list_tag
{
  char Title[MAX], Author[MAX];
  int year;
  float price;
  struct list_tag *next;
} ListNode;

typedef ListNode *Slist;

//Prototypes
void SlistInsert(Slist *sp, char TitleI[], char AuthorI[], int yearI, float priceI);
void SlistRemove(Slist *sp, char TitleR[]);
void SlistPrint(Slist *sp);
void SlistInit(Slist *sp);
void ExitFile(FILE *fout, Slist *sp);

int main() 
{
  //Variable Declarations
  Slist sl;
  char Title[MAX], Author[MAX], Buffer[MAX];
  int choice, year;
  float price;
  FILE *fout;

  SlistInit(&sl);

  //Continuous loop until select Exit
  while(choice != 4)
  {
    printf("---------------\n");
    printf("(1) Insert Book\n(2) Print Books\n(3) Remove Book\n(4) Exit\n");
    printf("Choice: ");
    scanf("%d", &choice);

    if(choice == 1) //Insert A Book
    {
      fgets(Buffer, MAX, stdin); //Catch Newline
      printf("\nEnter Title: ");
      fgets(Title, MAX, stdin);
      printf("Enter Author: ");
      fgets(Author, MAX, stdin);
      printf("Enter Publication Year: ");
      scanf("%d", &year);
      printf("Enter Price: ");
      scanf("%f", &price);

      SlistInsert(&sl, Title, Author, year, price);
    }
    else if(choice == 2) //Print Books (oldest->newest)
    {
      SlistPrint(&sl);
    }
    else if(choice == 3) //Remove A book
    {
      printf("\nEnter Title: ");
      fgets(Buffer, MAX, stdin); //Catch Newline
      fgets(Title, MAX, stdin);

      SlistRemove(&sl, Title);
    }
    else continue; //Exit or Loop
  }

  printf("\nPrinting to file 'library.txt'");
  ExitFile(fout, &sl);
  return 0;
}

void SlistInsert(Slist *sl, char TitleI[], char AuthorI[], int yearI, float priceI)
{
  int i;

  //Creation of New Node
  ListNode *n = (ListNode *) malloc(sizeof(ListNode));
  if(n == NULL)
  {
    printf("Out of memory, quit program");
    exit(1);
  }

  //Load New Node
  strcpy(n->Title, TitleI);
  strcpy(n->Author, AuthorI);
  n->year = yearI;
  n->price = priceI;

  //Insert/Sort Node 
  while(*sl != NULL && (*sl)->year < yearI)
    sl = &((*sl)->next);
  n->next = *sl;
  *sl = n;

  printf("\nA new record was created\n\n");
}

void SlistRemove(Slist *sp, char TitleR[])
{
  ListNode *n;

  while(*sp != NULL && strcmp((*sp)->Title, TitleR))
  {
    sp = &((*sp)->next);
  }

  if(*sp == NULL)
    printf("\nBook not found\n\n");
  else
  {
    n = *sp;
    *sp = (*sp)->next;
    free(n);
    
    printf("\nBook Removed\n\n");
  }
}

void SlistPrint(Slist *sp)
{
  int i;

  while((*sp) != NULL)
  {
      printf("\n%s%s%d\n$%f\n", (*sp)->Title, (*sp)->Author, (*sp)->year, (*sp)->price);
      sp = &((*sp)->next);
  }
  printf("\n");
}

void SlistInit(Slist *sp)
{
  *sp = NULL;
}

void ExitFile(FILE *fout, Slist *sp)
{
  fout = fopen("library.txt", "w");

  while((*sp) != NULL)
  {
    fprintf(fout, "%s%s%d\n$%f\n\n", (*sp)->Title, (*sp)->Author, 
            (*sp)->year, (*sp)->price);
    
    sp = &((*sp)->next);
  }
}