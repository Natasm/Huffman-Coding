#include "LinkedList.h"

#include <stdlib.h>

#define AND &&

struct linkedList
{
	char key;
	void* content;
	LinkedList next;
};

LinkedList newLinkedList()
{
	return EMPTYLIST;
}

LinkedList searchLinkedList(LinkedList ll, char key)
{
	while(ll != EMPTYLIST)
	{
		if(ll->key == key)
		{
			return ll;
		}

		ll = ll->next;
	}

	return ERROR;
}

LinkedList getNextNodeLinkedList(LinkedList ll){
   return ll->next;
}

char getKeyLinkedList(LinkedList ll){

   if(ll != EMPTYLIST){
       return ll->key;
   }

   return ERROR;
}

void* getContentLinkedList(LinkedList ll)
{
	if(ll != EMPTYLIST)
	{
		return ll->content;
	}

	return ERROR;
}

LinkedList nextLinkedList(LinkedList ll)
{
	if(ll != EMPTYLIST)
	{
		return ll->next;
	}

	return ERROR;
}

LinkedList newNodeLinkedList(char key, void* content)
{
	LinkedList new = (LinkedList) malloc(sizeof(struct linkedList));

	new->key = key;
	new->content = content;
	new->next = EMPTYLIST;

	return new;
}

LinkedList insertAfterLinkedList(LinkedList ll, char key, void* content)
{
	if(ll != EMPTYLIST)
	{
		LinkedList new = newNodeLinkedList(key, content);

		new->next = ll->next;

		ll->next = new;

		return ll;
	}

	return ERROR;
}

LinkedList updateLinkedList(LinkedList ll, char key, void* content)
{
    if(ll == EMPTYLIST){
        ll = newNodeLinkedList(key,content);
        return ll;
    }

    LinkedList ll_buffer = ll;
	while(ll != EMPTYLIST)
	{
		if(ll->key == key)
		{
            ll->content = ll->content + (int) content;
            return ll_buffer;
		}

		ll = ll->next;
	}

	if(ll_buffer != EMPTYLIST)
	{
		LinkedList new = newNodeLinkedList(key, content);

		new->next = ll_buffer->next;

		ll_buffer->next = new;

		return ll_buffer;
	}

	return ERROR;
}

LinkedList insertBeginningLinkedList(LinkedList ll, char key, void* content)
{
	LinkedList new = newNode(key, content);

	new->next = ll;

	return new;
}

void deleteNode(LinkedList ll)
{
	free(ll);
}

LinkedList removeAfterLinkedList(LinkedList ll)
{
	if(ll != EMPTYLIST AND ll->next != EMPTYLIST)
	{
		LinkedList aux = ll->next;

		ll->next = ll->next->next;

		deleteNode(aux);

		return ll;
	}

	return ERROR;
}

LinkedList removeByKeyLinkedList(LinkedList ll, char key)
{
	if(ll != EMPTYLIST)
	{
		if(ll->key == key)
		{
			return removeBeginningLinkedList(ll);
		}

		LinkedList aux = ll->next;
		LinkedList parent = ll;

		while(aux != EMPTYLIST)
		{
			if(aux->key == key)
			{
				removeAfterLinkedList(parent);

				return ll;
			}

			parent = aux;
			aux = aux->next;
		}
	}

	return ERROR;
}

LinkedList removeBeginningLinkedList(LinkedList ll)
{
	if(ll != EMPTYLIST)
	{
		LinkedList aux = ll->next;

		deleteNode(ll);

		return aux;
	}

	return ERROR;
}

LinkedList invertLinkedList(LinkedList ll){
    if(ll != EMPTYLIST){
        LinkedList first = ll;
        LinkedList last = EMPTYLIST;

        while(first != EMPTYLIST){
            last = first;
            first = first->next;
        }
    }
}

void deleteLinkedList(LinkedList ll)
{
	LinkedList aux;
	while(ll != EMPTYLIST)
	{
		aux = ll;
		ll = ll->next;
		deleteNode(aux);
	}
}

void toString(LinkedList ll){
    while(ll != NULL){
        printf("%c - %d\n", ll->key,(int) ll->content);
        ll = ll->next;
    }
}

int sizeLinkedList(LinkedList ll){
    int sum = 0;
    while(ll != NULL){
        sum++;
        ll = ll->next;
    }
    return sum;
}
