#include <stdio.h>
#include <string.h>

#define MAX 50

char names[MAX][30];
int adj[MAX][MAX];
int n = 0;

int getIndex(const char *name) {
    for (int i = 0; i < n; i++)
        if (strcmp(names[i], name) == 0) return i;
    return -1;
}

/* BFS: returns 1 if target found */
int bfs(int start, int target) {
    int visited[MAX] = {0}, queue[MAX], front = 0, rear = 0;
    int found = 0;
    visited[start] = 1;
    queue[rear++] = start;
    printf("BFS traversal: ");
    while (front < rear) {
        int u = queue[front++];
        printf("%s ", names[u]);
        if (u == target) { found = 1; break; }
        for (int v = 0; v < n; v++)
            if (adj[u][v] && !visited[v]) {
                visited[v] = 1;
                queue[rear++] = v;
            }
    }
    printf("\n");
    return found;
}

/* DFS (recursive): returns 1 if target found */
int dfs(int u, int target, int visited[]) {
    visited[u] = 1;
    printf("%s ", names[u]);
    if (u == target) return 1;
    for (int v = 0; v < n; v++)
        if (adj[u][v] && !visited[v])
            if (dfs(v, target, visited)) return 1;
    return 0;
}

void printMatrix() {
    printf("\nAdjacency Matrix:\n%-12s", "");
    for (int i = 0; i < n; i++) printf("%-4d", i);
    printf("\n");
    for (int i = 0; i < n; i++) {
        printf("%-3d%-9s", i, names[i]);
        for (int j = 0; j < n; j++) printf("%-4d", adj[i][j]);
        printf("\n");
    }
}

int main() {
    int e;
    char a[30], b[30];

    printf("Enter number of files/directories: ");
    scanf("%d", &n);
    printf("Enter names (no spaces):\n");
    for (int i = 0; i < n; i++) scanf("%29s", names[i]);

    printf("Enter number of connections: ");
    scanf("%d", &e);
    printf("Enter each connection as: parent child\n");
    for (int i = 0; i < e; i++) {
        scanf("%29s %29s", a, b);
        int u = getIndex(a), v = getIndex(b);
        if (u == -1 || v == -1) { printf("Invalid name, skipped.\n"); continue; }
        adj[u][v] = 1;
    }

    printMatrix();

    printf("\nEnter starting node: ");
    scanf("%29s", a);
    printf("Enter file to search: ");
    scanf("%29s", b);
    int s = getIndex(a), t = getIndex(b);
    if (s == -1) { printf("Start node not found in file system.\n"); return 1; }
    if (t == -1) { printf("'%s' does not exist in the graph.\n", b); }

    printf("\n--- BFS ---\n");
    int r1 = bfs(s, t);
    printf("Result: %s %s\n", b, r1 ? "FOUND using BFS" : "NOT FOUND using BFS");

    printf("\n--- DFS ---\n");
    int visited[MAX] = {0};
    printf("DFS traversal: ");
    int r2 = dfs(s, t, visited);
    printf("\nResult: %s %s\n", b, r2 ? "FOUND using DFS" : "NOT FOUND using DFS");
    return 0;
}
