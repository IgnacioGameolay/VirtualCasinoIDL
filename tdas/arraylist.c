#include "arraylist.h"
#include <stdio.h>
#include <stdlib.h>

struct ArrayList
{
  int *elements;
  int size;
  int maxSize;
};

void initializeArrayList(ArrayList *list, int max_size)
{
  list->elements = (int *)malloc(max_size * sizeof(int));
  list->size = 0;
  list->maxSize = max_size;
}

void insert(ArrayList *list, int element)
{
  if (list->size < list->maxSize)
  {
    list->elements[list->size++] = element;
  }
  else
  { 
    printf("Error: ArrayList lleno, no se puede insertar más elementos.\n");
    return;
  }
}

void destroyArrayList(ArrayList *list)
{
  free(list->elements);
  list->size = 0;
  list->maxSize = 0;
}

int getElement(ArrayList *list, int index)
{
  if (index < 0 || index >= list->size)
  {
    printf("Error: Índice fuera de rango.\n");
    return -1;  // O podrías manejar el error de otra manera según tu aplicación
  }
  
  return list->elements[index];
}