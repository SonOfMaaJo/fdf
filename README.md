*This project has been created as part of the 42 curriculum by vnaoussi.*

# FdF (Fil de Fer)

## Description

**FdF** is a computer graphics project that involves representing a 3D wireframe landscape. The program reads a file containing coordinates $(x, y, z)$ and uses the **MiniLibX** library to project and connect these points in a graphic window, allowing for the visualization of complex terrains in an interactive way.

## Project Description: Technical Choices

### Line Drawing: Bresenham's Algorithm

Drawing the segments connecting the points of the map is one of the project's pillars. To ensure optimal performance, **Bresenham's algorithm** was implemented.

*   **Why Bresenham?**
    *   **Performance:** It uses only integer addition, subtraction, and bit shifting, avoiding costly floating-point calculations.
    *   **Precision:** It minimizes the distance error between the plotted pixels and the theoretical line, ensuring a sharp visual rendering without gaps in the segments.

### Projections: Isometric vs Parallel

The subject requires a representation in **isometric projection**. However, to provide better flexibility, the project offers two types of views:

#### 1. Isometric Projection (Mandatory)
*   **Concept:** The three axes of space ($x, y, z$) are represented with the same scale factor, creating a balanced 3D illusion.
*   **Calculation:** We apply a $45^{\circ}$ rotation on the Z axis followed by a rotation of approximately $35.26^{\circ}$ on the X axis (or via the simplified formula using $\cos(30^{\circ})$ and $\sin(30^{\circ})$).

#### 2. Parallel Projection (Bonus)
*   **Concept:** Parallel lines in 3D space remain parallel on the 2D screen. This view is ideal for inspecting the raw data layout without isometric distortion.

### Graphic Management: MiniLibX Images

Using the `mlx_pixel_put` function is forbidden for mass rendering because it is extremely slow (individual communication with the X server for each pixel).

*   **Solution:** Mandatory use of MiniLibX **Images**.
*   **Mechanism:** The program allocates a memory buffer (pixel buffer), calculates and writes all the frame's pixels directly into this buffer, then pushes the entire image to the window in a single call (`mlx_put_image_to_window`). This ensures smooth navigation and no flickering.

---

## Controls

The program offers full interactive management of the model via keyboard and mouse:

### 1. Geometric Transformations
*   **Translation:** Use the **arrow keys** (Up, Down, Left, Right) to move the model.
*   **Rotation:**
    *   `W` / `S`: Rotation on the **X** axis.
    *   `A` / `D`: Rotation on the **Y** axis.
    *   `Q` / `E`: Rotation on the **Z** axis.
*   **Zoom:** **Mouse wheel** (Scroll Up to zoom in, Scroll Down to zoom out).
*   **Relief (Altitude):** `Page Up` and `Page Down` keys to accentuate or flatten peaks.

### 2. Display and Projections
*   **Projections:**
    *   `I`: Switch to **Isometric Projection**.
    *   `P`: Switch to **Parallel Projection**.
*   **Reset:** `R` key to reset the model to its original position and zoom.
*   **Shearing:** `K` and `L` keys (Experimental bonus).

### 3. System
*   **Quit:** `ESC` key or click on the **red cross** of the window to close the program cleanly.

---

## Instructions

### 1. Compilation

The project uses a `Makefile` that adheres to the school's Norm.

*   **Mandatory Part:**
    ```bash
    make
    ```
    Generates the `fdf` executable.

*   **Bonus Part:**
    ```bash
    make bonus
    ```

*   **Cleaning:**
    ```bash
    make fclean
    ```

### 2. Usage

The program takes a `.fdf` file as an argument:

```bash
./fdf test_maps/42.fdf
```

---

## Bonus Part

In accordance with Chapter VII of the subject, the following features were added to enhance the user experience:

*   **Full Transformations:** Rotation on 3 axes (X, Y, Z), Translation, and Zoom.
*   **Extra Projection:** Ability to toggle between Isometric and Parallel views (keys `I` and `P`).
*   **Relief Management:** Keys allowing to exaggerate or flatten altitudes in real-time.
*   **Color Gradient:** If no color is specified in the file, a dynamic gradient (Blue -> Green -> White) is applied based on altitude.
*   **Mouse Management:** Smooth zooming via the scroll wheel.

---

## AI Usage

Artificial Intelligence was used to assist in structuring this README, providing theoretical explanations of Bresenham's algorithm, and solving specific bugs related to color and memory management (notably `free()` errors during parsing).

---

## Resources

*   [MiniLibX Documentation (42Docs)](https://harm-smits.github.io/42docs/libs/minilibx)
*   [Bresenham's line algorithm - Wikipedia](https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm)
*   [3D Projection Mathematics](https://en.wikipedia.org/wiki/3D_projection)
