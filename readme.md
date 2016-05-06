ofxPlotter
==========

![alt tag](https://raw.githubusercontent.com/yeswecan/ofxPlotter/master/screenshot.png)

Introduction
------------
A simple function plotter class for openFrameworks with built-in variable filtering and a ascetic syntax.

Usage
-----
ofxPlotter is designed to be as simple and as minimal as possible for plotting functions in realtime.

setWindow(int windowSize); // set window (a.k.a. plot length)

plotter["variable name"] << variable; // add a new data to the plot "variable name"

plotter.draw(100, 100, 300, 300); // draw the plot

Every _variable name_'s plot will be drawn separately in a Rectangle that's position on screen is x = 100, y = 100 and size is width = 300, height = 300.