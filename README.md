# Triangulation Algorithm (C++ & Python)

This repository contains an implementation of a **triangulation algorithm** in both C++ and Python.
The core of the triangulation is built using the **Bowyer–Watson algorithm**.

---

## 📦 Python "geometry" Package Setup

To build and use the custom `geometry` package in Python:

1. Navigate to the `./logic` folder:

   ```bash
   cd logic
   ```

2. Build the extension:

   ```bash
   python setup.py build_ext --inplace
   ```

3. Move the resulting package into the same folder as `main.py` and `visualize_triangulation.py`.

---

## 📐 Bowyer–Watson Algorithm (Pseudocode)

```text
function BowyerWatson(points):
    # 1. Create a super-triangle that fully contains all points
    superTriangle = build_super_triangle(points)

    # 2. Initialize triangulation with just the super-triangle
    triangulation = {superTriangle}

    # 3. Insert points one by one
    for P in points:
        badTriangles = {}

        # 3.1 Find triangles whose circumcircle contains P
        for T in triangulation:
            if P inside_circumcircle(T):
                badTriangles.add(T)

        # 3.2 Find the "polygonal hole" boundary of badTriangles
        polygon = {}
        for T in badTriangles:
            for edge in T.edges:
                if edge not shared by another triangle in badTriangles:
                    polygon.add(edge)

        # 3.3 Remove bad triangles
        triangulation.removeAll(badTriangles)

        # 3.4 Re-triangulate the hole with P
        for edge in polygon:
            newTriangle = Triangle(edge.start, edge.end, P)
            triangulation.add(newTriangle)

    # 4. Remove triangles that share a vertex with the super-triangle
    for T in triangulation:
        if T has_vertex_of(superTriangle):
            triangulation.remove(T)

    return triangulation
```

---

## 🖼️ Results So Far

<p align="center">
  <img width="600" src="https://github.com/user-attachments/assets/30d1ad05-8571-4b5a-9a80-8db76c613a90" />
  <img width="600" src="https://github.com/user-attachments/assets/a38df510-faff-4ee2-9023-0c92bd0070e3" />
</p>

---

## 🚀 Possible Improvements

* Enforce a **minimum angle constraint** to avoid skinny triangles
* Optimize **point deletion** during inner grid generation
* Improve performance of circumcircle checks
* Explore parallelization for large datasets

---

## 🛠️ Tech Stack

* **C++** — core algorithm implementation
* **Python** — bindings, visualization, and quick prototyping

---

✨ Contributions, improvements, and feedback are welcome!
