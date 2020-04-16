#pragma once

static inline int _constexpr_assert_failure(const char *msg)
{
    (void) msg;
    // we do 2 things that the compiler will refuse to execute at compile-time
    // (and therefore trigger a compilation error):
    // - define a local static variable
    // - declare the method as non constexpr
    static int i = 0;
    return i;
}

/**
 * Assertion that fails compilation if used in a constexpr context (that is executed at
 * compile-time).
 *
 * Important: you need to ensure the code is executed at compile-time, e.g. by
 * assigning the returned value of a constexpr method (where the assert is used)
 * to a variable marked as constexpr. Otherwise the compiler might silently move
 * execution to runtime.
 *
 * If executed at runtime, it has no effect other than slight runtime overhead.
 */
#define constexpr_assert(expr, msg) \
    if (!(expr)) { \
        _constexpr_assert_failure(msg); \
    }
