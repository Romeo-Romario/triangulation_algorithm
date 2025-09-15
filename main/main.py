import matplotlib.pyplot as plt
from matplotlib.patches import Circle as C
import numpy as np
from geometry import Point, Circle, get_start_triangle, triangulation

incoming_data = [Point(0, 0), Point(0, 10), Point(3, 5), Point(6, 10), Point(6, 0)]

triangulation_res = triangulation(incoming_data)


fig, ax = plt.subplots()

x = [p.x for p in incoming_data]
y = [p.y for p in incoming_data]
ax.scatter(x, y, color="blue", label="Input Points")

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
