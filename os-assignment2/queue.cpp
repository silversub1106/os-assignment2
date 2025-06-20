#include <iostream>
#include "queue.h"
#include <mutex>

std::mutex mtx;

Queue* init(void) { 
	Queue* queue = (Queue*)malloc(sizeof(Queue));
	queue->head = NULL;

	return queue;
}

//realease -> 현재구현중
void release(Queue* queue) {
	Node* temp;
	while (queue->head != NULL) {
		temp = queue->head->next;
		nfree(queue->head);
		queue->head = temp;
	}
	
	free(queue);

	return;
}


//nalloc 
Node* nalloc(Item item) {  
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->item = item;
	newNode->next = NULL;
	return newNode;
}

void nfree(Node* node) {
	//free(node->item.value);
	free(node);
}


Node* nclone(Node* node) {
	std::lock_guard<std::mutex> lock(mtx);
	if (node == NULL) {
		std::cerr << "nclone(): NULL node passed!" << std::endl;
		return NULL;
	}

	Node* cp = (Node*)malloc(sizeof(Node));
	cp->item.key = node->item.key;
	cp->item.value = node->item.value;
	return cp;
}


// :★size추가 필요★ 어디에 추가할지 표시했음
Reply enqueue(Queue* queue, Item item) { 
	std::lock_guard<std::mutex> lock(mtx);
	Reply reply = { false, NULL };
	
	Node* newNode = nalloc(item);
	

	// queue가 비어있을때  (잘됨)
	if (queue->head == NULL) {		 
		queue->head = newNode;
	
		reply.success = true; 
		reply.item = item;   
		return reply;
	}

	// newNode key값이 head와 동일할때 -> 기존 노드삭제후 그자리에 새로추가(잘됨)

	if (newNode->item.key == queue->head->item.key) {
		newNode->next = queue->head->next;
		free(queue->head);
		queue->head = newNode;

		reply.success = true;
		reply.item = item;
		return reply;
	}


	// newNode가 head보다 key값이 높을시 (유일하게 새로운노드를 앞에삽입) (잘됨) 
	if (newNode->item.key > queue->head->item.key) { 
		newNode->next = queue->head;
		queue->head = newNode;
		
		reply.success = true;
		reply.item = item;    
		return reply;
	}


	//노드중간에추가해야할때 :★★★여기에size추가 필요★★★
	Node* curr = queue->head;       
	while(1) {
		// 새로운노드가 기준 노드보다 작은 경우(뒤에삽입)
		if (curr->item.key >= item.key) {
			// 현재노드의 next가 있을경우 그리고 기준노드의 다음노드가 새로운노드보다 작을경우
			if (curr->next != NULL && curr->next->item.key < newNode->item.key) {
				newNode->next = curr->next;
				curr->next = newNode;

				reply.success = true;
				reply.item = item;
				return reply;
			}

			else if (curr->next != NULL &&  curr->next->item.key == item.key) {
				newNode->next = curr->next->next;
				nfree(curr->next);
				curr->next = newNode;
				
				
				reply.success = true;
				reply.item = item;  
				return reply;
			}

			// 
			else {
				// 기준노드의 다음노드도 새로운노드보다 큼(그럼 기준노드를 다음노드로)
				if (curr->next == NULL){
					curr->next = newNode;

					reply.success = true;
					reply.item = item;   
					return reply;
				}
		
				else {
					curr = curr->next;
					continue;
				}
						// 노드가 한개밖에없음.
			}
		}
	}
}

// 완성 X
Reply dequeue(Queue* queue) {
	std::lock_guard<std::mutex> lock(mtx);
	
	Reply reply = { false, NULL };
	if (queue->head == NULL) return reply;
	Node* temp = queue->head->next;

	reply.success = true;
	reply.item = queue->head->item;
	
	nfree(queue->head);
	queue->head = temp;
	return reply;
}



Queue* range(Queue* queue, Key start, Key end) {
	std::lock_guard<std::mutex> lock(mtx);

	Queue* cpQueue = init();
	if (queue->head == NULL) return cpQueue;

	int cnt = 0;
	Node* cursor = queue->head; //index 0
	Node* cpNode = nclone(cursor);
	while (cnt < start) {
		cursor = cursor->next;
		cnt++;
	}

	while (cnt <= end) {
		if (cursor == NULL) break;
		cpNode = nclone(cursor);
		enqueue(cpQueue, cpNode->item);
		cursor = cursor->next;
		cnt++;
	}
	

	
	return cpQueue;
}
