# cub3D 🎮🧱

![Demo_Bonus](Demo/bonus_demo.gif)

A simple 3D game inspired by *Wolfenstein 3D*, built using ray-casting.  
This project introduces basic graphic rendering and engine logic.

## 🧭 Goal
Turn a `.cub` map into a first-person 3D view using raycasting and vector math.

## 🧱 What it Includes
- Ray-casting engine (walls, perspective, textures)
- Movement: walk + rotate
- Collision detection
- Parsing `.cub` map (walls, player start, textures, colors)
- Textured walls
- MLX42 usage for windowing, textures & events

## 🎓 What I Learned

Building this engine was a deep dive into **computational geometry** and **low-level graphics**.

#### 1. The Raycasting Engine
I developed a "pseudo-3D" renderer by calculating 2D intersections in a grid.
* **The Projection:** Learned to map the distance of a ray to a vertical column height, creating a depth illusion from a 2D map.
* **Ray Traversal:** Implemented an incremental coordinate-step method to track ray paths and detect wall collisions in a discrete grid.



#### 2. Trigonometric Corrections
* **The "Fish-Bowl" Effect:** Solved perspective distortion by using **perpendicular distance** ($dist \times \cos(\theta)$) to ensure flat walls appear straight rather than curved.
* **FOV Logic:** Mastered the relationship between the player’s viewing angle and the screen’s horizontal resolution.



#### 3. Precision & Performance
* **Floating Point Math:** Utilized high-precision `double` calculations to prevent "wall-bleeding" and ensure smooth movement.
* **Buffer Management:** Achieved high frame rates by writing raw data to an **image buffer** in memory, bypassing slow pixel-by-pixel drawing methods.

## 🔧 Build & Run
```bash
make
./cub3D maps/map.cub
```
## 🗺️ Map Format
Example:

```bash
NO ./path_to_texture
SO ...
WE ...
EA ...
F 220,100,0
C 225,30,0

111111
100001
101P01
111111
```
## 📝 Notes

- Engine built from scratch (no Unity, no prebuilt libs)
- Learned: raycasting math, state management, event loops

![Demo](Demo/man_demo.gif)
