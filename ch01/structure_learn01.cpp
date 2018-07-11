#include <stdio.h>

typedef struct{
  int no;
  char name[8];
  char sex[2];
  char classNo[4];
}Stud;


typedef struct Studnode {
  int no;
  char name[8];
  char sex[2];
  char classNo[4];
  struct Studnode *next;
} StudType;
