#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>
#include <inttypes.h>

#include "papi.h"

#define fl 8
#define arraysize  (8*(1 << 20))

typedef struct ver0 {
	int fa[fl];
	char fb[fl];
	int fc[fl];
	char fd[fl];
	int fe[fl];
} ver0;

typedef struct ver1 {
	int fa[fl];
	char fb[fl];
	char fd[fl];
	int fc[fl];
	int fe[fl];
} ver1;

typedef struct ver2 {
	struct {
		int fc[fl];
		int fe[fl];
\
	}sub1[arraysize];

	struct {
		int fa[fl];
		char fb[fl];
		char fd[fl];
	}sub2[arraysize]; 

} ver2;


void flush(int * g, int size){
	int i;

	for(i = 0; i<size; i++){
		g[i]++;
	}
}

int main(){
	ver0 * a0;// orignal code
	ver1 * a1;
	ver2 * a2;

	int * garbage;

	int i, j, stride;
	int iter, numOfIter;
	struct timeval start, end;
	int r;

	int nEvents, ret;
	int events[2] = {PAPI_L1_DCM, PAPI_TOT_CYC};
	long_long values[2];

	if (PAPI_num_counters() < 2) {
		fprintf(stderr, "No hardware counters here, or PAPI not supported.\n");
		exit(1);
	}



	garbage = (int *) malloc(sizeof(int) * arraysize);
	for (i = 0; i < arraysize; i++) {
		garbage[i] = rand();
	}

	a0 = (ver0 *) malloc(sizeof(ver0) * arraysize);
	a1 = (ver1 *) malloc(sizeof(ver1) * arraysize);
	a2 = (ver2 *) malloc(sizeof(ver2));

	numOfIter = 10;

	/* ver. 1: ver. 0*/

	flush(garbage, arraysize);

	nEvents = sizeof(values)/sizeof(values[0]);

	if ((ret = PAPI_start_counters(events, nEvents)) != PAPI_OK) {
		fprintf(stderr, "PAPI failed to start counters: %s\n", PAPI_strerror(ret));
		exit(1);
	}

	for(iter = 0; iter < numOfIter; iter++){
		for (i = 0; i < arraysize; i++) {
			a0[i].fa[0] = a0[i].fb[0]+a0[i].fd[0];
		}
	}

	for(iter = 0; iter < numOfIter; iter++){
		for (i = 0; i < arraysize; i++) {
			a0[i].fc[0] = a0[i].fe[0]*2;
		}
	}


	if ((ret = PAPI_stop_counters(values, nEvents)) != PAPI_OK) {
		fprintf(stderr, "PAPI failed to read counters: %s\n", PAPI_strerror(ret));
		exit(1);
	}

	printf("ver. 0:\n");

	for(i = 0; i < nEvents; i++){
		printf("counter[%d]: %lld\n", i, values[i]);
	}

	/* ver. 1: */
	flush(garbage, arraysize);

	nEvents = sizeof(values)/sizeof(values[0]);

	if ((ret = PAPI_start_counters(events, nEvents)) != PAPI_OK) {
		fprintf(stderr, "PAPI failed to start counters: %s\n", PAPI_strerror(ret));
		exit(1);
	}

	for(iter = 0; iter < numOfIter; iter++){
		for (i = 0; i < arraysize; i++) {
			a1[i].fa[0] = a1[i].fb[0]+a1[i].fd[0];
		}
	}

	for(iter = 0; iter < numOfIter; iter++){
		for (i = 0; i < arraysize; i++) {
			a1[i].fc[0] = a1[i].fe[0]*2;
		}
	}


	if ((ret = PAPI_stop_counters(values, nEvents)) != PAPI_OK) {
		fprintf(stderr, "PAPI failed to read counters: %s\n", PAPI_strerror(ret));
		exit(1);
	}

	printf("ver. 1:\n");

	for(i = 0; i < nEvents; i++){
		printf("counter[%d]: %lld\n", i, values[i]);
	}

	/* ver. 2: */
	flush(garbage, arraysize);

	nEvents = sizeof(values)/sizeof(values[0]);

	if ((ret = PAPI_start_counters(events, nEvents)) != PAPI_OK) {
		fprintf(stderr, "PAPI failed to start counters: %s\n", PAPI_strerror(ret));
		exit(1);
	}

	for(iter = 0; iter < numOfIter; iter++){
		for (i = 0; i < arraysize; i++) {
			a2->sub1[i].fc[0] = a2->sub1[i].fe[0]*2;
		
		for(iter = 0; iter < numOfIter; iter++){
			for(i=0; i<arraysize; i++){
				a2->sub2[i].fa[0] = a2->sub2[i].fb[0]+ a2->sub2[i].fd[0];
			}
		}
		}
	}

	


	if ((ret = PAPI_stop_counters(values, nEvents)) != PAPI_OK) {
		fprintf(stderr, "PAPI failed to read counters: %s\n", PAPI_strerror(ret));
		exit(1);
	}

	printf("ver. 2:\n");

	for(i = 0; i < nEvents; i++){
		printf("counter[%d]: %lld\n", i, values[i]);
	}


	//printf("%d %d %d\n", garbage[rand()%arraysize], a0[rand()%arraysize].fa[0], a1[rand()%arraysize].fa[0] );

	free(a0);
	free(a1);
	free(a2);

	free(garbage);
}
