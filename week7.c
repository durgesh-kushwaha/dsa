#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100

int stack[MAX];
int top = -1;

void push(int value) {
    if (top == MAX - 1) {
        printf("Stack Overflow\n");
    } else {
        stack[++top] = value;
        printf("%d pushed onto stack\n", value);
    }
}

void pop() {
    if (top == -1) {
        printf("Stack Underflow\n");
    } else {
        printf("%d popped from stack\n", stack[top--]);
    }
}

void display() {
    if (top == -1) {
        printf("Stack is empty\n");
    } else {
        printf("Stack elements: ");
        for (int i = top; i >= 0; i--) {
            printf("%d ", stack[i]);
        }
        printf("\n");
    }
}

void checkPalindrome() {
    char str[100];
    int i, len, flag = 1;
    top = -1;
    printf("Enter a string: ");
    scanf("%s", str);
    len = strlen(str);
    for (i = 0; i < len; i++) {
        push(str[i]);
    }
    for (i = 0; i < len; i++) {
        if (str[i] != stack[top--]) {
            flag = 0;
            break;
        }
    }
    if (flag)
        printf("Palindrome\n");
    else
        printf("Not Palindrome\n");
}

int main() {
    int choice, value;
    while (1) {
        printf("\n--- STACK MENU ---\n");
        printf("1. Push\n2. Pop\n3. Check Palindrome\n4. Display Stack\n5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("Enter value to push: ");
                scanf("%d", &value);
                push(value);
                break;
            case 2:
                pop();
                break;
            case 3:
                checkPalindrome();
                break;
            case 4:
                display();
                break;
            case 5:
                exit(0);
            default:
                printf("Invalid choice\n");
        }
    }
    return 0;
}
