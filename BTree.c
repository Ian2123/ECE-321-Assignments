/*
Author: Ian Isely
Date: 4/13/2019

Description:
  This program takes integer input and puts them into a binary search tree then prints
  the tree depth-first and breadth-first
Contributors: Ian Isely
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX 20

//Tree Declaration
typedef struct TreeNode_Tag
  {
    int data;
    struct TreeNode_Tag *left, *right;
  } TreeNode;

typedef TreeNode * tree;

//Queue Declaration
typedef struct List_Tag
  {
    TreeNode *Qt;
    struct List_Tag *next;
  } ListNode;

typedef struct
  {
    ListNode *first, *last;
  } queue;

const queue QueueEmpty = {NULL, NULL};

//Function Prototypes
void TreeInsert(tree *t, int d);
void TreePrintDF(tree t);
void TreePrintBF(tree t);
void QueueInsert(queue *qp, tree t);
tree QueueRemove(queue *qp);
int QueueIsEmpty(queue qp);
int max(int a, int b);

int main() 
{
  int Nums[MAX], choice, i=0, j;
  tree t;

  //Input of Numbers
  printf("Insert numbers into the binary tree (0=stop):\n");
  while(1)
  {
    scanf("%d", &choice);
    if(choice == 0)
      break;
    Nums[i] = choice;
    i++;
  }

  //Insertion into BST
  for(j=0;j<i;j++)
    TreeInsert(&t, Nums[j]);

  //Print Tree
  printf("Depth-First:   ");
  TreePrintDF(t);
  printf("\nBreadth-First: ");
  TreePrintBF(t);
}

void TreeInsert(tree *t, int d)
{
  if(*t == NULL)
  {
    *t = (TreeNode *)malloc(sizeof(TreeNode));
    if(*t == NULL)
    {
      printf("Out of Memory");
      exit(1);
    }
    (*t)->data = d;
    (*t)->left = (*t)->right = NULL;
  }
  else
  {
    if(d >= (*t)->data)
      TreeInsert(&(*t)->right, d);
    else 
      TreeInsert(&(*t)->left, d);
  }
}

void TreePrintDF(tree t)
{
  if(t != NULL)
  {
    printf("%d ", t->data);
    TreePrintDF(t->left);
    TreePrintDF(t->right);
  }
}

void TreePrintBF(tree t)
{
  queue q = QueueEmpty;
  if(t != NULL)
    QueueInsert(&q, t);

  while(!QueueIsEmpty(q))
  {
    TreeNode *n = QueueRemove(&q);
    printf("%d ", n->data);

    if(n->left != NULL)
      QueueInsert(&q, n->left);
    if(n->right != NULL)
      QueueInsert(&q, n->right);
  }
}

void QueueInsert(queue *qp, tree t)
{
  ListNode *n = (ListNode *)malloc(sizeof(ListNode));
  if(n == NULL)
  {
    printf("Out of memory");
    exit(1);
  }

  n->Qt = t;
  n->next = NULL;
  if(qp->first == NULL)
    qp->first = qp->last = n;
  else 
  {
    qp->last->next = n;
    qp->last = n;
  }
}

int QueueIsEmpty(queue q)
{
  if(q.first == NULL)
    return 1;
  else return 0;
}

tree QueueRemove(queue *qp)
{
  TreeNode *n;
  ListNode *m;

  if(qp->first == NULL)
  {
    printf("Empty Queue");
    exit(1);
  }

  m = qp->first;
  n = m->Qt;
  qp->first = m->next;
  free(m);

  if(qp->first == NULL)
    qp->last = NULL;
  
  return n;
}

int max(int a, int b)
{
  if(a>b)
    return a;
  else 
    return b;
}