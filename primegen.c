#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char **argv)
{
    int opt;
    const char *optstr = "n:";
    long count = -1;
    int current, i, primecount = 0;

    while ((opt = getopt(argc, argv, optstr)) != -1)
    {
        switch (opt)
        {
        case 'n':
            count = strtol(optarg, NULL, 0);
            break;

        case '?':
            exit(1);
        }
    }

    if (count <= 0)
    {
        exit(1);
    }

    char *sieve = malloc(sizeof(char) * count);
    memset(sieve, 1, sizeof(char) * count);

    current = 2;

    while (current < count)
    {
        if (sieve[current])
        {
            primecount++;

            for (i = current*2; i < count; i+=current)
            {
                sieve[i] = 0;
            }
        }

        current++;
    }

    printf("const long prime_table[%d] = { 2", primecount);

    for (i = 3; i < count; ++i)
    {
        if (sieve[i])
        {
            printf(",%d", i);
        }
    }

    printf("\n};\n");

    printf("const long prime_table_size = %d;\n", primecount);

    free(sieve);

    return 0;
}