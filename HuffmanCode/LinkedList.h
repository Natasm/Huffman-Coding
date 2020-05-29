#ifndef LINKEDLIST_H_INCLUDED
#define LINKEDLIST_H_INCLUDED

#define EMPTYLIST NULL
#define ERROR ((void*) -1)

typedef struct linkedList* LinkedList;

LinkedList newLinkedList();

LinkedList getNextNodeLinkedList(LinkedList ll);

LinkedList searchLinkedList(LinkedList, char);

void* getContentLinkedList(LinkedList);

LinkedList nextLinkedList(LinkedList);

LinkedList insertAfterLinkedList(LinkedList, char, void*);

LinkedList insertBeginningLinkedList(LinkedList, char, void*);

LinkedList updateLinkedList(LinkedList ll, char key, void* content);

LinkedList removeAfterLinkedList(LinkedList);

LinkedList removeByKeyLinkedList(LinkedList, char);

LinkedList removeBeginningLinkedList(LinkedList);

LinkedList invertLinkedList(LinkedList);

void deleteLinkedList(LinkedList);

void toString(LinkedList ll);

int sizeLinkedList(LinkedList ll);

#endif // LINKEDLIST_H_INCLUDED
