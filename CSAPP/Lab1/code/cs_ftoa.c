#include <stdio.h>
#include <string.h>
#include <assert.h>

#define MAX_BIGINT_LEN 256
typedef struct {
    char val[MAX_BIGINT_LEN]; // little endian
} bigint;

bigint bigzero();
void showbigint(const bigint* num);
bigint add(bigint a, bigint b);
bigint mul(bigint a, bigint b);
bigint pow(bigint a, unsigned exponent);
bigint strtobig(const char* str);
bigint* strsetbig(bigint* dest, const char* str);

char* cs_itoa(int val, char* buf, int base);
char* reverse(char* str);

union f_and_ull {
    float f;
    unsigned i;
};

char* cs_ftoa(float val, char* buf, int decimals_digit) {
    union f_and_ull data;
    data.f = val;

    int sign = (data.i & 0x80000000) >> 31;
    int exponent = (data.i & 0x7f800000) >> 23;
    int fraction = data.i & 0x007fffff;

    int shift_left = 0; // count that dot to be shift left (in base 10)
    // original 0 mean no shift, represent the float: sign * fraction.000000(...)

    bigint num1, num2; // for calculation

    if (exponent == 0xff) {
        if (fraction == 0)
            if (sign == 0)
                return strcpy(buf, "inf");
            else
                return strcpy(buf, "-inf");
        else
            return strcpy(buf, "nan");
    }
    else if (exponent == 0) { // denormalised
        shift_left = 149; // equivalent to times 10^(-149)
        reverse(cs_itoa(fraction, num1.val, 10)); // now the fraction is in num1

        strsetbig(&num2, "5");
        num2 = pow(num2, 149); // 5^149
        num1 = mul(num1, num2); // frac * 10^(-149) * 5^149 = frac * 2^(-149)
    }
    else { // normalised
        fraction |= (1 << 23); // 1.xxxxxxxxxxxxxxxxxxxxxxx for normalised number
        exponent -= (127 + 23);
        // the 23 is to 'right shift' the fraction, make it like: 1xxxxxxxxxxxxxxxxxxxxxxx.000(...)
        //                                                                     ^ 23 xs
        // so the fraction we calculated is the whole integer part, no need to handle decimals

        reverse(cs_itoa(fraction, num1.val, 10)); // now the fraction is in num1

        // here, the result is like: fraction * 2^exponent
        if (exponent >= 0) { // indicate that the result is a integer
            strsetbig(&num2, "2");
            num2 = pow(num2, exponent); // 2^exponent
            num1 = mul(num1, num2); // frac * 2^exponent
        }
        else {
            // so the result is like: fraction * 2^(- abs of exponent)
            // we will do the same thing like line 49 part

            exponent = -exponent; // abs of exponent
            shift_left = exponent; // equivalent to times 10^(exponent)

            strsetbig(&num2, "5");
            num2 = pow(num2, exponent); // 5^(-exponent)
            num1 = mul(num1, num2); // frac * 10^(exponent) * 5^(-exponent) = frac * 2^(exponent)
        }
    }

    // calculate completed, now making string
    int i = 0;
    if (sign)
        buf[i++] = '-';
    int fraction_len = strlen(num1.val);

    int j = fraction_len - 1;
    for (; j >= shift_left; --j) // before dot
        buf[i++] = num1.val[j];
    
    if (shift_left >= fraction_len) // if nothing before dot
        buf[i++] = '0';

    buf[i++] = '.';

    for (int _ = 1; _ <= shift_left - fraction_len; ++_) { // shift_len > fraction_len, need to supplement front zeros
        buf[i++] = '0';
        if (_ >= decimals_digit) { // the front zeros len equals to decimals_digit, should stop and return
            j = -2; // for return purpose
            break;
        }
    }

    for (; j >= 0 && j >= shift_left - decimals_digit; --j) // after dot
        buf[i++] = num1.val[j];

    if (j == -1) // the whole fraction is output, no need to round, supplement back zeros
        for (int _ = 0; _ < decimals_digit - shift_left; ++_)
            buf[i++] = '0';
    else // need to round, so no need to supplement back zero
        if (j >= 0 && num1.val[j] >= '5')
            ++buf[i - 1]; // round up

    buf[i] = '\0';
    return buf;
}

