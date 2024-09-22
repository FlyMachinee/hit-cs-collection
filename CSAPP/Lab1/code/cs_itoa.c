#include <stdio.h>
#include <string.h>
#include <assert.h>

void reverse(char* str);

// base must in range [2, 37)
char* cs_itoa(int val, char* buf, int base)
{
    assert(base >= 2 && base < 37);

    char index[] = "0123456789abcdefghijklmnopqrstuvwxyz";
    unsigned int abs_val;
    int i = 0;

    // get absolute value
    if (base == 10 && val < 0) { // only base 10 will reserve the negative sign
        abs_val = -val;
        buf[i++] = '-'; // add negative sign to the result
    }
    else
        abs_val = (unsigned int)val; // in other case, cast to unsigned int

    // convertion
    do {
        buf[i++] = index[abs_val % base];
        abs_val /= base;
    } while (abs_val); // while (abs_val != 0)

    buf[i] = '\0';

    // reverse the string (except negative sign '-')
    int begin = buf[0] == '-' ? 1 : 0;
    reverse(buf + begin);

    return buf;
}

int main() {
    char buf[256];
    printf("%s\n", cs_itoa(987654321, buf, 2));
    printf("%s\n", cs_itoa(987654321, buf, 8));
    printf("%s\n", cs_itoa(987654321, buf, 16));
    printf("%s\n", cs_itoa(0, buf, 10));
    printf("%s\n", cs_itoa(-1, buf, 10));
    printf("%s\n", cs_itoa(-1, buf, 2));
    printf("%s\n", cs_itoa(-1, buf, 8));
    printf("%s\n", cs_itoa(-1, buf, 16));
    return 0;
}

void reverse(char* str) {
    int len = strlen(str);
    for (int i = 0; i < len / 2; i++) {
        char temp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = temp;
    }
}