/* WARNING: Do not include any other libraries here,
 * otherwise you will get an error while running test.py
 * You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.
 *
 * Using printf will interfere with our script capturing the execution results.
 * At this point, you can only test correctness with ./btest.
 * After confirming everything is correct in ./btest, remove the printf
 * and run the complete tests with test.py.
 */

 /*
 * bitAnd - x & y using only ~ and |
 * Example: bitAnd(4, 5) = 4
 * Legal ops: ~ |
 * Max ops: 7
 * Difficulty: 1
 */
int bitAnd(int x, int y) {
    return ~(~x|~y);
}

/*
 * bitXor - x ^ y using only ~ and &
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 7
 *   Difficulty: 1
 */
int bitXor(int x, int y) {
    return ~(~x&~y)&(~(x&y));
}

/*
 * samesign - Determines if two integers have the same sign.
 *   0 is not positive, nor negative
 *   Example: samesign(0, 1) = 0, samesign(0, 0) = 1
 *            samesign(-4, -5) = 1, samesign(-4, 5) = 0
 *   Legal ops: >> << ! ^ && if else &
 *   Max ops: 12
 *   Difficulty: 2
 *
 * Parameters:
 *   x - The first integer.
 *   y - The second integer.
 *
 * Returns:
 *   1 if x and y have the same sign , 0 otherwise.
 */
int samesign(int x, int y) {
    if(x){
        if(y) return !((x^y)>>31);
        return 0;
    }
    return !y;
}

/*
 * logtwo - Calculate the base-2 logarithm of a positive integer using bit
 *   shifting. (Think about bitCount)
 *   Note: You may assume that v > 0
 *   Example: logtwo(32) = 5
 *   Legal ops: > < >> << |
 *   Max ops: 25
 *   Difficulty: 4
 */
int logtwo(int v) {
    int res = 0, a;
    a = (v>0xFFFF)<<4;
    res = res | a;
    v = v >> a;

    a = (v>0xFF)<<3;
    res = res | a;
    v = v >> a;
    
    a = (v>0xF)<<2;
    res = res | a;
    v = v >> a;
    
    a = (v>3)<<1;
    res = res | a;
    v = v >> a;
    
    a = v>1;
    res = res | a;
    return res;
}

/*
 *  byteSwap - swaps the nth byte and the mth byte
 *    Examples: byteSwap(0x12345678, 1, 3) = 0x56341278
 *              byteSwap(0xDEADBEEF, 0, 2) = 0xDEEFBEAD
 *    Note: You may assume that 0 <= n <= 3, 0 <= m <= 3
 *    Legal ops: ! ~ & ^ | + << >>
 *    Max ops: 17
 *    Difficulty: 2
 */
int byteSwap(int x, int n, int m) {
    n = n << 3,m = m << 3;
    int t = ((x>>n)^(x>>m))&255;
    x = x^(t<<n)^(t<<m);
    return x;
}

/*
 * reverse - Reverse the bit order of a 32-bit unsigned integer.
 *   Example: reverse(0xFFFF0000) = 0x0000FFFF reverse(0x80000000)=0x1 reverse(0xA0000000)=0x5
 *   Note: You may assume that an unsigned integer is 32 bits long.
 *   Legal ops: << | & - + >> for while ! ~ (You can define unsigned in this function)
 *   Max ops: 30
 *   Difficulty: 3
 */
unsigned reverse(unsigned v) {
    unsigned low,high;
    low = v&0x0000FFFF, high = v&0xFFFF0000;
    v = low<<16|high>>16;
    
    low = v&0x00FF00FF, high = v&0xFF00FF00;
    v = low<<8|high>>8;
    
    low = v&0x0F0F0F0F, high = v&0xF0F0F0F0;
    v = low<<4|high>>4;
    
    low = v&0x33333333, high = v&0xCCCCCCCC;
    v = low<<2|high>>2;
    
    low = v&0x55555555, high = v&0xAAAAAAAA;
    v = low<<1|high>>1;
    
    return v;
}

/*
 * logicalShift - shift x to the right by n, using a logical shift
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Note: You can assume that 0 <= n <= 31
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Difficulty: 3
 */
int logicalShift(int x, int n) {
    int a = x&2147483647,b = (x>>31&1);
    return (b << (31^n)) | a >> n;
}

/*
 * leftBitCount - returns count of number of consective 1's in left-hand (most) end of word.
 *   Examples: leftBitCount(-1) = 32, leftBitCount(0xFFF0F0F0) = 12,
 *             leftBitCount(0xFE00FF0F) = 7
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 50
 *   Difficulty: 4
 */
int leftBitCount(int x) {
    int res=0,v,t;
    v = x&0xFFFF0000;
    t = !~(v|0x0000FFFF);
    res += t<<4;
    x >>= ((!t)<<4);

    v = x&0xFFFFFF00;
    t = !~(v|0x000000FF);
    res += t<<3;
    x >>= ((!t)<<3);
    
    v = x&0xFFFFFFF0;
    t = !~(v|0x0000000F);
    res += t<<2;
    x >>= ((!t)<<2);
    
    v = x&0xFFFFFFFC;
    t = !~(v|0x00000003);
    res += t<<1;
    x >>= ((!t)<<1);

    v = x&0xFFFFFFFE;
    t = !~(v|0x00000001);
    res += t;
    x >>= (!t);

    v = x;//x&0xFFFFFFFF
    t = !~v;
    res += t;
    return res;
}

/*
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but it is to be interpreted as
 *   the bit-level representation of a single-precision floating point values.
 *   Legal ops: if else while for & | ~ + - >> << < > ! ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned float_i2f(int x) {
    if(!x) return 0;
    unsigned S=0;
    int mx=-1;
    if(x>>31) S=0x80000000,x = -x;
    unsigned y=x;
    while(y) y>>=1,mx++;
    x-=1u<<mx;
    if(mx<=23) x<<=(23-mx); 
    else{
        unsigned now=mx-23,low=x&((1u<<now)-1);
        unsigned key = 1u<<(now-1);
        x >>= now;
        if((low+(x&1))>key){
            x += 1;
        }
        if(x>>23) mx++,x=0;
    }
    return S|((mx+127)<<23)|x;
}

/*
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: & >> << | if > < >= <= ! ~ else + ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatScale2(unsigned x) {
    return 0;
}

/*
 * float64_f2i - Convert a 64-bit IEEE 754 floating-point number to a 32-bit signed integer.
 *   The conversion rounds towards zero.
 *   Note: Assumes IEEE 754 representation and standard two's complement integer format.
 *   Parameters:
 *     uf1 - The lower 32 bits of the 64-bit floating-point number.
 *     uf2 - The higher 32 bits of the 64-bit floating-point number.
 *   Returns:
 *     The converted integer value, or 0x80000000 on overflow, or 0 on underflow.
 *   Legal ops: >> << | & ~ ! + - > < >= <= if else
 *   Max ops: 60
 *   Difficulty: 3
 */
int float64_f2i(unsigned uf1, unsigned uf2) {
    return 2;
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
 *   Legal ops: < > <= >= << >> + - & | ~ ! if else &&
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatPower2(int x) {
    return 2;
}
