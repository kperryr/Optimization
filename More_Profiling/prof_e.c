#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static unsigned t1, t2, t3;

int freq_e[10];
void func(int a1, int a2, int a3)
{
	int i,j,k;

	if(a1){
		freq_e[0]++;
		i++;
		freq_e[2]++;
		if(a2){
			freq_e[4]++;
			j++;
			freq_e[6]++;
			
		}else{
			freq_e[5]++;
			
		}

	} else {
		freq_e[1]++;
		k++;
		freq_e[3]++;
	}

	if(a3){
		freq_e[7]++;
		k++;
		freq_e[8]++;
	}else{
		freq_e[9]++;
		
	}
}
 
/* No profiling for code below*/

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
	int i;
	unsigned a1, a2, a3;

	input1();
	/* input2(); */

	srand(time(NULL));

	for(i=0; i<10000; i++){
		a1 = (rand() > t1);
		a2 = (rand() > t2);
		a3 = (rand() > t3);

		func(a1, a2, a3);
	}

	/* Print out your profiling results here */
	for(int i = 0; i < 10; i++){
			printf("%d ", freq_e[i]);
	}
	return EXIT_SUCCESS;
}