int main() {
    char buf[256];

    printf("%.6f\n", (float)0);
    printf("%s\n", cs_ftoa(0, buf, 6));

    printf("%.10f\n", (float)123.456);
    printf("%s\n", cs_ftoa(123.456, buf, 10));

    printf("%.3f\n", (float)16461879313721493751646731.0);
    printf("%s\n", cs_ftoa(16461879313721493751646731.0, buf, 3));

    printf("%.18f\n", (float)-123.424613736913375156);
    printf("%s\n", cs_ftoa(-123.424613736913375156, buf, 18));

    printf("%.20f\n", (float)1e18);
    printf("%s\n", cs_ftoa(1e18, buf, 20));

    printf("%.20f\n", (float)1e-18);
    printf("%s\n", cs_ftoa(1e-18, buf, 20));

    printf("%.20f\n", (float)6.02e-23);
    printf("%s\n", cs_ftoa(6.02e-23, buf, 20));
 
    printf("%.30f\n", (float)6.02e-23);
    printf("%s\n", cs_ftoa(6.02e-23, buf, 30));

    printf("%.3f\n", (float)1e38);
    printf("%s\n", cs_ftoa(1e38, buf, 3));

    printf("%.3f\n", (float)1e39);
    printf("%s\n", cs_ftoa(1e39, buf, 3));
    return 0;
}

bigint bigzero() {
    bigint ret;
    memset(ret.val, 0, sizeof(ret.val));
    return ret;
}

void showbigint(const bigint* num) {
    for (int i = strlen(num->val) - 1; i >= 0; --i)
        putchar(num->val[i]);
}

bigint add(bigint a, bigint b) {
    bigint ret;
    int a_len = strlen(a.val), b_len = strlen(b.val);
    int ret_len = (a_len > b_len) ? a_len : b_len;

    int carry = 0;
    for (int i = 0; i < ret_len; ++i) {
        int a_digit = (a.val[i] >= '0' && a.val[i] <= '9') ? (a.val[i] - '0') : 0;
        int b_digit = (b.val[i] >= '0' && b.val[i] <= '9') ? (b.val[i] - '0') : 0;
        int sum = a_digit + b_digit + carry;
        carry = sum / 10;
        ret.val[i] = sum % 10 + '0';
    }

    if (carry > 0)
        ret.val[ret_len++] = carry + '0';
    ret.val[ret_len] = '\0';

    return ret;
}

bigint mul(bigint a, bigint b) {
    bigint ret = bigzero();
    int a_len = strlen(a.val), b_len = strlen(b.val);
    
    int carry = 0;
    for (int i = 0; i < a_len; ++i) {
        int carry = 0;

        for (int j = 0; j < b_len; ++j) {
            int a_digit = (a.val[i] >= '0' && a.val[i] <= '9') ? (a.val[i] - '0') : 0;
            int b_digit = (b.val[j] >= '0' && b.val[j] <= '9') ? (b.val[j] - '0') : 0;

            ret.val[i + j] += a_digit * b_digit + carry;
            carry = ret.val[i + j] / 10;
            ret.val[i + j] %= 10;
        }
        
        ret.val[b_len + i] = carry;
    }

    int ret_len = a_len + b_len;
    while (ret.val[ret_len - 1] == 0)
        --ret_len;

    ret.val[ret_len] = '\0';
    for (int i = 0; i < ret_len; ++i)
        ret.val[i] += '0';

    return ret;
}

// fast power
bigint pow(bigint a, unsigned exponent) {
    bigint ret = strtobig("1");
    while (exponent) {
        if (exponent & 1) // if (exponent % 2 == 1)
            ret = mul(ret, a);
        a = mul(a, a);
        exponent >>= 1;
    }
    return ret;
}

bigint strtobig(const char* str) {
    bigint ret;
    strncpy(ret.val, str, MAX_BIGINT_LEN);
    reverse(ret.val);
    return ret;
}

bigint* strsetbig(bigint* dest, const char* str) {
    strncpy(dest->val, str, MAX_BIGINT_LEN);
    reverse(dest->val);
    return dest;
}

char* reverse(char* str) {
    int len = strlen(str);
    for (int i = 0, j = len - 1; i < j; ++i, --j) {
        char temp = str[i];
        str[i] = str[j];
        str[j] = temp;
    }
    return str;
}

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