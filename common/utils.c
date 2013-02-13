#include <stdlib.h>
#include <math.h>

#include "utils.h"

/* http://www.evanmiller.org/mathematical-hacker.html */
static long int _fib(unsigned long int n)
{
    return lround((pow(0.5 + 0.5 * sqrt(5.0), n) -
                   pow(0.5 - 0.5 * sqrt(5.0), n)) / sqrt(5.0));
}

/* http://blog.noblemail.ca/2013/01/on-calculating-fibonacci-numbers-in-c.html */
long int fib(unsigned long int n)
{
    return lround((pow(0.5 + 0.5 * sqrt(5.0), n)) / sqrt(5.0));
}

/* factorial */
long int fac(unsigned long int n) {
    return lround(exp(lgamma(n+1)));
}

list_t *list_append(list_t *list, void *value)
{
    list_t *ret, *curr;

    ret = malloc(sizeof(list_t));
    ret->value = value;
    ret->next = NULL;

    if (!list)
    {
        return ret;
    }

    curr = list;
    while (curr->next)
    {
        curr = curr->next;
    }

    curr->next = ret;

    return list;
}

list_t *list_append_int(list_t *list, int i)
{
    int *p = malloc(sizeof(int));
    *p = i;
    return list_append(list, p);
}

list_t *list_append_long(list_t *list, long l)
{
    long *p = malloc(sizeof(long));
    *p = l;
    return list_append(list, p);
}

int list_len(list_t *list)
{
    int i = 0;

    while (list)
    {
        list = list->next;
        ++i;
    }

    return i;
}

void *list_get_n(list_t *list, int n)
{
    int i = 0;

    for (; list && i < n; ++i)
    {
        list = list->next;
    }

    if (list)
        return list->value;

    return NULL;
}

void list_append_list(list_t *list, list_t *elem)
{
    while (list->next)
    {
        list = list->next;
    }

    list->next = elem;
}

void list_sort(list_t **list, list_compare_cb cmp)
{
    int len = list_len(*list);
    list_t *pivot = *list;
    list_t *less = NULL, *greater = NULL;
    list_t *curr;

    if (len <= 1)
        return;

    curr = pivot->next;
    pivot->next = NULL;

    while (curr)
    {
        list_t *next = curr->next;
        curr->next = NULL;

        if (cmp(curr->value, pivot->value) <= 0)
        {
            if (!less)
                less = curr;
            else
                list_append_list(less, curr);
        }
        else
        {
            if (!greater)
                greater = curr;
            else
                list_append_list(greater, curr);
        }

        curr = next;
    }

    list_sort(&less, cmp);
    list_sort(&greater, cmp);

    list_append_list(less, pivot);
    list_append_list(less, greater);

    *list = less;
}

void list_free_int(void *value)
{
    free((int*)value);
}

void list_free_long(void *value)
{
    free((long*)value);
}

void list_free(list_t *list, list_free_cb cb)
{
    list_t *tmp;

    if (!list)
    {
        return;
    }

    while (list->next)
    {
        cb(list->value);
        tmp = list;
        list = list->next;
        free(tmp);
    }

    cb(list->value);
    free(list);
}

list_t *prime_factors_naive(const long *prime_table, long prime_table_size,
    long number)
{
    long prime = 0;
    long i;
    char quot_is_prime;

    list_t *factors = NULL;

    // printf("table size: %ld\n", prime_table_size);

    while (prime < prime_table_size)
    // while (1)
    {
        // printf("prime: %ld\n", prime);

        long quot = number / prime_table[prime];
        long rem = number % prime_table[prime];

        if (rem == 0)
        {
            // printf("factor: %ld\n", prime_table[prime]);

            factors = list_append_long(factors, prime_table[prime]);

            if (quot == 1)
            {
                break;
            }

            quot_is_prime = 1;

            for (i = 2; i < sqrt(quot); ++i)
            {
                if (quot % i == 0)
                {
                    quot_is_prime = 0;
                    break;
                }
            }

            if (quot_is_prime)
            {
                // printf("factor: %ld\n", quot);
                factors = list_append_long(factors, quot);
                break;
            }

            number = quot;
            prime = 0;
        }
        else
        {
            prime++;
        }
    }

    return factors;
}

