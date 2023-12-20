#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int data;
    struct TreeNode *left, *right;
} TreeNode;

TreeNode n1 = {1, NULL, NULL};
TreeNode n2 = {4, &n1, NULL};
TreeNode n3 = {16, NULL, NULL};
TreeNode n4 = {25, NULL, NULL};
TreeNode n5 = {20, &n3, &n4};
TreeNode n6 = {15, &n2, &n5};
TreeNode *root = &n6;

void inorder(TreeNode *root) {
    if(root) {
        inorder(root -> left);
        printf("%d ", root -> data);
        inorder(root -> right);
    }
}

void preorder(TreeNode *root) {
    if(root) {
        printf("%d ", root -> data);
        preorder(root -> left);
        preorder(root -> right);
    }
}

void postorder(TreeNode *root) {
    if(root) {
        postorder(root -> left);
        postorder(root -> right);
        printf("%d ", root -> data);
    }
}

TreeNode *new_node(int key) {
    TreeNode *node = (TreeNode *)malloc(sizeof(TreeNode));
    node -> data = key;
    node -> left = node -> right = NULL;

    return node;
}

void search(TreeNode *node, int key) {
    while (node != NULL) {
        if (key == node->data) {
            printf("탐색 성공!");
            return;
        }
        else if (key < node->data)
            node = node->left;
        else
            node = node->right;
    }
    printf("탐색 실패!");
}

TreeNode *insert_node(TreeNode *node, int key) {
    // 트리가 공백이면 새로운 노드를 반환한다.
    if (node == NULL)
        return new_node(key);

    // 그렇지 않으면 순환적으로 트리를 내려간다.
    if (key < node->data)
        node->left = insert_node(node->left, key);
    else if (key > node->data)
        node->right = insert_node(node->right, key);
    
    // 변경된 루트 포인터를 반환한다.
    return node;
}

// 이진 탐색 트리와 키가 주어지면 키가 저장된 노드를 삭제하고
// 새로운 루트 노드를 반환한다.
TreeNode *delete_node(TreeNode *root, int key) {
    if (root == NULL)
        return root;
    // 만약 키가 루트보다 작으면 왼쪽 서브 트리에 있는 것임
    if (key < root->data)
        root->left = delete_node(root->left, key);
    // 만약 키가 루트보다 크면 오른쪽 서브 트리에 있는 것임
    else if (key > root->data)
        root->right = delete_node(root->right, key);
    // 키가 루트와 같으면 이 노드를 삭제하면 됨
    else {
        // 첫 번째나 두 번째 경우
        if (root->left == NULL) {
            TreeNode *temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            TreeNode *temp = root->left;
            free(root);
            return temp;
        }
        // 세 번째 경우
        TreeNode *temp = min_value_node(root->right);
        // 중외 순회시 후계 노드를 복사한다.
        root->data = temp->data;
        // 중외 순회시 후계 노드를 삭제한다.
        root->right = delete_node(root->right, temp->data);
    }
    
    return root;
}

TreeNode *min_value_node(TreeNode *node) {
    TreeNode *current = node;
    // 맨 왼쪽 단말 노드를 찾으러 내려감
    while (current->left != NULL)
        current = current->left;

    return current;
}

void main() {
    printf("중위 순회\n");
    inorder(root);
    printf("\n");

    printf("전위 순회\n");
    preorder(root);
    printf("\n");

    printf("후위 순회\n");
    postorder(root);
    printf("\n");

    insert_node(root, 3);
    search(root, 3);

    return 0;
}