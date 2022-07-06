#include <iostream>
#include <fstream>
#include <cstdlib>
#include "algorithm1.h"
#include "algorithm2.h"
#include <time.h>

using namespace std;
#define num 100000
clock_t start_time;
clock_t end_time ;
void test()
{
    
    start_time = clock();
    tree();
    end_time = clock();
    printf("1 time=%f\n", (double)(end_time - start_time) / CLOCKS_PER_SEC);

    start_time = clock();
    slow();
    end_time = clock();
    printf("2 time=%f\n", (double)(end_time - start_time) / CLOCKS_PER_SEC);
}
int main()
{
    
    test();    
    return 0;
}
