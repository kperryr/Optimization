#include <stdio.h>
#include <stdlib.h>

#include <papi.h>

/* Please add your event here */
//int events[1] = {PAPI_TOT_CYC}; /*PAPI_L1_DCM, PAPI_L2_DCM, PAPI_TLB_DM*/
//int eventnum = 1;
//long long values[1];
//int eventset;
int r=0;
int freq_p[6];// there are six paths

static unsigned t1, t2, t3;

typedef struct s1 {
	int a;
	int b;
	int c;
	int d;
	int e;
} s1;

static s1 * a;

const int arraysize = 16*(1 << 10); 

static inline void func(int a1, int a2, int a3)
{
	int i;
	r=0;
	if(a1 || a3){
		r++;// weight val of node 1 equals 1
		for(i=0; i<arraysize; i++){
			a[i].a += a[i].e;
		}
		if(a2){
			r=r+3;// weight val of node 4
			for(i=0; i<arraysize; i++){
				a[i].b++;
			}
		}else{
			r=r+1;// weight val of node 5
		}
	}else {
		for(i=0; i<arraysize; i++){
			a[i].c = a[i].d++;
		}

	}

	if(a2 && a3){
		r++;// weight val of node 6 equals 1
		for(i=0; i<arraysize; i++){
			a[i].b = a[i].d++;
		}
	}
	freq_p[r]++;
}

/* Input set 1 */
void input1()
{
	t1 = 0.5 * RAND_MAX;
	t2 = 0.5 * RAND_MAX;
	t3 = 0.5 * RAND_MAX;
}
/* End input set 1*/

/* Input set 2 */
void input2()
{
	t1 = 0.2 * RAND_MAX;
	t2 = 0.6 * RAND_MAX;
	t3 = 0.8 * RAND_MAX;
}
/* End input set 2*/

int main()
{


	a = (s1 *) malloc(sizeof(s1) * arraysize);

	/*if(PAPI_VER_CURRENT != PAPI_library_init(PAPI_VER_CURRENT)){
		printf("Can't initiate PAPI library!\n");
		exit(-1);
	}

	eventset = PAPI_NULL;
	if(PAPI_create_eventset(&eventset) != PAPI_OK){
		printf("Can't create eventset!\n");
		exit(-3);
	}
	if(PAPI_OK != PAPI_add_events(eventset, events, eventnum)){
		printf("Can't add events!\n");
		exit(-4);
	}*/


	int i;
	unsigned a1, a2, a3;
	
	srandom(0);

	input1();
	/* input2(); */


	for(i=0; i<10000; i++){
		a1 = (random() > t1);
		a2 = (random() > t2);
		a3 = (random() > t3);

		func(a1, a2, a3);
	}

	/* Print out your profiling results here */
	for(int i = 0; i < 6; i++){
				printf("%d ", freq_p[i]);
	}
}

