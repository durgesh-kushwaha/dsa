#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

static Node *tail = NULL;

Node* new_node(int val) {
    Node *n = (Node*)malloc(sizeof(Node));
    if (!n) { fprintf(stderr, "Allocation failed\n"); exit(EXIT_FAILURE); }
    n->data = val;
    n->next = NULL;
    return n;
}

int is_empty(void) { return tail == NULL; }

void insert_begin(int val) {
    Node *n = new_node(val);
    if (is_empty()) {
        n->next = n;
        tail = n;
    } else {
        n->next = tail->next;
        tail->next = n;
    }
    printf("Inserted %d at beginning\n", val);
}

void insert_end(int val) {
    Node *n = new_node(val);
    if (is_empty()) {
        n->next = n;
        tail = n;
    } else {
        n->next = tail->next;
        tail->next = n;
        tail = n;
    }
    printf("Inserted %d at end\n", val);
}

int insert_after_key(int key, int val) {
    if (is_empty()) return 0;
    Node *curr = tail->next;
    do {
        if (curr->data == key) {
            Node *n = new_node(val);
            n->next = curr->next;
            curr->next = n;
            if (curr == tail) tail = n;
            printf("Inserted %d after %d\n", val, key);
            return 1;
        }
        curr = curr->next;
    } while (curr != tail->next);
    return 0;
}

int delete_begin(void) {
    if (is_empty()) return 0;
    Node *head = tail->next;
    int val = head->data;
    if (head == tail) {
        free(head);
        tail = NULL;
    } else {
        tail->next = head->next;
        free(head);
    }
    printf("Deleted from beginning: %d\n", val);
    return 1;
}

int delete_end(void) {
    if (is_empty()) return 0;
    Node *head = tail->next;
    int val = tail->data;
    if (head == tail) {
        free(tail);
        tail = NULL;
    } else {
        Node *prev = head;
        while (prev->next != tail) prev = prev->next;
        prev->next = head;
        free(tail);
        tail = prev;
    }
    printf("Deleted from end: %d\n", val);
    return 1;
}

int delete_key(int key) {
    if (is_empty()) return 0;
    Node *head = tail->next;
    Node *prev = tail;
    Node *curr = head;
    do {
        if (curr->data == key) {
            if (curr == prev && curr == tail) {
                free(curr);
                tail = NULL;
            } else {
                prev->next = curr->next;
                if (curr == tail) tail = prev;
                if (curr == head) {
                }
                free(curr);
            }
            printf("Deleted key: %d\n", key);
            return 1;
        }
        prev = curr;
        curr = curr->next;
    } while (curr != head);
    return 0;
}

void display(void) {
    if (is_empty()) { printf("[List is empty]\n"); return; }
    Node *head = tail->next;
    Node *curr = head;
    printf("List: ");
    do {
        printf("%d ", curr->data);
        curr = curr->next;
    } while (curr != head);
    printf("\n");
}

void destroy_all(void) {
    if (is_empty()) return;
    Node *head = tail->next;
    Node *curr = head;
    do {
        Node *next = curr->next;
        free(curr);
        curr = next;
    } while (curr != head);
    tail = NULL;
}

int main(void) {
    int choice, x, key;
    for (;;) {
        printf("\n--- Singly Circular Linked List ---\n");
        printf("1. Insert at beginning\n");
        printf("2. Insert at end\n");
        printf("3. Insert after key\n");
        printf("4. Delete from beginning\n");
        printf("5. Delete from end\n");
        printf("6. Delete given key\n");
        printf("7. Display\n");
        printf("8. Exit\n");
        printf("Enter choice: ");
        if (scanf("%d", &choice) != 1) break;

        switch (choice) {
            case 1: printf("Enter value: "); scanf("%d", &x); insert_begin(x); break;
            case 2: printf("Enter value: "); scanf("%d", &x); insert_end(x); break;
            case 3: printf("Enter key and value: "); scanf("%d%d", &key, &x);
                    if (!insert_after_key(key, x)) printf("Key %d not found\n", key);
                    break;
            case 4: if (!delete_begin()) printf("List empty\n"); break;
            case 5: if (!delete_end()) printf("List empty\n"); break;
            case 6: printf("Enter key to delete: "); scanf("%d", &key);
                    if (!delete_key(key)) printf("Key %d not found\n", key);
                    break;
            case 7: display(); break;
            case 8: destroy_all(); return 0;
            default: printf("Invalid choice\n");
        }
    }
    destroy_all();
    return 0;
}
