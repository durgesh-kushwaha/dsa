#include <stdio.h>

int sum_of_n_numbers(int n) {
    if (n == 0) {
        return 0;
    }
    return n + sum_of_n_numbers(n - 1);
}

int fibonacci(int n) {
    if (n <= 1) {
        return n;
    }
    return fibonacci(n - 1) + fibonacci(n - 2);
}

void tower_of_hanoi(int n, char from_rod, char to_rod, char aux_rod) {
    if (n == 1) {
        printf("Move disk 1 from rod %c to rod %c\n", from_rod, to_rod);
        return;
    }
    tower_of_hanoi(n - 1, from_rod, aux_rod, to_rod);
    printf("Move disk %d from rod %c to rod %c\n", n, from_rod, to_rod);
    tower_of_hanoi(n - 1, aux_rod, to_rod, from_rod);
}

int main() {
    int n = 10;
    
    printf("Sum of first %d numbers is: %d\n", n, sum_of_n_numbers(n));

    printf("--------------------\n");
    printf("Fibonacci sequence up to %d:\n", n);
    for (int i = 0; i < n; i++) {
        printf("%d ", fibonacci(i));
    }
    printf("\n");

    printf("--------------------\n");
    printf("Towers of Hanoi for %d disks:\n", 3);
    tower_of_hanoi(3, 'A', 'C', 'B');

    return 0;
}