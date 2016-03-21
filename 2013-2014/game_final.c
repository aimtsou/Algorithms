#include <stdio.h>
#include <stdlib.h>

#define MIN(a,b) ((a) < (b) ? a : b)

int main(int argc, char **argv) {
    unsigned int i, j, n, k, t;
    int maxp, maxi, new_min;

    scanf("%d", &n);

    int *p = NULL, *sum = NULL;
    int **pos = NULL, **tmp = NULL;

    p = (int *) calloc (n,sizeof(int));
    sum = (int *) calloc (n,sizeof(int));
    pos = (int **) calloc (n,sizeof(int *));
    tmp = (int **) calloc (n,sizeof(int *));

    for (i = 0; i < n; i++) {
        scanf("%d", &p[i]);
        sum[i] = 0;
    }

    sum[0] = 0;
    for (i = 1; i <= n; i++) {
        sum[i] = sum[i-1] + p[i-1];
    }

    for (i = 0; i < n; i++) {
        pos[i] = (int*) calloc (n,sizeof(int));
        tmp[i] = (int*) calloc (n,sizeof(int));
    }

    for (j = 1; j < n; j++) {
        k = j;
        for (i = 0; i < n-1; i++) {
            if (k == n)
                break;
            if (k == i) { 
                pos[i][k] = i;
                tmp[i][k] = 0;
            }
            else if (k == i+1) {
                pos[i][k] = i;
                tmp[i][k] = MIN(p[i], p[k]);
            }
            else {
                maxp = -1;
                maxi = pos[i][k-1];
                for (t = maxi; t <= pos[i+1][k]; t++) {
                    new_min = MIN(tmp[i][t] + (sum[t+1] - sum[i]), tmp[t+1][k] + (sum[k+1] - sum[t+1]));
                    if (maxp < new_min) {
                        maxp = new_min;
                        maxi = t;
                    }
                }
                tmp[i][k] = maxp;
                pos[i][k] = maxi;
            }
            k++;
        }
    }
    printf("%d\n", tmp[0][n-1]);    

    return 0;
}
