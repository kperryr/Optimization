#include <papi.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

#define fl 4
#define arraysize (16*(1 << 20))

static unsigned len = 16*(1 << 20);

/*typedef struct Mem {
	int fa[fl];
	char fb[fl];
	int fc[fl];
	char fd[fl];
	int fe[fl];
} Mem;*/

typedef struct Mem {
	struct {
			int fa[fl];
			char fb[fl];
			char fd[fl];
		}sub1[len];

		struct {
			int fc[fl];
			int fe[fl];
		}sub2[len]; 
}Mem;

/*typedef struct Mem {
	int fa[fl];
	char fb[fl];
	char fd[fl];
	int fc[fl];
	int fe[fl];
} Mem;*/

void func(Mem * a)
{
	int i;

	/*for(i=0; i<len; i++){
		a[i].fa[0] = a[i].fb[0]+a[i].fd[0];
	}

	for(i=0; i<len; i++){
		a[i].fc[0] = a[i].fe[0]*2;
	}*/



	for(i=0; i<len; i++){
		
		a->sub1[i].fa[0] = a->sub1[i].fb[0]+a->sub1[i].fd[0];
	}

	for(i=0; i<len; i++){
		a->sub2[i].fc[0] = a->sub2[i].fe[0]*2;
	}
	

}

/* Please add your events here */
int events[2] = {PAPI_TOT_CYC,PAPI_L1_DCM}; /*PAPI_L1_DCM, PAPI_L2_DCM, PAPI_TLB_DM*/
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
		for(int i = 0; i < eventnum; i++){
		printf("counter[%d]: %lld\n", i, values[i]);
	}
	
	return EXIT_SUCCESS;
}
