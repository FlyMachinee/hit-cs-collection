#include <stdio.h>
#include <stdlib.h>

int cs_atoi(const char *str) {
    int res = 0, sign = +1;

    if (str == NULL) // null pointer
        return 0;

    while (*str == ' ' || *str == '\n' || *str == '\t' || *str == '\r' || *str == '\v' || *str == '\f') // skip blank character
        str++;

    if (*str == '+' || *str == '-') { // handle sign
        if (*str == '-')
            sign = -1;
        ++str;
    }

    while (*str >= '0' && *str <= '9') // handel number
        res = (res * 10) + (*(str++) - '0');

    return sign * res;
}

int main() {
    const char* str = " \n\r\r\n\t\v\f-123 ab456";
    int num = cs_atoi(str);
    printf("%d\n", num);
    return 0;
}
