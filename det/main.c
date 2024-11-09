#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

void create_matrix(int order, int*** a_matrix,int **b_vector)
{
  int counter2,counter1;
  (*a_matrix) = (int**)malloc(sizeof(int*) * order);
  (*b_vector) = (int*)malloc(sizeof(int) * order);
  for (counter1 = 0; counter1 < order; counter1++)
    (*a_matrix)[counter1] = (int*)malloc(sizeof(int) * order);

  for (counter1 = 0; counter1 < order; counter1++)
  {
    for (counter2 = 0; counter2 < order; counter2++)
    {
      printf("a[%d][%d] = ", counter1, counter2);
      scanf("%d", &(*a_matrix)[counter1][counter2]);
    }
    printf("b[%d] = ", counter1);
    scanf("%d", &(*b_vector)[counter1]);
  }
}

void print_for_extended_matrix(int order, int** matrix,int*b_vector)
{
  int counter1, counter2;
  for (int counter1 = 0; counter1 < order; counter1++)
  {
    if (counter1 == 0)
      printf("/\t");
    else if (counter1 + 1 == order)
      printf("\\\t");
    else
      printf("|\t");
    for (int counter2 = 0; counter2 < order; counter2++)
    {
      printf("%d\t", (matrix)[counter1][counter2]);
    }
    printf("|\t%d\t", b_vector[counter1]);
    if (counter1 == 0)
      printf("\\\t\n");
    else if (counter1 + 1 == order)
      printf("/\t\n");
    else
      printf("|\t\n");
  }
}

void print_for_matrix(int order,int** matrix)
{
  int counter1, counter2;
  for (int counter1 = 0; counter1 < order; counter1++)
  {
    if (counter1 == 0)
      printf("/\t");
    else if (counter1 + 1 == order)
      printf("\\\t");
    else
      printf("|\t");
    for (int counter2 = 0; counter2 < order; counter2++)
    {
      printf("%d\t", (matrix)[counter1][counter2]);
    }
    if (counter1 == 0)
      printf("\\\t\n");
    else if (counter1 + 1 == order)
      printf("/\t\n");
    else
      printf("|\t\n");
  }
}

void free_matrix(int order, int** matrix)
{
  for (int counter = 0; counter < order; counter++)
    free(matrix[counter]);
  free(matrix);
}

void new_matrix_for_determinant(int string, int order, int** matrix,int***new_matrix)
{
  int counter1, counter2,new_counter1 = 0,new_counter2;
  (*new_matrix) = (int**)malloc(sizeof(int*) * (order - 1));
  for (counter1 = 0; counter1 < order - 1; counter1++)
    (*new_matrix)[counter1] = (int*)malloc(sizeof(int) * (order - 1));
  for (counter2 = 1; counter2 < order; counter2++)
  {
    new_counter2 = 0;
    for (counter1 = 0; counter1 < order; counter1++)
    {
      if(counter1!=string)
      { 
        (*new_matrix)[new_counter2][new_counter1] = matrix[counter1][counter2];
        new_counter2++;
      }
    }
    new_counter1++;
  }
}

int determinant(int order,int** matrix)
{
  int counter1, counter2,det = 0;
  int** new_matrix;
  if (order == 2)
    return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
  else
  {
    for (counter1 = 0; counter1 < order; counter1++)
    {
      new_matrix_for_determinant(counter1, order, matrix, &new_matrix);
      det += matrix[counter1][0] * determinant(order - 1, new_matrix)*pow(-1,counter1);
      free_matrix(order - 1, new_matrix);
    }
    return det;
  }
}

void create_matrix_for_cramer(int***matrix_for_cramer,int** matrix, int* b_vector,int order,int column)
{
  int counter;
  int counter2, counter1;
  (*matrix_for_cramer) = (int**)malloc(sizeof(int*) * order);
  for (counter1 = 0; counter1 < order; counter1++)
    (*matrix_for_cramer)[counter1] = (int*)malloc(sizeof(int) * order);

  for (counter1 = 0; counter1 < order; counter1++)
  {
    for (counter2 = 0; counter2 < order; counter2++)
    {
      (*matrix_for_cramer)[counter1][counter2] = matrix[counter1][counter2];
    }
  }

  for (counter = 0; counter < order; counter++)
    (*matrix_for_cramer)[counter][column] = b_vector[counter];
}

void cramer(int** matrix, int* b_vector, int order)
{
  int counter,determinant_of_matrix;
  int** matrix_for_cramer;
  determinant_of_matrix = determinant(order, matrix);
  for (counter = 0; counter < order; counter++)
  {
    create_matrix_for_cramer(&matrix_for_cramer, matrix, b_vector, order, counter);
    printf("\n");
    print_for_matrix(order,matrix_for_cramer);
    printf("x[%d] = %d/%d\n", counter, determinant(order, matrix_for_cramer), determinant_of_matrix);
    free_matrix(order, matrix_for_cramer);
  }
}

int main()
{
  int** a_matrix;
  int* b_vector;
  int order;
  srand(time(0));
  printf("Rang: ");
  scanf("%d", &order);
  create_matrix(order, &a_matrix,&b_vector);
  print_for_extended_matrix(order,a_matrix,b_vector);
  cramer(a_matrix, b_vector, order);
  free_matrix(order,a_matrix);
  free(b_vector);
}