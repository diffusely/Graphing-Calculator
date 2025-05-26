# Graphing Calculator

This is a simple graphical calculator built with OpenGL.  
It renders mathematical functions in real time using an expression tree.

## Features

- Zoom with mouse scroll  
- Move/pan the view using `W`, `A`, `S`, `D` keys  
- Real-time rendering of graphs  
- Interactive GUI powered by ImGui for inputting and updating expressions on the fly

## How It Works

- The camera zooms in and out with the mouse scroll wheel  
- The camera moves/pans using the keyboard keys `W`, `A`, `S`, and `D`  
- Expressions are parsed into an expression tree for evaluation and rendering  
- ImGui interface allows real-time function input and updates  

## Requirements

- OpenGL 3.3 or higher  
- GLFW  
- GLAD  
- ImGui  
- C++17 compatible compiler

## Build Instructions

1. Clone the repository  
2. Ensure dependencies (GLFW, GLAD, ImGui) are available in the `lib/` directory  
3. Run CMake and build:  
   ```bash
   mkdir build && cd build
   cmake ..
   make



