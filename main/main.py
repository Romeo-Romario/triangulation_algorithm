import matplotlib.pyplot as plt
import numpy as np
from geometry import Point, get_start_triangle  # type: ignore

# # Input points
# incoming_data = [Point(0, 0), Point(0, 10), Point(6, 10), Point(6, 0)]

# # Get big triangle
# triangle = get_start_triangle(incoming_data)

# # Plot all original points
# x = [p.x for p in incoming_data]
# y = [p.y for p in incoming_data]
# plt.scatter(x, y, color="blue", label="Input Points")

# # Plot triangle vertices
# tx = [triangle.a.x, triangle.b.x, triangle.c.x, triangle.a.x]
# ty = [triangle.a.y, triangle.b.y, triangle.c.y, triangle.a.y]
# plt.plot(tx, ty, color="red", label="Start Triangle")

# plt.gca().set_aspect("equal", adjustable="box")
# plt.legend()
# plt.show()


matrix = np.array([[2, 3], [4, -1]], dtype=float)
b = np.array([7, 9], dtype=float)

print(np.linalg.solve(matrix, b))
