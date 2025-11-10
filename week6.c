#include <stdio.h>
#include <stdlib.h>

size_t my_strlen(const char *s) {
    size_t n = 0;
    while (s && s[n] != '\0') n++;
    return n;
}

void trim_newline_inplace(char *s) {
    if (!s) return;
    size_t n = my_strlen(s);
    if (n > 0 && s[n - 1] == '\n') s[n - 1] = '\0';
}

int starts_with_at(const char *text, const char *pat, size_t i) {
    size_t j = 0;
    while (pat[j] != '\0') {
        if (text[i + j] == '\0' || text[i + j] != pat[j]) return 0;
        j++;
    }
    return 1;
}

size_t count_occurrences(const char *str, const char *pat) {
    size_t n = my_strlen(str), m = my_strlen(pat), i = 0, cnt = 0;
    if (m == 0) return 0;
    while (i + m <= n) {
        if (starts_with_at(str, pat, i)) {
            cnt++; i += m;
        } else {
            i++;
        }
    }
    return cnt;
}

char* replace_all(const char *str, const char *pat, const char *rep) {
    size_t n = my_strlen(str), m = my_strlen(pat), r = my_strlen(rep);
    if (m == 0) return NULL;

    size_t cnt = count_occurrences(str, pat);
    if (cnt == 0) {
        char *copy = (char*)malloc(n + 1);
        if (!copy) return NULL;
        for (size_t i = 0; i <= n; ++i) copy[i] = str[i];
        return copy;
    }

    size_t out_len = n + cnt * (r - m);
    char *out = (char*)malloc(out_len + 1);
    if (!out) return NULL;

    size_t i = 0, k = 0;
    while (i < n) {
        if (i + m <= n && starts_with_at(str, pat, i)) {
            for (size_t j = 0; j < r; ++j) out[k++] = rep[j];
            i += m;
        } else {
            out[k++] = str[i++];
        }
    }
    out[k] = '\0';
    return out;
}

int main(void) {
    char STR[1024], PAT[256], REP[256];

    printf("Enter main string (STR): ");
    if (!fgets(STR, sizeof(STR), stdin)) return 0;
    trim_newline_inplace(STR);

    printf("Enter pattern string (PAT): ");
    if (!fgets(PAT, sizeof(PAT), stdin)) return 0;
    trim_newline_inplace(PAT);

    printf("Enter replace string (REP): ");
    if (!fgets(REP, sizeof(REP), stdin)) return 0;
    trim_newline_inplace(REP);

    if (my_strlen(PAT) == 0) {
        printf("Pattern cannot be empty.\n");
        return 0;
    }

    size_t before_len = my_strlen(STR);
    char *result = replace_all(STR, PAT, REP);
    if (!result) {
        printf("Memory allocation failed or invalid input.\n");
        return 0;
    }

    if (count_occurrences(STR, PAT) == 0) {
        printf("PAT does not exist in STR. No replacement performed.\n");
    } else {
        printf("\n--- REPLACED STRING ---\n%s\n", result);
    }

    printf("\nLength before: %zu\n", before_len);
    printf("Length after : %zu\n", my_strlen(result));

    free(result);
    return 0;
}
