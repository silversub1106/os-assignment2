#include <iostream>
#include "queue.h"


// queue���� queue�� �ϳ��� � 
// Queue ������ Queue = init()�ذ����� �ʱ�ȭ ���� ������?
// �׸��� return���� ���� ������� ��ȯ�ؼ� �ʱ�ȭ?
Queue* init(void) { //������
	Queue* queue = (Queue*)malloc(sizeof(Queue));
	queue->head = NULL; // head �ʱ�ȭ
	queue->tail = NULL; // tail �ʱ�ȭ
	return queue;
}

// queue���� queue������ ��� ��� ���� �� queue ����
// �ٵ� �ڼ����� �𸣰���. �������� �Ҵ��� queue�� �׾ȿ� �ִ� ��带 
// �����ϴ� �Ű����ѵ� �����ư�����ΰǰ�
void release(Queue* queue) {
	

	return;
}



//��� ���� ��Ʈ : nalloc, nfree, nclone

Node* nalloc(Item item) { //������
	// Node ����, item���� �ʱ�ȭ
	Node* node = (Node*)malloc(sizeof(Node));
	node->item = item;
	return node;
}

// node ���� 
// �������� �Ҵ��� ��带 ���������ش�.
void nfree(Node* node) {
	return;
}

// node ���� �Ʒ� range�� ���� ����ҵ�?
Node* nclone(Node* node) {
	return NULL;
}


// enqueue : Queue�� 'tail'�� ��� �߰�
Reply enqueue(Queue* queue, Item item) {
	Reply reply = { false, NULL };
	Node* node = nalloc(item);
	
	if (queue->head == NULL) { //queue�� ��������� node�� head���� tail
		queue->head = node;
		queue->tail = node;
		reply.success = true;
		reply.item = item;
		return reply;
	}

	if (node->item.key > queue->head->item.key) {
		node->next = queue->head;
		queue->head = node;
		node->
	}

	Node * cur = queue->head;
	while (cur!=queue->tail) {
		if (cur->item.key < item.key) { // ���� ����� Ű�� ���� �߰��� �������� Ű���� ������
			cur = cur->next; // ���� ���� �̵�
		}
		
		
	}
	



	return reply;
}

// dequeue : Queue�� 'head'���� ��廩�� -> GET�� �����ɵ� (main.cpp -> enum Operation)
// Ž���ؼ� �����°Ŷ��� �ٸ� queue�� FIFO�̱⶧��  
// ������ head���� ��������
Reply dequeue(Queue* queue) {
	Reply reply = { false, NULL };
	return reply;
}

// range -> Ư�������� ������ ����(nclone)�ؼ� ��ȯ -> GETRANGE�� ���������� (main.cpp -> enum Operation)
// temp�ϳ� ���� �ű�ٰ� nclone�ϰ� �װ� �ݺ��ҵ�
// abcd��忡�� bc�� �����Ѵ�ġ�� aŽ���� bŽ���� nclone �׸��� cŽ���� nclone �� ����
// �̰� Ư�� ���� ������ �� �ۿ� ���� ������ 
// queue���� ���� �� �ִ� ���� head�ۿ����⶧���̴�.
Queue* range(Queue* queue, Key start, Key end) {
	return NULL;
}
