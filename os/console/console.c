/*
 * Copyright 2026 Aananth C N
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "console.h"
#include <drivers/uart/uart.h>
#include <stdarg.h>


/* ============================================================
   printf
   ============================================================ */

static int put_uint(unsigned n, unsigned base, int upper) {
    char buf[12];
    int i = 0;
    const char *digits = upper ? "0123456789ABCDEF"
                                : "0123456789abcdef";
    if (n == 0) { uart1_putchar('0'); return 1; }
    while (n) { buf[i++] = digits[n % base]; n /= base; }
    int len = i;
    while (i > 0) uart1_putchar(buf[--i]);
    return len;
}

static int put_int(int n) {
    int len = 0;
    if (n < 0) { uart1_putchar('-'); n = -n; len = 1; }
    return len + put_uint((unsigned)n, 10, 0);
}

int printf(const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    int n = 0;

    for (; *fmt; fmt++) {
        if (*fmt != '%') {
            uart1_putchar(*fmt);
            n++;
            continue;
        }

        fmt++;
        switch (*fmt) {
        case 'd': case 'i': n += put_int(va_arg(ap, int));              break;
        case 'u':           n += put_uint(va_arg(ap, unsigned), 10, 0); break;
        case 'x':           n += put_uint(va_arg(ap, unsigned), 16, 0); break;
        case 'X':           n += put_uint(va_arg(ap, unsigned), 16, 1); break;
        case 's': {
            const char *s = va_arg(ap, const char *);
            while (*s) { uart1_putchar(*s++); n++; }
            break;
        }
        case 'c': uart1_putchar((char)va_arg(ap, int)); n++; break;
        case '%': uart1_putchar('%');                    n++; break;
        default:  uart1_putchar('%'); uart1_putchar(*fmt); n += 2; break;
        }
    }

    va_end(ap);
    return n;
}


/* ============================================================
   scanf
   ============================================================ */

static int is_space(char c) {
    return c == ' ' || c == '\t' || c == '\r' || c == '\n';
}

/*
 * Read one whitespace-delimited token into buf[0..max-1] with echo.
 *
 * - Leading whitespace is consumed silently.
 * - Printable characters are echoed as they are typed.
 * - Backspace (0x08) or DEL (0x7F) erases the last character using the
 *   terminal sequence "\b \b" (move left, overwrite with space, move left).
 * - CR ('\r') ends input and echoes "\r\n" so the cursor moves to a new line.
 * - LF ('\n') also ends input (for hosts that send LF only).
 *
 * Returns the number of characters stored (excluding the null terminator).
 */
static int read_token(char *buf, int max) {
    int i = 0;
    char c;

    do { c = uart1_getchar(); } while (is_space(c));

    while (1) {
        if (c == '\r' || c == '\n') {
            uart1_puts("\r\n");
            break;
        }

        if (c == '\b' || c == 0x7F) {
            if (i > 0) {
                i--;
                uart1_puts("\b \b");
            }
        } else if (c >= 0x20 && c < 0x7F && i < max - 1) {
            buf[i++] = c;
            uart1_putchar(c);
        }

        c = uart1_getchar();
    }

    buf[i] = '\0';
    return i;
}

static int parse_dec(const char *s, unsigned *out) {
    unsigned val = 0;
    if (!*s) return 0;
    for (; *s; s++) {
        if (*s < '0' || *s > '9') return 0;
        val = val * 10u + (unsigned)(*s - '0');
    }
    *out = val;
    return 1;
}

static int parse_hex(const char *s, unsigned *out) {
    unsigned val = 0;
    if (s[0] == '0' && (s[1] == 'x' || s[1] == 'X')) s += 2;
    if (!*s) return 0;
    for (; *s; s++) {
        unsigned d;
        if      (*s >= '0' && *s <= '9') d = (unsigned)(*s - '0');
        else if (*s >= 'a' && *s <= 'f') d = (unsigned)(*s - 'a') + 10u;
        else if (*s >= 'A' && *s <= 'F') d = (unsigned)(*s - 'A') + 10u;
        else return 0;
        val = (val << 4) | d;
    }
    *out = val;
    return 1;
}

int scanf(const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    int matched = 0;

    for (; *fmt; fmt++) {
        if (*fmt != '%') continue;

        fmt++;
        char tok[32];

        switch (*fmt) {
        case 'd': case 'i': {
            read_token(tok, sizeof(tok));
            int neg = (tok[0] == '-');
            unsigned val = 0;
            if (parse_dec(neg ? tok + 1 : tok, &val)) {
                *va_arg(ap, int *) = neg ? -(int)val : (int)val;
                matched++;
            }
            break;
        }
        case 'u': {
            read_token(tok, sizeof(tok));
            unsigned val = 0;
            if (parse_dec(tok, &val)) {
                *va_arg(ap, unsigned *) = val;
                matched++;
            }
            break;
        }
        case 'x': case 'X': {
            read_token(tok, sizeof(tok));
            unsigned val = 0;
            if (parse_hex(tok, &val)) {
                *va_arg(ap, unsigned *) = val;
                matched++;
            }
            break;
        }
        case 's':
            if (read_token(va_arg(ap, char *), 32) > 0)
                matched++;
            break;
        case 'c': {
            char c;
            do { c = uart1_getchar(); } while (is_space(c));
            uart1_putchar(c);
            *va_arg(ap, char *) = c;
            matched++;
            break;
        }
        default: break;
        }
    }

    va_end(ap);
    return matched;
}
