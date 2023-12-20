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
            printf("Ž�� ����!");
            return;
        }
        else if (key < node->data)
            node = node->left;
        else
            node = node->right;
    }
    printf("Ž�� ����!");
}

TreeNode *insert_node(TreeNode *node, int key) {
    // Ʈ���� �����̸� ���ο� ��带 ��ȯ�Ѵ�.
    if (node == NULL)
        return new_node(key);

    // �׷��� ������ ��ȯ������ Ʈ���� ��������.
    if (key < node->data)
        node->left = insert_node(node->left, key);
    else if (key > node->data)
        node->right = insert_node(node->right, key);
    
    // ����� ��Ʈ �����͸� ��ȯ�Ѵ�.
    return node;
}

// ���� Ž�� Ʈ���� Ű�� �־����� Ű�� ����� ��带 �����ϰ�
// ���ο� ��Ʈ ��带 ��ȯ�Ѵ�.
TreeNode *delete_node(TreeNode *root, int key) {
    if (root == NULL)
        return root;
    // ���� Ű�� ��Ʈ���� ������ ���� ���� Ʈ���� �ִ� ����
    if (key < root->data)
        root->left = delete_node(root->left, key);
    // ���� Ű�� ��Ʈ���� ũ�� ������ ���� Ʈ���� �ִ� ����
    else if (key > root->data)
        root->right = delete_node(root->right, key);
    // Ű�� ��Ʈ�� ������ �� ��带 �����ϸ� ��
    else {
        // ù ��°�� �� ��° ���
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
        // �� ��° ���
        TreeNode *temp = min_value_node(root->right);
        // �߿� ��ȸ�� �İ� ��带 �����Ѵ�.
        root->data = temp->data;
        // �߿� ��ȸ�� �İ� ��带 �����Ѵ�.
        root->right = delete_node(root->right, temp->data);
    }
    
    return root;
}

TreeNode *min_value_node(TreeNode *node) {
    TreeNode *current = node;
    // �� ���� �ܸ� ��带 ã���� ������
    while (current->left != NULL)
        current = current->left;

    return current;
}

void main() {
    printf("���� ��ȸ\n");
    inorder(root);
    printf("\n");

    printf("���� ��ȸ\n");
    preorder(root);
    printf("\n");

    printf("���� ��ȸ\n");
    postorder(root);
    printf("\n");

    insert_node(root, 3);
    search(root, 3);

    return 0;
}