#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ====================== LINKED LIST (Tabs) ======================
typedef struct Tab {
    char title[50];
    struct Tab *next;
} Tab;

Tab *head = NULL;

void openTab(char *title) {
    Tab *newTab = (Tab *)malloc(sizeof(Tab));
    strcpy(newTab->title, title);
    newTab->next = NULL;

    if (head == NULL) head = newTab;
    else {
        Tab *temp = head;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = newTab;
    }
    printf("Opened new tab: %s\n", title);
}

void closeTab(char *title) {
    if (head == NULL) {
        printf("No tabs open.\n");
        return;
    }

    Tab *temp = head, *prev = NULL;
    while (temp != NULL && strcmp(temp->title, title) != 0) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Tab not found.\n");
        return;
    }

    if (prev == NULL) head = temp->next;
    else prev->next = temp->next;

    free(temp);
    printf("Closed tab: %s\n", title);
}

void showTabs() {
    Tab *temp = head;
    printf("\nOpen Tabs:\n");
    if (temp == NULL) {
        printf("No tabs open.\n");
        return;
    }
    while (temp != NULL) {
        printf("- %s\n", temp->title);
        temp = temp->next;
    }
}

// ====================== STACK (Back/Forward Navigation) ======================
typedef struct Stack {
    char page[50];
    struct Stack *next;
} Stack;

Stack *back = NULL, *forward = NULL;

void push(Stack **top, char *page) {
    Stack *newNode = (Stack *)malloc(sizeof(Stack));
    strcpy(newNode->page, page);
    newNode->next = *top;
    *top = newNode;
}

char *pop(Stack **top) {
    if (*top == NULL) return NULL;
    Stack *temp = *top;
    *top = (*top)->next;
    char *page = temp->page;
    return page;
}

void visitPage(char *page) {
    push(&back, page);
    while (forward != NULL) forward = forward->next; // clear forward stack
    printf("Visited page: %s\n", page);
}

void goBack() {
    if (back == NULL || back->next == NULL) {
        printf("No previous page.\n");
        return;
    }
    char *curr = pop(&back);
    push(&forward, curr);
    printf("Went back to: %s\n", back->page);
}

void goForward() {
    if (forward == NULL) {
        printf("No forward page.\n");
        return;
    }
    char *nextPage = pop(&forward);
    push(&back, nextPage);
    printf("Went forward to: %s\n", nextPage);
}

// ====================== QUEUE (Downloads) ======================
typedef struct Download {
    char file[50];
    struct Download *next;
} Download;

Download *front = NULL, *rear = NULL;

void enqueue(char *file) {
    Download *newFile = (Download *)malloc(sizeof(Download));
    strcpy(newFile->file, file);
    newFile->next = NULL;

    if (rear == NULL) {
        front = rear = newFile;
    } else {
        rear->next = newFile;
        rear = newFile;
    }
    printf("Added to download queue: %s\n", file);
}

void dequeue() {
    if (front == NULL) {
        printf("No downloads in queue.\n");
        return;
    }
    Download *temp = front;
    printf("Downloading: %s\n", temp->file);
    front = front->next;
    if (front == NULL) rear = NULL;
    free(temp);
}

void showDownloads() {
    Download *temp = front;
    printf("\nDownload Queue:\n");
    if (temp == NULL) {
        printf("No downloads.\n");
        return;
    }
    while (temp != NULL) {
        printf("- %s\n", temp->file);
        temp = temp->next;
    }
}

// ====================== BST (Bookmarks) ======================
typedef struct Bookmark {
    char name[50];
    struct Bookmark *left, *right;
} Bookmark;

Bookmark *root = NULL;

Bookmark *createBookmark(char *name) {
    Bookmark *newNode = (Bookmark *)malloc(sizeof(Bookmark));
    strcpy(newNode->name, name);
    newNode->left = newNode->right = NULL;
    return newNode;
}

Bookmark *insertBookmark(Bookmark *node, char *name) {
    if (node == NULL) return createBookmark(name);
    if (strcmp(name, node->name) < 0)
        node->left = insertBookmark(node->left, name);
    else if (strcmp(name, node->name) > 0)
        node->right = insertBookmark(node->right, name);
    return node;
}

void inorder(Bookmark *root) {
    if (root != NULL) {
        inorder(root->left);
        printf("- %s\n", root->name);
        inorder(root->right);
    }
}

Bookmark *searchBookmark(Bookmark *root, char *name) {
    if (root == NULL || strcmp(root->name, name) == 0)
        return root;
    if (strcmp(name, root->name) < 0)
        return searchBookmark(root->left, name);
    else
        return searchBookmark(root->right, name);
}

// ====================== MAIN MENU ======================
int main() {
    int choice;
    char name[50];

    while (1) {
        printf("\n========== Browser Tabs and History Manager ==========\n");
        printf("1. Open New Tab\n");
        printf("2. Close Tab\n");
        printf("3. Show All Tabs\n");
        printf("4. Visit Page\n");
        printf("5. Back\n");
        printf("6. Forward\n");
        printf("7. Add Download\n");
        printf("8. Process Download\n");
        printf("9. Show Download Queue\n");
        printf("10. Add Bookmark\n");
        printf("11. Show Bookmarks\n");
        printf("12. Search Bookmark\n");
        printf("0. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                printf("Enter tab title: ");
                gets(name);
                openTab(name);
                break;
            case 2:
                printf("Enter tab title to close: ");
                gets(name);
                closeTab(name);
                break;
            case 3:
                showTabs();
                break;
            case 4:
                printf("Enter page to visit: ");
                gets(name);
                visitPage(name);
                break;
            case 5:
                goBack();
                break;
            case 6:
                goForward();
                break;
            case 7:
                printf("Enter file name to download: ");
                gets(name);
                enqueue(name);
                break;
            case 8:
                dequeue();
                break;
            case 9:
                showDownloads();
                break;
            case 10:
                printf("Enter bookmark name: ");
                gets(name);
                root = insertBookmark(root, name);
                printf("Bookmark added.\n");
                break;
            case 11:
                printf("\nBookmarks:\n");
                inorder(root);
                break;
            case 12:
                printf("Enter bookmark to search: ");
                gets(name);
                if (searchBookmark(root, name))
                    printf("Bookmark found: %s\n", name);
                else
                    printf("Bookmark not found.\n");
                break;
            case 0:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice.\n");
        }
    }
    return 0;
}
