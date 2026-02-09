*This project has been created as part of the 42 curriculum by vnaoussi.*

# FdF (Fil de Fer)

## Description

FdF is a simple wireframe model representation project. The goal is to create a graphic representation of a relief landscape by linking various points $(x, y, z)$ stored in a file. The project utilizes the **MiniLibX** library to open a window, draw lines, and manage events.

## Project Description: Technical Choices

### Rendering: Bresenham's Line Algorithm

To draw the lines connecting the points of the map, the **Bresenham's algorithm** was chosen. This algorithm is crucial for performance as it determines the points of an $n$-dimensional raster that should be selected in order to form a close approximation to a straight line between two points.

*   **Efficiency:** It uses only integer addition, subtraction, and bit shifting, which are very cheap operations in standard computer architectures.
*   **Precision:** It avoids floating-point arithmetic errors that can occur with simple slope calculations ($y = mx + b$).

### Graphics: Image Buffering vs `mlx_pixel_put`

The MiniLibX library provides a function `mlx_pixel_put` to draw a pixel on the window. However, using this function for thousands of pixels (like in a wireframe map) is extremely slow because it pushes pixels to the window server one by one.

**Image Buffering** was implemented to solve this:
1.  An **Image** is created in memory (`mlx_new_image`).
2.  All pixels are drawn directly into the image's memory buffer (`char *data_addr`).
3.  Once the frame is complete, the entire image is pushed to the window at once using `mlx_put_image_to_window`.
This technique ensures smooth rendering and eliminates flickering.

### Projections: Isometric vs Parallel

The project implements two types of projections to convert 3D coordinates $(x, y, z)$ into 2D screen coordinates $(x_{screen}, y_{screen})$.

#### Isometric Projection
*   **Concept:** Simulates 3D by rotating the object. The standard isometric projection angles are used ($\approx 30^{\circ}$ or $0.523599$ radians).
*   **Formula:**
    *   $x' = (x - y) * \cos(30^{\circ})$
    *   $y' = -z + (x + y) * \sin(30^{\circ})$

#### Parallel Projection
*   **Concept:** Keeps parallel lines parallel and offers a "top-down" or "front" view depending on the angles.
*   **Usage:** Useful for inspecting the raw data layout without the isometric distortion.

---

## Instructions

### 1. Compilation

The project is compiled using a `Makefile`.

*   **Standard Build:**
    ```bash
    make
    ```
    Generates the `fdf` executable.

*   **Cleaning:**
    ```bash
    make fclean
    ```

### 2. Running the Program

Run the program by passing a map file as an argument. Maps are located in the `test_maps/` directory.

```bash
./fdf test_maps/42.fdf
```

### 3. Controls

The project supports keyboard and mouse interactions:

| Key / Action | Description |
| :--- | :--- |
| `WASDQE` | **Rotate** the map along X, Y, and Z axes. |
| `Arrow Keys` | **Translate** (move) the map. |
| `Scroll / +/-` | **Zoom** in and out. |
| `Page Up/Down` | **Relief**: Flatten or exaggerate the altitude ($z$). |
| `I` / `P` | Switch between **Isometric** and **Parallel** projections. |
| `K` / `L` | **Shear** the map. |
| `R` | **Reset** the view to default. |
| `ESC` / `Cross` | **Quit** the program cleanly. |

---

## Bonus Part

The mandatory part requires basic wireframe display. This project includes the following bonus features:

*   **Full Transformations:** Implementation of rotation matrices for X, Y, and Z axes, translation, and zooming.
*   **Dynamic Colors:**
    *   Supports hex colors defined in the map file (e.g., `10,0xFF0000`).
    *   **Auto-Gradient:** If no color is provided, a gradient is applied based on altitude:
        *   **Blue** for lowest points (Water).
        *   **Green** for mid-level points (Land).
        *   **White** for highest points (Peaks/Snow).
*   **Dual Projection:** Ability to toggle between Isometric and Parallel views at runtime.
*   **Clean Exit:** Proper memory management ensuring no leaks on exit.

---

## AI Usage

Artificial Intelligence was used to assist in debugging memory management issues (specifically `free` errors), optimizing the rotation logic to center the map correctly, and refining the color gradient algorithm for better visual aesthetics.

---

## Resources

*   [Bresenham's line algorithm - Wikipedia](https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm)
*   [MiniLibX Documentation](https://harm-smits.github.io/42docs/libs/minilibx)
*   [Isometric Projection Mathematics](https://en.wikipedia.org/wiki/Isometric_projection)

---
