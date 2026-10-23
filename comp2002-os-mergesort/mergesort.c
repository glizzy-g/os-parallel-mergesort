/**
 * This file implements parallel mergesort.
 */

#include <stdio.h>
#include <string.h> /* for memcpy */
#include <stdlib.h> /* for malloc */
#include "mergesort.h"

/* this function will be called by mergesort() and also by parallel_mergesort(). */
void merge(int leftstart, int leftend, int rightstart, int rightend){
	int i = leftstart;
	int j = rightstart;
	int k;

	for(k=leftstart; k<=rightend; k++){
		if((i<=leftend) & (j>rightend || A[i] <= A[j])) {
			B[k] = A[i];
			i++;
		} else {
			B[k] = A[j];
			j++;
		}
	}

	memcpy(A+leftstart, B+leftstart, (rightend-leftstart+1)*sizeof(int) );
}

/* this function will be called by parallel_mergesort() as its base case. */
void my_mergesort(int left, int right){
	if(left >= right){
		return;
	}

	int mid = (left+right)/2;
	
	my_mergesort(left, mid);
	my_mergesort(mid+1, right);

	merge(left, mid, mid+1, right);
}

/* this function will be called by the testing program. */
void * parallel_mergesort(void *arg){
	struct argument* a = (struct argument*)arg;

	if(a->level >= cutoff){
		my_mergesort(a->left, a->right);
		return NULL;
	}

	int mid = (a->left+a->right)/2;

	struct argument* b = buildArgs(a->left, mid, a->level+1);
	struct argument* c = buildArgs(mid+1, a->right, a->level+1);

	pthread_t t1, t2;
	pthread_create(&t1, NULL, parallel_mergesort, b);
	pthread_create(&t2, NULL, parallel_mergesort, c);

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);

	free(b);
	free(c);

	merge(a->left, mid, mid+1, a->right);

	return NULL;
}

/* we build the argument for the parallel_mergesort function. */
struct argument * buildArgs(int left, int right, int level){
	struct argument* a = malloc(sizeof(struct argument));
	a->left = left;
	a->right = right;
	a->level = level;
	return a;
}

