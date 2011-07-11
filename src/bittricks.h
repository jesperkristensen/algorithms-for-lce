#ifndef _BITTRICKS_H_
#define _BITTRICKS_H_

// multiplication, division and modulo bittricks for uint32

// Declare auxiliary variables for variable "b", supporting MUL and DIV.
#define S_DECL(b) uint32 b##_sham;

// Declare auxiliary variables for variable "b", supporting MUL, DIV and MOD.
#define S_DECL_MOD(b) S_DECL(b) uint32 b##_mask;

// Change "b" to the smallest power of two, which is greater than "b", and
// initialize auxiliary variables declared with S_DECL.
#define S_PREP(b) b##_sham = 0;\
    while (1u<<b##_sham < b)\
        b##_sham++;\
    b = 1u<<b##_sham;

// Change "b" to the smallest power of two, which is greater than "b", and
// initialize auxiliary variables declared with S_DECL_MOD.
#define S_PREP_MOD(b) S_PREP(b) b##_mask = b - 1;

// Modulo operation, where "a" is any arithmetic expression, and "b" is a
// variable prepared with S_PREP_MOD.
#define S_MOD(a, b) ((a)&b##_mask)

// Multiplication, where "a" is any arithmetic expression, and "b" is a
// variable prepared with S_PREP or S_PREP_MOD.
#define S_MUL(a, b) ((a)<<b##_sham)

// Division, where "a" is any arithmetic expression, and "b" is a
// variable prepared with S_PREP or S_PREP_MOD.
#define S_DIV(a, b) ((a)>>b##_sham)

// Clear auxiliary variables initialized with S_DECL.
#define S_CLEAR(b) b##_sham = 0;

// Clear auxiliary variables initialized with S_DECL_MOD.
#define S_CLEAR_MOD(b) S_CLEAR(b) b##_mask = 0;

#endif
