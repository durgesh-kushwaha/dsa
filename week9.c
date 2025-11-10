#include <stdio.h>
#include <stdlib.h>

#define MAX 10

static char q[MAX];
static int front = -1;
static int rear  = -1;

int isEmpty(void) {
    return front == -1;
}

int isFull(void) {
    return ((rear + 1) % MAX) == front;
}

void enqueue(char x) {
    if (isFull()) {
        printf("Overflow: Queue is full. Cannot insert '%c'.\n", x);
        return;
    }
    if (isEmpty()) {
        front = rear = 0;
    } else {
        rear = (rear + 1) % MAX;
    }
    q[rear] = x;
    printf("Inserted: %c\n", x);
}

int dequeue(char *out) {
    if (isEmpty()) {
        printf("Underflow: Queue is empty. Cannot delete.\n");
        return 0;
    }
    *out = q[front];
    if (front == rear) {
        front = rear = -1;
    } else {
        front = (front + 1) % MAX;
    }
    return 1;
}

void display(void) {
    if (isEmpty()) {
        printf("[Queue is empty]\n");
        return;
    }
    printf("Queue status (front -> rear): ");
    int i = front;
    while (1) {
        printf("%c ", q[i]);
        if (i == rear) break;
        i = (i + 1) % MAX;
    }
    printf("\n");
    printf("front=%d, rear=%d, MAX=%d\n", front, rear, MAX);
}

int main(void) {
    int choice;
    for (;;) {
        printf("\n--- Circular Queue of Characters (Array, MAX=%d) ---\n", MAX);
        printf("1. Insert (Enqueue)\n");
        printf("2. Delete (Dequeue)\n");
        printf("3. Display status\n");
        printf("4. Demonstrate Overflow\n");
        printf("5. Demonstrate Underflow\n");
        printf("6. Exit\n");
        printf("Enter choice: ");
        if (scanf("%d", &choice) != 1) return 0;

        if (choice == 1) {
            char c;
            printf("Enter a character to insert: ");
            scanf(" %c", &c);
            enqueue(c);
        } else if (choice == 2) {
            char out;
            if (dequeue(&out)) {
                printf("Deleted: %c\n", out);
            }
        } else if (choice == 3) {
            display();
        } else if (choice == 4) {
            printf("Filling queue to trigger Overflow...\n");
            while (!isFull()) enqueue('#');  /* demo filler */
            enqueue('X'); /* forces overflow message */
        } else if (choice == 5) {
            printf("Emptying queue to trigger Underflow...\n");
            char out;
            while (dequeue(&out)) { /* do nothing */ }
            dequeue(&out); /* forces underflow message */
        } else if (choice == 6) {
            printf("Exiting...\n");
            break;
        } else {
            printf("Invalid choice.\n");
        }
    }
    return 0;
}
