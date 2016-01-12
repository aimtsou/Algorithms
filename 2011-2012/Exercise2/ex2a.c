#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct column {
	int a;
	int b;
} column_t;


int compare(const void *v1, const void *v2) {
	const struct column *kp1 = *(const struct column **)v1;
	const struct column *kp2 = *(const struct column **)v2;
	//fprintf (stderr, "\nVector 1, column A: %d\n", kp1->a);
	int tmp = kp1->b - kp2->b;
	if (kp1->b == kp2->b) {
		tmp = kp1->a - kp2->a;
	}
	return tmp;

}


int lis(column_t *x, int n) {
	int i, length, left, right, mid;

	int *last = (int*) calloc (n,sizeof(int));

	last[0] = x[0].a;
	length  = 0;
	for (i = 1; i < n; i++) {
		if (x[i].a >= last[length]) last[++length] = x[i].a;
		else if (x[i].a < last[0]) last[0] = x[i].a;
		else {
			for (left = 0, right = length; left != right-1; ) {
				mid = (left + right) / 2;
				(last[mid] <= x[i].a) ? (left = mid) : (right = mid);
			}
			last[right] = x[i].a;
		}
	}
	free(last);
	return length + 1;
}

int main(int argc, char **argv) {
	int n_digits, idx;
	column_t *digits;

	fscanf(stdin, "%d", &n_digits);

	digits = calloc (n_digits, sizeof(column_t));

	for (idx = 0; idx < n_digits; idx++) {
		scanf ("%d", &digits[idx].a);
		scanf ("%d", &digits[idx].b);
   	}


	qsort(digits, n_digits, sizeof(digits[0]), compare);

	printf("%d\n", lis(digits, n_digits));


	free(digits);

	return 0;
}
