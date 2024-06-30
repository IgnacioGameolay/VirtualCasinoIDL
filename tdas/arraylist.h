#ifndef ARRAYLIST_H
#define ARRAYLIST_H

typedef struct ArrayList ArrayList; 

void initializeArrayList(ArrayList *list, int maxSize);
void insert(ArrayList *list, int data);
void destroyArrayList(ArrayList *list);
int getElement(ArrayList *list, int index);

#endif // ARRAYLIST_H