# 🌌 Solar System Simulation

A basic real-time 2D solar system simulator using C and X11. It simulates gravitational physics and renders celestial bodies using vector math.

---

![Demo](demo.gif)

## ✨ Features

- Basic gravitational physics (Newtonian)
- Real-time rendering with X11
- Logging with levels (DEBUG, INFO, WARN, ERROR)
- Keyboard input (`q` to quit)
- Modular structure (X11, physics, logging, vector math)

---

## 🛠️ Build Instructions

### Dependencies

- X11 development libraries (`libx11-dev`)
- A C compiler like `gcc`
- Make

Install on Debian/Ubuntu:
```bash
sudo apt update
sudo apt install build-essential libx11-dev
```


# How to run

```
make
./solar_system
```

## ⚙️ Configuration Options

### Global Simulation Parameters

| Key | Type | Description |
|----------|----------|----------|
| timestep  | int  | Time delta used for each simulation step  |
| resolution  | int  | Resolution (width and height) of the window in pixels  |
| gravity | float | Gravitational constant used in physics


### Planet
Each planet is defined with a unique number (e.g. planet0, planet1) and has the following properties:


| Key | Type | Description |
|----------|----------|----------|
| mass  | float  | Mass of the planet  |
| pos  | float,float,float  | Initial position (x, y, z)  |
| mom  | float,float,float  | Initial momentum (px, py, pz)  |
| color  | int,int,int,int	  | RGBA color (Red, Green, Blue, Alpha)  |
| rad  | float  | Radius of the planet (visual scale)  |
