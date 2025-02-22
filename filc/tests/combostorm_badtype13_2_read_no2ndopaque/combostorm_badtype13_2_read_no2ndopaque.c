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
    char* buf = opaque(malloc(24));
    *(int16_t*)(buf + 6) = value;
    *(int16_t*)(buf + 14) = value;
    *(int16_t*)(buf + 22) = value;
    buf = (char*)(buf) + 0;
    int16_t f0 = *(int16_t*)(buf + 6);
    int16_t f1 = *(int16_t*)(buf + 14);
    char* f2 = *(char**)(buf + 16);
    ZASSERT(f0 == value);
    ZASSERT(f1 == value);
    ZASSERT(!strcmp(f2, "hello"));
    return 0;
}
