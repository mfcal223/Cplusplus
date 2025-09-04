# CPP Module 2 - Exercise 01 - Fixed-Point numbers vol 2

## The scale ("𝑆")

In the previous exercise, we were introduce to the concept of *fixed-point number representation*, through which a real number can be represented  in a way that the position of the binary (or decimal) point is fixed. It's an alternative to floating-point representation.

**It implicitly converts an integer to a real number by defining a constant relationship between an integer value and its actual real-world value.**   

Example:  
```yaml
if [1.23] is stored as the integer [123], the scale (or scaling factor) is [1/100], which means the stored integer is multiplied by [10^-2] to get the real value.
```

The `scale`, also known as the `scaling factor`, is a constant by which the integer representation is multiplied to get the true real-world value.  
In many systems, the scaling factor is a power of two, which simplifies hardware implementation and arithmetic operations.  

The number of bits allocated to the fractional part of a fixed-point number determinate the power of two that will be use as scale. 

For 8 fractional bits:
```
S = 2 ^ _fracBits = 2^8 = 256.
```

```cpp
scale (S) = 2^b 
b = the number of fractional bits. 
If b = 4, S = 2^4 = 16.
```

`With 8 fractional bits, you store a number as an integer that is implicitly scaled by 256 (because 2^8 = 256)`.  
- To store a real number → multiply by 256 and round to an integer.  
- To read it back as a real → divide the stored integer by 256.  

```cpp
scale (S) = 2^b   
```

If b = 8, S = `2^8` = `256`.   

You don’t move a binary point in hardware; you just agree that whatever you store in _raw is really “value × 256”. So:  

* When storing an int n: _raw = n * S → _raw = n << 8.
* When storing a float f: _raw = roundf(f * S).
* When reading as float: toFloat() returns _raw / (float)S → _raw / 256.0f.
* When reading as int: toInt() returns _raw / S with truncation → _raw >> 8.

 
In the exercises, "b" is store as private member _fracBits  
```
b = Fixed::_fracBits = 8  
```
 
To go from int to fixed-point (_raw  in class Fixed):  
(1) _raw = num * S = num * 2^b 
(2) _raw = num(binary) << _fracBits 

> Example

Given int n = 4

(1) Fixed::_raw  = n * 256 = 4 * 256 = 1024 

(2) Bitwise view (16-bit shown):  
```
4 in binary : 0000 0000 0000 0100
_raw = n * (1 << _fracBits);
_raw = 4 << 8 → 0000 0001 0000 0000 (that’s 1024)
```


---

What is the “scale”?

Call it 𝑆


---

## What is the “step”?

The step (also called *resolution* or *quantum*) is the smallest difference between two distinct representable values in your fixed-point format.

For _fracBits = 8 
Scale S = 2^_fracBits = 256;  
the smallest representable increment is 1/S = 1/256 ≈ 0.00390625.