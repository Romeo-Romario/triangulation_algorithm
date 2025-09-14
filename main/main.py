import matplotlib.pyplot as plt
from matplotlib.patches import Circle as C
import numpy as np
from geometry import Point, Circle, get_start_triangle  # type: ignore

# Input points
incoming_data = [Point(0, 0), Point(0, 10), Point(6, 10), Point(6, 0)]

# Get big triangle
triangle = get_start_triangle(incoming_data)
print(triangle.a, triangle.b, triangle.c)
circle = Circle.calculate_circumscribed_circle(triangle)

fig, ax = plt.subplots()

print(f"circle: {circle}")
# Plot all original points
x = [p.x for p in incoming_data]
y = [p.y for p in incoming_data]
ax.scatter(x, y, color="blue", label="Input Points")

# Add circle
ax.add_patch(
    C(
        (circle.center.x, circle.center.y),
        circle.radius,
        edgecolor="red",
        facecolor="none",
    )
)

# Plot triangle vertices
tx = [triangle.a.x, triangle.b.x, triangle.c.x, triangle.a.x]
ty = [triangle.a.y, triangle.b.y, triangle.c.y, triangle.a.y]
ax.plot(tx, ty, color="red", label="Start Triangle")

plt.gca().set_aspect("equal", adjustable="box")
ax.legend()
plt.show()
