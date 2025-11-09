# pathing experiments

Goal: develop an efficient pathfinding algorithm that
- Paths around constant velocity, maybe constant acceleration obstacles
- Navigates a visibility graph, NOT cells
- Can vary acceleration along path within maximum to minimize traversal time
- Tolerates new obstacles and changes to obstacle trajectories 

Currently (as of `bea317`):
- A*
- Visibility graph generation
- Rectangular obstacles

Stay tuned!

## Building
This uses a GNU Make build system I've reused for lots of my projects. No other software is required except a C++ compiler and an sh-compatible shell.
1. `cp Makefile.localconfig.sample Makefile.localconfig`
2. Set documented options in Makefile.localconfig
3. `make -j test`

And done. No outputs just yet, but the `test` rule builds and runs unit tests.
