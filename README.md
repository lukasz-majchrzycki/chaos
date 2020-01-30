# Deterministic chaos

Simple C++ App visualising the deterministic chaos system, which lead to the bifurcation.
Based on WinApi and OpenGL.

## Theory
In this simulation first 30 iteration of following function are calculated:

![y=f(r)]( https://latex.codecogs.com/svg.latex?\fn_phv&space;x=f\left&space;(&space;r&space;\right&space;) )

where

![ x_{n}=r*x_{n-1}*(= 1-x_{n-1}) ]( https://latex.codecogs.com/svg.latex?\fn_phv&space;x_{n}=r*x_{n-1}\left&space;(&space;1-x_{n-1}&space;\right&space;) )

## Result
![ screan shot ]( http://nano-code.eu/wp-content/uploads/2020/01/chaos_screen-shot.png )
