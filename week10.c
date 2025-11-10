#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 30
#define NAMELEN 40

static int N = 0;
static char city[MAXN][NAMELEN];
static int adj[MAXN][MAXN];
static int name_count = 0;

int find_index_by_name(const char *name) {
    for (int i = 0; i < N; ++i) {
        if (strcmp(city[i], name) == 0) return i;
    }
    return -1;
}

void create_graph(void) {
    printf("Enter number of cities N (<= %d): ", MAXN);
    if (scanf("%d", &N) != 1 || N <= 0 || N > MAXN) {
        printf("Invalid N\n"); exit(0);
    }
    /* read city names */
    for (int i = 0; i < N; ++i) {
        printf("Enter name of city %d: ", i);
        scanf("%s", city[i]); /* simple token input */
    }
    /* zero out adjacency */
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            adj[i][j] = 0;

    int E;
    printf("Enter number of directed edges E: ");
    scanf("%d", &E);
    for (int k = 0; k < E; ++k) {
        char uname[NAMELEN], vname[NAMELEN];
        printf("Edge %d (u v) as names: ", k + 1);
        scanf("%s %s", uname, vname);
        int u = find_index_by_name(uname);
        int v = find_index_by_name(vname);
        if (u == -1 || v == -1) {
            printf("Invalid city name(s). Try again.\n");
            --k; continue;
        }
        adj[u][v] = 1; /* directed edge u -> v */
    }
    printf("Graph created with %d cities and %d edges.\n", N, E);
}

void display_adj_matrix(void) {
    if (N == 0) { printf("Create graph first.\n"); return; }
    printf("\nAdjacency Matrix (rows: from, cols: to)\n     ");
    for (int j = 0; j < N; ++j) printf("%-4d", j);
    printf("\n");
    for (int i = 0; i < N; ++i) {
        printf("%-3d ", i);
        for (int j = 0; j < N; ++j) printf("%-4d", adj[i][j]);
        printf("\n");
    }
    printf("\nIndex → City:\n");
    for (int i = 0; i < N; ++i) printf("%d: %s\n", i, city[i]);
}

static int visited[MAXN];

void dfs_util(int u) {
    visited[u] = 1;
    printf("%s ", city[u]);
    for (int v = 0; v < N; ++v) {
        if (adj[u][v] && !visited[v]) dfs_util(v);
    }
}

void run_dfs(void) {
    if (N == 0) { printf("Create graph first.\n"); return; }
    char start[NAMELEN];
    printf("Enter start city for DFS: ");
    scanf("%s", start);
    int s = find_index_by_name(start);
    if (s == -1) { printf("Unknown city.\n"); return; }
    for (int i = 0; i < N; ++i) visited[i] = 0;
    printf("Reachable (DFS order): ");
    dfs_util(s);
    printf("\n");
}

void run_bfs(void) {
    if (N == 0) { printf("Create graph first.\n"); return; }
    char start[NAMELEN];
    printf("Enter start city for BFS: ");
    scanf("%s", start);
    int s = find_index_by_name(start);
    if (s == -1) { printf("Unknown city.\n"); return; }

    for (int i = 0; i < N; ++i) visited[i] = 0;
    int q[MAXN], front = 0, rear = 0; /* simple circular queue */
    q[rear] = s; rear = (rear + 1) % MAXN;
    visited[s] = 1;

    printf("Reachable (BFS level order): ");
    while (front != rear) {
        int u = q[front]; front = (front + 1) % MAXN;
        printf("%s ", city[u]);
        for (int v = 0; v < N; ++v) {
            if (adj[u][v] && !visited[v]) {
                visited[v] = 1;
                q[rear] = v; rear = (rear + 1) % MAXN;
            }
        }
    }
    printf("\n");
}

int main(void) {
    for (;;) {
        int ch;
        printf("\n--- Graph of Cities (Adjacency Matrix, Directed) ---\n");
        printf("1. Create graph\n");
        printf("2. Display adjacency matrix\n");
        printf("3. DFS (reachable cities)\n");
        printf("4. BFS (reachable cities)\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        if (scanf("%d", &ch) != 1) break;

        switch (ch) {
            case 1: create_graph(); break;
            case 2: display_adj_matrix(); break;
            case 3: run_dfs(); break;
            case 4: run_bfs(); break;
            case 5: return 0;
            default: printf("Invalid choice.\n");
        }
    }
    return 0;
}
