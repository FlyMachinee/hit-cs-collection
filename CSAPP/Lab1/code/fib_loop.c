#include <stdio.h>
#include <stdlib.h>

typedef unsigned long datatype; // if changed here, also change line 24

datatype mem[256] = {0, 1, 1}; // dynamic programing

datatype fib_loop(int n) {
    if (mem[n] == 0) {
        int i = 0;
        while(mem[++i]);

        for (; i <= n; ++i) {
            mem[i] = mem[i - 1] + mem[i - 2];
            if (! (mem[i] > mem[i - 1] && mem[i] > mem[i - 2])) { // overflowed
                puts("Overflowed!!");
                exit(-1);
            }
        }
    }
    return mem[n];
}

int main() {
    for (int n = 1; n < 255; ++n) {
        printf("n = %d: %lu\n", n, fib_loop(n));
    }
    return 0;
}