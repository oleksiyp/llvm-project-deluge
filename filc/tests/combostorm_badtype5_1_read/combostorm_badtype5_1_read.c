#include <stdfil.h>
#include <inttypes.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "utils.h"
static char* hello = "hello";
static unsigned char value;
static void init_test(void)
{
    unsigned index;
    value = 42;
    bool good = false;
    while (!good) {
        good = true;
        for (index = sizeof(char*); index--;) {
            if (((char*)&hello)[index] == value) {
                good = false;
                break;
            }
        }
        if (good)
            break;
        value++;
    }
}
int main()
{
    init_test();
    char* buf = opaque(malloc(25));
    *(int8_t*)(buf + 0) = value;
    *(int8_t*)(buf + 8) = value;
    *(int8_t*)(buf + 16) = value;
    *(int8_t*)(buf + 24) = value;
    buf = (char*)opaque(buf) + 0;
    int8_t f0 = *(int8_t*)(buf + 0);
    char* f1 = *(char**)(buf + 8);
    int8_t f2 = *(int8_t*)(buf + 16);
    int8_t f3 = *(int8_t*)(buf + 24);
    ZASSERT(f0 == value);
    ZASSERT(!strcmp(f1, "hello"));
    ZASSERT(f2 == value);
    ZASSERT(f3 == value);
    return 0;
}
