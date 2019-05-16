#ifndef DATASET
#define DATASET
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAXSIZE 30

typedef struct house{
  int id;
  int lotarea;
  char* street;
  int saleprice;
  char* neighborhood;
  int yearbuilt;
  int overallqual;
  int overallcond;
  int kitchenqual;
} House;

typedef struct List_house{
  House house;
  struct List_house* next;
}List_house;


void insertion_sort(int *array, int size);
void sort_char(char** array, int size);

int hash_compute(House house);
int is_in_array(int* list,int value,int size_of_array);
int is_in_array_string(char** list,char* string,int size_of_array);

int size_of_list(List_house*head);
int alphabetic_order(char* first,char* second);

void copy_house(House* source,House* destination);
List_house** create_hash();

void read_house(char* text,House* house,int x);
int read_house_data(FILE* file,List_house** hash_table,int x);
int save_sorted_houses(FILE* file,List_house** head,char* criter);

void print_house (House house);
void print_list(List_house* head);
void print_hash(List_house** head);

List_house* list_add(List_house* head, House house);
void hash_add(List_house** head, House house);

void hash_clean(List_house** head);
void list_clean(List_house* head);

List_house* top_10_houses(List_house** head);
House get_house_byid(List_house** head,int id);
List_house** get_neighborhoods(List_house** head,House house);

int* get_criter_list_int(List_house** head,char* criter);
char** get_criter_list_char(List_house** head,char* criter);
float* mean_sale_prices(List_house** head,char* criter);

List_house* sort_all_houses(List_house** head,char* criter);
List_house* merge(List_house* left, List_house* right,char* criter);
void split_list(List_house* source, List_house** left,List_house** right);
void merge_sort_list(List_house** head,char* criter);
void sort_houses(List_house** head, char* criter);


#endif
