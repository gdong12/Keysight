/* mbed Microcontroller Library
 * Copyright (c) 2006-2013 ARM Limited
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#ifndef MBED_DEBUG_H
#define MBED_DEBUG_H
#include "device.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef DEVICE_STDIO_MESSAGES
#include <stdio.h>
#include <stdarg.h>

/** Output a debug message
 *
 * @param format printf-style format string, followed by variables
 */
static inline void debug(const char *format, ...) {
    va_list args;
    va_start(args, format);
    vfprintf(stderr, format, args);
    va_end(args);
}

/** Conditionally output a debug message
 *
 * NOTE: If the condition is constant false (!= 1) and the compiler optimization
 * level is greater than 0, then the whole function will be compiled away.
 *
 * @param condition output only if condition is true (== 1)
 * @param format printf-style format string, followed by variables
 */
static inline void debug_if(int condition, const char *format, ...) {
    if (condition == 1) {
        va_list args;
        va_start(args, format);
        vfprintf(stderr, format, args);
        va_end(args);
    }
}

#else
static inline void debug(const char *format, ...) {}
static inline void debug_if(int condition, const char *format, ...) {}

#endif

#ifdef __cplusplus
}
#endif

#endif
