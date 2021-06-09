#include <stdio.h>

extern char _binary_cow_start;
extern char _binary_cow_end;

main()
{
    char cowel;
    for (char* p = &_binary_cow_start; p != &_binary_cow_end; ++p) {
        cowel += p;
    };

    printf(cowel);
}
