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
