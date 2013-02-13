#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char **argv)
{
    long i=0, sum1=0, sum2=0;

    for (i = 1; i <= 100; ++i)
    {
        sum1 += i;
        sum2 += i*i;
    }

    sum1 *= sum1;

    printf("%ld\n", labs(sum1-sum2));

    return 0;
}