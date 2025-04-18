#include <stdio.h>

int costMatrix[20][20], n;

struct router
 {
    int distance[20];
    int adjNodes[20];
} node[20];

void readCostMatrix()
 {
    int i, j;
    printf("Enter cost matrix (enter -1 for unreachable nodes):\n");
    for (i = 0; i < n; ++i) {
        for (j = 0; j < n; ++j) {
            if (i == j)
                costMatrix[i][j] = 0;
            else {
                printf("Enter cost from Node %d to Node %d: ", i + 1, j + 1);
                scanf("%d", &costMatrix[i][j]);
                if (costMatrix[i][j] == -1) {
                    costMatrix[i][j] = 9999;
                }
            }
            node[i].distance[j] = costMatrix[i][j];
            node[i].adjNodes[j] = (costMatrix[i][j] == 9999) ? -1 : j;
        }
    }
}

void calcRoutingTable() {
    int i, j, k;
    for (i = 0; i < n; ++i) {
        for (j = 0; j < n; ++j) {
            for (k = 0; k < n; ++k) {
                if (node[i].distance[j] > node[i].distance[k] + node[k].distance[j]) {
                    node[i].distance[j] = node[i].distance[k] + node[k].distance[j];
                    node[i].adjNodes[j] = k;
                }
            }
        }
    }
}

void displayRoutes() {
    int i, j;
    printf("\nFinal Routing Table:\n");
    printf("From Node -> To Node : Minimum Distance and Route\n");
    for (i = 0; i < n; ++i) {
        printf("\nRouter %d:\n", i + 1);
        for (j = 0; j < n; ++j) {
            if (node[i].distance[j] == 9999)
                printf("Node %d is unreachable\n", j + 1);
            else
                printf("Node %d: Distance %d, Route via Node %d\n", j + 1, node[i].distance[j], node[i].adjNodes[j] + 1);
        }
        printf("\n");
    }
}

int main() {
    printf("Enter the number of nodes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            node[i].distance[j] = 0;
            node[i].adjNodes[j] = -1;
        }
    }

    readCostMatrix();
    calcRoutingTable();
    displayRoutes();

    return 0;
}