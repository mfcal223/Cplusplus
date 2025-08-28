# CPP Module 2 

## Real Numbers Representation

Ther is a limit at the ability for binary and fixed-point numbers to represent all possible fraction (real numbers). 
There are multiple choices for this numbers can be represented, but the floating-point representation standardized in IEEE 754 is the most common choice.
A float is just a number with a fractional part stored in a format that supports decimals (technically: scientific notation in base 2 with limited precision). 

It is not extremely mandatory to master all the internal float representation details for CPP02, but DO watch this video to handle the basic key concepts

* https://www.youtube.com/watch?v=bbkcEiUjehk

Afterwards, if possible, do check the [annex I](/home/florencia/proyectos/CPP/Cplusplus/Exercises/CPP_2/cpp_2_floatnumbers.md)
---

## **Fixed-point Number Representation**  

This link explains the math concept clearly: [Fixed-point Number Representation - Berkeley University](https://web.archive.org/web/20231224143018/https://inst.eecs.berkeley.edu/~cs61c/sp06/handout/fixedpt.html)

Some key points:  
1. Floating point numbers are not the only way to represent fractional numbers. Fixed point data type is a valid alternative, specially where performance is more important than precision.   
   
2. A **binary point** is like the **decimal point** in a decimal system. It acts as a divider between the integer and the fractional part of a number.
     
3. As in the decimal system, a binary point represents the coefficient of the term 2^0 = 1.
- All digits (or bits) to the left of the binary point carries a weight of 2^0, 2^1, 2^2, and so on. 
- Digits (or bits) on the right of binary point carries a weight of 2^-1, 2^-2, 2^-3, and so on.
   
4. Given a fixed binary point position, shifting (>> 1) the bit pattern of a number to the right by 1 bit always *divides the number by 2*. 
5. Similarly, shifting a number to the left (<< 1) by 1 bit *multiplies the number by 2*. 
  
6. To define a *fixed point number type* simply implicitly fix the binary point to be at some position of a numeral. This needs 2 parameters:
- `w` width of the number representation (total number of bit),  
- `b` fractional bit (the position of binary point counting from the least significant bit).
- Notation = `fixed<w, b>`

> Example  (1)
  
**fixed<8,3>** denotes an 8-bit fixed-point number with 3 fractional bits.  

pattern ---> `00010.110` = `2.75`

```
| 1*2^1 | 0*2^0 | 1* 2^-1 | 1* 2^-2  |
|-------|-------|---------|----------|
| 2     |   0   |   0.5   |   0.25   |
  
2 + 0 + 0.5 + 0.25 = 2.75
```

> Example (2)

**fixed<8,5>** : denotes an 8-bit fixed-point number with 5 fractional bits.
  
pattern ---> `000.10110` = `0.6875`

```
| 1*2^-1 | 0*2^-2 | 1* 2^-3 | 1* 2^-4 |
|--------|--------|---------|---------|
| 0.5    |   0    |  0.125  |  0.0625  |
  
0.5 + 0.125 + 0.0625 = 0.6875
```

> Using the shift rule: `2.75 >> 1` = `1.375`; `>> 1` again = `0.6875`.

---

## What is the drawback of fixed-point?

The disadvantage of fixed point numberis the trade-off between range and precision, or in other words the loss of range and precision when compare with floating point number representations.  
For example, in a **fixed<8,1>** representation, our fractional part is only precise to a quantum of 0.5.  
We cannot represent number like 0.75. We can represent 0.75 with **fixed<8,2>**, but then we loose range on the integer part.  

```yaml
Let’s compare 8-bit signed fixed-point formats (two’s complement):

fixed<8,1>
step (precision): 2^-1 = 0.5
range: [-64.0, 63.5]
cannot represent: 0.25, 0.75, etc.

fixed<8,5>
step (precision): 2^-5 = 1/32 ≈ 0.03125 (much better precision)
range: [-4.0, 3.96875] (much smaller range)

1. Scenario: You’re measuring a signal that can reach 5.0.

With fixed<8,5>, 5.0 is out of range (max is 3.96875) → you’ll overflow/saturate or wrap, depending on your implementation.

If you switch to fixed<8,1> for range, you lose precision: the closest to π ≈ 3.1416 is either 3.0 or 3.5 (quantization error up to ~0.3584).

2. Accumulation error example (precision loss):
Suppose you need to add 0.2 one hundred times (expected sum = 20.0).

With fixed<8,4> (step = 1/16 = 0.0625), 0.2 must be quantized to 0.1875.
After 100 adds: 18.75 (error = −1.25, a 6.25% shortfall).

With fixed<8,6> (step = 1/64 ≈ 0.015625), 0.2 quantizes to 0.203125.
After 100 adds: 20.3125 (error = +0.3125, a 1.56% overshoot).  
  
Better precision → smaller error, but remember: the higher b gets, the smaller your representable range becomes.
```

Other links:  
https://www.geeksforgeeks.org/computer-organization-architecture/fixed-point-representation/  
https://en.wikipedia.org/wiki/Fixed-point_arithmetic   
