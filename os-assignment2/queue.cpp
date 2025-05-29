#include <iostream>
#include "queue.h"

// queue생성 queue는 하나만 운영 
// Queue 생성후 Queue = init()해가지고 초기화 하지 않을까?
// 그리고 return으로 안의 내용들을 반환해서 초기화?
Queue* init(void) {
	return NULL;
}

// queue해제 queue내부의 모든 노드 해제 후 queue 삭제
// 근데 자세히는 모르겠음. 동적으로 할당한 queue와 그안에 있는 노드를 
// 해제하는 거같긴한데 종료버튼느낌인건가
void release(Queue* queue) {
	

	return;
}



//노드 관리 세트 : nalloc, nfree, nclone
// 노드생성후 반환하면될듯 ㅇㅇ 아님말고
Node* nalloc(Item item) {
	// Node 생성, item으로 초기화
	return NULL;
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
