#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
typedef struct edge_t {
    int src;
    int dest;
    int weight;
} edge;

typedef struct subset_t {
    int parent;
    int rank;
} subset;
 
int find(subset *subsets, int i)
{
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);
 
    return subsets[i].parent;
}
 
void Union(subset *subsets, int x, int y)
{
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);
 
    if (subsets[xroot].rank < subsets[yroot].rank)
        subsets[xroot].parent = yroot;
    else if (subsets[xroot].rank > subsets[yroot].rank)
        subsets[yroot].parent = xroot;
    else {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
} 
 

int compare(const void *v1, const void *v2)
{
    const edge *p1 = (edge *)v1;
    const edge *p2 = (edge *)v2;
    if (p1->weight > p2->weight) return 1;
    if (p1->weight < p2->weight) return -1;
        return 0;
}
 
int main(int argc, char **argv) {
    int i, j, e, N, M, K;
    edge *edges, *result;
    subset *subsets;

    scanf("%d %d %d", &N, &M, &K);

    edges = calloc (M, sizeof(edge));
    result = calloc (100*M, sizeof(edge));
    subsets = calloc (M, sizeof(subset));

    for (i = 0; i < M; i++) 
        scanf("%d %d %d", &edges[i].src, &edges[i].dest, &edges[i].weight);

    qsort(edges, M, sizeof(edges[0]), compare);

    for (i = 0; i < M; i++) {
        subsets[i].parent = i;
        subsets[i].rank = 0;
    }

    j = 0;
    e = 0;
    for (i = 0; i < N-1; i++) {
        j++;
        int x = find(subsets, edges[j].src);
        int y = find(subsets, edges[j].dest);

        if (x != y) {
            result[e++] = edges[j];
            Union(subsets, x, y);
        }
    }
    printf("Following are the edges in the constructed MST\n");
    for (i = 0; i < e; ++i)
        printf("%d -- %d == %d\n", result[i].src, result[i].dest,
                                                   result[i].weight);

    /*if (K>e)  
        printf("infinity");
    else 
        printf("%d", result[e-K+1].weight);*/
    return 0;
}