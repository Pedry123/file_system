#include<stdio.h>
#include<stdlib.h>

typedef struct node {
    int info;
    struct node *next;
    struct node *prev;
} Node;

void prepend(Node **head, int value) {
    Node *newNode = (Node *) malloc(sizeof(Node));
    newNode->info = value;
    newNode->next = *head;
    newNode->prev = NULL;
    if (*head != NULL) {
        (*head)->prev = newNode;
    }
}

void append(Node **head, int value) {
    Node *newNode = (Node *) malloc(sizeof(Node));
    newNode->info = value;
    newNode->next = NULL;
    if (*head == NULL) {
        newNode->prev = NULL;
        *head = newNode;
        return;
    }
    Node *last = *head;
    while (last->next != NULL) {
        last = last->next;
    }
    last->next = newNode;
    newNode->prev = last;
}

void insertAfter(Node *prevNode, int value) {
    if (prevNode == NULL) {
        return;
    }
    Node *newNode = (Node *) malloc(sizeof(Node));
    newNode->info = value;
    newNode->next = prevNode->next;
    prevNode->next = newNode;
    newNode->prev = prevNode;
    if (newNode->next != NULL) {
        newNode->next->prev = newNode;
    }
}

Node* remove(Node* head, int value) {
    Node *temp = head;
    // If head node itself holds the key to be deleted
    if (temp != NULL && temp->info == value) {
        head = temp->next;
        free(temp);
        return head;
    }
    // Search for the key to be deleted, keep track of the
    while (temp != NULL && temp->info != value) {
        temp = temp->next;
    }
    if (temp == NULL) {
        return head;
    }
    // Unlink the node from linked list
    temp->prev->next = temp->next;
    if (temp->next != NULL) {
        temp->next->prev = temp->prev;
    }
    free(temp);
    return head;
}

void freeList(Node *head) {
    Node *temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}



int main() {

}