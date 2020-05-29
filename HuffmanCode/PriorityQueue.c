#include "PriorityQueue.h"

#include <stdlib.h>

#define AND &&

#define PARENT(i) ((i) - 1) / 2
#define LCHILD(i) 2 * (i) + 1
#define RCHILD(i) 2 * (i) + 2

typedef struct element
{
	int priority;
	void* content;
} Element;

struct priorityQueue
{
	Element* elements;
	int currentSize;
	int maxSize;
};

PriorityQueue newPriorityQueue(int size)
{
	PriorityQueue new = (PriorityQueue) malloc(sizeof(struct priorityQueue));

	new->elements = (Element*) malloc(size * sizeof(Element));

	new->currentSize = 0;

	new->maxSize = size;

	return new;
}

int isEmptyPriorityQueue(PriorityQueue pq)
{
    if(pq->currentSize > 0) return 0;
    else return 1;
}

int isFullPriorityQueue(PriorityQueue pq)
{
	if(pq->currentSize == pq->maxSize) return pq->maxSize;
	else return 0;
}

void swap(Element* elements, int i, int j)
{
	Element aux = elements[i];
	elements[i] = elements[j];
	elements[j] = aux;
}

int insertPriorityQueue(PriorityQueue pq, int priority, void* content)
{
	if(!isFullPriorityQueue(pq))
	{
		int index = pq->currentSize;
		pq->currentSize++;

		Element* elements = pq->elements;

		elements[index].priority = priority;
		elements[index].content = content;

		while(	PARENT(index) >= 0 AND
				elements[index].priority < elements[PARENT(index)].priority)
		{
                      swap(elements, index, PARENT(index));
                      index = PARENT(index);
		}

		return priority;
	}

	return ERROR;
}

void* findMinPriorityQueue(PriorityQueue pq)
{
	if(!isEmptyPriorityQueue(pq))
	{
        return pq->elements[0].content;
	}

	return NULL;
}

void* removeMinPriorityQueue(PriorityQueue pq)
{
	if(!isEmptyPriorityQueue(pq))
	{
		Element* elements = pq->elements;

		void* content = elements[0].content;

		pq->currentSize--;

		elements[0] = elements[pq->currentSize];

		void heapify(int parent, int heapSize)
		{
			int leftChild = LCHILD(parent);
			int rightChild = RCHILD(parent);
			int greatest = parent;

			if(	leftChild < heapSize AND elements[leftChild].priority < elements[greatest].priority)
			{
				greatest = leftChild;
			}

			if(	rightChild < heapSize AND elements[rightChild].priority < elements[greatest].priority)
			{
				greatest = rightChild;
			}

			if(greatest != parent)
			{
				swap(elements, parent, greatest);
				heapify(greatest, heapSize);
			}
		}

		heapify(0, pq->currentSize);

		return content;
	}

	return NULL;
}

void deletePriorityQueue(PriorityQueue pq)
{
	free(pq->elements);

	free(pq);
}
