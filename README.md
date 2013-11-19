Simple-GL-Framework
===================

A GLUT framework wrapper designed to make getting a simple graphical application going quickly.

## Overview
GL Framework provides a bare-bones intro to graphics programming with OpenGL and GLUT.
Detailed documentation available at: http://doxy.glutfmk.evanedstrom.com

The framework is comprised of two main components, Engine and Element.

## Engine
* Initializes GLUT and handles key events, window resizing, projection matrix setup / scaling, and a basic frame timer.
* Contains a list of Elements that are drawn on each frame.
* Provides before draw loop and after draw loop virtual functions for things like scorekeeping or collision detection.
* Subscribes to events for key and mouse handling.

## Element
* Contains a coordinate system for positioning objects in 3D space.
* Contains velocity, scale and rotation variables.
* Draw() and Move() functions called in engine display loop using polymorphism.
* Overwrite Draw() in a subclass to get specific drawing behavior.
* Overwrite Move() in a subclass to get specific movement behavior.

## More Info
Written for Whitworth University for use in introductory programming courses.
> Author: Evan Edstrom
