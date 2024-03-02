#include "queue.h"
#include <stdio.h>
#include <stdlib.h>

queue_t* create_queue()   // return a newly created empty queue
{
	// DO NOT MODIFY!!!
	queue_t* Q = (queue_t*) malloc(sizeof(queue_t));
	Q->list = create_list();
	Q->front = Q->list->head;
	Q->rear = Q->list->tail;
	Q->size = Q->list->size;
	return Q;
}

void enqueue(queue_t* q, int data) // TODO: insert data at the end of a queue
{
    insert_back(q->list,data);
    q->front=q->list->head;
    q->rear=q->list->tail;
    q->size++;
}

int dequeue(queue_t* q) 	// TODO: return the data at the front of a queue and remove it. Return -1 if queue is empty
{
    if(q->front==NULL)
        return -1;
    else if(q->front==q->rear){     //single node case
        int a=front(q);
        free(q->front);
        q->front=NULL;
        q->rear=NULL;
        q->list->head=NULL;     
        q->list->tail=NULL; 
        --q->size;
        q->list->size=q->size;
        return a;
    }
    else{
        int a=front(q);
        q->front=q->front->next;
        free(q->front->prev);
        q->front->prev=NULL;
        q->list->head=q->front;
        --q->size;
        q->list->size=q->size;
        return a;
    }
}

int front(queue_t* q) // TODO: return the data at the front of a queue. Return -1 if queue is empty
{
    if(q->front==NULL)
        return -1;
    else{
        return q->front->data;
    }
}

int empty(queue_t* q) // return if the queue is empty
{
	// DO NOT MODIFY!!!
	return is_empty(q->list);
}

int queue_size(queue_t* q) // returns the number of elements in the queue
{
	// DO NOT MODIFY!!!
	return q->size;
}

void delete_queue(queue_t* q) // empty the contents of the queue
{
	// DO NOT MODIFY!!!
	delete_list(q->list);
	free(q);
}