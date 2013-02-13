#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "utils.h"

int main(int argc, char **argv)
{
    // 90 = 2*3*3*5
    // 17 = 17
    // 147 = 3*7*7

    long number = 600851475143;

#include "primes_10000000.h"

    list_t *factors = prime_factors_naive(prime_table, prime_table_size,
        number);

    list_t *curr = factors;
    while (curr)
    {
        printf("%ld\n", *((long*)curr->value));
        curr = curr->next;
    }

    list_free(factors, &list_free_long);

    return 0;
}
