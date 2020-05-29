#ifndef PRIORITYQUEUE_H_INCLUDED
#define PRIORITYQUEUE_H_INCLUDED

#define ERROR -1

typedef struct priorityQueue* PriorityQueue;

PriorityQueue newPriorityQueue(int);

int isEmptyPriorityQueue(PriorityQueue);

int isFullPriorityQueue(PriorityQueue);

int insertPriorityQueue(PriorityQueue, int, void*);

void* findMinPriorityQueue(PriorityQueue);

void* removeMinPriorityQueue(PriorityQueue);

void deletePriorityQueue(PriorityQueue);

#endif // PRIORITYQUEUE_H_INCLUDED
