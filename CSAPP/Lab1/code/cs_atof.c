#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>

double cs_atof(const char *str) {
    int fraction_sign = 1, exponent_sign = 1;
    double fraction = 0.0;
    int dot_digit = 0, exponent = 0;

    if (str == NULL) // null pointer
        return 0.0;

    while (*str == ' ' || *str == '\n' || *str == '\t' || *str == '\r' || *str == '\v' || *str == '\f') // skip blank character
        str++;

    if (*str == '+' || *str == '-') { // handle sign
        if (*str == '-')
            fraction_sign = -1;
        ++str;
    }
    
    while (*str >= '0' && *str <= '9') // handel number
        fraction = (fraction * 10) + (*(str++) - '0');

    if (*str == '.') { // handle the dot and the following fraction number
        ++str;
        while (*str >= '0' && *str <= '9')
            fraction += (*(str++) - '0') * pow(10, -(++dot_digit));
    }

    if (*str == 'e' || *str == 'E') { // handle exponent
        ++str;

        if (*str == '+' || *str == '-') { // handle exponent sign
            if (*str == '-')
                exponent_sign = -1;
            ++str;
        }

        while (*str >= '0' && *str <= '9') // handel exponent number
            exponent = (exponent * 10) + (*(str++) - '0');
    }

    return fraction_sign * fraction * pow(10, exponent_sign * exponent);
}

int main() {
    const char *str[] = {
        "-1.64e+21",
        "2.94E-2",
        "3.1415926535",
        ".2345",
        "4e16",
        ".9E-3",
        "250.",
        "12ab3.4",
        "as12.1e5",
        "12.a2",
        "12a.3e4",
        "12e.123",
        "12.12e2a3"
    };
    for (int i = 0; i < 13; ++i)
        printf("str: %s\natof:    %f\ncs_atof: %f\n", str[i], atof(str[i]), cs_atof(str[i]));
    return 0;
    
}
