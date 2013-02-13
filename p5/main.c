#include <stdio.h>
#include <stdlib.h>

void basic()
{
    long int i = 0;
    long int j;
    int done = 0;

    while (!done)
    {
        i += 20;

        done = 1;

        // 20 (2*2*5)       2, 4, 10, 20
        // 19
        // 18 (2*3*3)       2, 6, 9, 18
        // 17
        // 16 (2*2*2*2)     2, 4, 8, 16
        // 15 (3*5)         3, 5
        // 14 (2*7)         2, 7
        // 13
        // 12 (2*2*3)       2, 3
        // 11
        // no need to check for 1-9, because they are included in the
        // numbers above

        for (j = 11; j <= 20 && done; ++j)
        {
            done = done && (i % j == 0);
        }
    }

    printf("%ld\n", i);
}

int main(int argc, char **argv)
{
    basic();
    return 0;
}