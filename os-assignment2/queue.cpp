#include <iostream>
#include "queue.h"


// queue생성 queue는 하나만 운영 
// Queue 생성후 Queue = init()해가지고 초기화 하지 않을까?
// 그리고 return으로 안의 내용들을 반환해서 초기화?
Queue* init(void) { //구현완
	Queue* queue = (Queue*)malloc(sizeof(Queue));
	queue->head = NULL; // head 초기화
	queue->tail = NULL; // tail 초기화
	return queue;
}

// queue해제 queue내부의 모든 노드 해제 후 queue 삭제
// 근데 자세히는 모르겠음. 동적으로 할당한 queue와 그안에 있는 노드를 
// 해제하는 거같긴한데 종료버튼느낌인건가
void release(Queue* queue) {
	

	return;
}



//노드 관리 세트 : nalloc, nfree, nclone

Node* nalloc(Item item) { //구현완
	// Node 생성, item으로 초기화
	Node* node = (Node*)malloc(sizeof(Node));
	node->item = item;
	return node;
}

// node 해제 
// 동적으로 할당한 노드를 해제시켜준다.
void nfree(Node* node) {
	return;
}

// node 복사 아래 range랑 같이 사용할듯?
Node* nclone(Node* node) {
	return NULL;
}


// enqueue : Queue의 'tail'에 노드 추가
Reply enqueue(Queue* queue, Item item) {
	Reply reply = { false, NULL };
	Node* node = nalloc(item);
	
	if (queue->head == NULL) { //queue가 비어있을시 node가 head이자 tail
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
		if (cur->item.key < item.key) { // 현재 노드의 키가 새로 추가할 아이템의 키보다 작으면
			cur = cur->next; // 다음 노드로 이동
		}
		
		
	}
	



	return reply;
}

// dequeue : Queue의 'head'에서 노드빼기 -> GET과 연동될듯 (main.cpp -> enum Operation)
// 탐색해서 꺼내는거랑은 다름 queue는 FIFO이기때문  
// 무조건 head에서 꺼내야함
Reply dequeue(Queue* queue) {
	Reply reply = { false, NULL };
	return reply;
}

// range -> 특정범위의 노드들을 복사(nclone)해서 반환 -> GETRANGE와 연관있을듯 (main.cpp -> enum Operation)
// temp하나 만들어서 거기다가 nclone하고 그걸 반복할듯
// abcd노드에서 bc를 복사한다치면 a탐색후 b탐색후 nclone 그리고 c탐색후 nclone 후 종료
// 이게 특정 범위 복사일 수 밖에 없는 이유는 
// queue에서 꺼낼 수 있는 노드는 head밖에없기때문이다.
Queue* range(Queue* queue, Key start, Key end) {
	return NULL;
}
