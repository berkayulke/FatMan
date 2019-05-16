#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"dataset.h"
#define MAXBUCKETS 100

#ifndef MODELS
#define MODELS

typedef struct matrix{
  int satir;
  int sutun;
  double** numbers;
}matrix;

// Gerekli veri tanimlarini burada yapabilirsiniz

matrix* create_matrix(int satir,int sutun);
void free_matrix(matrix* m);
void print_matrix(matrix m,char* isim);

matrix* get_transpose(matrix source);
matrix* get_inverse(matrix m);
matrix* get_multiplication(matrix m , matrix n);

matrix* calculate_parameter(matrix X, matrix Y);

float model_by_similarity(List_house** head,House new_house);
void save_by_similarity(char* file_from,char* file_to,List_house** known_head);

void create_data_matrices(List_house** head,matrix** X,matrix** Y);
matrix* make_prediction(char* filename,matrix* W);
//void save_by_make_prediction(FILE* file,char* file_from,char* file_to);

#endif
