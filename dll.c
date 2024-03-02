#include "dll.h"
#include <stdio.h>
#include <stdlib.h>

list_t* create_list() 
{
	
	list_t* l = (list_t*) malloc(sizeof(list_t));
	l->head = NULL;
	l->tail = NULL;
	l->size = 0;
	return l;
}

void insert_front(list_t* list, int data)  
{
    node_t *newnode=malloc(sizeof(node_t));
    newnode->data=data;
    newnode->next=NULL;
    newnode->prev=NULL;
    if(list->tail==NULL){
        newnode->next=newnode->prev=NULL;
        list->head=newnode;
        list->tail=newnode;
        ++list->size;
    }
    else{
        newnode->next=list->head;
        list->head->prev=newnode;
        list->head=newnode;
		++list->size;
    }
}

void insert_back(list_t* list, int data) 
{
	node_t *newnode=malloc(sizeof(node_t));
    newnode->data=data;
    newnode->next=NULL;
    newnode->prev=NULL;
    if(list->tail==NULL){
        newnode->next=newnode->prev=NULL;
        list->head=newnode;
        list->tail=newnode;
        ++list->size;
    }
	else{
		newnode->prev=list->tail;
		list->tail->next=newnode;
		list->tail=newnode;
		++list->size;
	}
}

void insert_after(list_t* list, int data, int prev) 
{
	node_t *new=list->head;
	node_t *newnode=malloc(sizeof(node_t));
		newnode->data=data;
		newnode->next=NULL;
		newnode->prev=NULL;

	if(new->data==prev && new->next==NULL){		
		new->next=newnode;
		newnode->prev=new;
		list->tail=newnode;
		++list->size;
	}
	else{
	while(new->next!=NULL){
		if(new->data==prev){
			break;
		}
		new=new->next;
	}
	if(new->next!=NULL){
		newnode->next=new->next;
		newnode->prev=new;
		new->next->prev=newnode;
		new->next=newnode;
		++list->size;
	}
	else if(new->data==prev){    	
		new->next=newnode;
		newnode->prev=new;
		list->tail=newnode;
		++list->size;
	}

}}

void delete_front(list_t* list) 
{
	node_t *node=list->head;
	if(node->next==NULL){		
		free(node);
		list->head=NULL;
		list->tail=NULL;
		--list->size;
	}
	else{
		node->next->prev=NULL;
		list->head=node->next;
		free(node);
		--list->size;
	}
}

void delete_back(list_t* list) 
{
	node_t *node=list->tail;
	if(node->next==NULL){		
		free(node);
		list->head=NULL;
		list->tail=NULL;
		--list->size;
	}
	else{
		node->prev->next=NULL;
		list->tail=node->prev;
		free(node);
		--list->size;
	}
}

void delete_node(list_t* list, int data) 
{
	node_t *ptr=search(list,data);
	if(ptr==NULL){
		return;
	}
	else{
	if(ptr->prev==NULL){
		delete_front(list);
	}
	else if(ptr->next==NULL){
		delete_back(list);
	}	
	else{
		ptr->prev->next=ptr->next;
		ptr->next->prev=ptr->prev;
		free(ptr);
	}
}
}
node_t* search(list_t* list, int data) 
{	
	node_t *node=list->head;
	while(node!=NULL){
		if(node->data==data)
			return node;
		node=node->next;
	}
	return node;
}

int is_empty(list_t* list) 
{
	return list->size == 0;
}

int size(list_t* list) 
{
	return list->size;
}

void delete_nodes(node_t* head) // helper
{
	if(head == NULL)
		return;
	delete_nodes(head->next);
	free(head);	
}

void delete_list(list_t* list) 
{
	delete_nodes(list->head);
	free(list);
}

void display_list(list_t* list) 
{
	node_t* it = list->head;
	while(it != NULL)
	{
		printf("%d ", it->data);
		it = it->next;
	}
	printf("\n");
}