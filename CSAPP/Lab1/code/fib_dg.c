#include <stdio.h>
#include <stdlib.h>

typedef unsigned long datatype; // if changed here, also change line 24

datatype mem[256] = {0, 1, 1}; // dynamic programing

datatype fib_dg(int i) {
    if (mem[i] != 0)
        return mem[i];
    else {
        mem[i] = fib_dg(i - 1) + fib_dg(i - 2);
        if (mem[i] > mem[i - 1] && mem[i] > mem[i - 2])
            return mem[i];
        else { // overflowed
            puts("Overflowed!!");
            exit(-1);
        }
    }
}

int main() {
    for (int n = 1; n < 255; ++n) {
        printf("n = %d: %lu\n", n, fib_dg(n));
    }
    return 0;
}