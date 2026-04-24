#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <queue>
#define MAX 1001

bool graph[MAX][MAX];
int check[MAX];
int result[MAX];
typedef struct queue {
	int item;
	struct queue* ptr;
}q;
q* front = NULL;
q* rear = NULL;
void push(const int);
int pop();
int isEmpty();

int main(void) {
	int n, m, input_number, before, input;
	int index = 0;
	int edge;
	scanf("%d %d", &n, &m);
	while (m--) {
		scanf("%d %d", &input_number, &before);
		while (--input_number) {
			scanf("%d", &input);
			if (!graph[before][input]) { //중복 간선을 걸러주는 if문
				graph[before][input] = true;
				++check[input];
			}
			before = input;
		}
	}
	for (int i = 1; i <= n; ++i) {
		if (!check[i]) {
			push(i); //부모 노드의 개수가 0일때 큐에 push
		}
	}

	for (int i = 0; i < n; ++i) {
		if (isEmpty()) { //비어있으면 0을 출력하고 프로그램 종료 
			puts("0");
			return 0;
		}
		else {
			edge = pop();
			result[index++] = edge;
			for (int j = 1; j <= n; ++j) {
				if (graph[edge][j]) {
					--check[j];
					if (!check[j]) {
						push(j);
					}
				}
			}
		}

	}
	for (int i = 0; i < n; ++i) printf("%d\n", result[i]);
	return 0;
}

int isEmpty() {
	return rear == NULL;
}

int pop() {
	int item;
	q* tmp = (q*)malloc(sizeof(q));
	if(front->ptr == NULL) {
		int ret = front->item;
		front = rear = NULL;
		return ret;
	}
	tmp = front;
	front = tmp->ptr;
	item = tmp->item;
	free(tmp);
	return item;
}

void push(const int item) {
	q* node = (q*)malloc(sizeof(q));
	node->item = item;
	node->ptr = NULL;
	if (!front) {
		front = node;
		rear = node;
	}
	else {
		rear->ptr = node;
		rear = node;
	}
	return;
}
