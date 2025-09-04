# CPP Module 2

## General rules

The same as before. 
* Split files: Class declaration in *.hpp (with include guards), implementation in *.cpp.
* No function bodies in headers (except templates).
* Must compile with -Wall -Wextra -Werror and still compile with -std=c++98.
* No STL until Module 08/09 (containers/algorithms).
* No using namespace std; (forbidden unless subject says otherwise).
* Use of the Orthodox Canonical Form.

## Ex00 — My First Canonical Class (Fixed skeleton)

1. **Goal:** 
Build a Fixed class in Orthodox Canonical Form that stores a raw integer _raw and a static const int _fracBits = 8, plus getRawBits() / setRawBits() and all 4 OCF members.

> Explain what the OCF is, what is the main difference between the constructors.

2. **What does _raw represent?**
The internal fixed-point storage (scaled integer); it’s just the bits you’ll reinterpret as a real number in later exercises.

3. **Why is _fracBits static const and set to 8?**
It’s a format constant common to all Fixed objects; the subject fixes the fractional precision to 8 bits.

4. **What should getRawBits() print during tests?**
Initially 0 for default-constructed objects (you only store raw integers in ex00).

5. **Key concepts concerning OCF & Polymorphism (overloading):**
- Copy constructor: builds a brand-new object as a copy of another.  
- Copy-assignment operator: it replaces the state of an already-existing object with the state of another (“make this existing thing look like that other thing”).  
- Ad-hoc polymorphism in C++ means overloading: you provide multiple functions (or operators) with the same name but different parameter types/signatures, and the compiler picks the right one at compile time.  

---

## Ex01 — Fixed behaves like a number (conversions & streaming)

1. **Goal:** 
Add the following to Fixed
- Ctors from int and float that write _raw with scale S = 1 << _fracBits = 256 (use roundf for float).
- toFloat() / toInt() to read back the value.
- Non-member operator<< that prints the number (via toFloat()).

> Convert int/float to and from FPN + learn basic about overloading an operator

2. **How do you convert int → Fixed?**
Multiply by the scale: _raw = n << _fracBits; (with _fracBits = 8, that’s ×256).

3. **How do you convert float → Fixed and why roundf?**
_raw = roundf(f * (1 << _fracBits)); 
(Rounding centers the quantization error; allowed by the subject.)

4. **How does toFloat() avoid integer division?**
Cast one side or use a float literal: return _raw / 256.0f; (or cast) to force floating-point math.

5. **Why is operator<< a non-member?**
Because the left operand is std::ostream; you can’t add members to it, so you overload as a free function.

6. **What’s the “scale” and the “step”?**
Scale S = 2^_fracBits = 256; the smallest representable increment is 1/S = 1/256 ≈ 0.00390625.

---

## Ex02 — Overloading (comparisons, arithmetic, ++/--, min/max)

1. **Goal:** 
Added the following to Fixed
- Overload comparisons (< <= > >= == !=), arithmetic (+ - * /), pre/post ++/-- by one LSB (= 1/256).
- Static min/max overloads for const and non-const refs.

2. **Why do ++/-- change by 1/256?**
_raw changes by ±1; since value = _raw / 256, the delta is exactly 1/256. This is the smallest epsilon.

3. **How do you implement multiplication in fixed-point?**
(a_raw * b_raw) yields scale S^2; divide once by S: r_raw = (a_raw * b_raw) >> _fracBits;  
(use wider type to avoid overflow).

4. **How do you implement division?**
Keep scale by multiplying numerator: r_raw = (a_raw << _fracBits) / b_raw; (watch for divide-by-zero).

5. **Why two overloads for min/max (const & non-const)?**
So you can return a reference that respects the const-ness of the inputs; avoids binding a non-const ref to a const object.

6. **Pre vs post increment: why does post return a value (not ref)?**
- x++ must return the old value, so you copy to a temp and return by value;  
- ++x (pre) returns *this by reference.

---

## Ex03 — Point-in-Triangle (bsp) with Fixed

1. **Goal:** 
- create class Point in OCF with const members _x/_y (Fixed), getters, and ctors;  
- create function `bool bsp(Point a, Point b, Point c, Point p)` returning true only if P is strictly inside (edges/vertices ⇒ false).

2. **Why is copy-assignment of Point a no-op?**
Members are const; you still provide the operator for OCF, but it can’t change _x/_y and simply returns *this.

3. **What’s the test you use to decide “inside”?**
The half-plane / cross-product sign test on edges A→B, B→C, C→A:
```cpp
cross(AB, AP) = (Bx−Ax)(Py−Ay) − (By−Ay)(Px−Ax).
```
- If all three signs are the same (none zero) → inside;  
- If any is zero → on edge → false;  
- If mixed signs → outside.

4. **Why check for degeneracy first?**
If cross(AB, AC) == 0, A,B,C are collinear → no interior → return false.

5. **Why is this method good for Fixed?**
It uses only +, −, × and comparisons [no division] so it’s stable and fits the fixed-point API perfectly.

---

## Concept crib (for quick recall)

1. Fixed-point basics. A real value is stored as an integer _raw with an implicit scale S = 2^_fracBits (here 256). 

2. Conversions:

* store int: _raw = n << 8

* store float: _raw = roundf(f * 256)

* to float: _raw / 256.0f

* step (epsilon) = 1/256.

3. Operator<< design. Non-member overload because std::ostream must be on the left. Print via toFloat().

4. Arithmetic scaling.

* +/−: add/sub _raw directly.

* *: (a_raw * b_raw) >> 8.

* /: (a_raw << 8) / b_raw.

5. Min/Max overload set. Provide both const and non-const versions to preserve const-ness through the reference result.

6. `bsp logic` = 3 cross-products; reject zeros; interior if all signs match (use !(hasPos && hasNeg)).