#include <iostream>
#include <thread>
#include <atomic>
#include "queue.h"
#include <Windows.h>
using namespace std;

// 초간단 구동 테스트
// 주의: 아래 정의(Operation, Request)는 예시일 뿐
// 큐의 Item은 void*이므로 얼마든지 달라질 수 있음

#define REQUEST_PER_CLINET	10000

atomic<int> sum_key = 0;
atomic<int> sum_value = 0;
//atomic<double> response_time_tot = 0.0;

typedef enum {
	GET,		// GET: 큐에서 아이템을 꺼내는 연산
	SET,        // SET: 큐에 아이템을 추가하는 연산 
	GETRANGE    // GETRANGE: 큐에서 어떤범위만큼 복사할지  . -> range() + 
} Operation;

typedef struct {
	Operation op;		// operation -> 연산자 -> GET, SET, GETRANGE
	Item item;			// item -> 아이템 -> key, value
} Request;


// 매개변수로 queue와, 요청사항 배열(get할지set할지, 아이템목록등)과 요청의 갯수
// 를 받는다.

void client_func(Queue* queue, Request requests[], int n_request) {
	Reply reply = { false, 0 };

	// start_time = .....

	for (int i = 0; i < n_request; i++) {
		if (requests[i].op == GET) {
			reply = dequeue(queue);
		}
		else { // SET
			reply = enqueue(queue, requests[i].item);
		}

		if (reply.success) {
			// 단순히 리턴받은 키 값을 더함(아무 의미 없음)
			// 그럼 뭘 해야 할까? 
			sum_key += reply.item.key;
			sum_value += (int)reply.item.value; // void*에서 다시 int로 변환

			// 리턴받은 key, value 값 검증
			// ...생략...
		}
		else {
			// noop
		}
		
		// test
		
		
		/*printf("Queue -> ");
		if (queue != NULL) {
			Node* cur = queue->head;
			for (int i = 0; i < sizeof(queue) / 4; i++) {
				printf("%d ", cur->item.key);
				cur = cur->next;
				system("pause");
			}
			printf("\n");
		}
		
		*/
	}

	// 진짜로 필요한 건 지연시간을 측정하는 코드
	//
	// elapsed_time = finish_time - start_time;
	// finish_time = ....
	// average_response_time = elapsed_time / REQUEST_PER_CLIENT;
	// printf(...average_response_time of client1 = .....);
	// response_time_tot += finish_time - start_time;
}

int main(void) {
	srand((unsigned int)time(NULL));

	// 워크로드 생성(GETRANGE는 패스)
	Request requests[REQUEST_PER_CLINET];
	for (int i = 0; i < REQUEST_PER_CLINET / 2; i++) {
		requests[i].op = SET;
		requests[i].item.key = i;
		requests[i].item.value = (void*)(rand() % 1000000);
	}
	for (int i = REQUEST_PER_CLINET / 2; i < REQUEST_PER_CLINET; i++) {
		requests[i].op = GET;
	}

	Queue* queue = init();
	//if (queue == NULL) return 0;

	// 일단 한 개 뿐인데, 그래도 multi client라고 가정하기
	thread client = thread(client_func, queue, requests, REQUEST_PER_CLINET);
	client.join();

	release(queue);

	//TESt
	


	// 의미 없는 작업
	cout << "sum of returned keys = " << sum_key << endl;
	cout << "sum of returned values = " << sum_value << endl;

	// 진짜로 필요한 코드
	// 진짜로 필요한 코드
	// total_average_response_time = total_response_time / n_cleint;
	// printf("total average response time = ....

	//Test code

	return 0;
}

