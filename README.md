#Quake 3 BSP Renderer
Ryan Lewellen
December 2012

##Objective
Create a renderer for iD Tech 3 maps following these goals:
* Use C++ features; iD Tech 3 was written completely in C, and as such, does everything in the C way - class-less and
completely imperative.  I'd like to explore how this translates to a more OO/functional paradigm, in the methodolgy
that C++ offers.
* OpenGL; specifically, no fixed-pipeline. I've traditionally, in the past, always done fixed pipeline, so of course
something like this would be a great first project. This will be complicated by the fact that my primary development
machine runs an older version of the OpenGL API, so I'll likely have to deal with extensions.
* Complete reproduction of the map geometry, including the brushes, meshes, and models
* Simple spectator-style camera controls

##Resources
For details on the BSP file format:
http://www.mralligator.com/q3/

For a more algorithm-orientated resource in the same style as the above resource:
http://graphics.cs.brown.edu/games/quake/quake3.html