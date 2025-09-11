/**
 * PTOOLS typedefs for common C types.
 *
 * I think the way that programming languages tend to have signed as the
 * integer default, and unsigned as a modifier, is unfathomably stupid,
 * and so here I have corrected it. Also, I am trying to normalize using
 * CS-focused words like byte, word, dword, and qword, instead of the
 * obnoxiously ambiguous int, short, long etc, the first of which is
 * especially problematic because it basically implies that a 32-bit
 * integer type should be the default for ALL numeric computations
 * (including for loops, for god's sake!)
 */

#ifndef __PTOOLS_TYPES_H__
#define __PTOOLS_TYPES_H__

#ifndef __PTOOLS_H__
#error "DO NOT INCLUDE THIS FILE DIRECTLY; USE PTOOLS.H INSTEAD"
#endif

#include <stdint.h>

typedef uint8_t     byte;
typedef uint16_t    word;
typedef uint32_t    dword;
typedef uint64_t    qword;
typedef int8_t      s_byte;
typedef int16_t     s_word;
typedef int32_t     s_dword;
typedef int64_t     s_qword;

#endif //_PTOOLS_TYPES_H__
