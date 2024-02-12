#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define TMin INT_MIN
#define TMax INT_MAX

#include "btest.h"
#include "bits.h"

test_rec test_set[] = {

 {"tmin", (funct_t) tmin, (funct_t) test_tmin, 0, "! ~ & ^ | + << >>", 1, 1,
  {{TMin, TMax},{TMin,TMax},{TMin,TMax}}},
 {"bitAnd", (funct_t) bitAnd, (funct_t) test_bitAnd, 2, "| ~", 4, 1,
  {{TMin, TMax},{TMin,TMax},{TMin,TMax}}},
 {"negate", (funct_t) negate, (funct_t) test_negate, 1,
    "! ~ & ^ | + << >>", 2, 1,
  {{TMin, TMax},{TMin,TMax},{TMin,TMax}}},
 {"isEqual", (funct_t) isEqual, (funct_t) test_isEqual, 2,
    "! ~ & ^ | + << >>", 2, 2,
  {{TMin, TMax},{TMin,TMax},{TMin,TMax}}},
 {"addOK", (funct_t) addOK, (funct_t) test_addOK, 2,
    "! ~ & ^ | + << >>", 14, 3,
  {{TMin, TMax},{TMin,TMax},{TMin,TMax}}},
 {"signMag2TwosComp", (funct_t) signMag2TwosComp, (funct_t) test_signMag2TwosComp, 1, "! ~ & ^ | + << >>", 10, 4,
  {{TMin, TMax},{TMin,TMax},{TMin,TMax}}},
 {"satAdd", (funct_t) satAdd, (funct_t) test_satAdd, 2,
    "! ~ & ^ | + << >>", 25, 4,
  {{TMin, TMax},{TMin,TMax},{TMin,TMax}}},
 {"dividePower2", (funct_t) dividePower2, (funct_t) test_dividePower2, 2,
    "! ~ & ^ | + << >>", 8, 3,
  {{TMin, TMax},{0,30},{TMin,TMax}}},
 {"replaceByte", (funct_t) replaceByte, (funct_t) test_replaceByte, 3,
    "! ~ & ^ | + << >>", 10, 3,
  {{TMin, TMax},{0,3},{0,255}}},
 {"floatAbsVal", (funct_t) floatAbsVal, (funct_t) test_floatAbsVal, 1,
    "$", 5, 2,
     {{1, 1},{1,1},{1,1}}},
 {"floatIsEqual", (funct_t) floatIsEqual, (funct_t) test_floatIsEqual, 2,
    "$", 19, 3,
     {{1, 1},{1,1},{1,1}}},
 {"floatPower2", (funct_t) floatPower2, (funct_t) test_floatPower2, 1,
    "$", 16, 4,
     {{TMin,TMax},{TMin,TMax},{TMin,TMax}}},
  {"", NULL, NULL, 0, "", 0, 0,
   {{0, 0},{0,0},{0,0}}}
};
