#ifndef INCLUDE_CUSTOM_CODEGEN
#define INCLUDE_CUSTOM_CODEGEN

// #define CAT(a, ...) CCG_PRIMITIVE_CAT(a, __VA_ARGS__)
#define CCG_PRIMITIVE_CAT(a, ...) a ## __VA_ARGS__

#define EXCEPTION_CHECK_N(x, n, ...) n
#define EXCEPTION_CHECK(...) EXCEPTION_CHECK_N(__VA_ARGS__, USUAL_HANDLING,)
#define DEFAULT_EXCEPTION SPECIAL_PROC(~)
#define SPECIAL_PROC(x) x, EXCEPTION_HANDLING,
#define SPECIAL_EXCEPTION(x) 1, x

#define HANDLING(x) EXCEPTION_CHECK(CCG_PRIMITIVE_CAT(EXCEPTION_, x))

/* 
 * after including this file, define exceptions and usual handling:

#define EXCEPTION_asd SPECIAL_EXCEPTION({ int baz; printf("Exceptional exception handling\n"); })
#define EXCEPTION_def DEFAULT_EXCEPTION
#define EXCEPTION_xxxx SPECIAL_EXCEPTION({ int baz2; printf("Exceptional exception handling #2\n"); })
#define USUAL_HANDLING { int usual; printf("This is business as usual\n"); }
#define EXCEPTION_HANDLING { int bar; printf("This is a default exception\n"); }

and then code-generate:

HANDLING(asd)
HANDLING(def)
HANDLING(xxxx)
HANDLING(whatever)
HANDLING(some_other_whatever)

*/

/* a bit of kung-fu borrowed from https://github.com/pfultz2/Cloak/wiki/C-Preprocessor-tricks,-tips,-and-idioms */

#define CCG_ICCG_IF(c) CCG_PRIMITIVE_CAT(CCG_ICCG_IF_, c)
#define CCG_ICCG_IF_0(t, ...) __VA_ARGS__
#define CCG_ICCG_IF_1(t, ...) t

#define CCG_COMPL(b) CCG_PRIMITIVE_CAT(CCG_COMPL_, b)
#define CCG_COMPL_0 1
#define CCG_COMPL_1 0

#define CCG_CHECK_N(x, n, ...) n
#define CCG_CHECK(...) CCG_CHECK_N(__VA_ARGS__, 0,)
#define CCG_PROBE(x) x, 1,

#define CCG_NOT(x) CCG_CHECK(CCG_PRIMITIVE_CAT(CCG_NOT_, x))
#define CCG_NOT_0 CCG_PROBE(~)

#define CCG_BOOL(x) CCG_COMPL(CCG_NOT(x))
#define CCG_IF(c) CCG_ICCG_IF(CCG_BOOL(c))

/* test if x is empty, then return ea, else return nea */
#define CCG_TEST_EMPTY(x, ea, nea) _CCG_TEST_EMPTY_SELECT(x, 0, ea, nea)
#define _CCG_TEST_EMPTY_SELECT(x, y, ea, nea) CCG_ICCG_IF(CCG_BOOL(CCG_PRIMITIVE_CAT(x, y)))(nea, ea)

/* test if x is empty, then call ea(a1, a2), else call nea(a1, a2) */
#define CCG_TEST_EMPTY_CB2(x, ea, nea, a1, a2) _CCG_TEST_EMPTY_SELECT_CB2(x, 0, ea, nea, a1, a2)
#define _CCG_TEST_EMPTY_SELECT_CB2(x, y, ea, nea, a1, a2) CCG_ICCG_IF(CCG_BOOL(CCG_PRIMITIVE_CAT(x, y)))(nea, ea)(a1, a2)




#endif
