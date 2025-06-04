#include <iostream>
#include "queue.h"



Queue* init(void) { 
	Queue* queue = (Queue*)malloc(sizeof(Queue));
	queue->head = NULL;
	queue->tail = NULL;
	return queue;
}


void release(Queue* queue) {
	Node* curr = queue->head;
	

	return;
}



Node* nalloc(Item item) { 
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->item = item;
	newNode->next = NULL;
	newNode->prev = NULL;
	return newNode;
}

void nfree(Node* node) {
	return;
}


Node* nclone(Node* node) {
	return NULL;
}


Reply enqueue(Queue* queue, Item item) {
	Reply reply = { false, NULL };
	
	Node* newNode = nalloc(item);

	if (queue->head == NULL) {
		queue->head = newNode;
		queue->tail = newNode;
		queue->head->next = queue->tail;
		queue->tail->next = queue->head;
		reply.success = true;
		reply.item = item;
		return reply;
	}

	/*else {
		Node* curr = queue->head;
		if (curr->item.key < item.key) {
			newNode->next = curr;
		}
	}*/


	return reply;
}


Reply dequeue(Queue* queue) {
	Reply reply = { false, NULL };

	return reply;
}

Queue* range(Queue* queue, Key start, Key end) {
	return NULL;
}
