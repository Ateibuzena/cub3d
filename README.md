# cub3D

> A 42 School project — Raycasting engine based on Wolfenstein 3D.

## 📷 Demo

![Demo animated](cub3D_optimized.gif)

## 🎯 Goal

The goal of this project is to build a simple 3D game using raycasting in C and the MiniLibX graphics library. It renders a first-person view of a 2D map, handles player movement, and displays textured walls in a pseudo-3D perspective.

## 🧱 Features

- Raycasting algorithm for wall rendering
- Texture loading and mapping (XPM files)
- Player movement and rotation
- Map parsing from `.cub` file
- Floor and ceiling coloring
- Error handling and validations
- MiniLibX integration

## 🗺️ Map format (`.cub`)

Each map file must contain:
- Paths to four wall textures: `NO`, `SO`, `WE`, `EA`
- RGB colors for the floor (`F`) and ceiling (`C`)
- A valid 2D map using `1` for walls, `0` for empty space
- A single player start position with direction: `N`, `S`, `E`, or `W`

Example:
```
  NO ./textures/wall_north.xpm
  SO ./textures/wall_south.xpm
  WE ./textures/wall_west.xpm
  EA ./textures/wall_east.xpm
  F 220,100,0
  C 225,30,0

  111111
  100001
  1000N1
  111111
```

## 🛠️ Build Instructions

This project uses **MiniLibX**, so make sure you have it installed.

```bash
  git clone https://github.com/yourusername/cub3d.git
  cd cub3d
  make
```
To run the program:
```
  ./cub3D maps/example.cub
```

## 🎮 Controls
- W / S — Move forward / backward

- A / D — Strafe left / right (if implemented)

- ← / → — Rotate left / right

- ESC — Quit the game

## 🧑‍💻 Authors
- Ana Zubieta (@ateibuzena)

- Manuel Hoyuela (@mhoyuela)

## 📚 Resources
- MLX42 documentation (42)

- Lodev Raycasting tutorial

- Wolfenstein 3D
