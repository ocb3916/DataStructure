#include <stdio.h>
#include <stdlib.h>
#define MAX_QUEUE_SIZE 100

typedef int element;
typedef struct {
    element queue[MAX_QUEUE_SIZE];
    int front;
    int rear;
} QueueType;

void init(QueueType *q) {
    q->front = 0;
    q->rear = 0;
}

// 공백 상태 검출 함수
int is_empty(QueueType *q) {
    return (q->front == q->rear);
}

// 포화 상태 검출 함수
int is_full(QueueType *q) {
    return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}

// 삽입 함수
void enqueue(QueueType *q, element item) {
    if (is_full(q))
        fprintf(stderr, "큐가 포화상태입니다\n");
    q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
    q->queue[q->rear] = item;
}

// 삭제 함수
element dequeue(QueueType *q) {
    if (is_empty(q))
        fprintf(stderr, "큐가 공백상태입니다\n");
    q->front = (q->front + 1) % MAX_QUEUE_SIZE;
    return q->queue[q->front];
}

int main(void) {
    QueueType q;
    init(&q);

    enqueue(&q, 10);
    enqueue(&q, 20);
    printf("%d\n", dequeue(&q));
    printf("%d\n", dequeue(&q));

    return 0;
}