# CPP Module 2 - Exercise 01 - Fixed-Point numbers vol 2

## The scale

In the previous exercise, we were introduce to the concept of *fixed-point number representation*, through which a real number can be represented  in a way that the position of the binary (or decimal) point is fixed. It's an alternative to floating-point representation.

**It implicitly converts an integer to a real number by defining a constant relationship between an integer value and its actual real-world value.**   

Example:  
```yaml
if [1.23] is stored as the integer [123], the scale (or scaling factor) is [1/100], which means the stored integer is multiplied by [10^-2] to get the real value.
```

The `scale`, also known as the `scaling factor`, is a constant by which the integer representation is multiplied to get the true real-world value.  
In many systems, the scaling factor is a power of two, which simplifies hardware implementation and arithmetic operations.  

The number of bits allocated to the fractional part of a fixed-point number determinate the power of two that will be use as scale. 

```cpp
scale (S) = 2^b 
b = the number of fractional bits. 
If b = 4, S = 2^4 = 16.
```

With 8 fractional bits, you store a number as an integer that is implicitly scaled by 256 (because 2^8 = 256). 
- To store a real number → multiply by 256 and round to an integer.
- To read it back as a real → divide the stored integer by 256.

```cpp
scale (S) = 2^b   
If b = 8, S = 2^8 = 256.  

--- 
In the exercise, "b" is store as private member _fracBits  
b = Fixed::_fracBits = 8  

--- 
To go from int to fixed-point (_raw  in class Fixed):  
(1) _raw = num * S = num * 2^b 
(2) _raw = num(binary) << _fracBits 
---

Given int n = 4

(1) Fixed::_raw  = n * 256 = 4 * 256 = 1024 

(2) Bitwise view (16-bit shown):  
4 in binary : 0000 0000 0000 0100
_raw = n * (1 << _fracBits);
_raw = 4 << 8 → 0000 0001 0000 0000 (that’s 1024)
```




---

What is the “scale”?

Call it 𝑆
For 8 fractional bits:
```
S = 2 ^ _fracBits = 2^8 = 256.

You don’t move a binary point in hardware; you just agree that whatever you store in _raw is really “value × 256”. So:

When storing an int n: _raw = n * S → _raw = n << 8.

When storing a float f: _raw = roundf(f * S).

When reading as float: toFloat() returns _raw / (float)S → _raw / 256.0f.

When reading as int: toInt() returns _raw / S with truncation → _raw >> 8.

What is the “step”?

The step (also called resolution or quantum) is the smallest difference between two distinct representable values in your fixed-point format.

With 8 fractional bits:

step
=
1
/
𝑆
=
1
/
256
≈
0.00390625
step=1/S=1/256≈0.00390625.

So your fixed-point can represent values like:

…, -0.0078125, -0.00390625, 0, 0.00390625, 0.0078125, …


and it cannot represent anything in between those ticks.

Equivalently: increasing _raw by 1 changes the real value by 1/256.

This is why in ex02 the “smallest representable ε such that 1 + ε > 1” is exactly 1/256.

Why _raw / 256.0f?

Because _raw is the scaled integer. To recover the real value, you undo the scale by dividing by 256:

float Fixed::toFloat() const {
    return static_cast<float>(_raw) / 256.0f; // 256 = 2^8
}

Walkthrough with real numbers
1) From int to fixed, back to float

Input: n = 5

Store: _raw = n << 8 = 5 * 256 = 1280

Read as float: 1280 / 256.0f = 5.0f

Read as int: 1280 >> 8 = 5

2) From float to fixed (quantization), back to float

Input: f = 3.1416f

Store: _raw = roundf(3.1416 * 256) = roundf(804.25…) = 804

Read as float: 804 / 256.0f = 3.140625f
(You see a tiny quantization error because the step is 1/256 ≈ 0.00390625.)

3) Bit intuition (optional)

For 8 fractional bits you can imagine the binary like:

[ integer bits ][........fraction bits........]
                 ^ 8 bits after the binary point


Example: the real value 2.75

Store: _raw = 2.75 * 256 = 704

Binary of 704 is 10 1100 0000₂.

If you “place” the point 8 bits from the right: 10.11000000₂ = 2 + 0.5 + 0.25 = 2.75.

TL;DR

Scale 
𝑆
S is 2^{\text{_fracBits}} → here 256.

Step is 
1
/
𝑆
1/S → here 1/256.

Store int: _raw = n << 8.

Store float: _raw = roundf(f * 256).

Read as float: _raw / 256.0f.

Read as int: _raw >> 8.