#include <iostream>
#include <thread>
#include <atomic>
#include "queue.h"
#include <Windows.h>
#include <vector>
#include <chrono> 
using namespace std;

// 초간단 구동 테스트
// 주의: 아래 정의(Operation, Request)는 예시일 뿐
// 큐의 Item은 void*이므로 얼마든지 달라질 수 있음

#define REQUEST_PER_CLINET	1000000

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

int getcnt = 0;
int setcnt = 0;

void client_func(Queue* queue, Request requests[], int n_request) {
	Reply reply = { false, 0 };
	
	// start_time = .....

	for (int i = 0; i < n_request; i++) {
		if (requests[i].op == GET) {
			reply = dequeue(queue);
			sum_key += reply.item.key;
			sum_value += (int)reply.item.value;
			getcnt++;
			//cout << "GET : key: " << reply.item.key << ", value: " << (int)reply.item.value << endl;
		}
		else { // SET
			reply = enqueue(queue, requests[i].item);
			
			setcnt++;
			//cout << "SET : key: " << reply.item.key << ", value: " << (int)reply.item.value << endl;
		}

		if (reply.success) {
			// 단순히 리턴받은 키 값을 더함(아무 의미 없음)
			// 그럼 뭘 해야 할까? 
			 // void*에서 다시 int로 변환

			// 리턴받은 key, value 값 검증
			// ...생략...

			
		}
		else {
			// noop
		}
		
		
	}
	std::cout << "[Thread] 종료: " << std::this_thread::get_id() << endl;



	// 진짜로 필요한 건 지연시간을 측정하는 코드
	//
	// elapsed_time = finish_time - start_time;
	// finish_time = ....
	// average_response_time = elapsed_time / REQUEST_PER_CLIENT;
	// printf(...average_response_time of client1 = .....);
	// response_time_tot += finish_time - start_time;
}

