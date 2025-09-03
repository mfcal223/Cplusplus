# CPP Module 2 - ex01 - Annex I

## Float number representation

Ther is a limit at the ability for binary and fixed-point numbers to represent all possible fraction (real numbers). 
There are multiple choices for this numbers can be represented, but the floating-point representation standardized in IEEE 754 is the most common choice.
A float is just a number with a fractional part stored in a format that supports decimals (technically: scientific notation in base 2 with limited precision). 

It is not extremely mandatory to master all the internal float representation details for CPP02, but DO watch this video to handle the basic key concepts

* https://www.youtube.com/watch?v=bbkcEiUjehk

---

The information in this section was obtain from these articles. 
- [Floating point number representation](https://www.cprogramming.com/tutorial/floating_point/understanding_floating_point_representation.html)
- [Understanding and Using Floating Point Numbers](https://www.cprogramming.com/tutorial/floating_point/understanding_floating_point.html)
- [Printing floating point numbers](https://www.cprogramming.com/tutorial/floating_point/understanding_floating_point_printing.html)  
- [Floating point representation Basic concepts](https://www.geeksforgeeks.org/digital-logic/floating-point-representation-basics/)

`EXCELLENT VIDEO !`
["How floating-Point Numbers Are Represented"](https://www.youtube.com/watch?v=bbkcEiUjehk)
---

### Key Concepts

Floating-point (FP) numbers are prevalent in programming, but they are often counterintuitive. They create an illusion of "real" numbers with decimals and vast magnitudes, but in reality, a 4-byte floating-point number can hold fewer distinct values than a 4-byte integer. This is because their internal representation is not straightforward, unlike integers where bits are interpreted literally as a binary number.  

A common observation in C/C++ is that floating-point numbers that look the same may not satisfy the **==** test, leading new programmers to avoid using **==** for floats.  

#### Comparing Integers and Floats:
* `Integers:`  
    * Enjoy complete accuracy: "2" is exactly 2, and operations are exact (provided no overflow).  
    * Lack precision: They cannot track fractional parts (e.g., 5/2 and 4/2 both yield 2, losing information).  
    * Analogy: Building with "chunky" bricks – perfect for cubes, but not for spheres.  
  
* `Floating-Point Numbers:`  
    * Are the exact opposite of integers regarding accuracy and precision.  
    * Have good precision: They don't deliberately discard information. With enough bits, FP calculations could theoretically be reversed.
    * Have poor accuracy: In many cases, there's literally no hope of a floating-point answer matching the correct answer bit for bit.  
    * Analogy: Silly putty – good for complex, curved shapes, but struggles to form a precise target shape like a perfect cube.  


The fundamental reason for poor accuracy: Not every fraction can be represented exactly in binary (just like 1/3 cannot be represented perfectly with a finite number of decimal digits). This means that results are likely to be wrong by at least a little bit due to "roundoff errors".  

---

### Floating-Point Representation: The IEEE-754 Standard

Floating-point representation helps computers handle real numbers with a large range of values, both very small and very large. These formats are based on scientific notation, with a sign bit, exponent, and mantissa.  

In C/C++, the ***IEEE-754 standard*** defines how numbers are stored in memory:

> 1. Components:  
  
An IEEE-754 `float (4 bytes)` or `double (8 bytes)` has **3 main parts**:  
	
* Sign bit `(s)`: A single bit tha determines if the number is positive (0) or negative (1).
* Exponent `(e)`: Gives the order of magnitude (8 bits for simple float, 11 for double). It determines how large or small it is, by indicating the position of the binary point.  
* Mantissa `(m)`(or Significand) : Specifies the actual digits of the number (23 bits for float, 52 for double).
  
> 2. Bit Layout (Single-Precision Float): `seeeeeeeemmmmmmmmmmmmmmmmmmmmmmm`
  
* `s` = sign bit (bit 31)
* `e` = exponent (bits 30-23)
* `m` = mantissa (bits 22-0)

> 3. Value Calculation: 

* The number's value is generally (sign ? -1:1) * 2^(exponent) * 1.(mantissa bits).  

```
value = (−1)^sign x (1.fraction) x 2^(exponent−127)
```

* This involves binary fractions, where 0.1 (binary) means 1/2 (decimal).

> 4. Shift-127 Exponent Encoding (for Single-Precision):  

* The exponent bits (e) are not a direct representation of the exponent.
In simple float numbers, the exponent uses 8 bits to store its value, which can represent numbers from 0  up to 255.  
To represent negative exponents, we need to shift this range to allow negative exponents too.  

* To do that, it will be consider that the number at the middle of the range 0-255, meaning 127 (0x7f), will represent an exponent of 0. 
Numbers > 0 will be > 127 `(max 127)`. | Numbers < 0 (negative) will be < 127 `(min -126)`.  

* The actual exponent is calculated as `[eeeeeeee - 127]`. ==> this is known as "Shift-127"

> 5. "1.m" Representation (Normalized Numbers):
    
* Each bit of the mantissa represents some fractional place that let us represent a number equal or bigger than 1 but smaller than 2.
* Since all of this numbers start with "1". we don´t actually need to store the 1.  
* To save bits and ensure a unique representation, an implied leading "1" is assumed to be to the left of the binary decimal point in the mantissa.
* For example, if you write a number in binary and shift the decimal point after the first '1', you only need to store the fractional part (the 'm' bits) and adjust the exponent to reflect the shift.  
* This means  that even though we're using 23 bits to store the mantissa, we can actually represent  the mantissa with 24 bits of precision.  

---

### EXAMPLES

> Example 1: **fraction 9/2 => decimal 4.5**

1. Represent in binary = **100.1**  
2. Normalized (only one 1 before the point): 100.1 >>> `1.001 x 2^2`
    - Unbiased Exponent = **2**
3. Build IEEE-754 fields (float32)
- Sign = **0 (positive)**
- Biased Exponent = 2 + 127 =  129 = `10000001`
- Fraction bits (digits after the "."): 
    - for 1.001 = `.001`
    - filling them in 23 bits (mantissa): `00100000000000000000000`
- Put everything together:

```r
0 | 10000001 | 00100000000000000000000
```
  
4. Convert **32-bit IEEE-754 float bit pattern** to **float32 Hexadecimal** 

Method: Group into nibbles (4 bits) and map to hex to obtain a float32

```yaml
0 10000001 00100000000000000000000
^ ^^^                              (we’ll build 8 groups of 4 bits)

Nibble 1: 0100  -> 0x4 -> 4
Nibble 2: 0000  -> 0x0 -> 0
Nibble 3: 1001  -> 0x9 -> 9
Nibble 4: 0000  -> 0x0 -> 0
Nibble 5: 0000  -> 0x0 -> 0
Nibble 6: 0000  -> 0x0 -> 0
Nibble 7: 0000  -> 0x0 -> 0
Nibble 8: 0000  -> 0x0 -> 0

Combine: 0x 4 0 9 0 0 0 0 0 → 0x40900000 ✅
```

> IMPORTANT: DO NOT CONFUSE THE HEX **FLOAT32** TYPE WITH THE UNSIGNED INT HEXADECIMAL.     
[IEEE-754 single -> float32 (hex)] ≠  [unsigned int hex (int -> hex)]   

> Example 2: **Decimal 0.1**  

1. In binary (repreating pattern):  `0.0001100110011…₂`  
2. Normalized (only one 1 before the point): `1.100110011…₂ x 2^(-4)`  
    - Unbised Exponent = **(-4)**
3. Build IEEE-754 fields (float32)
- sign = 0 (+)
- exponent : -4 + 127 = 123  → in binary: `01111011`
- mantissa (fill 23 bits after the leading 1): `10011001100110011001101`

Put together:  

```r
sign | exponent  | fraction (23 bits)
 0    01111011     1001 1001 1001 1001 1001 101
```

4. Convert 32 bits to float32
```yaml

0 01111011 10011001100110011001101
= 0011 1101 1100 1100 1100 1100 1100 1101
=   3    D    C    C    C    C    C    D
→ 0x3DCCCCCD

Result: 0.1f (float32) = 0x3DCCCCCD.
(As a number, that float equals approximately 0.10000000149011612.)
```

Here is a useful link to a [IEEE-754 Floating Point Converter](https://www.h-schmidt.net/FloatConverter/IEEE754.html) to check this results.

---

### Special Cases in Representation  
IEEE-754 includes special bit patterns for specific values:  

* **Zero (0.0)**: Represented when all bits are zero (the sign bit is irrelevant). `0x00000000 for 0.0`    

* Positive/Negative **Infinity** (+/-inf): Occurs when all exponent bits are set (0xff for single-precision), and all mantissa bits are zero. 0x7f800000 for +inf, 0xff800000 for -inf. These values tend to behave as expected in calculations (e.g., inf + 1 = inf).  
  
* **Not-a-Number (NaN)/ Invalid number**: Occurs when all exponent bits are set, and any mantissa bits are also set. 0x7fc00000 or 0x7ff00000 for +NaN. Used for undefined or non-sensical results (e.g., infinity times zero).  
  
* **Denormalized Numbers (Subnormal Numbers)**: A special case for very small numbers.  
	* When the exponent bits are all zero (meaning the encoded exponent is the minimum possible, e.g., -126 for single-precision), but mantissa bits are not all zero, `the implied "1." is no longer assumed`.   
    * This allows representing numbers smaller than 2^-126.  
    * However, these "extra-small numbers" sacrifice precision, with the absolute smallest having only a single bit of precision.  

---

### Practical Implications for C/C++ Programming:
1. Equality (==): Never use == to compare floating-point numbers directly. Due to inherent inaccuracy and rounding, two mathematically equal floats might not match bit-for-bit. Instead, compare if the absolute difference between them is less than a small tolerance (e.g., fabs((a)-(b)) < EPSILON). However, even this approach has caveats; the EPSILON should relate to the desired number of significant digits, not an absolute magnitude, as precision is relative to the number's scale.  
2. Overflow:  
* Unlike integers, which wrap around on overflow, floats conveniently become +/-inf. This can be useful for detecting overflow in integer math.  
* Avoid needless intermediate overflows: A final result might be representable, but intermediate calculations could exceed the maximum float value. For example, sqrt(re*re + im*im) for large re or im can cause re*re to overflow to infinity, even if the final magnitude is well within range. It's better to rearrange the formula to re*sqrt(1.0 + (im/re)^2) or im*sqrt(1.0 + (re/im)^2) by normalizing against the larger component to prevent intermediate overflow.  
* Loss of Significance:  
    - Occurs when subtracting two very close numbers. The implied leading '1's and common mantissa bits cancel out, leaving fewer significant bits in the result and drastically reducing precision. You should actively look for and rearrange computations to avoid such subtractions.  
    - Also a problem when summing a series of numbers if small terms are added to much larger ones. If a small term is less than the float's epsilon relative to a large term, it might be completely swallowed (e.g., 1.0 + 1e-8 remains 1.0 in single precision). If many small terms contribute significantly, sorting them from smallest to largest before summing can help preserve accuracy.  
* Casting: Be cautious when casting floats to integers. A 32-bit float only offers about 7 decimal digits of precision, which might not be enough to preserve a large 32-bit integer (which can represent any 9-digit number).   Doubles, however, usually have enough precision for 32-bit integers.  
* Don't Forget Integers: For rational numbers or precise fractions, it's often better to store them as integer numerators and denominators to avoid floating-point issues entirely.  

---

### 📌 Note — The f suffix on numeric literals (C++)

In C/C++, a decimal literal like 4.5 or 0.1 is a **double** by default (64-bit).  

Adding the `f suffix` (e.g., 4.5f, 0.1f) makes the literal a **float** (32-bit, IEEE-754 single precision).  

This matters for:  
- Overload resolution / constructor selection: Fixed(42.42f) clearly calls the Fixed(float) ctor in ex01.
- Precision & rounding: float has ~7 decimal digits of precision; double has ~15–17. Many decimals (like 0.1) can’t be represented exactly, so 0.1f and 0.1 have different bit patterns (slightly different values).  
- Downstream quantization to fixed-point: in ex01, the float you pass gets scaled and rounded to the 1/256 grid; starting from float vs double can produce minutely different _raw values.  

- Examples  
* 4.5f → float; 4.5 → double  
* 0.1f (≈ 0.10000000149) vs 0.1 (≈ 0.10000000000000000555)  

`Rule of thumb: use the f suffix in this module when you intend to call the Fixed(float) constructor explicitly.`