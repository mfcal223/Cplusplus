# CPP Module 2 - Ex 03 - Point-in-Triangle with Fixed

## TASK
- Allowed functions : roundf (from <cmath>)
- Build a small 2D geometry toolkit using your Fixed class: a Point class (Orthodox Canonical Form) and a function that checks whether a point lies strictly inside a triangle.  
- Point class (2D point)
    * Private:  
        * Fixed const _x;
        * Fixed const _y;
        * any other private helpers you find useful  
    * Public
        * Default constructor → initializes (0, 0).
        * Constructor from two float (or const float) → initializes (x, y).
        * Copy constructor.  
        * Copy-assignment operator.  
        * Destructor.  
        * Getters for x and y (return by Fixed const & or by value).

Note: members are *const*, so the copy-assignment operator can’t actually modify them; it should still exist (for Orthodox Canonical Form) and typically just return *this.  


- Function to implement:  
	* Parameters: a, b, c are the triangle’s vertices; p is the query point.  
	* Return value: true if p is strictly inside the triangle; false otherwise.  
	* Points on an edge or exactly at a vertex must return false.
```cpp
bool bsp(Point const a, Point const b, Point const c, Point const p);
```

- Tests: provide your own tests in main.cpp that exercise typical and edge cases (inside, outside, on each edge, on a vertex, degenerate triangles).

---

## Binary Space Partitioning

*In computer science, **binary space partitioning (BSP)** is a `method for space partitioning which recursively subdivides a Euclidean space into two` convex sets by using hyperplanes as partitions. This process of subdividing gives rise to a representation of objects within the space in the form of a tree data structure known as a `BSP tree`.*    

![BSP tree](/Exercises_task_&_theory/images/BSP_planes.png)

*The structure of a BSP tree is useful in rendering because it can efficiently give spatial information about the objects in a scene. Other applications of BSP include: performing geometrical operations with shapes (constructive solid geometry) in CAD,[3] collision detection in robotics and 3D video games, ray tracing, virtual landscape simulation,[4] and other applications that involve the handling of complex spatial scenes.*  

> **Don't panic. We are not diving into this now!**

To learn more about BSP, you can check this links:
- [Geeks for Geeks - Binary Space Partitioning](https://www.geeksforgeeks.org/dsa/binary-space-partitioning/)  
- [Wikipedia - Binary space partitioning](https://en.wikipedia.org/wiki/Binary_space_partitioning)  

---

### How to use BSP for this exercise

The exercise does NOT demando to build a full BSP tree. Just to decide wheter a point is inside a triangle or not. That’s the whole “BSP” idea the subject hints at.

![Triangle ABC & sample points](/Exercises_task_&_theory/images/BSP_triangle2.png)

Take each edge of the triangle and imagine the infinite line that contains it.  

That line splits the plane into two half-planes (a binary partition).   
For an oriented edge (say A→B), one half is on the “left” of the arrow and the other is on the “right”.  

For a triangle ABC, define the “inside” side of each edge as the half-plane that contains the third vertex:  
- For edge AB, the “inside” side is the half that contains C.
- For edge BC, inside side contains A.
- For edge CA, inside side contains B.

Then a point P is inside the triangle if P lies on the “inside” side of all three edges. 
If P falls exactly on any edge (boundary), we say "outside" for this exercise.




```
	 A/
     /\
	/  \
   /    \
B /______\ 
 /         C
/
```