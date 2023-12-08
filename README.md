# 3DViewer_v2.0

## Develop a program to visualise the 3D wireframe models.
The program C++17 standard
Writing code e Google style
The program principles of object-oriented programming MVC Patterns.
Unit tests. GTest.


Load a wireframe model from an obj file.
Translate the model by a given distance in relation to the X, Y, Z axes.
Rotate the model by a given angle in relation to its X, Y, Z axes.
Scale the model by a given value.


## Technical specifications

You need to develop a program to visualise 3D wireframe models:

- The program must be developed in C language of C11 standard using gcc compiler. You can use any additional QT libraries and modules
- The program code must be located in the src folder
- The program must be built with Makefile which contains standard set of targets for GNU-programs: all, install, uninstall, clean, dvi, dist, tests, gcov. Installation directory could be arbitrary, except the building one
- The program must be developed according to the principles of structured programming
- When writing code it is necessary to follow the Google style
- Prepare full coverage of modules related to model loading and affine transformations with unit-tests
- There should be only one model on the screen at a time
- The program must provide the ability to:
    - Load a wireframe model from an obj file (vertices and surfaces list support only).
    - Translate the model by a given distance in relation to the X, Y, Z axes.
    - Rotate the model by a given angle relative to its X, Y, Z axes.
    - Scale the model by a given value.
- GUI implementation, based on any GUI library with API for C89/C99/C11 <br/>
  * For Linix: GTK+, CEF, Qt<br/>
  * For Mac: GTK+, Nuklear, raygui, microui, libagar, libui, IUP, LCUI, CEF, Qt
- The graphical user interface must contain:
    - A button to select the model file and a field to output its name.
    - A visualisation area for the wireframe model.
    - Button/buttons and input fields for translating the model.
    - Button/buttons and input fields for rotating the model.
    - Button/buttons and input fields for scaling the model.
    - Information about the uploaded model - file name, number of vertices and edges.

## Settings.
The program customizing the type of projection (parallel and central).
The program choosing the background color.

The programma saving the captured (rendered) images as bmp and jpeg files. (640-480)


![3dViewer](misc/images/for_readme.gif)


##### Makefile targets:

- **install**
  Installs the calculator in the build folder and on the desktop

- **uninstall**
  Uninstall the calculator

- **dvi**
  Opens project documentation

- **dist**
  Generates distribution `.tgz` with an executable and necessary documentation

- **test**s
  Start testing calculator modules and its controller. The report can be viewed in the `/tests/BUILD/bin_test/` folder

- **gcov_report**
  Generates an html report displaying the coverage of all functions by tests


![GIF Example](m/for_readme.gif)
