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
    char* buf = (malloc(28));
    *(int32_t*)(buf + 0) = value;
    *(int32_t*)(buf + 4) = value;
    *(int32_t*)(buf + 8) = value;
    *(int32_t*)(buf + 12) = value;
    *(char**)(buf + 16) = hello;
    *(int32_t*)(buf + 24) = value;
    buf = (char*)opaque(buf) + 0;
    int32_t f0 = *(int32_t*)(buf + 0);
    int32_t f1 = *(int32_t*)(buf + 4);
    int32_t f2 = *(int32_t*)(buf + 8);
    int32_t f3 = *(int32_t*)(buf + 12);
    int32_t f4 = *(int32_t*)(buf + 16);
    int32_t f5 = *(int32_t*)(buf + 20);
    int32_t f6 = *(int32_t*)(buf + 24);
    ZASSERT(f0 == value);
    ZASSERT(f1 == value);
    ZASSERT(f2 == value);
    ZASSERT(f3 == value);
    ZASSERT(f4 == value);
    ZASSERT(f5 == value);
    ZASSERT(f6 == value);
    return 0;
}
