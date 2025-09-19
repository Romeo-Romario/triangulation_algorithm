import matplotlib.pyplot as plt
from matplotlib.patches import Circle as C
import numpy as np
import geometry
from geometry import Point


import matplotlib.pyplot as plt
import numpy as np


def visualize_triangulation(
    incoming_data, additional_vertexes, triangulation, circles=None, radius_limit=0.0
):
    # Create figure(s) based on whether circles are provided
    if circles is not None:
        # Create two separate figures/windows
        fig1, ax1 = plt.subplots(num="Triangulation")
        fig2, ax2 = plt.subplots(num="Triangulation with Circumcircles")
        axes = [ax1, ax2]
    else:
        # Create just one figure/window
        fig, ax = plt.subplots()
        axes = [ax]

    # Plot common elements on all axes
    for ax in axes:
        x = [p.x for p in incoming_data]
        y = [p.y for p in incoming_data]
        ax.scatter(x, y, color="red", label="Input Points")

        ax.scatter(
            [p.x for p in additional_vertexes],
            [p.y for p in additional_vertexes],
            color="blue",
            s=50,
            label="Added points",
            alpha=0.6,
        )

    # Plot triangulation on all axes
    colors = plt.cm.tab10(np.linspace(0, 1, len(triangulation)))
    for i, tri in enumerate(triangulation):
        # Extract triangle vertices
        tri_x = [tri.a.x, tri.b.x, tri.c.x, tri.a.x]
        tri_y = [tri.a.y, tri.b.y, tri.c.y, tri.a.y]

        # Plot triangle on all axes
        for ax in axes:
            ax.plot(
                tri_x,
                tri_y,
                color=colors[i],
                linestyle="--",
                linewidth=2,
                label=f"Triangle {i+1}" if i == 0 else "",
            )

    # Plot circles on the second axis if provided
    if circles is not None:
        for i, circle in enumerate(circles):
            if circle.radius > radius_limit:
                continue
            # Draw circumcircle with less transparent border and more transparent fill
            circle_patch = plt.Circle(
                (circle.center.x, circle.center.y),
                circle.radius,
                color=colors[i],
                fill=True,
                alpha=0.2,  # Fill transparency
                ec=colors[i],  # Edge color same as fill
                linewidth=1.5,  # Border line width
                linestyle="-",  # Border line style
                label=f"Circumcircle {i+1}" if i == 0 else "",
            )
            axes[1].add_patch(circle_patch)

    # Set properties for all axes
    for ax in axes:
        ax.set_aspect("equal", adjustable="box")
        ax.legend(bbox_to_anchor=(1.05, 1), loc="upper left")

    plt.show()
