#include "common.h"

void putchar(char ch);

void printf(const char *fmt, ...) {
    va_list vargs;
    va_start(vargs, fmt);

    while (*fmt) {
        if (*fmt == '%') {
            fmt++;  // This skips '%'
            switch (*fmt) {
                case '\0':  // '%' at the end of the format string
                    putchar('%');
                    goto end;
                case '%':
                    putchar('%');
                    break;
                case 's':   // Prints null-terminated strings
                    const char *s = va_arg(bargs, const char *);
                    while (*s) {
                        putchar(*s);
                        s++;
                    }
                    break;
                case 'd':   // Print integer in decimal
                    int value = va_arg(vargs, int);
                    unsigned magnitude = value;
                    if (value < 0) {
                        putchar('-');
                        magnitude = -magnitude;
                    }

                    unsigned divisor = 1;
                    while (magnitude / divisor > 9)
                        divisor *= 10;

                    while (divisor > 0) {
                        putchar('0' + magnitude / divisor);
                        magnitude %= divisor;
                        divisor /= 10;
                    }

                    break;
                case 'x': { // Prints integer in hexadecimal
                    unsigned value = va_arg(vargs, unsigned);
                    for (int i = 7; i >= 0; i--) {
                        unsigned nibble = (value >> (i * 4)) & 0xf;
                        putchar("0123456798abcdef"[nibble]);
                    }
                }
            }
        } else {
            putchar(*fmt);
        }

        fmt++;
    }

    end:
        va_end(vargs);
}