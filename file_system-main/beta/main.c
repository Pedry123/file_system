#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to represent a file or folder
struct Node {
    char name[100];
    struct Node* parent;
    struct Node* child;
    struct Node* sibling;
};

// Function to create a new file or folder
struct Node* createNode(char name[]) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    strcpy(newNode->name, name);
    newNode->parent = NULL;
    newNode->child = NULL;
    newNode->sibling = NULL;
    return newNode;
}

// Function to display the current folder path
void displayPath(struct Node* current) {
    if (current == NULL) {
        return;
    }
    displayPath(current->parent);
    printf("%s/", current->name);
}

// Function to display the contents of a folder
void displayContents(struct Node* current) {
    if (current == NULL) {
        printf("Folder is empty.\n");
        return;
    }
    struct Node* temp = current->child;
    while (temp != NULL) {
        printf("%s\n", temp->name);
        temp = temp->sibling;
    }
}

// Function to navigate to a specific folder
struct Node* navigate(struct Node* current, char name[]) {
    struct Node* temp = current->child;
    while (temp != NULL) {
        if (strcmp(temp->name, name) == 0) {
            return temp;
        }
        temp = temp->sibling;
    }
    return NULL;
}

// Function to create a file or folder
void create(struct Node* current, char name[], char type[]) {
    struct Node* newNode = createNode(name);
    newNode->parent = current;
    if (strcmp(type, "file") == 0) {
        if (current->child == NULL) {
            current->child = newNode;
        } else {
            struct Node* temp = current->child;
            while (temp->sibling != NULL) {
                temp = temp->sibling;
            }
            temp->sibling = newNode;
        }
    } else if (strcmp(type, "folder") == 0) {
        if (current->child == NULL) {
            current->child = newNode;
        } else {
            struct Node* temp = current->child;
            while (temp->sibling != NULL) {
                temp = temp->sibling;
            }
            temp->sibling = newNode;
        }
    }
}

// Function to delete a file or folder
void delete(struct Node* current, char name[]) {
    struct Node* temp = current->child;
    struct Node* prev = NULL;
    while (temp != NULL) {
        if (strcmp(temp->name, name) == 0) {
            if (prev == NULL) {
                current->child = temp->sibling;
            } else {
                prev->sibling = temp->sibling;
            }
            free(temp);
            printf("Successfully deleted %s.\n", name);
            return;
        }
        prev = temp;
        temp = temp->sibling;
    }
    printf("%s not found.\n", name);
}

int main() {
    struct Node* root = createNode("root");
    struct Node* current = root;

    char command[100];
    char name[100];
    char type[100];

    while (1) {
        printf("\nCurrent Path: ");
        displayPath(current);
        printf("\n");
        printf("Available Commands:\n");
        printf("1. ls - List contents of the current folder.\n");
        printf("2. cd <folder_name> - Navigate to a specific folder.\n");
        printf("3. touch <file_name> - Create a file.\n");
        printf("4. mkdir <folder_name> - Create a folder.\n");
        printf("5. rm <file/folder_name> - Delete a file or folder.\n");
        printf("6. exit - Terminate the program.\n");
        printf("Enter command: ");
        scanf("%s", command);

        if (strcmp(command, "ls") == 0) {
            displayContents(current);
        } else if (strcmp(command, "cd") == 0) {
            scanf("%s", name);
            struct Node* temp = navigate(current, name);
            if (temp == NULL) {
                printf("%s not found.\n", name);
            } else {
                current = temp;
            }
        } else if (strcmp(command, "touch") == 0) {
            scanf("%s", name);
            create(current, name, "file");
        } else if (strcmp(command, "mkdir") == 0) {
            scanf("%s", name);
            create(current, name, "folder");
        } else if (strcmp(command, "rm") == 0) {
            scanf("%s", name);
            delete(current, name);
        } else if (strcmp(command, "exit") == 0) {
            break;
        } else {
            printf("Invalid command.\n");
        }
    }

    return 0;
}