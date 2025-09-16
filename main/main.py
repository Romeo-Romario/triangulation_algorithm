import matplotlib.pyplot as plt
from matplotlib.patches import Circle as C
import numpy as np
from geometry import Point, generate_grid, Circle, get_start_triangle, triangulation

# incoming_data = [Point(0, 0), Point(0, 10), Point(3, 5), Point(6, 10), Point(6, 0)]

# triangulation_res = triangulation(incoming_data)


# fig, ax = plt.subplots()

# x = [p.x for p in incoming_data]
# y = [p.y for p in incoming_data]
# ax.scatter(x, y, color="blue", label="Input Points")

# colors = plt.cm.tab10(np.linspace(0, 1, len(triangulation_res)))
# for i, tri in enumerate(triangulation_res):
#     # Extract triangle vertices
#     tri_x = [tri.a.x, tri.b.x, tri.c.x, tri.a.x]
#     tri_y = [tri.a.y, tri.b.y, tri.c.y, tri.a.y]

#     # Plot triangle
#     ax.plot(
#         tri_x,
#         tri_y,
#         color=colors[i],
#         linestyle="--",
#         linewidth=2,
#         label=f"Triangle {i+1}",
#     )


# plt.gca().set_aspect("equal", adjustable="box")
# ax.legend(bbox_to_anchor=(1.05, 1), loc="upper left")
# plt.show()


incoming_data = [Point(-2, 0), Point(2, 0), Point(0, 2), Point(0, -2)]

additinal_vertexes = generate_grid(incoming_data, 5.0)

plt.figure(figsize=(10, 8))

# Відображаємо вхідні точки червоним кольором
plt.scatter(
    [p.x for p in incoming_data],
    [p.y for p in incoming_data],
    color="red",
    s=100,
    label="Starting points",
    zorder=5,
)

# Відображаємо додаткові точки синім кольором
plt.scatter(
    [p.x for p in additinal_vertexes],
    [p.y for p in additinal_vertexes],
    color="blue",
    s=50,
    label="Added points",
    alpha=0.6,
)

# Додаємо сітку для кращої орієнтації
plt.grid(True, linestyle="--", alpha=0.7)
plt.axhline(y=0, color="k", linestyle="-", alpha=0.3)
plt.axvline(x=0, color="k", linestyle="-", alpha=0.3)

# Налаштовуємо графік
plt.title("Візуалізація точок")
plt.xlabel("X координата")
plt.ylabel("Y координата")
plt.legend()
plt.axis("equal")  # Щоб масштаб по обох осях був однаковий

# Показуємо графік
plt.show()
