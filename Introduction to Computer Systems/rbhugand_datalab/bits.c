/* REMEMBER:
 * - This is the only file that you need to edit!
 * - Declare variables only at the beginning of a function (as in C89).
 * - Do not include <stdio.h> header (it confuses dlc)
 * - Check correctness with ./btest
 * - Check operator constraints with ./dlc bits.c
 * - Run ./grade before you commit/push your solution
 */

/*
 * tmin - return minimum two's complement integer
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 1
 *   Rating: 1
 */
int tmin(void) {
  return 1<<31;
}

/*
 * bitAnd - x&y using only ~ and |
 * (tip: always remember De Morgan's laws!)
 *   Example: bitAnd(6, 5) = 4
 *   Legal ops: ~ |
 *   Max ops: 4
 *   Rating: 1
 */
int bitAnd(int x, int y) {
  return ~(~x | ~y);
}

/*
 * negate - return -x
 * (tip: remember the definition of two's complement!)
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 2
 *   Rating: 1
 */
int negate(int x) {
  return ~x + 1;
}

/*
 * isEqual - return 1 if x == y, and 0 otherwise
 * (tip: which bitwise op computes the difference?)
 *   Examples: isEqual(5,5) = 1, isEqual(4,5) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 2
 *   Rating: 2
 */
int isEqual(int x, int y) {
  return !(x^y);
}

/*
 * addOK - Determine if can compute x+y without overflow
 *   Example: addOK(0x80000000,0x80000000) = 0,
 *            addOK(0x80000000,0x70000000) = 1,
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 14
 *   Rating: 3
 */
int addOK(int x, int y) {

  // int a = x>>31;
  // int b = y>>31;
  // int sum = x+y;
  // int c = sum>>31;
  // return (!!(a^b))|(!(a^c)&!(b^c));

  int sum = x + y;

  return (!!((x^y)>>31)) | (!((x^sum)>>31) & !((y^sum)>>31) );


}

/*
 * signMag2TwosComp - Convert from sign-magnitude to two's complement
 *   where the MSB is the sign bit
 *   Example: signMag2TwosComp(0x80000005) = -5.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 10
 *   Rating: 4
 */
int signMag2TwosComp(int x) {

  int a = 1<<31;

  int abs_x = ~a & x;

  int sign_x = x>>31;

  return (sign_x & (~abs_x + 1)) | (~sign_x & abs_x);

  // return 2;
}

/*
 * satAdd - adds two numbers but when positive overflow occurs, returns
 *          maximum possible value, and when negative overflow occurs,
 *          it returns minimum negative value.
 *   Examples: satAdd(0x40000000,0x40000000) = 0x7fffffff
 *             satAdd(0x80000000,0xffffffff) = 0x80000000
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 25
 *   Rating: 4
 */
int satAdd(int x, int y) {

  
  int sum = x+y;

  int sum_sign = sum>>31; //sum_sign

  int overflow_check = ((x^sum)>>31 & (y^sum)>>31);
  
  int positive_overflow_value =  (1<<31);

  int res1 = (sum_sign & ~(positive_overflow_value)) | (~sum_sign & positive_overflow_value); 

  return (overflow_check & res1) | (~overflow_check & sum);





 
  
}

/*
 * dividePower2 - Compute x/(2^n), for 0 <= n <= 30
 *  Round toward zero
 *   Examples: dividePower2(15,1) = 7, dividePower2(-33,4) = -2
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 3
 */
int dividePower2(int x, int n) {

  int sign = x>>31;

  int bias = (sign & ((1<<n)+~0));

  return ((x + bias))>>n;
  
}

/* 
 * replaceByte(x,n,c) - Replace byte n in x with c
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: replaceByte(0x12345678,1,0xab) = 0x1234ab78
 *   You can assume 0 <= n <= 3 and 0 <= c <= 255
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 10
 *   Rating: 3
 */
int replaceByte(int x, int n, int c) {

  int shift = n<<3;

  int mask = 0xFF;

  int mask_shifted = mask<<shift;

  int num1 = (~mask_shifted) & x;

  int c_shifted = c<<shift;

  return num1 | c_shifted;

   
  
}

/*
 * floatAbsVal - Return bit-level equivalent of absolute value of f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument..
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 5
 *   Rating: 2
 */
unsigned floatAbsVal(unsigned uf) {

  int remaining_bits = (uf) & (0x7fffffff);

  int exp_bits = remaining_bits>>23;

  if(exp_bits == 255)
  {
    if((remaining_bits<<9) != 0){

      return uf;

    }
  }

  return remaining_bits;



  
}

/*
 * floatIsEqual - Compute f == g for floating point arguments f and g.
 *   Both the arguments are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   If either argument is NaN, return 0.
 *   +0 and -0 are considered equal.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 19
 *   Rating: 3
 */
int floatIsEqual(unsigned uf, unsigned ug) {

  int remaining_bits = (uf) & (0x7fffffff);

  int exp_bits = remaining_bits>>23;

  int remaining_bits_ug = (ug) & (0x7fffffff);

  int exp_bits_ug = remaining_bits_ug>>23;

  if(exp_bits == 255)
  {
    if((remaining_bits<<9) != 0){

      return 0;

    }
  }

  if(exp_bits_ug == 255)
  {
    if((remaining_bits_ug<<9) != 0){

      return 0;

    }
  }

  if(!remaining_bits && !remaining_bits_ug)
  {
    return 1;
  }



  return uf == ug;
}

/*
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 *
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. Also if, while
 *   Max ops: 16
 *   Rating: 4
 */
unsigned floatPower2(int x) {

  // int excess_bits = (x+127)<<23;

  // if(x < -149){
  //   return 0;
  // }
  // if(x>128)
  // {
  //   return 0x7F800000;
  // }
  // if(x >= -149 && x <= -127)
  // {
  //  int  x_complement = ~x + 1;

  //  return (x_complement+127)<<23;

  // }

  // return excess_bits;

  //x is too big.

  if(x>128)
  {
    return 0x7F800000;
  }
  //x is normal range

  if(x > -127 )
  {
    int excess_bits = (x+127)<<23;

    return excess_bits;
  }

  if(x > -150)
  {
    int excess_bits = 1<<(149+x);

    return excess_bits;
  }

  

  return 0;

}
