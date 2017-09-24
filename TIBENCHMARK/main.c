#include <stdio.h>
#include <stdlib.h>
#include "tibenchmark.h"
#include <time.h>

#define LOOP_CNT		10000000ul

clock_t start, end;

int main() {
	int i;


    printf("Hello world!\n");

    start=clock();					//time stamp
    //put your benchmark here
    //benchmark(main_fir, LOOP_CNT);
    benchmark(main_8bitmath, LOOP_CNT);
    end=clock();
    printf("clock elapsed = %5d\n\r", end-start);
    return 0;
}
