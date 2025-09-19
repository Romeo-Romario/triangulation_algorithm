import matplotlib.pyplot as plt
from matplotlib.patches import Circle as C
import numpy as np
from geometry import Point, generate_grid, Circle, get_start_triangle, triangulation

# incoming_data = [Point(0, 0), Point(0, 10), Point(3, 5), Point(6, 10), Point(6, 0)]
# incoming_data = [Point(-2, 0), Point(2, 0), Point(0, 2), Point(0, -2)]

incoming_data = [
    Point(-2.5, 2.0),
    Point(-1.0, 2.0),
    Point(1.0, 1.0),
    Point(2.5, -1.0),
    Point(0.5, -1.0),
    Point(-1.5, 0),
]


additinal_vertexes = generate_grid(incoming_data, 4.0, 0.05)

all_points = [*incoming_data, *additinal_vertexes]

triangulation_res = triangulation(all_points)


fig, ax = plt.subplots()

x = [p.x for p in incoming_data]
y = [p.y for p in incoming_data]
ax.scatter(x, y, color="red", label="Input Points")

ax.scatter(
    [p.x for p in additinal_vertexes],
    [p.y for p in additinal_vertexes],
    color="blue",
    s=50,
    label="Added points",
    alpha=0.6,
)

colors = plt.cm.tab10(np.linspace(0, 1, len(triangulation_res)))
for i, tri in enumerate(triangulation_res):
    # Extract triangle vertices
    tri_x = [tri.a.x, tri.b.x, tri.c.x, tri.a.x]
    tri_y = [tri.a.y, tri.b.y, tri.c.y, tri.a.y]

    # Plot triangle
    ax.plot(
        tri_x,
        tri_y,
        color=colors[i],
        linestyle="--",
        linewidth=2,
        label=f"Triangle {i+1}",
    )


plt.gca().set_aspect("equal", adjustable="box")
ax.legend(bbox_to_anchor=(1.05, 1), loc="upper left")
plt.show()
