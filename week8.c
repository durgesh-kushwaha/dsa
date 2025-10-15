#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX 100

char stack[MAX];
int top = -1;

void push(char c) {
    if (top == MAX - 1)
        printf("Stack Overflow\n");
    else
        stack[++top] = c;
}

char pop() {
    if (top == -1)
        return '\0';
    else
        return stack[top--];
}

char peek() {
    if (top == -1)
        return '\0';
    else
        return stack[top];
}

int precedence(char op) {
    if (op == '^') return 3;
    if (op == '*' || op == '/' || op == '%') return 2;
    if (op == '+' || op == '-') return 1;
    return 0;
}

int isRightAssociative(char op) {
    if (op == '^') return 1;
    return 0;
}

void infixToPostfix(char infix[], char postfix[]) {
    int i, k = 0;
    char ch;
    for (i = 0; i < strlen(infix); i++) {
        ch = infix[i];
        if (isalnum(ch))
            postfix[k++] = ch;
        else if (ch == '(')
            push(ch);
        else if (ch == ')') {
            while (top != -1 && peek() != '(')
                postfix[k++] = pop();
            pop();
        } else {
            while (top != -1 && precedence(peek()) > precedence(ch) ||
                  (precedence(peek()) == precedence(ch) && !isRightAssociative(ch)) && peek() != '(')
                postfix[k++] = pop();
            push(ch);
        }
    }
    while (top != -1)
        postfix[k++] = pop();
    postfix[k] = '\0';
}

int main() {
    char infix[MAX], postfix[MAX];
    printf("Enter an Infix Expression: ");
    gets(infix);
    infixToPostfix(infix, postfix);
    printf("Postfix Expression: %s\n", postfix);
    return 0;
}
