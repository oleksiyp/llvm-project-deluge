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
    char* buf = opaque(malloc(28));
    *(int32_t*)(buf + 0) = value;
    *(int32_t*)(buf + 8) = value;
    *(int32_t*)(buf + 16) = value;
    *(int32_t*)(buf + 24) = value;
    buf = (char*)opaque(buf) + 0;
    char* f0 = *(char**)(buf + 0);
    int32_t f1 = *(int32_t*)(buf + 8);
    int32_t f2 = *(int32_t*)(buf + 16);
    int32_t f3 = *(int32_t*)(buf + 24);
    ZASSERT(!strcmp(f0, "hello"));
    ZASSERT(f1 == value);
    ZASSERT(f2 == value);
    ZASSERT(f3 == value);
    return 0;
}
