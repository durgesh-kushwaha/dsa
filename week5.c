#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WEEK_DAYS 7
#define MAX_INPUT 256

typedef struct {
    char *day;
    int   date;
    char *activity;
} DayEntry;

static char* dupstr(const char *s) {
    char *p = malloc(strlen(s) + 1);
    strcpy(p, s);
    return p;
}

static void trim_newline(char *s) {
    size_t n = strlen(s);
    if (n > 0 && s[n-1] == '\n')
        s[n-1] = '\0';
}

DayEntry* create() {
    DayEntry *calendar = (DayEntry*) malloc(WEEK_DAYS * sizeof(DayEntry));
    for (int i = 0; i < WEEK_DAYS; i++) {
        calendar[i].day = NULL;
        calendar[i].date = 0;
        calendar[i].activity = NULL;
    }
    return calendar;
}

void readEntries(DayEntry *calendar) {
    char input[MAX_INPUT];

    for (int i = 0; i < WEEK_DAYS; i++) {
        printf("Enter Day Name: ");
        fgets(input, sizeof(input), stdin);
        trim_newline(input);
        calendar[i].day = dupstr(input);

        printf("Enter Date (integer): ");
        scanf("%d", &calendar[i].date);
        getchar();

        printf("Enter Activity: ");
        fgets(input, sizeof(input), stdin);
        trim_newline(input);
        calendar[i].activity = dupstr(input);

        printf("----- Saved Entry %d/7 -----\n\n", i + 1);
    }
}

void display(DayEntry *calendar) {
    printf("\n========== WEEK ACTIVITY REPORT ==========\n");
    for (int i = 0; i < WEEK_DAYS; i++) {
        printf("Day %d\n", i + 1);
        printf("  Name     : %s\n", calendar[i].day);
        printf("  Date     : %d\n", calendar[i].date);
        printf("  Activity : %s\n", calendar[i].activity);
        printf("------------------------------------------\n");
    }
}

void destroy(DayEntry *calendar) {
    for (int i = 0; i < WEEK_DAYS; i++) {
        free(calendar[i].day);
        free(calendar[i].activity);
    }
    free(calendar);
}

int main() {
    DayEntry *week = create();
    readEntries(week);
    display(week);
    destroy(week);
    return 0;
}
