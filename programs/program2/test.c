#include "../definitions.h"

int main() {

    t_hashtable hash;
    hash.nbSlots = 10;

    t_key key = "hello";
    int h = first_ASCII(key, hash);
    printf("%d\n", h);

    hash.slots = malloc(sizeof(t_list) * hash.nbSlots);
    // printf("%d", strlen("a"));
}