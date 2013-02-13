#include <stdlib.h>
#include <stdio.h>

int gen(int p, int pmax, int q)
{
    int a, b, c;

    for (; p < pmax; p += 2)
    {
        int _q = q;

        for (; _q < p; _q += 2)
        {
            if (!pythagorean_triplet(p, _q, &a, &b, &c))
                continue;

            printf("p:%d q:%d a:%d\tb:%d\tc:%d\n", p, _q, a, b, c);

            if (a+b+c == 1000)
                goto found;

            if (1000 % (a+b+c) == 0)
            {
                int m = 1000 / (a+b+c);

                printf("triplet sum (%d) is divisor of 1000, multiply by %d\n",
                    a+b+c, m);

                a *= m;
                b *= m;
                c *= m;

                if (a+b+c == 1000)
                    goto found;
            }
        }
    }

    return 0;

found:

    printf("got it: a:%d b:%d c:%d a*b*c=%d\n", a, b, c, a*b*c);

    return 1;
}

int main(int argc, char **argv)
{
    // some different ways to generate pythagorean triples, let's hope one of
    // these yields the result

    if (gen(3, 20, 3))
        return 0;

    printf("--\n");

    if (gen(3, 20, 2))
        return 0;

    printf("--\n");

    if (gen(2, 20, 3))
        return 0;

    // and of course the brute-force way :-) (this could be optimized by
    // making the condition b<1000 -> b<1000-a and just stating c=1000-a-b
    // instead of iterating values of c).

    // int a, b, c;

    // for (a = 1; a < 1000; a++)
    // {
    //     for (b = a+1; b < 1000; b++)
    //     {
    //         for (c = b+1; c < 1000; c++)
    //         {
    //             if ((a + b + c == 1000) && (a*a + b*b == c*c))
    //             {
    //                 printf("a:%d b:%d c:%d a*b*c:%d\n", a, b, c, a*b*c);
    //                 return 0;
    //             }
    //         }
    //     }
    // }

    return 0;
}

