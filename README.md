# SFML PRIMITIVE SHAPES

This C++ program utilizes the SFML library to read descriptions of primitive shapes from a configuration file and draw them on a window. The shapes include rectangles and circles, each defined by various parameters such as position, speed, color, and size.

## Usage 

1. Create a `config.txt` file with shape definitions following the specified format for rectangles and circles.
2. Run the program, and it will read the configuration file, create the shapes, and display them in an SFML window.

## Shape Specifications 

### Rectangle Class Specification 

Rectangle N X Y SX SY R G B W H 
Shape Name:              Name        std::string
Initial Position:        (X,Y)       float,float
Initial Speed:           (SX, SY)    float,float
RGB Color:               (R,G,B)     int,int,int
Size:                    (W, H)      float,float

## Circle Class Specification

Circle N X Y SX SY R G B R 
Shape Name:              N           std::string
Initial Position:        (X,Y)       float,float
Initial Speed:           (SX, SY)    float,float
RGB Color:               (R,G,B)     int,int,int
Radius:                  R           float 

## Dependencies

- SFML library
- Font file: OpenSans-Light.ttf "or any other font"

## Installation 

0. Install C++
1. Install the SFML library.
2. Place the font xxx.ttf in the project directory.
3. Compile the C++ program using a C++ compiler with SFML support.

## Code Structure 

- main.cpp: The main program that reads the configuration file, creates shapes, and displays them using SFML.
- xxx.ttf: Font file for rendering text.
- config.txt: Configuration file containing shape definitions.
