#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int element; // 요소의 타입
typedef struct DlistNode { // 노드의 타입
    element data;
    struct DlistNode *llink;
    struct DlistNode *rlink;
} DlistNode;

typedef struct DequeType { // 덱의 타입
    DlistNode *head;
    DlistNode *tail;
} DequeType;

void init(DequeType *dq) {
    dq->head = dq->tail = NULL;
}

bool is_empty(DequeType *dq) {
    return (dq->head == NULL);
}

DlistNode *create_node(DlistNode *llink, element item, DlistNode *rlink) {
    DlistNode *new_node = (DlistNode *)malloc(sizeof(DlistNode));
    if (new_node == NULL)
        fprintf(stderr, "메모리 할당 오류");
    new_node->llink = llink;
    new_node->data = item;
    new_node->rlink = rlink;
    return new_node;
}

void add_front(DequeType *dq, element item) {
    DlistNode *new_node = create_node(NULL, item, dq->head);
    if (is_empty(dq))
        dq->tail = new_node;
    else
        dq->head->llink = new_node;
    dq->head = new_node;
}

void add_rear(DequeType *dq, element item) {
    DlistNode *new_node = create_node(dq->tail, item, NULL);
    if (is_empty(dq))
        dq->head = new_node;
    else
        dq->tail->rlink = new_node;
    dq->tail = new_node;
}

element delete_front(DequeType *dq) {
    element item;
    DlistNode *removed_node;
    if (is_empty(dq))
        fprintf(stderr, "공백 덱에서 삭제");
    else {
        removed_node = dq->head;    // 삭제할 노드
        item = removed_node->data;  // 데이터 추출
        dq->head = dq->head->rlink; // 헤드 포인터 변경
        free(removed_node);         // 메모리 공간 반납
        if (dq->head == NULL)       // 공백상태이면
            dq->tail = NULL;
        else // 공백상태가 아니면
            dq->head->llink = NULL;
    }
    return item;
}

element delete_rear(DequeType *dq) {
    element item;
    DlistNode *removed_node;
    if (is_empty(dq))
        fprintf(stderr, "공백 덱에서 삭제");
    else
    {
        removed_node = dq->tail;
        item = removed_node->data;
        dq->tail = dq->tail->llink;
        free(removed_node);
        if (dq->tail == NULL)
            dq->head = NULL;
        else
            dq->tail->rlink = NULL;
    }
    return item;
}

int main(void) {
    DequeType *dq = (DequeType *)malloc(sizeof(DequeType));
    init(dq);

    add_front(dq, 10);
    add_front(dq, 20);
    add_rear(dq, 30);
    printf("%d\n", delete_front(dq));
    printf("%d\n", delete_front(dq));
    printf("%d\n", delete_rear(dq));

    return 0;
}