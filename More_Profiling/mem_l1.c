#include <papi.h>
#include <stdio.h>
#include <stdlib.h>

static unsigned len = 16*(1 << 20);

typedef struct Mem {
	int fa;
	char fb;
	int fc;
	char fd;
	int fe;
} Mem;

void func(Mem * a)
{
	int i;

	for(i=0; i<len; i++){
		a[i].fc = a[i].fe*2;
		a[i].fa = a[i].fb+a[i].fd;
	}

	/* for(i=0; i<len; i++){
		a[i].fc = a[i].fe*2;
	} */

}

/* Please add your events here */
int events[2] = {PAPI_TOT_CYC, PAPI_L1_DCM}; /*PAPI_L1_DCM, PAPI_L2_DCM, PAPI_TLB_DM*/
int eventnum = 2;

int main()
{
	long long values[2];
	int eventset;
	Mem * a;

	if(PAPI_VER_CURRENT != PAPI_library_init(PAPI_VER_CURRENT)){
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
	}

	a = (Mem *) malloc(len*sizeof(Mem));
	PAPI_start(eventset);
	func(a);
	PAPI_stop(eventset, values);
	free(a);

	/*Print out PAPI reading*/
	char event_name[PAPI_MAX_STR_LEN];
	if (PAPI_event_code_to_name( events[0], event_name ) == PAPI_OK)
		for(i = 0; i < eventnum; i++){
		printf("counter[%d]: %lld\n", i, values[i]);
	}
	
	return EXIT_SUCCESS;
}
