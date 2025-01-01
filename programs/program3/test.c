#include "../definitions.h"

int main(int argc, char **argv)
{
    char *test = "hello";
    printf("%s\n", (test + 1));
    char *string = argv[1] + 2;
    char id = argv[1][1];
    printf("%s, %c\n", string, id);
}