#include "queue.h"
#include "dll.h"
#include "music_player.h"
#include <stdio.h>
#include <stdlib.h>

playlist_t* create_playlist() // return a newly created doubly linked list
{
	// DO NOT MODIFY!!!
	playlist_t* playlist = (playlist_t*) malloc(sizeof(playlist_t));
	playlist->list = create_list();
	playlist->num_songs = 0;
	playlist->last_song = NULL;
	return playlist;
}

void delete_playlist(playlist_t* playlist) // delete the playlist
{
	// DO NOT MODIFY!!!
	delete_list(playlist->list);
	free(playlist);
}

music_queue_t* create_music_queue() // return a newly created queue
{
	// DO NOT MODIFY!!!
	return create_queue();
}

void clear_music_queue(music_queue_t* q) // clear the queue q
{	
	// DO NOT MODIFY!!!
	delete_queue(q);
}

void add_song(playlist_t* playlist, int song_id, int where) //  add a song id to the end of the playlist
{	
	++playlist->num_songs;
	if(where==-1){
		insert_front(playlist->list,song_id);
	}
	else if(where==-2){
		
		insert_back(playlist->list,song_id);
	}
	else{
	insert_after(playlist->list,song_id,where);
	}
}

void delete_song(playlist_t* playlist, int song_id) //  remove song id from the playlist
{
	
	delete_node(playlist->list,song_id);
	--playlist->num_songs;
}

song_t* search_song(playlist_t* playlist, int song_id) // return a pointer to the node where the song id is present in the playlist
{
	song_t *ptr=playlist->list->head;
	while (ptr!=NULL){
		if(ptr->data==song_id)
			return ptr;
		else
			ptr=ptr->next;
	}
	return NULL;
}

void search_and_play(playlist_t* playlist, int song_id) //  play the song with given song_id from the list(no need to bother about the queue. Call to this function should always play the given song and further calls to play_next and play_previous)
{
	song_t *ptr=search_song(playlist,song_id);
	if(ptr==NULL)
		return;
	else{
		play_song(ptr->data);
		playlist->last_song=ptr;

}
}
void play_next(playlist_t* playlist, music_queue_t* q) //  play the next song in the linked list if the queue is empty. If the queue if not empty, play from the queue
{
	if(playlist->last_song==NULL){
		playlist->last_song=playlist->list->head;
		printf("Playing: %d\n",playlist->last_song->data);
	}
	else if(q->front!=NULL){
		play_from_queue(q);

	}
	else{
		if(playlist->last_song->next==NULL){
			playlist->last_song=playlist->list->head;
			printf("Playing: %d\n",playlist->last_song->data);
		}
		else{
			playlist->last_song=playlist->last_song->next;
			printf("Playing: %d\n",playlist->last_song->data);
		}
	}
}

void play_previous(playlist_t* playlist) //  play the previous song from the linked list
{
	if(playlist->list->head==NULL)
		return;
	else{
		if(playlist->last_song->prev==NULL){
			playlist->last_song=playlist->list->tail;
			printf("Playing: %d\n",playlist->last_song->data);
		}
		else{
			playlist->last_song=playlist->last_song->prev;
			printf("Playing: %d\n",playlist->last_song->data);
		}
	}

}

void play_from_queue(music_queue_t* q) //  play a song from the queue
{
	if(q->front==q->rear){
		printf("playing: %d",q->front->data);
		q->front=q->rear=NULL;
	}
	else{
		printf("playing: %d",q->front->data);
		q->front=q->front->next;
	}
}

void insert_to_queue(music_queue_t* q, int song_id) //  insert a song id to the queue
{	
	enqueue(q,song_id);
}

void reverse(playlist_t* playlist) //  reverse the order of the songs in the given playlist. (Swap the nodes, not data)
{
	song_t *ptr=playlist->list->tail;
	song_t *ptr1;
	playlist->list->tail=playlist->list->head;
	playlist->list->head=ptr;
	while(ptr!=playlist->list->tail){
		ptr1=ptr->next;
		ptr->next=ptr->prev;
		ptr->prev=ptr1;
		ptr=ptr->next;
	}
	ptr1=ptr->next;
	ptr->next=ptr->prev;
	ptr->prev=ptr1;
}

void k_swap(playlist_t* playlist, int k) //  swap the node at position i with node at position i+k upto the point where i+k is less than the size of the linked list
{	
	int j;

	song_t *temp=playlist->list->head;
	song_t *ptr=NULL;
	song_t *t=NULL;

	j=0;
	for(int i=0;(i+k)<playlist->num_songs;i++){
		ptr=temp;
		j=0;
		while(j<k){
			ptr=ptr->next;
			j++;
		}
		t=temp->next;
		temp->next=ptr->next;
		if(k==1) 
			ptr->next=temp;
		else 
			ptr->next=t;
		t=temp->prev;
		if(k==1) 
			temp->prev=ptr;
		else temp->prev=ptr->prev;
		ptr->prev=t;
		if(temp->prev!=NULL)
			temp->prev->next=temp;
			//
		if(ptr->prev!=NULL)
			ptr->prev->next=ptr;
			//	
		if(temp->next==NULL) 
			playlist->list->tail=temp;
			
        if(temp->next!=NULL)
			temp->next->prev=temp;
        if(ptr->next!=NULL)
			ptr->next->prev=ptr;
        
        if(ptr->prev==NULL)
			playlist->list->head=ptr;
		
		temp=ptr->next;
	}
}
void shuffle(playlist_t* playlist, int k) //  perform k_swap and reverse
{
	k_swap(playlist,k);
	reverse(playlist);
}

song_t* debug(playlist_t* playlist) //  if the given linked list has a cycle, return the start of the cycle, else return null. Check cycles only in forward direction i.e with the next pointer. No need to check for cycles in the backward pointer.
{
	song_t *fst=playlist->list->head;
	song_t *slw=playlist->list->head;
	while(fst->next!=NULL){
		fst=fst->next->next;
		slw=slw->next;
		if(fst==slw){
			fst=playlist->list->head;
			while(fst!=slw){
				fst=fst->next;
				slw=slw->next;
			}
			return slw;
		}

	}
	return NULL;

}

void display_playlist(playlist_t* p) // Displays the playlist
{
	
	display_list(p->list);
}

void play_song(int song_id)
{
	
	printf("Playing: %d\n", song_id);
}