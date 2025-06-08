#include <iostream>
#include <thread>
#include <atomic>
#include "queue.h"
#include <Windows.h>
#include <vector>
#include <chrono> 
using namespace std;

// �ʰ��� ���� �׽�Ʈ
// ����: �Ʒ� ����(Operation, Request)�� ������ ��
// ť�� Item�� void*�̹Ƿ� �󸶵��� �޶��� �� ����

#define REQUEST_PER_CLINET	1000000

atomic<int> sum_key = 0;
atomic<int> sum_value = 0;
//atomic<double> response_time_tot = 0.0;

typedef enum {
	GET,		// GET: ť���� �������� ������ ����
	SET,        // SET: ť�� �������� �߰��ϴ� ���� 
	GETRANGE    // GETRANGE: ť���� �������ŭ ��������  . -> range() + 
} Operation;

typedef struct {
	Operation op;		// operation -> ������ -> GET, SET, GETRANGE
	Item item;			// item -> ������ -> key, value
} Request;


// �Ű������� queue��, ��û���� �迭(get����set����, �����۸�ϵ�)�� ��û�� ����
// �� �޴´�.

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
			// �ܼ��� ���Ϲ��� Ű ���� ����(�ƹ� �ǹ� ����)
			// �׷� �� �ؾ� �ұ�? 
			 // void*���� �ٽ� int�� ��ȯ

			// ���Ϲ��� key, value �� ����
			// ...����...

			
		}
		else {
			// noop
		}
		
		
	}
	std::cout << "[Thread] ����: " << std::this_thread::get_id() << endl;



	// ��¥�� �ʿ��� �� �����ð��� �����ϴ� �ڵ�
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

	// ��ũ�ε� ����(GETRANGE�� �н�)
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
	//Request���

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
	// Queue����
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
	////Original Queue ���
	//Node* cursor = queue->head;
	//
	//cout << "Origin Queue ���: " << endl;
	//while (cursor->next != NULL) {
	//	cout << cursor->item.key << " : " << (int)cursor->item.value << endl;
	//	cursor = cursor->next;
	//}
	//cout << cursor->item.key << " : " << (int)cursor->item.value << endl;

	//
	//// Queue Copy
	//Key s = 1, e = 3;

	//cout << endl;
	//cout << "cpQueue ���: " << endl;
	//Queue* cpQueue = range(queue, s, e);

	//Node* cpCursor = cpQueue->head;

	//// Copied Queue ���



	//while (cpCursor->next != NULL) {
	//	cout << cpCursor->item.key << " : " << (int)cpCursor->item.value << endl;
	//	cpCursor = cpCursor->next;
	//}
	//cout << cpCursor->item.key << " : " << (int)cpCursor->item.value << endl;
	//
	//
	////Copied Queue ���� (�������� �׽�Ʈ)
	//
	//cpQueue->head->item.key = 1111;
	//cpQueue->head->item.value = (void*)9999;
	//

	//////Original Queue ���
	//Node* cursor3 = queue->head;
	//cout << endl;
	//cout << "Origin Queue ���: " << endl;
	//while (cursor3->next != NULL) {
	//	cout << cursor3->item.key << " : " << (int)cursor3->item.value << endl;
	//	cursor3 = cursor3->next;
	//}
	//cout << cursor3->item.key << " : " << (int)cursor3->item.value << endl;

	//// �����Copied Queue ���

	//Node* cpCursor1 = cpQueue->head;
	//cout << endl;
	//cout << "����� cpQueue ���: " << endl;
	//while (cpCursor1->next != NULL) {
	//	cout << cpCursor1->item.key << " : " << (int)cpCursor1->item.value << endl;
	//	cpCursor1 = cpCursor1->next;
	//}
	//cout << cpCursor1->item.key << " : " << (int)cpCursor1->item.value << endl;


	// �ϴ� �� �� ���ε�, �׷��� multi client��� �����ϱ�
	
	
	std::vector<std::thread> threads;

	// ���� ���� ������ ����
	
	threads.emplace_back(client_func, queue, requests, REQUEST_PER_CLINET);
	threads.emplace_back(client_func, queue, requests2, REQUEST_PER_CLINET);
	
	


	// �� ���� join
 	for (auto& t : threads) {
		if (t.joinable()) {
			t.join();
		}
	}
	printf("sumk: %d, sumv: %d\n", sumk, sumv);

	printf("get: %d set: %d\n", getcnt, setcnt);
	
	//Original Queue ���
	
	
 	release(queue);
	//release(cpQueue);
	
	
	// �ǹ� ���� �۾�
	std::cout << "sum of returned keys = " << sum_key << endl;
	std::cout << "sum of returned values = " << sum_value << endl;
	auto end = std::chrono::high_resolution_clock::now();    // ��
	std::chrono::duration<double> elapsed = end - start;
	// ��¥�� �ʿ��� �ڵ�
	// ��¥�� �ʿ��� �ڵ�
	// total_average_response_time = total_response_time / n_cleint;
	// printf("total average response time = ....

	//Test code
	std::cout << "�� ���� �ð�: " << elapsed.count() << " ��" << std::endl;
	return 0;
}

