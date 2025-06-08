#include <iostream>
#include "queue.h"



Queue* init(void) { 
	Queue* queue = (Queue*)malloc(sizeof(Queue));
	queue->head = NULL;

	return queue;
}

//realease -> ���籸����
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
	Node* cp = (Node*)malloc(sizeof(Node));

	return NULL;
}


// :��size�߰� �ʿ�� ��� �߰����� ǥ������
Reply enqueue(Queue* queue, Item item) { 
	Reply reply = { false, NULL };
	
	Node* newNode = nalloc(item);


	// queue�� ���������  (�ߵ�)
	if (queue->head == NULL) {		 
		queue->head = newNode;
	
		reply.success = true; 
		reply.item = item;     //�̰� ���ؾߵɵ� 
		return reply;
	}

	// newNode key���� head�� �����Ҷ� -> ���� �������� ���ڸ��� �����߰�(�ߵ�)

	if (newNode->item.key == queue->head->item.key) {
		newNode->next = queue->head->next;
		free(queue->head);
		queue->head = newNode;

		reply.success = true;
		reply.item = item;
		return reply;
	}


	// newNode�� head���� key���� ������ (�����ϰ� ���ο��带 �տ�����) (�ߵ�) 
	if (newNode->item.key > queue->head->item.key) { 
		newNode->next = queue->head;
		queue->head = newNode;
		
		reply.success = true;
		reply.item = item;     //�̰� ���ؾߵɵ� 
		return reply;
	}


	//����߰����߰��ؾ��Ҷ� :�ڡڡڿ��⿡size�߰� �ʿ�ڡڡ�
	Node* curr = queue->head;       
	while(1) {
		// ���ο��尡 ���� ��庸�� ���� ���(�ڿ�����)
		if (curr->item.key >= item.key) {
			// �������� next�� ������� �׸��� ���س���� ������尡 ���ο��庸�� �������
			if (curr->next != NULL && curr->next->item.key < newNode->item.key) {
				newNode->next = curr->next;
				curr->next = newNode;

				reply.success = true;
				reply.item = item;     //�̰� ���ؾߵɵ� 
				return reply;
			}

			else if (curr->next != NULL &&  curr->next->item.key == item.key) {
				newNode->next = curr->next->next;
				nfree(curr->next);
				curr->next = newNode;
				
				
				reply.success = true;
				reply.item = item;     //�̰� ���ؾߵɵ� 
				return reply;
			}

			// 
			else {
				// ���س���� ������嵵 ���ο��庸�� ŭ(�׷� ���س�带 ��������)
				if (curr->next == NULL){
					curr->next = newNode;

					reply.success = true;
					reply.item = item;     //�̰� ���ؾߵɵ� 
					return reply;
				}
		
				else {
					curr = curr->next;
					continue;
				}
						// ��尡 �Ѱ��ۿ�����.
			}
		}
	}

	


}

// �ϼ� X
Reply dequeue(Queue* queue) {
	Reply reply = { false, NULL };
	Node* temp = queue->head->next;

	reply.success = true;
	reply.item = queue->head->item;
	
	nfree(queue->head);
	queue->head = temp;
	return reply;
}



Queue* range(Queue* queue, Key start, Key end) {
	Queue* cpQueue = init();
	
	int cnt = 0;
	Node* curr = queue->head; //index 0
	while (cnt < start) {
		curr = curr->next;
		cnt++;
	}

	while (cnt <= end) {
		enqueue(cpQueue, curr->item);
		curr = curr->next;
		cnt++;
	}



	return cpQueue;
}