long int gcd(long int a, long int b)
{
    if (a == 0)
        return b;

    if (b == 0)
        return a;

    while (1)
    {
        long int q = a / b;
        long int r = a % b;

        if (r == 0)
        {
            return b;
        }

        a = b;
        b = r;
    }
}

long int lcm(long int a, long int b)
{
    a = a / gcd(a, b);
    return a * b;
}

int is_coprime(long int a, long int b)
{
    if (gcd(a, b) == 1)
    {
        return 1;
    }

    return 0;
}

int pythagorean_triplet(int p, int q, int *a, int *b, int *c)
{
    // http://www.friesian.com/pythag.htm

    // Two cases:
    //
    // 1. p and q must both be odd, p>q, gcd(p,q)=1
    // 2. p and q must not both be odd, p>q, gcd(p,q)=1

    if (p > q && gcd(p, q) == 1)
    {
        if (p % 2 != 0 && q % 2 != 0)
        {
            *a = p*q;
            *b = (p*p - q*q) / 2;
            *c = (p*p + q*q) / 2;

            // sometimes a > b, we can just switch
            if (*a > *b)
            {
                p = *a;
                *a = *b;
                *b = p;
            }

            return 1;
        }
        else if ((p % 2 == 0 && q % 2 != 0) || (p % 2 != 0 && q % 2 == 0))
        {
            *a = 2*p*q;
            *b = p*p - q*q;
            *c = p*p + q*q;

            // sometimes a > b, we can just switch
            if (*a > *b)
            {
                p = *a;
                *a = *b;
                *b = p;
            }

            return 1;
        }
    }

    return 0;
}

// https://en.wikipedia.org/wiki/Modular_exponentiation
long modpow(long b, long e, long m)
{
    long result = 1;

    while (e > 0)
    {
        if (e % 2 == 1)
        {
            result = (result * b) % m;
        }

        e = e >> 1;

        b = (b*b) % m;
    }

    return result;
}

// Input: n > 3, an odd integer to be tested for primality;
// Input: k, a parameter that determines the accuracy of the test
// Output: composite if n is composite, otherwise probably prime
// write n − 1 as 2^s*d with d odd by factoring powers of 2 from n − 1
// WitnessLoop: repeat k times:
//    pick a random integer a in the range [2, n − 2]
//    x ← ad mod n
//    if x = 1 or x = n − 1 then do next WitnessLoop
//    repeat s − 1 times:
//       x ← x2 mod n
//       if x = 1 then return composite
//       if x = n − 1 then do next WitnessLoop
//    return composite
// return probably prime

int is_prime_rabmil(long int n, long int k)
{
    long pow2 = 0;
    long tmp = n-1;
    int q_is_prime;
    long i, j;
    long d;
    int next_witness;

    if (n == 2)
        return 1;

    if (n % 2 == 0)
        return 0;

    // write n − 1 as 2^s*d with d odd by factoring powers of 2 from n − 1
    while (1)
    {
        long q = tmp / 2;
        long r = tmp % 2;

        if (r == 0)
        {
            pow2++;

            if (q == 1)
            {
                break;
            }

            q_is_prime = 1;

            for (i = 2; i < sqrt(q); ++i)
            {
                if (q % i == 0)
                {
                    q_is_prime = 0;
                    break;
                }
            }

            if (q_is_prime)
            {
                break;
            }

            tmp = q;
        }
        else
        {
            break;
        }
    }

    d = (n-1) / (long)pow(2, pow2);

    // WitnessLoop: repeat k times:
    for (i = 0; i < k; ++i)
    {
        // pick a random integer a in the range [2, n − 2]
        long a = 2 + rand() % (n-2);

        // x ← a^d mod n
        // int x = ((long)pow(a, d)) % n;
        long x = modpow(a, d, n);

        // if x = 1 or x = n − 1 then do next WitnessLoop
        if (x == 1 || x == n-1)
            continue;

        next_witness = 0;

        // repeat s − 1 times:
        for (j = 0; j < pow2-1; ++j)
        {
            // x ← x2 mod n
            x = (x*x) % n;

            // if x = 1 then return composite
            if (x == 1) return 0;

            // if x = n − 1 then do next WitnessLoop
            if (x == n-1)
            {
                next_witness = 1;
                break;
            }
        }

        if (next_witness)
            continue;

        // return composite
        return 0;
    }

    // return probably prime
    return 1;
}
