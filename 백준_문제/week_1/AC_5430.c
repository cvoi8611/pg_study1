
/*
    함수 R은 배열에 있는 수를 뒤집는 함수이고
    D는 첫번째 수를 버리는 함수이다

    R이 짝수일 떄, D는 첫번째 수를 버리는 함수가 되고
    R이 홀수일 떄, D는 마지막 수를 버리는 함수가 된다.

    앞, 뒤의 수를 버릴 수 있는 자료구조 형태가 필요함
    -> 앞, 뒤로 값을 수정할 수 있는 자료구조로는 데크가 존재
    따라서 이 문제는 데크를 구현하여 풀어야 함
    
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct node {       //구조체 노드 생성
	int data;
	struct node* prev;
	struct node* next;
} node;

typedef struct {            //구조체 데크 생성
	node* front;
	node* rear;
	int count;
} Deque;

void initDeque(Deque* deque) {      //비어있는 데크 생성
	deque->front = deque->rear = NULL;
	deque->count = 0;
}

int is_empty(Deque* deque) {        //데크 값이 비어있음
	if (deque->count == 0) return 1;
	else return 0;
}

void add_back(Deque* deque, int data) {     //데크에 값을 추가로 생성
	node* now = (node*)malloc(sizeof(node));
	if (is_empty(deque)) {                  //데크가 비어있을 경우, 첫번째 노드로 생성
		deque->front = now;
		deque->rear = now;
		now->prev = NULL;
	}
	else {                                  //데크가 비어있지 않을 경우, 현재(now) 노드를 이전 노드와 연결
		now->prev = deque->rear;
		deque->rear->next = now;
		deque->rear = now;
	}
	now->next = NULL;
	now->data = data;
	(deque->count)++;
}

int delete_front(Deque* deque) {            //R이 짝수인 경우 + D가 입력됨 ) 첫번쨰 수를 버림
	if (is_empty(deque)) return -1;
	else {                                  //
		int del_data;
		node* del_node;
		del_data = deque->front->data;
		del_node = deque->front;
		deque->front = deque->front->next;
		if (deque->count == 1) deque->rear = NULL;
		free(del_node);
		(deque->count)--;
		return del_data;
	}
}

int delete_back(Deque* deque) {             //R이 홀수인 경우 + D가 입력됨 ) 마지막 수를 버림
	if (is_empty(deque)) return -1;
	else {
		int del_data;
		node* del_node;
		del_data = deque->rear->data;
		del_node = deque->rear;
		deque->rear = deque->rear->prev;
		if (deque->count == 1) deque->rear = NULL;
		free(del_node);
		(deque->count)--;
		return del_data;
	}
}

main() {
	int t, n, x;
	char p[100000], c;                      
	Deque deque;        //데크 구조체 생성
	scanf("%d", &t);
	for (int i=0; i<t; i++) {           //테스트 케이스(t) 만큼 반복
		initDeque(&deque);              //빈 데크 생성
		scanf("%s", p);
		scanf("%d", &n);
		getchar();                      
		if (n != 0) {                   // (n의 갯수가 0이 아니라면)
			scanf("%c", &c);                // '[' 버리기
			for (int i=0; i<n; i++) {
				scanf("%d%c", &x, &c);      // x값 받고, '[' 또는 ',' 버리기
				add_back(&deque, x);
			}
		}                               // (n의 갯수가 0이라면) -> []
		else scanf("%c%c", &c, &c);         // [] 입력 받고 버림
		getchar();
		int swap = 0, error = 0;
		for (int i=0; i<strlen(p); i++) {
			if (p[i] == 'R') {          // R을 입력받으면 swap 값이 바뀜
				swap = !swap;           // R이 홀수 : 1 , 짝수 : 0
			}
			else if (p[i] == 'D') {     // D를 입력받음
				if (is_empty(&deque)) {
					printf("error\n");
					error = 1;
					break;
				}
				else if (swap) {        //swap값이 1임 = R은 홀수   -> 마지막 수를 버림
					delete_back(&deque);
				}                       //swap값이 0임 = R은 짝수   -> 처음 수를 버림
				else delete_front(&deque);
			}
		}
		if (!error) {               //에러 발생 X 인 경우 데크 값 모두 출력
			printf("[");            
			if (!swap) {                
				while (!is_empty(&deque)) {
					printf("%d", delete_front(&deque));
					if (!is_empty(&deque)) {
						printf(",");
					}
				}
			}
			else {
				while (!is_empty(&deque)) {
					printf("%d", delete_back(&deque));
					if (!is_empty(&deque)) {
						printf(",");
					}
				}
			}
			printf("]\n");
		}
	}	
}