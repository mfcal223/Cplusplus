# CPP Module 2 - Ex 01 - Floating in weird place.

<insert summary of the exercise>


Considering the exercise goal, most of the code from the previous exercise is going to be use in this one.  

The exercise demands some extra class members and functions.
- 2 new constructors that will have to convert int -> fixed-point number and float -> fixed-point number
- A NON-class function to overload the operator "<<" 

## Int to fixed-point number
To consider an easy way to convert int to fixed-point number, knowing the scale will always be 8 bits, check [this document](/home/florencia/proyectos/CPP/Cplusplus/Exercises/CPP_2/cpp_2_1_FPN_scale.md)  


## Float to fixed-point number

Similarly to the int conversion, we need to consider the scale **(S)**:  
- _fracBits == 8 (or 1/256)  
- S = [1 << _fracBits]  or [256]

```cpp
// float -> fixed-point number
fixed-point-num = float * (1 << _fracBits)
or 
fixed-point-num = float * 256 //because subject states fracBits will always be 8
```
### 1st consideration - rounding
As mentioned in [Fixed-Point Numbers](/home/florencia/proyectos/CPP/Cplusplus/Exercises/CPP_2/cpp_2_0_FixedPointNumbers.md) and in [Float Numbers](/home/florencia/proyectos/CPP/Cplusplus/Exercises/CPP_2/cpp_2_2_floatnumbers.md), fixed format can only represent multiples of 1/256. Rounding centers the error around zero. In order to do this, we are allowed to use the function `roundf`from the <cmath> library.

Example:   
```r
fixed-point-value (float32) = 42.42f
42.42 * 256 = 10859.52 → roundf(...) = 10860 → _raw = 10860.
```

### 2nd consideration - data type
Multiplying a float (f) by an int promotes the int to float, so the product is float. So the initial result of this conversion is of data type **float**.  
As the class member **_raw** is an int, ***casting*** is needed.

---

## toFloat()
This functions needs to undo the scale.  
It divides the store integer _raw by the scale (_fracBits = 8), to get back the real value.
Casting is needed to ensuere `floating-point division` instead of integer division.

Example:   
```r
_raw = 10860
toFloat() = 10860 / 256.0f = 42.421875f.
```
> This is the value the operator << needs to print in this exercise-

NOTE
What happens with different literals
10860 / 256 → int / int = 42 (int division, truncates)
10860 / 256.0 → int / double = 42.421875 (double)
10860 / 256.0f → int / float = 42.421875f (float)

Against the need to cast operands consider that all of this are valid alternatives: 

```cpp
// A) Cast numerator only (denominator int will be promoted to float)
return static_cast<float>(_raw) / (1 << _fracBits);

// B) Cast denominator only (numerator int will be promoted to float)
return _raw / static_cast<float>(1 << _fracBits);

// C) Use float literals (no casts needed). Only if you’re OK with the fixed 8 bits:
return _raw / 256.0f;              // “magic number” – works because fracBits == 8

// D) Multiply by the reciprocal (often a tiny bit faster; same result)
return static_cast<float>(_raw) * (1.0f / static_cast<float>(1 << _fracBits));

// E) With a precomputed local (readable and avoids repeating the shift)
const float invScale = 1.0f / static_cast<float>(1 << _fracBits);
return static_cast<float>(_raw) * invScale;

```
---
//Edge case (range) - consideration to constructor float

If f is huge (so f * S overflows int), you’ll get UB or wrap. The subject doesn’t require clamping, so most ex01 solutions leave it as-is.