int main(void) {
	auto start = std::chrono::high_resolution_clock::now();
	srand((unsigned int)time(NULL));
	int sumk = 0, sumv = 0;

	// 워크로드 생성(GETRANGE는 패스)
	Request requests[REQUEST_PER_CLINET] = {};
	Request requests2[REQUEST_PER_CLINET] = {};

	//requests1
	for (int i = 0; i < REQUEST_PER_CLINET / 2; i++) {
		requests[i].op = SET;
		requests[i].item.key = i;
		requests[i].item.value = (void*)(rand() % 10);
		sumk += requests[i].item.key;
		sumv += (int)requests[i].item.value;
		//printf("%d\n", i);
	}
	for (int i = REQUEST_PER_CLINET / 2; i < REQUEST_PER_CLINET; i++) {
		requests[i].op = GET;
		//printf("%d\n", i);
	}
	//requests2
	for (int i = 0; i < REQUEST_PER_CLINET / 2; i++) {
		requests2[i].op = SET;
		requests2[i].item.key = i+ REQUEST_PER_CLINET/2;
		requests2[i].item.value = (void*)(rand() % 10);
		sumk += requests2[i].item.key;
		sumv += (int)requests2[i].item.value;
		//printf("%d\n", i);
	}

	for (int i = REQUEST_PER_CLINET / 2; i < REQUEST_PER_CLINET; i++) {
		requests2[i].op = GET;
		//printf("%d\n", i);
	}

	/*requests[1].item.key = 0;
	requests2[1].item.key = 5;*/
	//Request출력

	//cout << endl;
	//cout << "Request1: " << endl;
	/*for (int i = 0; i < REQUEST_PER_CLINET; i++) {
		cout << i << ":" << "requests1["<< i <<"].op = " << requests[i].op <<", requests1[" << i << "].item.key = " << requests[i].item.key << ", requests1[" << i << "].item.value : " << (int)requests[i].item.value << endl;
	}
	cout << endl;
	cout << "Request2: " << endl;
	for (int i = 0; i < REQUEST_PER_CLINET; i++) {
		cout << i << ":" << "requests2[" << i << "].op = " << requests2[i].op << ", requests2[" << i << "].item.key = " << requests2[i].item.key << ", requests2[" << i << "].item.value : " << (int)requests2[i].item.value << endl;
	}*/
	// Queue생성
	Queue* queue = init();
	if (queue == NULL) return 0;

	// enqueue, dequeue Test
	//Reply a;
	//Item newItem = { 3, (void*)123 };
	//a = enqueue(queue, newItem);
	//cout << a.item.key <<" : "<< (int)a.item.value << endl;
	//Item newItem2 = { 3, (void*)3 };
	//a = enqueue(queue, newItem2);
	//cout << a.item.key << " : " << (int)a.item.value << endl;
	//Item newItem3 = { 2, (void*)12 };
	//a = enqueue(queue, newItem3);
	//cout << a.item.key << " : " << (int)a.item.value << endl;
	//Item newItem4 = { 4, (void*)4 };
	//a = enqueue(queue, newItem4);
	//cout << a.item.key << " : " << (int)a.item.value << endl;
	//Item newItem5 = { 2, (void*)2 };
	//a = enqueue(queue, newItem5);
	//cout << a.item.key << " : " << (int)a.item.value << endl;
	//Item newItem6 = { 1, (void*)1 };
	//a = enqueue(queue, newItem6);
	//cout << a.item.key << " : " << (int)a.item.value << endl;
	//Item newItem7 = { 5, (void*)5 };
	//a = enqueue(queue, newItem7);
	//cout << a.item.key << " : " << (int)a.item.value << endl;

	///*a = dequeue(queue); 
	//printf("%d \n", a.item.value);*/

	//cout <<  endl;
	////Original Queue 출력
	//Node* cursor = queue->head;
	//
	//cout << "Origin Queue 출력: " << endl;
	//while (cursor->next != NULL) {
	//	cout << cursor->item.key << " : " << (int)cursor->item.value << endl;
	//	cursor = cursor->next;
	//}
	//cout << cursor->item.key << " : " << (int)cursor->item.value << endl;

	//
	//// Queue Copy
	//Key s = 1, e = 3;

	//cout << endl;
	//cout << "cpQueue 출력: " << endl;
	//Queue* cpQueue = range(queue, s, e);

	//Node* cpCursor = cpQueue->head;

	//// Copied Queue 출력



	//while (cpCursor->next != NULL) {
	//	cout << cpCursor->item.key << " : " << (int)cpCursor->item.value << endl;
	//	cpCursor = cpCursor->next;
	//}
	//cout << cpCursor->item.key << " : " << (int)cpCursor->item.value << endl;
	//
	//
	////Copied Queue 변경 (깊은복사 테스트)
	//
	//cpQueue->head->item.key = 1111;
	//cpQueue->head->item.value = (void*)9999;
	//

	//////Original Queue 출력
	//Node* cursor3 = queue->head;
	//cout << endl;
	//cout << "Origin Queue 출력: " << endl;
	//while (cursor3->next != NULL) {
	//	cout << cursor3->item.key << " : " << (int)cursor3->item.value << endl;
	//	cursor3 = cursor3->next;
	//}
	//cout << cursor3->item.key << " : " << (int)cursor3->item.value << endl;

	//// 변경된Copied Queue 출력

	//Node* cpCursor1 = cpQueue->head;
	//cout << endl;
	//cout << "변경된 cpQueue 출력: " << endl;
	//while (cpCursor1->next != NULL) {
	//	cout << cpCursor1->item.key << " : " << (int)cpCursor1->item.value << endl;
	//	cpCursor1 = cpCursor1->next;
	//}
	//cout << cpCursor1->item.key << " : " << (int)cpCursor1->item.value << endl;


	// 일단 한 개 뿐인데, 그래도 multi client라고 가정하기
	
	
	std::vector<std::thread> threads;

	// 여러 개의 스레드 생성
	
	threads.emplace_back(client_func, queue, requests, REQUEST_PER_CLINET);
	threads.emplace_back(client_func, queue, requests2, REQUEST_PER_CLINET);
	
	


	// 한 번에 join
 	for (auto& t : threads) {
		if (t.joinable()) {
			t.join();
		}
	}
	printf("sumk: %d, sumv: %d\n", sumk, sumv);

	printf("get: %d set: %d\n", getcnt, setcnt);
	
	//Original Queue 출력
	
	
 	release(queue);
	//release(cpQueue);
	
	
	// 의미 없는 작업
	std::cout << "sum of returned keys = " << sum_key << endl;
	std::cout << "sum of returned values = " << sum_value << endl;
	auto end = std::chrono::high_resolution_clock::now();    // 끝
	std::chrono::duration<double> elapsed = end - start;
	// 진짜로 필요한 코드
	// 진짜로 필요한 코드
	// total_average_response_time = total_response_time / n_cleint;
	// printf("total average response time = ....

	//Test code
	std::cout << "총 실행 시간: " << elapsed.count() << " 초" << std::endl;
	return 0;
}

