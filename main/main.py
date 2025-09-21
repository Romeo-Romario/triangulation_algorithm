import matplotlib.pyplot as plt
from matplotlib.patches import Circle as C
import numpy as np
import geometry
from geometry import Point
from visualize_triangulation import visualize_triangulation

# incoming_data = [Point(0, 1), Point(1, 0), Point(2, 0), Point(0, 2)]
# incoming_data = [Point(-2, 0), Point(2, 0), Point(0, 2), Point(0, -2)]

incoming_data = [
    Point(-2.5, 2.0),
    Point(-1.0, 2.0),
    Point(1.0, 1.0),
    Point(2.5, -1.0),
    Point(0.5, -1.0),
    Point(-1.5, 0),
]


additinal_vertexes = geometry.generate_grid(incoming_data, 10.0, 0.07)

all_points = [*incoming_data, *additinal_vertexes]

triangulation_res = geometry.triangulation(all_points)

circles = geometry.get_circles(triangulation_res)

visualize_triangulation(
    incoming_data, additinal_vertexes, triangulation_res, circles, radius_limit=1.0
)
