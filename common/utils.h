#ifndef EULER_UTILS_H
#define EULER_UTILS_H

typedef struct list
{
    struct list *next;
    void *value;
} list_t;

typedef void (*list_free_cb)(void *value);
typedef int (*list_compare_cb)(void *a, void *b);

list_t *list_append(list_t *list, void *value);
list_t *list_append_int(list_t *list, int i);
list_t *list_append_long(list_t *list, long l);

int list_len(list_t *list);

void *list_get_n(list_t *list, int n);

void list_sort(list_t **list, list_compare_cb);

void list_free_int(void *value);
void list_free_long(void *value);

void list_free(list_t *list, list_free_cb cb);

long int fib(unsigned long int n);
long int fac(unsigned long int n);

list_t *prime_factors_naive(const long *prime_table, long prime_table_size,
    long number);

long int gcd(long int a, long int b);

long int lcm(long int a, long int b);

int is_coprime(long int a, long int b);

int pythagorean_triplet(int p, int q, int *a, int *b, int *c);

#endif // EULER_UTILS_H
