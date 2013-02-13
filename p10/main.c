#include <stdlib.h>
#include <stdio.h>

#include "utils.h"

int main(int argc, char **argv)
{
    long i;
    long sum = 2;

    for (i = 3; i < 2000000; ++i)
    {
        int p = is_prime_rabmil(i, 30);

        if (p)
        {
            sum += i;
        }
    }

    printf("%ld\n", sum);

    return 0;
}

