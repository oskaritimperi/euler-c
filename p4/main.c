#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

list_t *digits(int i)
{
    list_t *lst = NULL;

    while (i > 0)
    {
        int digit = i % 10;
        i = i / 10;
        lst = list_append_int(lst, digit);
    }

    return lst;
}

int is_palindrome(int i)
{
    list_t *d = NULL;
    int len = 0;
    int j = 0;

    if (i < 10)
        return 1;

    d = digits(i);
    len = list_len(d);

    // printf("i:%d\n", i);

    for (j = 0; j < len/2; ++j)
    {
        int *a = (int*)list_get_n(d, j);
        int *b = (int*)list_get_n(d, len-1-j);

        // printf("a:%d b:%d\n", *a, *b);

        if (*a != *b)
        {
            return 0;
        }
    }

    list_free(d, list_free_int);

    return 1;
}

int main(int argc, char **argv)
{
    int i, j;

    for (i = 999; i >= 900; i--)
    {
        for (j = 999; j >= 900; j--)
        {
            int k = i*j;

            if (is_palindrome(k))
            {
                printf("%d * %d = %d\n", i, j, k);
                return 0;
            }
        }
    }

    return 0;
}