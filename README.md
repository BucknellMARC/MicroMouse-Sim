MicroMouse Simulator
====================

Bucknell MARC's OpenGL/FreeGLUT MicroMouse maze simulator.

Purpose
-------
The purpose of this project is to build a simulator for the MicroMouse challenge while maximizing code reuse.  The idea is the maze solving logic will be implemented in an abstract class that gets inherited by both the *VirtualRobot* and a real-world implementation class so the physical solving code can be directly shared.

Mapping The Maze
----------------
The *MazeMap* hold's the robot's view of what the maze looks like in memory.  There are two dimensional arrays containing information about whether or not a wall is in the way (also whether or not the robot knows it has scanned that location.

Simple API provides access to these confusing multi-dimensinal *horizontalWalls* and *vertcalWalls* arrays.

```c++
MazeMap::doesWallExist(int x, int y, Direction direction);
MazeMap::setWall(WallState state, int x, int y, Direction direction);
```

These are the main functions of the class, basically lets you get or set the state of walls at a particular place and direction.  This deals with the challenge of handling differentiation between vertical, horizontal walls, and how direction affects the array position.  The idea is that the robot drives along, it can check the status of the walls by looking left, right, and forward.  These functions will get the proper location in the array, making the check an easy one-liner.

Graphics
--------
This program comes with a simple, friendly graphics API that simplifies rendering with OP

**example**
To draw a rectangle with a position of *x*, *y* and dimensions of *width*, *height* - all in pixel coordinates

```c++
// in program init
Rectangle* rect = new Rectangle(x, y, width, height);

// in draw loop
rect->draw();
```

It is also simple to change the properties of the rectangle on the fly
```c++
// change position
rect->setPos(int x, int y);
rect->translate(int x, int y);

// resizing
rect->resize(int width, int height);
```

There is also support for coloring rectangles...
