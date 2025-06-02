#include <iostream>
#include "queue.h"

// queue���� queue�� �ϳ��� � 
// Queue ������ Queue = init()�ذ����� �ʱ�ȭ ���� ������?
// �׸��� return���� ���� ������� ��ȯ�ؼ� �ʱ�ȭ?
Queue* init(void) {
	return NULL;
}

// queue���� queue������ ��� ��� ���� �� queue ����
// �ٵ� �ڼ����� �𸣰���. �������� �Ҵ��� queue�� �׾ȿ� �ִ� ��带 
// �����ϴ� �Ű����ѵ� �����ư�����ΰǰ�
void release(Queue* queue) {
	

	return;
}



//��� ���� ��Ʈ : nalloc, nfree, nclone

Node* nalloc(Item item) {
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
	
	
	Node* current = queue->head;
	while (1) {
		if (node->item.key < current->item.key) {
			Node* temp = current->next;
			current->next = node;
			node->next = temp;
			free(temp);
			reply.success = true;
			return reply;
		}

		else {
			current = current->next;
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
