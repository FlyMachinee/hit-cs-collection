#include <stdio.h>
#include <string.h>

int utf8len(const char* str) {
    int len = 0;

    while (*str) { // while (*str != '\0')
        unsigned char ch = *str;

        if (ch <= 0x7f) { // single byte character
            ++len;
            ++str;
        }
        else if ((ch & 0xe0) == 0xc0) { // ch is like 110xxxxx, double byte character
            ++len;
            str += 2;
        }
        else if ((ch & 0xf0) == 0xe0) { // ch is like 1110xxxx, triple byte character
            ++len;
            str += 3;
        }
        else if ((ch & 0xf8) == 0xf0) { // ch is like 11110xxx, quadruple byte character
            ++len;
            str += 4;
        }
        else // is not utf-8 code
            return -1;
    }
    return len;
}

int main() {
    const char* str = "2022zyj张宇杰?!";
    printf("str: %s\n", str);
    printf("strlen: %ld\n", strlen(str));
    printf("utf8len: %d\n", utf8len(str));
    return 0;
}