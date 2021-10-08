# Triangles visible area calculator

## Table of contents

- [Introduction](#introduction)
- [Example program run](#example-program-run)
- [Technology](#technology)
- [Launch](#launch)
- [Project structure](#project-structure)

## Introduction

This project's aim is to calculate visible area of triangles being given the triangle verticies stored in a text file, observation point and looking directory in an infinite 3d space.

## Example program run

### Input data:

- "triangles.txt" file with this text:

```
0,0,1;0,3,1;4,0,1;
0,0,0;0,1,0;1,0,0;
```

- Observation point: (0,0,0)
- Looking direction: 1 (forward)

### Output data:

```
Please select observation point coordinates:
x: 0
y: 0
z: 0

Selected point [0, 0, 0]

Select looking direction:
1.Forward
2.Backward
3.Up
4.Down
5.Left
6.Right
1

Reading triangles...

Read triangle: {[0, 0, 1], [0, 3, 1], [4, 0, 1]}
Read triangle: {[0, 0, 0], [0, 1, 0], [1, 0, 0]}

Field of view (empty space around ignored):

1
11
211
22111

Triangle 1: 8 pixels
Triangle 2: 3 pixels
```

## Technology

- C++
- Visual Studio Code

## Launch

### Mac and Linux

Simply double click "main" file.

### Windows

You will need to install MinGW compilator to compile the source code to .exe file. Once installed, you should run this command in your terminal opened in the projects directory:

```
g++ -std=c++14 *.cpp -o main
```

## Project structure

### main.cpp

This file contains main algorithm of the program. It is also responsible for reading triangles from file.

### triangle.h/cpp

These files contain Triangle class made for storing data about tiangles read from the file. They also contain enum that deifnes possible looking directions.

### point.h/cpp

These files contain Point structure made for storing information about a particular point. It can hold triangle's verticies but also observation point and 3d coordinates in general.

### myExtentions.h

This file contains my custom defined exceptions.

### Other files

Other files are neccesary for Visual Studio Code to run this project correctly.
