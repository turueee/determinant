#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

void create_matrix(int order, int*** matrix)
{
  int counter2, counter1;
  (*matrix) = (int**)malloc(sizeof(int*) * order);
  for (counter1 = 0; counter1 < order; counter1++)
    (*matrix)[counter1] = (int*)malloc(sizeof(int) * order);
  for (counter1 = 0; counter1 < order; counter1++)
  {
    for (counter2 = 0; counter2 < order; counter2++)
      (*matrix)[counter1][counter2] = rand() % 10;
  }
}

void print_for_int_matrix(int columns, int strings, int** matrix)
{
  int counter1, counter2;
  for (int counter1 = 0; counter1 < columns; counter1++)
  {
    if (counter1 == 0)
      printf("/\t");
    else if (counter1 + 1 == columns)
      printf("\\\t");
    else
      printf("|\t");
    for (int counter2 = 0; counter2 < strings; counter2++)
    {
      printf("%d\t", (matrix)[counter1][counter2]);
    }
    if (counter1 == 0)
      printf("\\\t\n");
    else if (counter1 + 1 == columns)
      printf("/\t\n");
    else
      printf("|\t\n");
  }
}

void print_for_double_matrix(int columns, int strings, double** matrix)
{
  int counter1, counter2;
  for (int counter1 = 0; counter1 < columns; counter1++)
  {
    if (counter1 == 0)
      printf("/\t");
    else if (counter1 + 1 == columns)
      printf("\\\t");
    else
      printf("|\t");
    for (int counter2 = 0; counter2 < strings; counter2++)
    {
      printf("%lf\t", (matrix)[counter1][counter2]);
    }
    if (counter1 == 0)
      printf("\\\t\n");
    else if (counter1 + 1 == columns)
      printf("/\t\n");
    else
      printf("|\t\n");
  }
}

void free_int_matrix(int columns, int** matrix)
{
  for (int counter = 0; counter < columns; counter++)
    free(matrix[counter]);
  free(matrix);
}

void free_double_matrix(int columns, double** matrix)
{
  for (int counter = 0; counter < columns; counter++)
    free(matrix[counter]);
  free(matrix);
}

void new_matrix_for_determinant(int string,int column, int order, int** matrix, int*** new_matrix)
{
  int counter1, counter2, new_counter1 = 0, new_counter2;
  (*new_matrix) = (int**)malloc(sizeof(int*) * (order - 1));
  for (counter1 = 0; counter1 < order - 1; counter1++)
    (*new_matrix)[counter1] = (int*)malloc(sizeof(int) * (order - 1));
  for (counter2 = 0; counter2 < order; counter2++)
  {
    if (counter2 != column)
    {
      new_counter2 = 0;
      for (counter1 = 0; counter1 < order; counter1++)
      {
        if (counter1 != string)
        {
          (*new_matrix)[new_counter2][new_counter1] = matrix[counter1][counter2];
          new_counter2++;
        }
      }
      new_counter1++;
    }
  }
}

int determinant(int order, int** matrix)
{
  int counter1, counter2, det = 0;
  int** new_matrix;
  if (order == 2)
    return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
  else
  {
    for (counter1 = 0; counter1 < order; counter1++)
    {
      new_matrix_for_determinant(counter1,0, order, matrix, &new_matrix);
      det += matrix[counter1][0] * determinant(order - 1, new_matrix) * pow(-1, counter1);
      free_int_matrix(order - 1, new_matrix);
    }
    return det;
  }
}


void create_attached_matrix(int order, int** matrix, int*** attached_matrix)
{
  int counter2, counter1;
  int** det_matrix;
  (*attached_matrix) = (int**)malloc(sizeof(int*) * order);
  for (counter1 = 0; counter1 < order; counter1++)
    (*attached_matrix)[counter1] = (int*)malloc(sizeof(int) * order);

  for (counter1 = 0; counter1 < order; counter1++)
  {
    for (counter2 = 0; counter2 < order; counter2++)
    {
      new_matrix_for_determinant(counter1, counter2, order, matrix, &det_matrix);
      (*attached_matrix)[counter2][counter1] = determinant(order - 1, det_matrix)*pow(-1,counter1+counter2);
      free_int_matrix(order - 1, det_matrix);
    }
  }
}


void create_inverse_of_the_matrix(int order, int** matrix, double*** inverse_matrix)
{
  int counter2, counter1;
  int** det_matrix;
  int det = determinant(order, matrix);
  (*inverse_matrix) = (double**)malloc(sizeof(double*) * order);
  for (counter1 = 0; counter1 < order; counter1++)
    (*inverse_matrix)[counter1] = (double*)malloc(sizeof(double) * order);

  for (counter1 = 0; counter1 < order; counter1++)
  {
    for (counter2 = 0; counter2 < order; counter2++)
    {
      new_matrix_for_determinant(counter1, counter2, order, matrix, &det_matrix);
      (*inverse_matrix)[counter2][counter1] = (determinant(order - 1, det_matrix) * pow(-1, counter1 + counter2))/(double)det;
      free_int_matrix(order - 1, det_matrix);
    }
  }
}


int main()
{
  int** matrix;
  int** attached_matrix;
  double** inverse_matrix;
  int order;
  srand(time(0));
  printf("Rang: ");
  scanf("%d", &order);
  create_matrix(order, &matrix);
  print_for_int_matrix(order, order, matrix);
  printf("\n%d\n", determinant(order, matrix));
  create_attached_matrix(order, matrix, &attached_matrix);
  print_for_int_matrix(order, order, attached_matrix);
  create_inverse_of_the_matrix(order, matrix, &inverse_matrix);
  print_for_double_matrix(order, order, inverse_matrix);
  free_int_matrix(order, matrix);
  free_int_matrix(order, attached_matrix);
}